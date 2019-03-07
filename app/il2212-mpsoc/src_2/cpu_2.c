
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


unsigned int stencilmat(int i, int j,alt_u8 cropped_matrix[32*11]){ //x,y,mat
	unsigned int sum;
	sum=(cropped_matrix[(j-2)*32+i] + cropped_matrix[(j-1)*32+i-1] + cropped_matrix[(j-1)*(32)+i+1] + cropped_matrix[(j*32)+i-2] + cropped_matrix[j*32+i+2] + cropped_matrix[(j+1)*(32)+i-1] + cropped_matrix[(j+1)*(32)+i+1] + cropped_matrix[(j+2)*32+i]);  
	return sum; 	
}



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



      alt_mutex_dev* mutex_0 = altera_avalon_mutex_open( "/dev/mutex_0" );
	  alt_mutex_dev* mutex_2 = altera_avalon_mutex_open( "/dev/mutex_2" );
	  alt_u8 *Begin_1= (alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+60);

	  alt_u8 *SecondResult=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+6)+1;
	  alt_u8* SecondFlag=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+6)+5;
	  alt_u8* SecondCoords_1=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+6)+6;
	  alt_u8* SecondCoords_2=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+6)+7;
	  int i,j;

	  while( altera_avalon_mutex_trylock( mutex_0, ALT_CPU_CPU_ID_VALUE ) ){}
	  *Begin_1=1;
      altera_avalon_mutex_unlock( mutex_0 );
	  
	  while(*Begin_1!=0){ delay(10);}
	  
	  while( altera_avalon_mutex_trylock( mutex_0, ALT_CPU_CPU_ID_VALUE ) ){}
      if(altera_avalon_mutex_is_mine( mutex_0)) {printf("CPU2 Handshake with CPU0 correct!\n");}
	  *Begin_1=1; 
      altera_avalon_mutex_unlock( mutex_0 );
	  
      alt_u8* memory=(alt_u8* )SHARED_ONCHIP_BASE+(32*7*3);
	  alt_u8 picture[32*3*11];
	  alt_u8 graypicture[32*11];
	  unsigned int *storeresult;
	  
		  

	  while(1){
			
			altera_avalon_mutex_lock( mutex_2, ALT_CPU_CPU_ID_VALUE );
			
			NotSram2sm_p3(memory,picture);	

			Grayscale(picture,graypicture);			
			storeresult=posMax(graypicture);
			
			*SecondCoords_1=(alt_u8)storeresult[0];
			*SecondCoords_2=(alt_u8)storeresult[1];
			*SecondResult=storeresult[2];
			
			altera_avalon_mutex_unlock( mutex_2 );

			altera_avalon_mutex_lock( mutex_0, ALT_CPU_CPU_ID_VALUE );
			altera_avalon_mutex_unlock( mutex_0);
			
			
		}
	  return 0;
}
