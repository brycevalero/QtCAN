#include "canlib.h"
#include <stdio.h>
#include <conio.h>


//Prints an error message if a Canlib call fails
void Check(char* id, canStatus stat){
  if (stat != canOK) {
    char buf[50];
    buf[0] = '\0';
    canGetErrorText(stat, buf, sizeof(buf));
    printf("%s: failed, stat=%d (%s)\n", id, (int)stat, buf);
    exit(1);
  }
}


void dumpMessageLoop(canHandle hnd){
  canStatus stat = canOK;
  long id;
  unsigned int dlc, flags;
  unsigned char data[8];
  DWORD time;

  printf("Listening for messages on channel 0, press any key to close\n");

  //Loops until a key is pressed
  while (!kbhit()){

    //Waits up to 100 ms for a message
    stat = canReadWait(hnd, &id, data, &dlc, &flags, &time, 100);
    if (stat == canOK){
      if (flags & canMSG_ERROR_FRAME){
        printf("***ERROR FRAME RECEIVED***");
      }
      else {
        printf("Id: %ld, Data: %u %u %u %u %u %u %u %u DLC: %u Flags: %lu",
               id, dlc, data[0], data[1], data[2], data[3], data[4],
               data[5], data[6], data[7], time);
      }
    }
    //Breaks the loop if something goes wrong
    else if (stat != canERR_NOMSG){
      Check("canRead", stat);
      break;
    }
  }
}


void main(int argc, int* argv[]){
  canHandle hnd;
  canStatus stat;

  canInitializeLibrary();

  //Channel initialization
  hnd = canOpenChannel(0, 0);
  stat = canSetBusParams(hnd, canBITRATE_250K, 0, 0, 0, 0, 0);
  Check("canSetBusParams", stat);

  stat = canBusOn(hnd);
  Check("canBusOn", stat);

  //Starts listening for messages
  dumpMessageLoop(hnd);

  //Channel teardown
  printf("Going of bus and closing channel");
  stat = canBusOff(hnd);
  Check("CanBusOff", stat);
  stat = canClose(hnd);
  Check("CanClose", stat);
}
