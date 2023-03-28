

static cport_nr=0;
static char str[2][512];
static int t, r;

void serial_init(int port_nr)
{
    //cport_nr=0,        /* /dev/ttyS0 (COM1 on windows) */
     int bdrate=115200;     /* 115200 baud */

  char mode[]={'8','N','1',0};

  cport_nr=port_nr;
       
  if(RS232_OpenComport(cport_nr, bdrate, mode, 0))
  {
    printf("Can not open comport\n");

    return(0);
  }
}

void serial_puts(char* msg)
{
    strcpy(str[t], *msg);
    RS232_cputs(cport_nr, str[t]);
    printf("sent: %s\n", str[t++]);
    t%=2;
}
