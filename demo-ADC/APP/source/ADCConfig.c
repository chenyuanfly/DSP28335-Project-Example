#include "ADCConfig.h"

void ADC_Config()
{
    AdcRegs.ADCTRL3.bit.ADCPWDN = 0x1;          //启停模式
    AdcRegs.ADCTRL3.bit.ADCBGRFDN = 0x3;
    AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;     //ADC采样时间设置
    AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;    //ADC内核分频
    AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;           //级联工作模式
    AdcRegs.ADCTRL3.bit.SMODE_SEL = 0;          //顺序采样

    AdcRegs.ADCTRL1.bit.CONT_RUN = 0;           //0-启停模式  1-连续模式
    AdcRegs.ADCTRL1.bit.SEQ_OVRD = 1;           //完成排序后

    AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x1;     //打开SEQ1中断 允许向CPU发出中断 用于级联、双通道1

    AdcRegs.ADCREFSEL.bit.REF_SEL = 0;          //0-选择内部参考电压 1-选择外部参考电压

    //ADC 十六通道采集
    AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;      //通道与寄存器映射
    AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 0x1;
    AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 0x2;
    AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 0x3;
    AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 0x4;
    AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 0x5;
    AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 0x6;
    AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 0x7;
    AdcRegs.ADCCHSELSEQ3.bit.CONV08 = 0x8;
    AdcRegs.ADCCHSELSEQ3.bit.CONV09 = 0x9;
    AdcRegs.ADCCHSELSEQ3.bit.CONV10 = 0xA;
    AdcRegs.ADCCHSELSEQ3.bit.CONV11 = 0xB;
    AdcRegs.ADCCHSELSEQ4.bit.CONV12 = 0xC;
    AdcRegs.ADCCHSELSEQ4.bit.CONV13 = 0xD;
    AdcRegs.ADCCHSELSEQ4.bit.CONV14 = 0xE;
    AdcRegs.ADCCHSELSEQ4.bit.CONV15 = 0xF;

    AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0xF;     //设置通道数量
}
