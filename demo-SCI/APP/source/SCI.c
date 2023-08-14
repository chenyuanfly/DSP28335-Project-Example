#include "DSP2833x_Device.h"     // DSP2833x Headerfile Include File
#include "DSP2833x_Examples.h"   // DSP2833x Examples Include File
#include "DSP2833x_Gpio.h"
#include "serial.h"

#define   LED1  GpioDataRegs.GPADAT.bit.GPIO0
#define   LED2  GpioDataRegs.GPADAT.bit.GPIO1
#define   LED3  GpioDataRegs.GPADAT.bit.GPIO2
#define	  LED4	GpioDataRegs.GPADAT.bit.GPIO3
#define   LED5  GpioDataRegs.GPADAT.bit.GPIO4

//����N��Ϊ�͵�ѹ
#define KEY_R1_SETL GpioDataRegs.GPACLEAR.bit.GPIO26 = 1
#define KEY_R2_SETL GpioDataRegs.GPACLEAR.bit.GPIO25 = 1
#define KEY_R3_SETL GpioDataRegs.GPACLEAR.bit.GPIO24 = 1
#define KEY_R4_SETL GpioDataRegs.GPBCLEAR.bit.GPIO48 = 1

//����N��Ϊ�ߵ�ѹ
#define KEY_R1_SETH GpioDataRegs.GPASET.bit.GPIO26 = 1
#define KEY_R2_SETH GpioDataRegs.GPASET.bit.GPIO25 = 1
#define KEY_R3_SETH GpioDataRegs.GPASET.bit.GPIO24 = 1
#define KEY_R4_SETH GpioDataRegs.GPBSET.bit.GPIO48 = 1

#define KEY_C1 GpioDataRegs.GPADAT.bit.GPIO21
#define KEY_C2 GpioDataRegs.GPADAT.bit.GPIO20
#define KEY_C3 GpioDataRegs.GPADAT.bit.GPIO27

void configtestled(void);

void configkey(void);

void keyMatrixScan(void);

void checkNumberKey(int row);

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
 
    configkey();

    Serial_Init(115200);

    while(1){
        keyMatrixScan();
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

void configkey(void)
{
    EALLOW;

    //���̵�һ��
    GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 0;        //ѡ���� Ϊ��ͨ�˿�
    GpioCtrlRegs.GPAPUD.bit.GPIO26 = 0;         //ʹ���ض������ڲ�����
    GpioCtrlRegs.GPADIR.bit.GPIO26 = 1;         //����Ϊ�����

    //���̵ڶ���
    GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 0;        //ѡ���� Ϊ��ͨ�˿�
    GpioCtrlRegs.GPAPUD.bit.GPIO25 = 0;         //
    GpioCtrlRegs.GPADIR.bit.GPIO25 = 1;         //����Ϊ�����

    //���̵�����
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 0;        //ѡ���� Ϊ��ͨ�˿�
    GpioCtrlRegs.GPAPUD.bit.GPIO24 = 0;         //
    GpioCtrlRegs.GPADIR.bit.GPIO24 = 1;         //����Ϊ�����

    //���̵�����
    GpioCtrlRegs.GPBMUX2.bit.GPIO48 = 0;        //ѡ���� Ϊ��ͨ�˿�
    GpioCtrlRegs.GPBPUD.bit.GPIO48 = 0;         //
    GpioCtrlRegs.GPBDIR.bit.GPIO48 = 1;         //����Ϊ�����

    //���ö˿�Ĭ��Ϊ�ߵ�ƽ
    GpioDataRegs.GPASET.bit.GPIO26 = 1;
    GpioDataRegs.GPASET.bit.GPIO25 = 1;
    GpioDataRegs.GPASET.bit.GPIO24 = 1;
    GpioDataRegs.GPBSET.bit.GPIO48 = 1;

    GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 21;  //ѡ�񴥷��ж�Դ
    XIntruptRegs.XINT1CR.bit.POLARITY = 1;      //����Ϊ�½��ش����ж�
    XIntruptRegs.XINT1CR.bit.ENABLE = 1;        //ʹ��XINT�ж�

    //���̵�һ��
    GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 0;        //ѡ���� Ϊ��ͨ�˿�
    GpioCtrlRegs.GPAPUD.bit.GPIO21 = 0;         //
    GpioCtrlRegs.GPADIR.bit.GPIO21 = 0;         //����Ϊ�����

    //���̵ڶ���
    GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 0;        //ѡ���� Ϊ��ͨ�˿�
    GpioCtrlRegs.GPAPUD.bit.GPIO20 = 0;         //
    GpioCtrlRegs.GPADIR.bit.GPIO20 = 0;         //����Ϊ�����

    //���̵�����
    GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 0;        //ѡ���� Ϊ��ͨ�˿�
    GpioCtrlRegs.GPAPUD.bit.GPIO27 = 0;         //
    GpioCtrlRegs.GPADIR.bit.GPIO27 = 0;         //����Ϊ�����

    EDIS;

}

void keyMatrixScan(void)
{
    int i;
    for(i = 0; i < 4; i++)
    {
        checkNumberKey(i);
    }
}

void checkNumberKey(int row)
{
    switch(row)
    {
    case 0:
        KEY_R1_SETL;
        break;
    case 1:
        KEY_R2_SETL;
        break;
    case 2:
        KEY_R3_SETL;
        break;
    case 3:
        KEY_R4_SETL;
        break;
    }

    if(KEY_C1 == 0 || KEY_C2 == 0 || KEY_C3 == 0)
    {
        //�ӳ�����
        DELAY_US(100000);

        if(KEY_C1 == 0)
        {
            switch(row)
            {
            case 0:
                Serial_SendChar('1');
                break;
            case 1:
                Serial_SendChar('4');
                break;
            case 2:
                Serial_SendChar('7');
                break;
            case 3:
                Serial_SendChar('-');
                break;
            }
        }
        else if(KEY_C2 == 0)
        {
            switch(row)
            {
            case 0:
                Serial_SendChar('2');
                break;
            case 1:
                Serial_SendChar('5');
                break;
            case 2:
                Serial_SendChar('8');
                break;
            case 3:
                Serial_SendChar('0');
                break;
            }
        }
        else if(KEY_C3 == 0)
        {
            switch(row)
            {
            case 0:
                Serial_SendChar('3');
                break;
            case 1:
                Serial_SendChar('6');
                break;
            case 2:
                Serial_SendChar('9');
                break;
            case 3:
                Serial_SendChar('+');
                break;
            }
        }
    }


    KEY_R1_SETH;
    KEY_R2_SETH;
    KEY_R3_SETH;
    KEY_R4_SETH;
}

//===========================================================================
// No more.
//===========================================================================
