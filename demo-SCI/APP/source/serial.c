#include "serial.h"

void Serial_Init(Uint32 baud)
{
    unsigned char scihbaud = 0;
    unsigned char scilbaud = 0;
    Uint16 scibaud = 0;

    //设置波特率fan
    scibaud = 37500000 / (8*baud) - 1;
    scihbaud = scibaud >> 8;
    scilbaud = scibaud & 0xff;

    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;
    EDIS;

    //设置GPIO端口
    EALLOW;
    GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;
    GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;
    GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;
    GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;
    EDIS;

    //设置FIFO缓冲区
    SciaRegs.SCIFFTX.all = 0xE040;
    SciaRegs.SCIFFRX.all = 0x204F;
    SciaRegs.SCIFFCT.all = 0x0;

    SciaRegs.SCICCR.all = 0x0007;
    SciaRegs.SCICTL1.all = 0x0003;

    SciaRegs.SCICTL2.all = 0x0003;
    SciaRegs.SCIHBAUD = scihbaud;
    SciaRegs.SCILBAUD = scilbaud;
    SciaRegs.SCICTL1.all = 0x0023;
}

void Serial_SendChar(char data)
{
    while(SciaRegs.SCIFFTX.bit.TXFFST != 0);
    SciaRegs.SCITXBUF = data;
}

void Serial_SendString(char *msg)
{
    int i = 0;
    int len = sizeof(msg) / sizeof(char);

    for(; i < len; i++)
    {
        Serial_SendChar(msg[i]);
    }

}
