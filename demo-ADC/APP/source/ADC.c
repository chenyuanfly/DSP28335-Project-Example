#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "DSP2833x_Gpio.h"
#include "ADCConfig.h"

#define   LED1  GpioDataRegs.GPADAT.bit.GPIO0
#define   LED2  GpioDataRegs.GPADAT.bit.GPIO1
#define   LED3  GpioDataRegs.GPADAT.bit.GPIO2
#define	  LED4	GpioDataRegs.GPADAT.bit.GPIO3
#define   LED5  GpioDataRegs.GPADAT.bit.GPIO4

#define SAMPLE_SIZE 16  //����ͨ����

volatile Uint16 sampleTable[SAMPLE_SIZE];
volatile float resultTable[SAMPLE_SIZE];

void configtestled(void);

void timer0_Init(void);

interrupt void timer0_isr(void);    //timer0�жϺ���

void ADC_Task();

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

    ADC_Config();
 
    timer0_Init();

    while(1){

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


interrupt void timer0_isr(void)
{
    //����жϱ�־
    PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;

    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;       //�������ת����

    ADC_Task();
}

void ADC_Task()
{
    int count = 0;

    while(AdcRegs.ADCST.bit.INT_SEQ1 == 0);
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;     //���INT_SEQ1��־λ

    //��ȡADC��������
    sampleTable[count++] = (AdcRegs.ADCRESULT0) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT1) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT2) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT3) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT4) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT5) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT6) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT7) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT8) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT9) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT10) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT11) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT12) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT13) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT14) >> 4;
    sampleTable[count++] = (AdcRegs.ADCRESULT15) >> 4;

    int i;
    for(i = 0; i < SAMPLE_SIZE; i++)
    {
        resultTable[i] = (float)sampleTable[i] * 3.0 / 4096.0;
    }

}

//===========================================================================
// No more.
//===========================================================================
