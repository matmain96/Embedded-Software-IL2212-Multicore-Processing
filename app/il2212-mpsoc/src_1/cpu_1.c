
#include <stdio.h>
#include "sys/alt_irq.h"
#include "sys/alt_alarm.h"
#include "system.h"
#include "io.h"
#include "altera_avalon_mutex.h"
#define DEBUG 1



extern void delay (int millisec);
int dSPAN=15;
int cropSIZE=32;

/*
*	Burst Reading from the shared memory to the onchip memory of the processor
* 	
*/
void NotSram2sm_p3(alt_u8* memory, alt_u8 img[32*11*3])
{
	int  y;
	alt_u64* shared=(alt_u64*) memory;
	alt_u64* base=(alt_u64*) img;
	for(y = 0; y < 12; y++)
	{	
		*base++ = *shared++; 
		*base++ = *shared++; 
		*base++ = *shared++; 
		*base++ = *shared++;
		*base++ = *shared++; 
		*base++ = *shared++; 
		*base++ = *shared++; 
		*base++ = *shared++; 
		*base++ = *shared++; 
		*base++ = *shared++; 
		*base++ = *shared++; 
	}
}
/*
* 	Simplified version of grayscale, changed algorithm with bitshifting and loop unrolling for better performance
*/
void Grayscale(alt_u8 pic[32*3*11],alt_u8 gray[32*11]){
	int moving_index=0;
	int basic_index=0;
	int i;
	alt_u8* img=(alt_u8*) gray;
	alt_u8* mov=(alt_u8*) pic;
	for(i=0; i<22;i++){
		img[basic_index]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+1]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+2]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+3]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+4]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+5]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+6]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+7]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+8]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+9]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+10]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+11]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+12]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+13]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+14]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		img[basic_index+15]= ((mov[moving_index++])>>2 + (mov[moving_index++])>>1 + (mov[moving_index++])>>3);
		basic_index+=16;	
	}
}

/*
* The stencilmat function sums the values in the same position of the model's xPattern
*/
unsigned int stencilmat(int i, int j,alt_u8 cropped_matrix[32*11]){ //x,y,mat
	unsigned int sum;
	sum=(cropped_matrix[(j-2)*32+i] + cropped_matrix[(j-1)*32+i-1] + cropped_matrix[(j-1)*(32)+i+1] + cropped_matrix[(j*32)+i-2] + cropped_matrix[j*32+i+2] + cropped_matrix[(j+1)*(32)+i-1] + cropped_matrix[(j+1)*(32)+i+1] + cropped_matrix[(j+2)*32+i]);  
	return sum; 	
}

/*
* posMax finds out which is the highest value of the cropped picture, 
* the coordinate of the highest value will be one of the possible position of the bullet
*/

unsigned int* posMax(alt_u8 matrix[32*11]){
	unsigned int max=0;		//Variable used for the max
	unsigned int maybemax;		//Variable that is a max of it's own matrix but not the biggest
	static unsigned int result[3];
	 int maxX=0;
	 int maxY=0;
	int i,j;
	for(j=2; j<9;j++){
	for(i=2; i<30;i++){
			maybemax=stencilmat(i,j,matrix);
			
			if(maybemax> max){
				 max=maybemax;
				 maxX=i;
				 maxY=j;
			}
		}
	}	
	 result[0]=maxX;
	 result[1]=maxY;
	 result[2]=max;
	return result;
}


int main(void) {

		//Mutex creation
	  alt_mutex_dev* mutex_0 = altera_avalon_mutex_open( "/dev/mutex_0" );
	  alt_mutex_dev* mutex_1 = altera_avalon_mutex_open( "/dev/mutex_1" );
		//Handshake value
	  alt_u8 *Begin_2= (alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+61);
		//Variables utilized for computing
	  alt_u8* memory=(alt_u8* )SHARED_ONCHIP_BASE;
	  alt_u8 picture[32*3*11];
	  alt_u8 graypicture[32*11];
	  unsigned int *storeresult;
		int num=0;
		//HANDSHAKE BEGINS
	  while( altera_avalon_mutex_trylock( mutex_0, ALT_CPU_CPU_ID_VALUE ) );
	  *Begin_2=1;
      altera_avalon_mutex_unlock( mutex_0 );
	  
	  while(*Begin_2!=0){delay(10);}
	

	  while( altera_avalon_mutex_trylock( mutex_0, ALT_CPU_CPU_ID_VALUE ) ){}  
	  if(altera_avalon_mutex_is_mine( mutex_0)) printf("CPU1 Handshake with CPU0 correct!\n");
      *Begin_2=1;
      altera_avalon_mutex_unlock( mutex_0 );
		//HANDSHAKE FINISH
	  // Variables used to share information about final result
	  alt_u8* FirstResult=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3);	
	  alt_u8* FirstFlag=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+4);
	  alt_u8* FirstCoords_1=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+5);
	  alt_u8* FirstCoords_2=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+6);
	  int i,j;
	  while(1){
					
			altera_avalon_mutex_lock( mutex_1, ALT_CPU_CPU_ID_VALUE );
			
			NotSram2sm_p3(memory,picture);	

			Grayscale(picture,graypicture);
			storeresult=posMax(graypicture);

			*FirstCoords_1=(alt_u8)storeresult[0];
			*FirstCoords_2=(alt_u8)storeresult[1];
			*FirstResult=(alt_u8)storeresult[2];

			altera_avalon_mutex_unlock( mutex_1);

			altera_avalon_mutex_lock( mutex_0, ALT_CPU_CPU_ID_VALUE );
			altera_avalon_mutex_unlock( mutex_0);			
			
		}
	  return 0;
}


