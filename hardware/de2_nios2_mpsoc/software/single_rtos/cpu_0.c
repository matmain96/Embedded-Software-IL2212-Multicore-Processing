// Skeleton for lab 2
// 
// Task 1 writes periodically RGB-images to the shared memory
//
// No guarantees provided - if bugs are detected, report them in the Issue tracker of the github repository!

#include <stdio.h>
#include "altera_avalon_performance_counter.h"
#include "includes.h"
#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include "sys/alt_alarm.h"
#include "system.h"
#include "io.h"
#include "images.h"

#define DEBUG 1
#define HW_TIMER_PERIOD 100 /* 100ms */

/* Definition of Task Stacks */
#define   TASK_STACKSIZE       2048
OS_STK    StartTask_Stack[TASK_STACKSIZE]; 
OS_STK    GrayTask_stk[TASK_STACKSIZE];
OS_STK    CalcCoordTask_stk[TASK_STACKSIZE];
OS_STK    CropTask_stk[TASK_STACKSIZE];
OS_STK    xCorr2Task_stk[TASK_STACKSIZE];
OS_STK    PosMaxTask_stk[TASK_STACKSIZE];
OS_STK    ObjectPosTask_stk[TASK_STACKSIZE];

/* Definition of Task Priorities */

#define STARTTASK_PRIO	1
//#define TASK1_PRIORITY	10
#define GrayTask_PRIORITY	10
#define CalcCoordTask_PRIORITY	11
#define CropTask_PRIORITY	12
#define xCorr2Task_PRIORITY	13
#define PosMaxTask_PRIORITY	14
#define ObjectPosTask_PRIORITY	15

/* Definition of Task Periods (ms) */

#define TASK1_PERIOD 10000
#define SECTION_1 1


/* Definition of dimensions gave by the project */




/*
 * Global variables
 */
static const int dSPAN=15;
static const int cropSIZE=(2*15)+1;
static unsigned char imagematrix[31][31];		//Matrix of the img
static unsigned int matrixmix[27][27];
unsigned char xPATTERN[5][5]= {{0,0,1,0,0},{0,1,0,1,0},{1,0,0,0,1},{0,1,0,1,0},{0,0,1,0,0}};
int delay;		// Delay of HW-timer 
int finalresult[2];		//contains the final coordinates
int current_image=0;							
int Globcoords[2];		//Global coordinates
int objectmax[2];		//Variables used to send the position of the max value in the matrix

INT8U err;

/*
 * ISR for HW Timer
 */
alt_u32 alarm_handler(void* context)
{
  OSTmrSignal(); /* Signals a 'tick' to the SW timers */
  
  return delay;
}

// Semaphores
OS_EVENT *Task1TmrSem;
OS_EVENT *GrayedSem;
OS_EVENT *CalcCoordSem;
OS_EVENT *CropSem;
OS_EVENT *xCorr2Sem;
OS_EVENT *PosMaxSem;
OS_EVENT *objectPosSem;

/*

Every task at the beginning block itself thanks to the utilization of semaphores
and once that the function has finished they increase the value of the semaphore
of the next task.

*/

void Grayscale(unsigned char* img){
	int maxX=img[0];
	int maxY=img[1];
	int total= maxY*maxX*3;

	int moving_index=3;
	int basic_index=3;
	while(moving_index<total){
		img[basic_index]=(unsigned char)(img[moving_index]*0.3125+img[moving_index+1]*0.5625+img[moving_index+2]*0.125);
		basic_index++;
		moving_index+=3;
	}
}


void GrayTask(void* pdata){

	while(current_image<sequence_length){
		Grayscale(image_sequence[current_image]);
		OSSemPost(CalcCoordSem);
		OSSemPend(GrayedSem,0,&err);
	}
}


void CalcCoord(int coordX,int coordY,unsigned char* img){
	
	int imgW=img[0];	  	//pic size
	int imgH=img[1];
	
	printf("imgW=%d, imgH=%d, xvalue=%d, yvalue=%d\n",imgW,imgH,coordX,coordY);
	//equation used by the program below
	if( coordX <= dSPAN ){
		Globcoords[0] = 0;	
	}
	else if ( coordX > imgW-dSPAN){
			Globcoords[0] =imgW-cropSIZE-1;
		}
	else Globcoords[0] =coordX-dSPAN-1;

	if( coordY <= dSPAN ){
		Globcoords[1] = 0;	
	}
	else if ( coordY > imgH-dSPAN){
			Globcoords[1] =imgH - cropSIZE -1;
		}
	else {
		Globcoords[1]=coordY - dSPAN - 1;
	}
}

void CalcCoordTask(void *pdata){
	
	finalresult[0]=dSPAN; 
	finalresult[1]=dSPAN;
	OSSemPend(CalcCoordSem,0,&err);
	
	while(1){
		CalcCoord(finalresult[0],finalresult[1],image_sequence[current_image]);
		OSSemPost(CropSem);
		OSSemPend(CalcCoordSem,0,&err);
	}
}

void crop (int coordX,int coordY,unsigned char* img){ 
	
	int head;		//head to use as reference
	head=(img[0]*coordY)+coordX+3;		//Goes directly to the coords given (+3 because the first three values are x,y and maxvalue)
	int jump;		//defines how many values we need to skip once that the cropsize is over
	printf("\n  CX=%d , CY=%d\n\n", coordX,coordY);
	OSTimeDly(3000);
		
	jump=img[0]-cropSIZE; //Jump defines the gap between values to skip to have a perfect cropping
	int i,j;
	for(i=0;i<cropSIZE;i++){
		for(j=0;j<cropSIZE;j++){
			imagematrix[i][j]=(unsigned char)img[head];
			head++;
		}
		head+=jump;		//when we reach the border of the matrix we goes to the next line
	}	
}

void CropTask(void *pdata){

	OSSemPend(CropSem,0,&err);
	while(1){
		
		crop(Globcoords[0],Globcoords[1], image_sequence[current_image]);	
		OSSemPost(xCorr2Sem);
		OSSemPend(CropSem,0,&err);			
	}
}


unsigned int stencilmat(int i, int j,unsigned char cropped_matrix[31][31]){ //x,y,mat
	unsigned int sum;
	sum= (cropped_matrix[j][i+2] + cropped_matrix[j+1][i+1] + cropped_matrix[j+1][i+3] + cropped_matrix[j+2][i] + cropped_matrix[j+2][i+4] + cropped_matrix[j+3][i+1] + cropped_matrix[j+3][i+3] + cropped_matrix[j+4][i+2]);  
	return sum;  
	
}

void xCorr2(unsigned char matrix[31][31]){
		
	int i,j;


	OSTimeDly(3000);
	
	for(i=0; i<cropSIZE-4;i++){ 
		for(j=0; j<cropSIZE-4;j++){			
			matrixmix[i][j]=(unsigned int)stencilmat(j,i,matrix);
			
		}
		
	}

	
	
}


void xCorr2Task(void *pdata){
		
		OSSemPend(xCorr2Sem,0,&err);
		while(1){
			xCorr2(imagematrix);
			OSSemPost(PosMaxSem);
			OSSemPend(xCorr2Sem,0,&err);
		}
		
}




void posMax(unsigned int matrix[27][27]){
	int max=0;		//Variable used for the max
	int maybemax;		//Variable that is a max of it's own matrix but not the biggest

	//The following finds the highest value between all the different matrix
	int i,j;
	for(i=0; i<cropSIZE-4;i++){
		for(j=0; j<cropSIZE-4;j++){
			maybemax=matrix[i][j];
			if(maybemax > max){
				 max=maybemax;
				 objectmax[0]=j;
				 objectmax[1]=i;
			}
		}
	}	
	
}


void PosMaxTask(void *pdata){
	

	OSSemPend(PosMaxSem,0,&err);
	while(1){
	posMax(matrixmix);
	OSSemPost(objectPosSem);
	OSSemPend(PosMaxSem,0,&err);
	}
}

void objectPos(int coordX,int coordY, int posmax[2]){ 

	//Equation given by the haskell code
	finalresult[0]= coordX+posmax[0]+2;
	finalresult[1]= coordY+posmax[1]+2;
	printf("\nFinal result:[%d,%d]", (finalresult[0]), (finalresult[1]));
		
}

void ObjectPosTask(void *pdata){

	OSSemPend(objectPosSem,0,&err);
	while(1){
		objectPos(Globcoords[0],Globcoords[1],objectmax);
		current_image++;
		OSSemPost(GrayedSem);	
		OSSemPend(objectPosSem,0,&err);
	}
}


void StartTask(void* pdata)
{
 
  void* context=0;

  static alt_alarm alarm;     /* Is needed for timer ISR function */
  
  /* Base resolution for SW timer : HW_TIMER_PERIOD ms */
  delay = alt_ticks_per_second() * HW_TIMER_PERIOD / 1000; 
  printf("delay in ticks %d\n", delay);

  /* 
   * Create Hardware Timer with a period of 'delay' 
   */
  if (alt_alarm_start (&alarm,
      delay,
      alarm_handler,
      context) < 0)
      {
          printf("No system clock available!n");
      }

   /*
   * Creation of Kernel Objects
   */

  GrayedSem= OSSemCreate(0);
  CalcCoordSem= OSSemCreate(0);
  CropSem= OSSemCreate(0);
  xCorr2Sem = OSSemCreate(0);
  PosMaxSem = OSSemCreate(0);
  objectPosSem = OSSemCreate(0);
  /*
   * Create statistics task
   */

  OSStatInit();

  /* 
   * Creating Tasks in the system 
   */


	err=OSTaskCreateExt(CalcCoordTask,
                  NULL,
                  (void *)&CalcCoordTask_stk[TASK_STACKSIZE-1],
                  CalcCoordTask_PRIORITY,
                  CalcCoordTask_PRIORITY,
                  CalcCoordTask_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

	 if (DEBUG) {
     if (err == OS_ERR_NONE) { //if start successful
      printf("CalcCoordTask created\n");
    }}

	err=OSTaskCreateExt(xCorr2Task,
                  NULL,
                  (void *)&xCorr2Task_stk[TASK_STACKSIZE-1],
                  xCorr2Task_PRIORITY,
                  xCorr2Task_PRIORITY,
                  xCorr2Task_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

	 if (DEBUG) {
     if (err == OS_ERR_NONE) { //if start successful
      printf("xCorr2Task created\n");
    }}
	
	err=OSTaskCreateExt(CropTask,
                  NULL,
                  (void *)&CropTask_stk[TASK_STACKSIZE-1],
                  CropTask_PRIORITY,
                  CropTask_PRIORITY,
                  CropTask_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

	 if (DEBUG) {
		 if (err == OS_ERR_NONE) { //if start successful
		  printf("CropTask created\n");
   		 }	
	}

	err=OSTaskCreateExt(PosMaxTask,
                  NULL,
                  (void *)&PosMaxTask_stk[TASK_STACKSIZE-1],
                  PosMaxTask_PRIORITY,
                  PosMaxTask_PRIORITY,
                  PosMaxTask_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

	 if (DEBUG) {
     if (err == OS_ERR_NONE) { //if start successful
      printf("PosMaxTask created\n");
    }else printf("\n%d\n",err);}

  
	err=OSTaskCreateExt(GrayTask,
                  NULL,
                  (void *)&GrayTask_stk[TASK_STACKSIZE-1],
                  GrayTask_PRIORITY,
                  GrayTask_PRIORITY,
                  GrayTask_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

	 if (DEBUG) {
     if (err == OS_ERR_NONE) { //if start successful
      printf("GrayTask created\n");
    }}
	err=OSTaskCreateExt(ObjectPosTask,
                  NULL,
                  (void *)&ObjectPosTask_stk[TASK_STACKSIZE-1],
                  ObjectPosTask_PRIORITY,
                  ObjectPosTask_PRIORITY,
                  ObjectPosTask_stk,
                  TASK_STACKSIZE,
                  NULL,
                  0);

	 if (DEBUG) {
     if (err == OS_ERR_NONE) { //if start successful
      printf("ObjectPosTask created\n");
    }}

  printf("All Tasks and Kernel Objects generated!\n");

  /* Task deletes itself */

  OSTaskDel(OS_PRIO_SELF);
}


int main(void) {

  printf("MicroC/OS-II-Vesion: %1.2f\n", (double) OSVersion()/100.0);
     
  OSTaskCreateExt(
	 StartTask, // Pointer to task code
         NULL,      // Pointer to argument that is
                    // passed to task
         (void *)&StartTask_Stack[TASK_STACKSIZE-1], // Pointer to top
						     // of task stack 
         STARTTASK_PRIO,
         STARTTASK_PRIO,
         (void *)&StartTask_Stack[0],
         TASK_STACKSIZE,
         (void *) 0,  
         OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);
         
  OSStart();
  
  return 0;
}
