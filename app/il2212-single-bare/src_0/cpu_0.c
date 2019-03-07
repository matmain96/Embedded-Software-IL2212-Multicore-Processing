// Skeleton for lab 2
// 
// Task 1 writes periodically RGB-images to the shared memory
//
// No guarantees provided - if bugs are detected, report them in the Issue tracker of the github repository!

#include <stdio.h>
#include "altera_avalon_performance_counter.h"
#include "sys/alt_irq.h"
#include "sys/alt_alarm.h"
#include "system.h"
#include "io.h"
#include "images.h"
#include "ascii_gray.h"

#define DEBUG 0
#define PERFORMANCE 1


/* Definition of Task Periods (ms) */

#define SECTION_1 1
#define SECTION_2 2
#define SECTION_3 3
#define SECTION_4 4
#define SECTION_5 5

/*
 * Global variablesl
 */
static const int dSPAN=15;			//Values given by specification
static const int cropSIZE=(2*15)+1; 
static unsigned char imagematrix[31][31];		//Matrix of the img
static unsigned int matrixmix[27][27];			//Matrix after xcorr2
unsigned char current_image=0;					//Keeps track of what image are we working on
unsigned char objectmax[2];		//Variables used to send the position of the max value in the matrix
unsigned char finalresult[2];  //Stores the coordinate for every picture
int counter=0;   		//Used in performance mode
int max_calc_pos;	 	//Used in PosMax to calculate the 



//The grayscale function transforms the values of the starting array (RGB) into gray values
//By applying the formula stated into the Haskell model, switched to bitwise
//operation to improve the speed of the program

void Grayscale(unsigned char* img){
	int maxX=img[0];  			// width of the picture
	int maxY=img[1];			//Height of the picture
	int total= maxY*maxX*3;    //Lenght of array
	int moving_index=3;  
	int basic_index=3;
	//The following lines of code overwrites on the starting array, since we won't
	//need the starting values anymore after grayscaling
	while(moving_index<total){
		img[basic_index]=(unsigned char)(((img[moving_index])>>2)+((img[moving_index])>>4)+((img[moving_index+1])>>1)+((img[moving_index+1])>>4)+((img[moving_index+2])>>3));
		basic_index++;  
		moving_index+=3;
		
	}
}


/*This function calculates the coordinates on which the next cropping will 
*Be based on.
*/
void CalcCoord(int coordX,int coordY,unsigned char* img){
	
	int imgW=img[0];	  	
	int imgH=img[1];
	
	//equation used by the program below is given by the haskell model
	if( coordX <= dSPAN ){
		finalresult[0] = 0;	
	}
	else if ( coordX > imgW-dSPAN){
			finalresult[0] =imgW-cropSIZE-1;
		}
	else finalresult[0] =coordX-dSPAN-1;

	if( coordY <= dSPAN ){
		finalresult[1] = 0;	
	}
	else if ( coordY > imgH-dSPAN){
			finalresult[1] =imgH - cropSIZE -1;
		}
	else {
		finalresult[1]=coordY - dSPAN - 1;
	}
}


void crop (int coordX,int coordY,unsigned char* img){ 
	
	int head;		//head to use as reference
	head=(img[0]*coordY)+coordX+3;		//Goes directly to the coords given (+3 because the first three values are x,y and maxvalue)
	int jump;		
		
	jump=img[0]-cropSIZE; //Jump defines the gap between values to skip to have a perfect cropping
	int i,j;
	for(i=0;i<cropSIZE;i++){
		for(j=0;j<cropSIZE;j++){
			imagematrix[i][j]=img[head];
			head++;
		}

		head+=jump;		//when we reach the border of the matrix we goes to the next line
	}	
}

/*
* This function sums the values inside the matrix based on the position given
* by the xPattern inside the haskell model
*/
unsigned int stencilmat(int i, int j,unsigned char cropped_matrix[31][31]){ //x,y,mat
	unsigned int sum;
	sum= (cropped_matrix[j][i+2] + cropped_matrix[j+1][i+1] + cropped_matrix[j+1][i+3] + cropped_matrix[j+2][i] + cropped_matrix[j+2][i+4] + cropped_matrix[j+3][i+1] + cropped_matrix[j+3][i+3] + cropped_matrix[j+4][i+2]);  
	return sum;  
	
}

void xCorr2(unsigned char matrix[31][31]){
		
	int i,j;


	
	for(i=0; i<cropSIZE-4;i++){ 
		for(j=0; j<cropSIZE-4;j++){			
			matrixmix[i][j]=(unsigned int)stencilmat(j,i,matrix);
		}
	}

	
}

void posMax(unsigned int matrix[27][27]){

	int maybemax;		//Variable that is a max of it's own matrix but not the biggest
	max_calc_pos = 0;
	//The following finds the highest value between all the different matrix
	int i,j;
	for(i=0; i<cropSIZE-4;i++){
		for(j=0; j<cropSIZE-4;j++){
			maybemax=matrix[i][j];
			if(maybemax > max_calc_pos){
				 max_calc_pos=maybemax;
				 objectmax[0]=j;
				 objectmax[1]=i;
			}
		}
	}	
}

void objectPos(int coordX,int coordY, unsigned char posmax[2]){ 

	//Equation given by the haskell code
	finalresult[0]= coordX+posmax[0]+2;
	finalresult[1]= coordY+posmax[1]+2;

}

int main(void) {
/*
* PERFORMANCE MODE
*/
	  if(PERFORMANCE){
			printf("PERFORMANCE MODE!! \n\n\n");
			PERF_RESET(PERFORMANCE_COUNTER_0_BASE);
			PERF_START_MEASURING (PERFORMANCE_COUNTER_0_BASE);
			PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECTION_1);
			while(counter++<100){

				  if(current_image==0){
						  finalresult[0]=dSPAN; 
						  finalresult[1]=dSPAN;
					}
			Grayscale(image_sequence[current_image]);
			CalcCoord(finalresult[0],finalresult[1],image_sequence[current_image]);
			crop(finalresult[0],finalresult[1], image_sequence[current_image]);
			xCorr2(imagematrix);
			posMax(matrixmix);
			objectPos(finalresult[0],finalresult[1],objectmax);
			current_image++;
			current_image%=sequence_length;  
			}
			PERF_END(PERFORMANCE_COUNTER_0_BASE, SECTION_1);  
						perf_print_formatted_report
			(PERFORMANCE_COUNTER_0_BASE,            
			ALT_CPU_FREQ,        // defined in "system.h"
			1,                   // How many sections to print
			"Total time"   // Display-name of section(s).
			);   
		}   
	  else{
/*
* 	DEBUG MODE
*/

		  printf("DEBUG MODE!! \n\n\n");
		  finalresult[0]=dSPAN;   //As stated in the model, the initial values 
		  finalresult[1]=dSPAN;	  //Of the finalresult are dSPAN
		  while(current_image<sequence_length){
			
			PERF_RESET(PERFORMANCE_COUNTER_0_BASE);
			PERF_START_MEASURING (PERFORMANCE_COUNTER_0_BASE);

			PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECTION_1);
			Grayscale(image_sequence[current_image]);
			PERF_END(PERFORMANCE_COUNTER_0_BASE, SECTION_1);

			printf("\n INPUT \n");printAscii(image_sequence[current_image], image_sequence[current_image][0],image_sequence[current_image][1]);
			
			PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECTION_2);
			CalcCoord(finalresult[0],finalresult[1],image_sequence[current_image]);
			PERF_END(PERFORMANCE_COUNTER_0_BASE, SECTION_2);
			
			PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECTION_3);	
			crop(finalresult[0],finalresult[1], image_sequence[current_image]);
			PERF_END(PERFORMANCE_COUNTER_0_BASE, SECTION_1);
				
			PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECTION_4);
			xCorr2(imagematrix);
			PERF_END(PERFORMANCE_COUNTER_0_BASE, SECTION_4);

			PERF_BEGIN(PERFORMANCE_COUNTER_0_BASE, SECTION_5);
			posMax(matrixmix);
			PERF_END(PERFORMANCE_COUNTER_0_BASE, SECTION_5);

			printf("\nCROPPED OUTPUT\n");printAsciiHidden(matrixmix,cropSIZE-4,cropSIZE-4, objectmax[0], objectmax[1],4,max_calc_pos);

			/* Print report */
			perf_print_formatted_report
			(PERFORMANCE_COUNTER_0_BASE,            
			ALT_CPU_FREQ,        // defined in "system.h"
			5,                   // How many sections to print
			"Grayscale",
			"CalcCoord",
			"crop",
			"xCorr2",
			"posMax"        // Display-name of section(s).
			);   


			
			objectPos(finalresult[0],finalresult[1],objectmax);
		
			  
			

			

			current_image++;
		}
	  }         
	  
	  return 0;
}
