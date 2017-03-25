/*
 ============================================================================
 Name        : Final_Test.c
 Author      : martin
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define NUM_CHILDREN 4

int fd1[2];
int fd2[2];
int fd3[2];
int fd4[2];

int main(int argc, char *argv[])
{
	int i = 0;
	int x = 0;
	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	pipe(fd4);
	
	for (i = 0; i < NUM_CHILDREN; i++)
	{
		pid_t pid = fork();
		if (pid==0)
		{
			switch (i)
					{
						case 0: //lowercase
						{

							printf("Prosess %i\n", i);
							dup2(fd1[1], 1);
							close_all_pipes();
							char* args[]=
							{
									"./O3_3_makewords", NULL
							};
							execv(args[0],args);
							break;
						}

						case 1: //makewords
						{
							printf("Prosess %i\n", i);
							close(0);
							dup(fd1[0]);
							dup2(fd2[1], 1);
							close_all_pipes();
							execl(".O3_3_lowercase","O3_3_lowercase", NULL);
							break;
						}

						case 2: // sort
						{
							printf("Prosess %i\n", i);
							close(1);
							dup2(fd2[0], 0);
							dup(fd3[1]);
							close_all_pipes();
							execl("/usr/bin/sort", "sort", NULL);
							break;
						}

						case 3: // uniq
						{
							printf("Prosess %i\n", i);
							dup2(fd3[0], 0);
							dup2(fd4[1], 1);
							close_all_pipes();
							char* args[]=
							{
								"/usr/bin/uniq", NULL
							};
							execvp(args[0],args);
							break;
						}

							default:
						{
							printf("Error\n");
							break;
						}

					}
		}
	}

	dup2(fd4[0], 0); //mismatch
	close_all_pipes();
	execl("./O3_3_mismatch.sh", "O3_3_mismatch.sh", NULL);

	for (x = 0; x < NUM_CHILDREN; x++) //waiting for children to finish
	{
		wait(NULL);
	}
	return 0;

}

int close_all_pipes()
{
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);
	close(fd3[0]);
	close(fd3[1]);
	close(fd4[0]);
	close(fd4[1]);

}
