#include <stdio.h>
#include "altera_avalon_performance_counter.h"
#include "sys/alt_irq.h"
#include "sys/alt_alarm.h"
#include "system.h"
#include "io.h"
#include "images.h"
#include "altera_avalon_mutex.h"
#include "ascii_gray.h"

/*
* Defines section for performance counter
*/
#define VALUESIZE 3
#define SECTION_1 1
#define SECTION_2 2
#define SECTION_3 3
#define PERFORMANCE 0
/*
* Defines common values inside the algorithm
*/
int dSPAN=15;
int current_image=0;
int cropSIZE=32;

static unsigned int Globcoords[2]; //Saves coordinates as starting
extern void delay (int millisec);  //Delay used in the handshake to keep reading data

/*
* Burst Writing on the memory using Altera types
* The arguments point to the picture(SRAM) and shared memory 
*/
void sram2sm_p3(alt_u8* img, alt_u8* memory)
{
	int  y;
	alt_u64* shared=(alt_u64*) memory; //Switch to altera types
	alt_u64* base=(alt_u64*) img;
	//Loop unrolling for better performances
	for(y = 0; y < 16; y++)
	{	 
		*shared++ = *base++; 
		*shared++ = *base++; 
		*shared++ = *base++; 
		*shared++ = *base++; 
		*shared++ = *base++; 
		*shared++ = *base++; 
		*shared++ = *base++; 
		*shared++ = *base++;
	}
}
/*
* 	The following function takes as arguments the coordinates from the previous
*	result (dSPAN for picture 0), then it crops the picture to get the
* 	section that we are interested in and does a burst writing from the sram 
*	to the shared memory.
*/
void  CalcCoord(alt_u8 coordX,alt_u8 coordY, alt_u8 imgW, alt_u8 imgH,alt_u8* shared){
	
	// Algorithm given by Haskell specification
	if(coordX <= dSPAN ){
		Globcoords[0] = 0;	
	}
	else if ( coordX > imgW-dSPAN){
			Globcoords[0] =(imgW-cropSIZE-1);
		}
	else Globcoords[0] =(coordX-dSPAN-1);



	if( coordY <= dSPAN ){
		Globcoords[1] = 0;	
	}
	else if ( coordY > imgH-dSPAN){
			Globcoords[1] =(imgH - cropSIZE -1);
		}
	else {
		Globcoords[1]=(coordY - dSPAN - 1);
	}
	
   
	//printf("\ncoords=[%d,%d]\n",Globcoords[0],Globcoords[1]);
	
	int head;		//head to use as reference
	int jump;
	head=(shared[0]*Globcoords[1]*3)+(Globcoords[0]*3)+3; //Goes directly to the coords given (+3 because the first three values are x,y and maxvalue). The *3 moltiplication is there because we are still in RGB values.
	jump=(shared[0]-32)*3; //Jump defines the gap between values to skip to have a perfect cropping
	int i,j;
	alt_u64* starter=(alt_u64*) SHARED_ONCHIP_BASE;
	shared+=head;  //moves the pointer to the interested position.
	alt_u64* following=(alt_u64*)shared;
	
	//Burst Writing with loop unrolling for better performance
	
	for(i=0;i<32;i++){

			*starter++=(alt_u64)*following++; 
			*starter++=(alt_u64)*following++; 
			*starter++=(alt_u64)*following++;
			*starter++=(alt_u64)*following++;

			*starter++=(alt_u64)*following++; 
			*starter++=(alt_u64)*following++; 
			*starter++=(alt_u64)*following++; 
			*starter++=(alt_u64)*following++;

			*starter++=(alt_u64)*following++;  
			*starter++=(alt_u64)*following++; 
			*starter++=(alt_u64)*following++; 
			*starter++=(alt_u64)*following++; 
			shared+=32*3+jump;
			following=(alt_u64*)shared;
	}	

}
//Gray scale used only for debug mode
void Grayscale2(unsigned char* img){
	int maxX=img[0];
	int maxY=img[1];
	int total= maxY*maxX*3;
	int moving_index=3;
	int basic_index=3;
	while(moving_index<total){
		img[basic_index]=(unsigned char)(((img[moving_index])>>2)+((img[moving_index])>>4)+((img[moving_index+1])>>1)+((img[moving_index+1])>>4)+((img[moving_index+2])>>3));
		basic_index++;
		moving_index+=3;
		
	}
}



int main()
{	
	/*
	* There are common variables definition for every CPU
	* Result: where to store the highest value found
	* Flag: For shared memo synch.
	* Coord_1/2: Store the X&Y coordinate of the highest value
	* Previous_1/2: The result of the previous picture (dSPAN at the beginning)
	*/
	alt_u8* FirstResult,*SecondResult,*ThirdResult,*FourthResult; 
	alt_u8* FirstFlag,*SecondFlag,*ThirdFlag,*FourthFlag;
	alt_u8* FirstCoords_1;
	alt_u8* FirstCoords_2;
	alt_u8* SecondCoords_1;
	alt_u8* SecondCoords_2;
	alt_u8* ThirdCoords_1;
	alt_u8* ThirdCoords_2;
	alt_u8* FourthCoords_1;
	alt_u8* FourthCoords_2;
	alt_u8* Previous_1;
	alt_u8* Previous_2;	
	alt_u8* address;
	//Define mutex
	alt_mutex_dev* mutex_0 = altera_avalon_mutex_open( "/dev/mutex_0" );
	alt_mutex_dev* mutex_1 = altera_avalon_mutex_open( "/dev/mutex_1" );
	alt_mutex_dev* mutex_2 = altera_avalon_mutex_open( "/dev/mutex_2" );
	alt_mutex_dev* mutex_3 = altera_avalon_mutex_open( "/dev/mutex_3" );
	alt_mutex_dev* mutex_4 = altera_avalon_mutex_open( "/dev/mutex_4" );
	
	//Take mutex
	altera_avalon_mutex_trylock( mutex_1, 5 ); delay(1);
	 if(altera_avalon_mutex_is_mine( mutex_1)) printf("ok1\n"); 
	altera_avalon_mutex_lock( mutex_2, 5 ); delay(1);
	 if(altera_avalon_mutex_is_mine( mutex_2)) printf("ok2\n");
	altera_avalon_mutex_lock( mutex_3, 5 ); delay(1);
	 if(altera_avalon_mutex_is_mine( mutex_3)) printf("ok3\n");
	altera_avalon_mutex_lock( mutex_4, 5 ); delay(1);
	 if(altera_avalon_mutex_is_mine( mutex_4)) printf("ok4\n");

	
	//Variable definition of shared memory
	FirstResult=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3 );	
	FirstFlag=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+4);
	FirstCoords_1=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+5);
	FirstCoords_2=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+6);
	
	SecondResult=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+6)+1;
	SecondFlag=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+6)+5;
	SecondCoords_1=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+6)+6;
	SecondCoords_2=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+6)+7;

	ThirdResult=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+13)+1;
	ThirdFlag=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+13)+5;
	ThirdCoords_1=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+13)+6;
	ThirdCoords_2=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+13)+7;
	
	FourthResult=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+20)+1;
	FourthFlag=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+20)+5;
	FourthCoords_1=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+20)+6;
	FourthCoords_2=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+20)+7;

	Previous_1=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+20)+8;
	Previous_2=(alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+20)+9;
	
	address=(alt_u8*)SHARED_ONCHIP_BASE;
	alt_u8 *Begin_1= (alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+60);
	alt_u8 *Begin_2= (alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+61);
	alt_u8 *Begin_3= (alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+62);
	alt_u8 *Begin_4= (alt_u8*)SHARED_ONCHIP_BASE+(32*32*3+63);

	
	unsigned int max=0;
	
	//HANDSHAKE BEGINS
	while(((*Begin_1!=1) || (*Begin_2!=1) || (*Begin_3!=1) || (*Begin_4!=1))){
		//printf("\n%d,%d,%d,%d",*Begin_1,*Begin_2,*Begin_3,*Begin_4); 
		//delay();
	}

	printf("\nALL PROCESSORS ARE READY");
	altera_avalon_mutex_lock( mutex_0, 5 );
	
    *Begin_1=0;
	*Begin_2=0;
	*Begin_3=0;
	*Begin_4=0;
	
	*Previous_1=dSPAN;
	*Previous_2=dSPAN;
		
	altera_avalon_mutex_unlock( mutex_0 );


	while(((*Begin_1!=1) || (*Begin_2!=1) || (*Begin_3!=1) || (*Begin_4!=1))){ printf("\n%d,%d,%d,%d",*Begin_1,*Begin_2,*Begin_3,*Begin_4);}
	//HANDSHAKE FINISH

	int i=0;
	printf("\n\n");
	PERF_RESET(PERFORMANCE_COUNTER_0_BASE);
	PERF_START_MEASURING (PERFORMANCE_COUNTER_0_BASE);

#if !PERFORMANCE
	while(current_image<sequence_length){
printf("Starting");
				PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECTION_1);
				//Lock M0
				altera_avalon_mutex_lock( mutex_0, 5 );
				//Crops&Store the picture
				CalcCoord(*Previous_1,*Previous_2,image_sequence[current_image][0],image_sequence[current_image][1],image_sequence[current_image]);

				PERF_END(PERFORMANCE_COUNTER_0_BASE, SECTION_1);


				PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECTION_2);
				//Release mutex and make other cpu start
				altera_avalon_mutex_unlock( mutex_1);
				altera_avalon_mutex_unlock( mutex_2);
				altera_avalon_mutex_unlock( mutex_3);
				altera_avalon_mutex_unlock( mutex_4);
				//Wait for CPU to finish
				//When CPU0 gets all mutex back it starts again
				while(!(altera_avalon_mutex_is_mine(mutex_1) && altera_avalon_mutex_is_mine(mutex_2) && altera_avalon_mutex_is_mine(mutex_3) && altera_avalon_mutex_is_mine(mutex_4)))	
				{				
					if(altera_avalon_mutex_is_mine(mutex_1)==0){altera_avalon_mutex_trylock(mutex_1,5);*Begin_2=0;}
					if(altera_avalon_mutex_is_mine(mutex_2)==0){altera_avalon_mutex_trylock(mutex_2,5);*Begin_1=0;}
					if(altera_avalon_mutex_is_mine(mutex_3)==0){altera_avalon_mutex_trylock(mutex_3,5);*Begin_3=0;}
					if(altera_avalon_mutex_is_mine(mutex_4)==0){altera_avalon_mutex_trylock(mutex_4,5);*Begin_4=0;}
				}

				PERF_END(PERFORMANCE_COUNTER_0_BASE, SECTION_2);
				

				PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECTION_3);
				//Check highest value
				max= *FirstResult>*SecondResult?*FirstResult:*SecondResult;
				max= max>*ThirdResult?max:*ThirdResult;
				max= max>*FourthResult?max:*FourthResult;
				//Store the coordinates in Previous (see def. above)
				if(max==*FirstResult){
					  *Previous_1=*FirstCoords_1+Globcoords[0]; 
					  *Previous_2=*FirstCoords_2+Globcoords[1]; 
				} 
				else if (max==*SecondResult){
					*Previous_1=*ThirdCoords_1+Globcoords[0]; 
					*Previous_2=*ThirdCoords_2+7+Globcoords[1]; 
				}
				else if (max==*ThirdResult){
					*Previous_1=*ThirdCoords_1+Globcoords[0]; 
					*Previous_2=*ThirdCoords_2+14+Globcoords[1]; 
				}
				else {
					*Previous_1=*FourthCoords_1+Globcoords[0];  
					*Previous_2=*FourthCoords_2+21+Globcoords[1]; 
				}
				//Prints the result
				printf("\n[%d,%d]\n",*Previous_1,*Previous_2);
				altera_avalon_mutex_unlock( mutex_0);
				//Next picture
				delay(1);
				
				PERF_END(PERFORMANCE_COUNTER_0_BASE, SECTION_3);
				
				perf_print_formatted_report
					(PERFORMANCE_COUNTER_0_BASE,            
					ALT_CPU_FREQ,        // defined in "system.h"
					3,                   // How many sections to print
					"SRAM->Shared Mem","Communication","Compare Coords"// Display-name of section(s).
					);

				Grayscale2(image_sequence[current_image]);
				printf("\n INPUT \n");printAscii(image_sequence[current_image], image_sequence[current_image][0],image_sequence[current_image][1]);
				printf("CROPPED"); printAsciiHidden(image_sequence[current_image], cropSIZE-4, cropSIZE-4, Globcoords[0], Globcoords[1],4,max );	
				current_image++;

		}
#else
		
PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECTION_1);
	while(i<25){	
		
		current_image=0;
		*Previous_1=dSPAN;
		*Previous_2=dSPAN;
		
		while(current_image<sequence_length){

			altera_avalon_mutex_lock( mutex_0, 5 );

			CalcCoord(*Previous_1,*Previous_2,image_sequence[current_image][0],image_sequence[current_image][1],image_sequence[current_image]);

			altera_avalon_mutex_unlock( mutex_1);
			altera_avalon_mutex_unlock( mutex_2);
			altera_avalon_mutex_unlock( mutex_3);
			altera_avalon_mutex_unlock( mutex_4);

			current_image++;
					
			while(!(altera_avalon_mutex_is_mine(mutex_1) && altera_avalon_mutex_is_mine(mutex_2) && altera_avalon_mutex_is_mine(mutex_3) && altera_avalon_mutex_is_mine(mutex_4)))	
			{				
				if(altera_avalon_mutex_is_mine(mutex_1)==0){altera_avalon_mutex_trylock(mutex_1,5);*Begin_2=0;}
				if(altera_avalon_mutex_is_mine(mutex_2)==0){altera_avalon_mutex_trylock(mutex_2,5);*Begin_1=0;}
				if(altera_avalon_mutex_is_mine(mutex_3)==0){altera_avalon_mutex_trylock(mutex_3,5);*Begin_3=0;}
				if(altera_avalon_mutex_is_mine(mutex_4)==0){altera_avalon_mutex_trylock(mutex_4,5);*Begin_4=0;}
			}
					
			max= *FirstResult>*SecondResult?*FirstResult:*SecondResult;
			max= max>*ThirdResult?max:*ThirdResult;
			max= max>*FourthResult?max:*FourthResult;

			if(max==*FirstResult){
				  *Previous_1=*FirstCoords_1+Globcoords[0]; 
				  *Previous_2=*FirstCoords_2+Globcoords[1]; 
			} 
			else if (max==*SecondResult){
				*Previous_1=*ThirdCoords_1+Globcoords[0]; 
				*Previous_2=*ThirdCoords_2+7+Globcoords[1]; 
			}
			else if (max==*ThirdResult){
				*Previous_1=*ThirdCoords_1+Globcoords[0]; 
				*Previous_2=*ThirdCoords_2+14+Globcoords[1]; 
			}
			else {
				*Previous_1=*FourthCoords_1+Globcoords[0];  
				*Previous_2=*FourthCoords_2+21+Globcoords[1]; 
			}

			printf("\n[%d,%d]\n",*Previous_1,*Previous_2);

			altera_avalon_mutex_unlock( mutex_0);

			delay(1);

	}
i++;
}
PERF_END(PERFORMANCE_COUNTER_0_BASE, SECTION_1);

		perf_print_formatted_report
					(PERFORMANCE_COUNTER_0_BASE,            
					ALT_CPU_FREQ,        // defined in "system.h"
					1,                   // How many sections to print
					"100 images"// Display-name of section(s).
					);

		while(1);
#endif
	return 0;
}
