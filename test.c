/**************************************************

file: this is a file modified for series communication from demo_tx.c
purpose: simple demo that transmits characters to
the serial port and print them on the screen,
exit the program by pressing Ctrl-C

the other codes are in https://www.teuniz.net/RS-232/

compile with the command: gcc test.c rs232.c rs232.h -Wall -Wextra -o2 -o final

**************************************************/

#include <stdlib.h>
#include <stdio.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "rs232.h"



int main()
{
  int i=0,
      cport_nr=3,        /* /dev/ttyS0 (COM1 on windows) */
      bdrate=115200;       /* 9600 baud */

  int n;

  char mode[]={'8','N','1',0},
       str[4][5];

  unsigned char buf[4096];

  strcpy(str[0], "w0103");

  strcpy(str[1], "w027c");

  strcpy(str[2], "w0080");

  strcpy(str[3], "r06");


  for(i=0;i<4;i++){
    for(int j=0;j<5;j++){
    printf("string is %c\t",str[i][j]);
  }
    printf("\n");
  }

  if(RS232_OpenComport(cport_nr, bdrate, mode, 0))
  {
    printf("Can not open comport\n");

    return(0);
  }

  for(i=0;i<1;i++)
  {
    RS232_cputs(cport_nr, str[i]);

    printf("sent: %s\n", str[i]);

#ifdef _WIN32
    Sleep(1000);
#else
    usleep(1000000);  /* sleep for 1 Second */
#endif

  }



    n = RS232_PollComport(cport_nr, buf, 4095);

    if(n > 0)
    {
      buf[n] = 0;   /* always put a "null" at the end of a string! */

      for(i=0; i < n; i++)
      {
        if(buf[i] < 32)  /* replace unreadable control-codes by dots */
        {
          buf[i] = '.';
        }
      }

      printf("received %i bytes: %s\n", n, (char *)buf);
    }

    RS232_flushRXTX(3);
    RS232_CloseComport(3);
  return(0);
}
