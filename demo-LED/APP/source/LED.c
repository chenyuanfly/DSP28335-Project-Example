#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File

#define	  LED4	GpioDataRegs.GPADAT.bit.GPIO0
#define	  LED3	GpioDataRegs.GPADAT.bit.GPIO1
#define	  LED1	GpioDataRegs.GPADAT.bit.GPIO2
#define	  LED2	GpioDataRegs.GPADAT.bit.GPIO3

void configtestled(void);

void main(void)
{
   InitSysCtrl();

   InitXintf16Gpio();

   DINT;

   InitPieCtrl();

   IER = 0x0000;
   IFR = 0x0000;

   InitPieVectTable();
   configtestled();
 
      LED1=1;
   DELAY_US(10);
      LED2=1;
   DELAY_US(10);
      LED3=1;
   DELAY_US(10);
      LED4=1;
   DELAY_US(10);
 
   while(1){
      LED1=~LED1;
      DELAY_US(100000);
      LED2=~LED2;
      DELAY_US(100000);
      LED3=~LED3;
      DELAY_US(100000);
      LED4=~LED4;
      DELAY_US(100000);

   }

}

void configtestled(void)
{
   EALLOW;
   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0; // GPIO0复用为GPIO功能
   GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;  // GPIO0设置为输出
   GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0; //
   GpioCtrlRegs.GPADIR.bit.GPIO1 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0; //
   GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 0; //
   GpioCtrlRegs.GPADIR.bit.GPIO3 = 1;
   EDIS;
}
//===========================================================================
// No more.
//===========================================================================
