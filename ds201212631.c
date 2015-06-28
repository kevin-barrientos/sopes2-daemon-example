/*
 * daemonize.c
 * This example daemonizes a process, writes a few log messages,
 * sleeps 20 seconds and terminates afterwards.
 */


/*Librerias para daemon*/
#include <signal.h>
#include <sys/stat.h>
#include <syslog.h>

/*Librerias para server*/
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <time.h> 

/*Librerias para ambos*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

static void skeleton_daemon()
{
    int result = daemon(0, 0);

		if(result > 0)
			exit(EXIT_FAILURE);

    /* Close all open file descriptors */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>0; x--)
    {
        close (x);
    }

    /* Open the log file */
    openlog ("MyDaemonServer", LOG_PID, LOG_DAEMON);
}

int getport(){
	FILE *fp;
	int port = 5000;
	fp = fopen("/etc/ds201212631/port.conf","r"); // read mode
 
  if( fp == NULL ){
     return port;
	}
 
	while (fscanf(fp, "%d", &port) != EOF) {
	  fclose(fp);
		if(port > 9999 || port < 1000)
			port = 5001;
		return port;
	}
}

void server()
{
int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

    char sendBuff[1025];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(getport()); 

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

        ticks = time(NULL);
        snprintf(sendBuff, sizeof(sendBuff), "%.24s \r\nHola mundo", ctime(&ticks));
        write(connfd, sendBuff, strlen(sendBuff)); 

        close(connfd);
        sleep(1);
     }
}

/*Signals handlers*/
void term_signal_callback(int signum)
{
	syslog (LOG_NOTICE, "My daemon server terminated.");
	
	//terminate process
	exit(signum);	

  closelog();
}

/*Signals recognition*/
void signals_recog()
{
	// Register signal and signal handler
  signal(SIGTERM, term_signal_callback);

}
int main()
{
	/*create daemon*/  
	skeleton_daemon();

	/*register signals and callbacks*/
	signals_recog();	

	/*start server*/
	syslog (LOG_NOTICE, "My daemon server started.");

	server();	
  
	return EXIT_SUCCESS;
}
