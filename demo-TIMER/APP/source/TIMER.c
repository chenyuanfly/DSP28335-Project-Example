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

interrupt void timer0_isr(void);    //timer0�жϺ���

interrupt void timer1_isr(void);    //timer1�жϺ���

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
    GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0; // GPIO0����ΪGPIO����
    GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;  // GPIO0����Ϊ���

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
    PieVectTable.TINT0 = &timer0_isr;   //��ʱ���жϵ�ַ
    EDIS;

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer0, 150, 1000);  //��ʱΪ 1 ms
    CpuTimer0Regs.TCR.all = 0x4001;         //���� TSS bit = 0
    IER |= M_INT1;                          //CPU-Timer0 ����CPU INT1 ʹ��
    PieCtrlRegs.PIEIER1.bit.INTx7 = 1;      //ʹ�� TINT0 �� PIE �� �����ж�

    EINT;   //ʹ��INTM�ж�
    ERTM;   //ʹ��DBGM�ж�
}

void timer1_Init(void)
{
    EALLOW;
    PieVectTable.XINT13 = &timer1_isr;   //��ʱ���жϵ�ַ
    EDIS;

    InitCpuTimers();
    ConfigCpuTimer(&CpuTimer1, 150, 10000);  //��ʱΪ 10 ms
    CpuTimer1Regs.TCR.all = 0x4001;         //���� TSS bit = 0
    IER |= M_INT13;                          //CPU-Timer0 ����CPU INT1 ʹ��

    EINT;   //ʹ��INTM�ж�
    ERTM;   //ʹ��DBGM�ж�
}

interrupt void timer0_isr(void)
{
    //����жϱ�־
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
