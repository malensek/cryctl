#define _WITH_GETLINE
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "typedefs.h"
#include "serial.h"
#include "cf_packet.h"
#include "show_packet.h"

bool verbose = true;

bool wait_reply() {
    int k;
    bool timed_out;
    timed_out = true;
    for(k = 0; k <= 100; k++) {
        if(check_for_packet()) {
            if (verbose) {
                ShowReceivedPacket();
            }
            timed_out = false;
            break;
        }
        usleep(10000);
    }

    return timed_out;
}

bool clear_lcd() {
    outgoing_response.command = 6;
    outgoing_response.data_length = 0;
    send_packet();
    wait_reply();

    outgoing_response.command = 34;
    outgoing_response.data_length = 2;
    outgoing_response.data[0] = 11;
    outgoing_response.data[1] = 0;
    send_packet();
    wait_reply();

    outgoing_response.command = 9;
    outgoing_response.data_length = 9;

    outgoing_response.data[0] = 0;

    outgoing_response.data[1] = 0;
    outgoing_response.data[2] = 0;
    outgoing_response.data[3] = 0;
    outgoing_response.data[4] = 32;
    outgoing_response.data[5] = 48;
    outgoing_response.data[6] = 56;
    outgoing_response.data[7] = 60;
    outgoing_response.data[8] = 62;
    send_packet();
    wait_reply();

    outgoing_response.data[0] = 1;

    outgoing_response.data[1] = 0;
    outgoing_response.data[2] = 0;
    outgoing_response.data[3] = 0;
    outgoing_response.data[4] = 1;
    outgoing_response.data[5] = 3;
    outgoing_response.data[6] = 7;
    outgoing_response.data[7] = 15;
    outgoing_response.data[8] = 31;
    send_packet();
    wait_reply();

    outgoing_response.data[0] = 2;

    outgoing_response.data[1] = 0;
    outgoing_response.data[2] = 32;
    outgoing_response.data[3] = 48;
    outgoing_response.data[4] = 56;
    outgoing_response.data[5] = 60;
    outgoing_response.data[6] = 62;
    outgoing_response.data[7] = 63;
    outgoing_response.data[8] = 63;
    send_packet();
    wait_reply();

    outgoing_response.data[0] = 3;

    outgoing_response.data[1] = 0;
    outgoing_response.data[2] = 0;
    outgoing_response.data[3] = 0;
    outgoing_response.data[4] = 0;
    outgoing_response.data[5] = 0;
    outgoing_response.data[6] = 0;
    outgoing_response.data[7] = 0;
    outgoing_response.data[8] = 33;
    send_packet();
    wait_reply();

    outgoing_response.data[0] = 4;

    outgoing_response.data[1] = 0;
    outgoing_response.data[2] = 1;
    outgoing_response.data[3] = 3;
    outgoing_response.data[4] = 7;
    outgoing_response.data[5] = 15;
    outgoing_response.data[6] = 31;
    outgoing_response.data[7] = 63;
    outgoing_response.data[8] = 63;
    send_packet();
    wait_reply();

    outgoing_response.data[0] = 5;

    outgoing_response.data[1] = 63;
    outgoing_response.data[2] = 63;
    outgoing_response.data[3] = 31;
    outgoing_response.data[4] = 15;
    outgoing_response.data[5] = 7;
    outgoing_response.data[6] = 3;
    outgoing_response.data[7] = 1;
    outgoing_response.data[8] = 0;
    send_packet();
    wait_reply();

    outgoing_response.data[0] = 6;

    outgoing_response.data[1] = 63;
    outgoing_response.data[2] = 63;
    outgoing_response.data[3] = 63;
    outgoing_response.data[4] = 63;
    outgoing_response.data[5] = 63;
    outgoing_response.data[6] = 63;
    outgoing_response.data[7] = 63;
    outgoing_response.data[8] = 63;
    send_packet();
    wait_reply();

    outgoing_response.data[0] = 7;

    outgoing_response.data[1] = 63;
    outgoing_response.data[2] = 63;
    outgoing_response.data[3] = 62;
    outgoing_response.data[4] = 60;
    outgoing_response.data[5] = 56;
    outgoing_response.data[6] = 48;
    outgoing_response.data[7] = 32;
    outgoing_response.data[8] = 0;
    send_packet();
    wait_reply();


    return true;
}

bool update_lcd(int line, char *str) {
    size_t len = strlen(str);
    char buf[21] = { 0 };
    str[len - 1] = '\0';
    snprintf(buf, 21, "%-20s", str);

    if (verbose) {
        printf("%d: '%s'\n", line, buf);
    }

    outgoing_response.command = 31;
    outgoing_response.data[0] = 0; //col
    outgoing_response.data[1] = line; //row
    memcpy(&outgoing_response.data[2], buf, 20);
    outgoing_response.data_length = 22; // (size of col, row, text)
    send_packet();
    return wait_reply();
}

//============================================================================
int main(int argc, char* argv[]) {
    printf("Ultra-simple CFA-635 command-line communications example.\n");
    printf("Crystalfontz America, Inc. http://www.crystalfontz.com\n\n");
    printf("Usage:\n");
    printf("%s PORT BAUD\n",argv[0]);
    printf("PORT is something like \"/dev/ttyS0\" or \"/dev/usb/ttyUSB0\"\n");
    printf("BAUD is 19200 or 115200\n");
    printf("To clear the display, enter \"clear\" as an optional third parameter\n\n");


    //If only 0 or 1 parameter is entered, prompt for the missing parameter(s)
    if(argc < 3)
    {
        printf("\nMISSING A PARAMETER. Enter both PORT and BAUD.\n\n");
        return(0);
    }

    //Check for optional "clear" parameter and set flag if found
    int cleardisplay = 0;
    if((argc > 3)&&(!strcmp(argv[3],"clear"))) cleardisplay=1;


    int
        baud;
    //default the baud to 115200
    if(strcmp(argv[2],"19200"))
        baud=115200;
    else
        baud=19200;

    if(Serial_Init(argv[1],baud)) {
        printf("Could not open port \"%s\" at \"%d\" baud.\n",argv[1],baud);
        return(1);
    } else {
        printf("\"%s\" opened at \"%d\" baud.\n\n",argv[1],baud);
    }

    // For some reason, Linux seems to buffer up data from the LCD, and they are
    // sometimes dumped at the start of the program. Clear the serial buffer.
    while(BytesAvail()) {
        GetByte();
    }

    clear_lcd();

    int i;
    char *line = NULL;
    size_t sz;
    for (i = 0; i < 4 && (getline(&line, &sz, stdin)) > 0; ++i) {
        update_lcd(i, line);
    }

    outgoing_response.command = 4;
    outgoing_response.data_length = 0;
    send_packet();
    wait_reply();


    return EXIT_SUCCESS;
}
