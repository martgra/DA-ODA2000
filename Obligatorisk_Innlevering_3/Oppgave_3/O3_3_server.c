#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#define LOKAL_PORT 55555
#define BREV_STR 100
#define BAK_LOGG 10 // Størrelse på for kø ventende forespørsler

int main ()
{
	  int sd, ny_sd;
	  int current_read =1;
	  char buffer[1];
	  struct sockaddr_in  lok_adr; // Lokal adresse
	  struct sockaddr_in  fj_adr;  // Fjern adresse

	  char brev_buffer[BREV_STR];
	  char *text;
	  socklen_t adr_len;
	  int brv_len;
	  int select;


	  // Setter opp socket-strukturen
	  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	  // Initierer lokal adresse
	  lok_adr.sin_family = AF_INET;
	  lok_adr.sin_port = htons((u_short)LOKAL_PORT);
	  lok_adr.sin_addr.s_addr = htonl(INADDR_ANY);

	  // Kobler sammen socket og lokal adresse
	  bind(sd, (struct sockaddr *)&lok_adr, sizeof(lok_adr));

	  // Venter på forespørsel om forbindelse
	  listen(sd, BAK_LOGG);


	  while(1)
	  {
		  ny_sd = accept(sd, (struct sockaddr *)&fj_adr, &adr_len);

		  // Aksepterer mottatt forespørsel

			  if(0==fork())
			  {

					  dup2(ny_sd, 0);
					  dup2(ny_sd, 1);
					  execl("./O3_3_pipes", "O3_3_pipes", NULL);
			  }
		  wait(NULL);
		  read(ny_sd, brev_buffer, BREV_STR);
		  if (brv_len <= 0)
			  return 0;

	  }

	return 0;

}
