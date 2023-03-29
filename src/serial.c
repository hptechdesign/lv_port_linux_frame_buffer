
#include "ecu_configs.h"
#include "serial.h"

static int winPort=-1; // windows COM port is always equal to (port+1)
static int port=-1; /* port 0 = /dev/ttyS0 (COM1 on windows) */
static int bdrate=115200;     /* 115200 baud */
static char mode[]={'8','N','1',0};

static char msg[64];
static char str[2][512];
static int t=0, r=0;

void serial_selectPort(void)
{
    int userInput=0;
      

    while (port==-1)
    {
      // select serial port
#if SDL_ECU_DISPLAY
      printf("\nEnter a COM port number: ");
      scanf("%d", &userInput);
      if(userInput>0 && userInput <100)
      {
        winPort=userInput;
        port=winPort-1;
      }
      else
      {
        snprintf(msg, sizeof(msg), "\n\rSelection [%3d] is not valid.\
        Please enter a value [1-99].", userInput);
        printf(msg);
      }
#elif RPI_ECU_DISPLAY
      printf("\nEnter a serial port number: ");
      scanf("%d", &userInput);
      if(userInput>=0 && userInput <100)
      {
          port=userInput;
      }
      else
      {
        snprintf(msg, sizeof(msg), "\n\rSelection [%3d] is not valid.\
        Please enter a value [0-99].", userInput);
        printf(msg);
      }
#endif

    }
    
}


int serial_init(void)
{
  serial_selectPort();

  if(RS232_OpenComport(port, bdrate, mode, 0))
  {
    printf("Can not open comport\n");

    return(0);
  }

  // serial splash message
#if SDL_ECU_DISPLAY
  snprintf(msg, sizeof(msg), "\n\rOpened port: COM%d", (port+1));
#elif RPI_ECU_DISPLAY
  snprintf(msg, sizeof(msg), "\n\rOpened port: %3d", port);
#endif
  
  printf(msg);
  serial_puts(msg);
  return(0x2);
}

void serial_puts(char* msg)
{
    strcpy(str[t], msg);
    RS232_cputs(port, str[t]);
    printf("sent: %s\n", str[t++]);
    t%=2;
}
