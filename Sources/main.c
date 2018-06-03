#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */

#define LRESET	PTCD_PTCD5


unsigned long TIEMPO , i, dato;
volatile unsigned int bandera=0;
volatile unsigned long N[180]={400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,
		                       400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,
		                       400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,
		                       400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,
		                       400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,
		                       400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,
		                       400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,
		                       400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,
		                       400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,400,
};

void tiempo(long t){
	for(i=0;i<t;i++);
	return;	
}

void motor(void){
	if (TPM2C1V==4694){
		bandera=1;
	}
	if(TPM2C1V==1400){
		bandera=0;
	}
	if (bandera==1){
		TPM2C1V=TPM2C1V-18;
		dato=dato-1;
	}
	else{
		TPM2C1V=TPM2C1V+18;
		dato=dato+1;
	}
	
  } 

void main(void) 
{
	
	SOPT1 = 0;
	MCGTRM = 0xAA; 
	MCGC1 = 6;
	while(MCGSC_LOCK == 0){}; 
	PTEDD=0xFF;
	PTCDD=0b00100000;
	PTFDD=0b00100001;
	PTFPE=0b00000010;
	
	TPM1SC=0b00001010; //TIM1 Pre*4, Int. deshabilitada, TIM deshabilitado
	TPM1MOD=50000;
	TPM1C2SC=0b00101000;
	TPM1C2V=20;
	
	TPM1C3SC=0b00001100; 
	
	TPM2SC = 0b00001010; //TIM2 Pre*4, Int. deshabilitada, TIM deshabilitado
	TPM2MOD=40000;   
	TPM2C1SC=0b00101000;
	TPM2C1V=1400;
	
	LRESET=1;
	tiempo(5000);
	LRESET=0;
	dato=0;
	
	TPM1SC_CLKSA = 1;
	TPM2SC_CLKSA = 1;
	EnableInterrupts;//CLI
	
	for(;;) 
	{
		TPM1C3SC=0b00000100;
		while(TPM1C3SC_CH3F==0);
		TPM1C3SC_CH3F=1;
		
		TPM1CNT=0;
		
		TPM1C3SC=0b00001000;
		while(TPM1C3SC_CH3F==0);
		TPM1C3SC_CH3F=1;
		
		TIEMPO=TPM1C3V;
		motor();
		
	}
}

 

