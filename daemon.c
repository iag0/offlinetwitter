# include<stdio.h>
# include<sys/socket.h>
# include<stdlib.h>
# include<sys/types.h>
# include<netdb.h>
# include<unistd.h>
# include<sys/signal.h>
# include<string.h>
# include<sys/param.h>
# include<unistd.h>


struct addrinfo test,*result;
int sock,con,capture=0,waiting=0;

int main()
{	
	
	//printf("%d %d \n",getpid(),getpgrp());
	
	//Code for daemonization of the process
	
	/*switch(fork())
	{
		case 0: break;
		case -1: fprintf(stderr,"Error fork 1\n");
			exit(0);
			break;
		default: _exit(0);
	}
	
	//printf("%d %d \n",getpid(),getpgrp());
	
	setsid();
	
	//printf("%d %d \n",getpid(),getpgrp());
	
	
	switch(fork())
	{
		case 0: break;
		case -1: fprintf(stderr,"Error fork 2\n");
			exit(0);
			break;
		default: _exit(0);
	}
	
	printf("%d %d \n",getppid(),getpgrp());
	
	chdir("/");	
	*/	
	
	memset(&test,0,sizeof(test));
	test.ai_family=AF_INET;
	test.ai_socktype=SOCK_STREAM;
	
	
	
	getaddrinfo("www.google.com","80",&test,&result);
	
	
	while(1){
		sock=socket(result->ai_family,result->ai_socktype,result->ai_protocol);
	
	
	
		if(connect(sock,result->ai_addr,result->ai_addrlen)==0)
		{
			printf("Connected\n");
			if(capture!=0) kill(capture,SIGINT);
			capture=0;
			waiting=0;
			sleep(3);
		}
		else if(waiting!=1)
		{	
			printf("Not connected\n");
			waiting=1;
			capture=fork();
			if(capture==0)
			{	
				
				execl("./try.out","./try.out",(char *)0);
			}
		
		
		}
		//sleep(2);
		close(sock);	
		
	}
	
	
}
