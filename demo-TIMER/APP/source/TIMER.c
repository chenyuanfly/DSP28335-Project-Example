#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "DSP2833x_Gpio.h"

#define   LED1  GpioDataRegs.GPADAT.bit.GPIO0
#define   LED2  GpioDataRegs.GPADAT.bit.GPIO1
#define   LED3  GpioDataRegs.GPADAT.bit.GPIO2
#define	  LED4	GpioDataRegs.GPADAT.bit.GPIO3
#define   LED5  GpioDataRegs.GPADAT.bit.GPIO4


void configtestled(void);

void timer0_Init(void);

void timer1_Init(void);

interrupt void timer0_isr(void);    //timer0中断函数

interrupt void timer1_isr(void);    //timer1中断函数

void main(void)
{
    InitSysCtrl();

    //initGpio();
    InitXintf16Gpio();

    DINT;

    InitPieCtrl();

    IER = 0x0000;
    IFR = 0x0000;

    InitPieVectTable();

    configtestled();
 
    //timer0_Init();
    timer1_Init();

    while(1){
        LED3 = ~LED3;
        DELAY_US(200000);
        LED3 = ~LED3;
        DELAY_US(200000);
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

    GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 0; //
    GpioCtrlRegs.GPADIR.bit.GPIO4 = 1;
    EDIS;
}

void timer0_Init(void)
{
    EALLOW;
    PieVectTable.TINT0 = &timer0_isr;   //定时器中断地址
    EDIS;

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 150, 1000);  //定时为 1 ms
    CpuTimer0Regs.TCR.all = 0x4001;         //设置 TSS bit = 0
    IER |= M_INT1;                          //CPU-Timer0 属于CPU INT1 使能
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;      //使能 TINT0 在 PIE 中 第七中断

    EINT;   //使能INTM中断
    ERTM;   //使能DBGM中断
}

void timer1_Init(void)
{
    EALLOW;
    PieVectTable.XINT13 = &timer1_isr;   //定时器中断地址
    EDIS;

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer1, 150, 10000);  //定时为 10 ms
    CpuTimer1Regs.TCR.all = 0x4001;         //设置 TSS bit = 0
    IER |= M_INT13;                          //CPU-Timer0 属于CPU INT1 使能

    EINT;   //使能INTM中断
    ERTM;   //使能DBGM中断
}

interrupt void timer0_isr(void)
{
    //清除中断标志
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    LED1 = ~LED1;
    DELAY_US(200000);
    LED1 = ~LED1;
    DELAY_US(200000);
}

interrupt void timer1_isr(void)
{
    LED2 = ~LED2;
    DELAY_US(200000);
    LED2 = ~LED2;
    DELAY_US(200000);
}

//===========================================================================
// No more.
//===========================================================================
