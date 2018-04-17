#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
// #include <iostream>
 
int main (void)
{
        //open serial device
        int fd;
        fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);
        if (fd == -1)
        {
        perror("open_port: Unable to open /dev/ttyS0 - ");
        }
        else
        fcntl(fd, F_SETFL, 0);
        //Set baudrate to 19200
        struct termios options;
        tcgetattr(fd, &options);
        cfsetispeed(&options, B9600);
        cfsetospeed(&options, B9600);
        options.c_cflag |= (CLOCAL | CREAD);
        tcsetattr(fd, TCSANOW, &options);
        while(1) {
            readFile(fd);
            for (int t = 0; t < 100; t++) {}
        }
       
        // //Write text
        // int n;
        // n = write(fd, "Hello world!\r", 13);
        // if (n < 0)
        //         fputs("write() failed!\n", stderr);
 
        // n = write(fd, "Printed using the VoCore v1.0\r", 30);
        // if (n < 0)
        //         fputs("write() failed!\n", stderr);
 
        // n = write(fd, ":)\r", 3);
        // if (n < 0)
        //         fputs("write() failed!\n", stderr);
 
        //close connection
        close(fd);
        return printf("End\n");
}

void readFile(int fd) {
    char buffer[10];
    int bytes_read;
    int k = 0;
    do {
        char t = 0;
        bytes_read = read(fd, &t, 1); 
        buffer[k++] = t;    
        printf("%c", t);
        if(t == '\n' && t == '\0') {
            printf("%d", atoi(buffer));
            for(int i=0; i<10; i++) 
                buffer[i]='\0';
            k = 0;
        }
    }
    while (bytes_read != 0); 
}
