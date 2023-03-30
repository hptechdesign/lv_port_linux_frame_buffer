#include <stdio.h>
// Serial port
#include "rs232.h"



int serial_init(void);
void serial_puts(char* msg);
int serial_read(void);
char* serial_getBuffer();