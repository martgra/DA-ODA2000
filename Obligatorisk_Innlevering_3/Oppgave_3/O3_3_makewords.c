#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#define BUF_SIZE 8192

int main(int argc, char* argv[])
{

    int input_fd;    /* Input and output file descriptors */
    int current_read=1;
    char buffer[1];      /* Character buffer */

    input_fd= open(argv[1], O_RDWR);

    while (buffer[0] != '\n')
    {
    	current_read=read(0, &buffer, (sizeof(char)));
    	if(buffer[0]==' ')
    		write(1,"\n", (sizeof(char)));
    	else
    		write(1, buffer, current_read);

    }
}
