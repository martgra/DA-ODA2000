#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
 
#define BUF_SIZE 8192
 
int main(int argc, char* argv[])

{
 
    int current_read=1;
    char buffer[1];      /* Character buffer */

     while (current_read>0)
      {
	current_read=read(0, &buffer, (sizeof(char)));

	if(buffer[0]>64 && buffer[0]<90)
	  {
	    buffer[0]=buffer[0]+32;
	  }
	
	write(1, buffer, current_read);
	
      }
}

 
   
