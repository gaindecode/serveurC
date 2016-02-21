#include <stdio.h>
#include <errno.h>
#include <signal.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>



#include <time.h>
#include <stdlib.h>


#define SERVEURNAME "127.0.0.1"

int to_server_socket = -1;

void main ( void )
{
srand(time(NULL));
	int r;
	char cated_string[512];
	char *server_name = SERVEURNAME;
	struct sockaddr_in serverSockAddr;
	struct hostent *serverHostEnt;
	long hostAddr;
	long status;
	char buffer[512];
	char message[512];

	bzero(&serverSockAddr,sizeof(serverSockAddr));
	hostAddr = inet_addr(SERVEURNAME);
	if ( (long)hostAddr != (long)-1)
	  bcopy(&hostAddr,&serverSockAddr.sin_addr,sizeof(hostAddr));
	else
	{
	  serverHostEnt = gethostbyname(SERVEURNAME);
	  if (serverHostEnt == NULL)
	  {
	    printf("ca chie gethost\n");
	    exit(0);
	  }
	  bcopy(serverHostEnt->h_addr,&serverSockAddr.sin_addr,serverHostEnt->h_length);
	}
	serverSockAddr.sin_port = htons(30000);
	serverSockAddr.sin_family = AF_INET;

	/* creation de la socket */
	if ( (to_server_socket = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
	  printf("ca chie creation socket client\n");
	  exit(0);
	}
	/* requete de connexion */
	if(connect( to_server_socket,
		    (struct sockaddr *)&serverSockAddr,
		    sizeof(serverSockAddr)) < 0 )
	{
	  printf("ca chie demande de connection\n");
	  exit(0);
	}
	/* envoie de donne et reception */
	r = rand()%(rand()%89187125*rand()%89187125);
	strncpy(message, "Toto", 4);//message="Toto ";
	
	sprintf(cated_string,"%s %d",message,r);

	write(to_server_socket,cated_string,strlen(cated_string));
	read(to_server_socket,buffer,512);
	printf(buffer);
	/* fermeture de la connection */
	shutdown(to_server_socket,2);
	close(to_server_socket);
}
