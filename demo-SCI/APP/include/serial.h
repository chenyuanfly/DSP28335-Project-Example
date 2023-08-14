#ifndef SERIAL_H
#define SERIAL_H

#include "DSP2833x_Device.h"
#include "DSP2833x_GlobalPrototypes.h"

void Serial_Init(Uint32 baud);

void Serial_SendChar(char data);

void Serial_SendString(char *msg);

#endif

//===========================================================================
// End of file.
//===========================================================================

