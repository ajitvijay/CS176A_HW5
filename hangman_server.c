/*
    Hangman game server in C using sockets
*/
//Ajit Vijayakumar
//Shu Yang

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>    //strlen
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <fcntl.h> //for open
#include <unistd.h> //for close and write


#define NUM_THREADS 5
/*
void *print_thread_id (void *id);
int getRand();
void checkGuess(char guess, char w[], char trivia[]);
int checkWin(char trivia[]);*/

int inc=0;
flag = 0;
bool won = false;


char * words[15];


int n_threads;

int main(int argc, char* argv[])
{
    int sockfd , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];

    words[0]="cat";
    words[1]="dog";
    words[2]="sea";
    words[3]="fun";
    words[4]="run";
    words[5]="buzz";
    words[6]="java";
    words[7]="maze";
    words[8]="bank";
    words[9]="blue";
    words[10]="adult";
    words[11]="black";
    words[12]="crowd";
    words[13]="drama";
    words[14]="faith";


    int i=0;

    n_threads= 0;
    int id,rid;
    pthread_t thread[NUM_THREADS];

    //Create socket
    sockfd = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd == -1)
    {
        printf("Could not create socket\n");
    }
    printf("Socket Created\n");
    int port = htons(atoi(argv[2]));
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = port;

    //Bind
    if( bind(sockfd,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        printf("Bind failed. Error\n");
        return 1;
    }
    printf("Bind Done\n");


	while(1){

		    //Listen
		    listen(sockfd , 1);

		    //Accept and incoming connection
		/*	if(n_threads <= 0){
		    printf("Waiting for incoming connections...\n");
			}*/

		    c = sizeof(struct sockaddr_in);


    //accept connection from an incoming client
			if(n_threads <3)
			{
			    client_sock = accept(sockfd, (struct sockaddr )&client, (socklen_t)&c);

			/*    if (client_sock < 0)
			    {
				printf("Accept Failed\n");
				return 0;
			    }
			   	 printf("Connection Accepted\n");

         strcpy(client_message,"Ready to start game? (y/n):");*/

					//Send the message back to client
					write(client_sock , client_message, strlen(client_message));

	     			n_threads++;
				rid = pthread_create(&thread[id],NULL,&print_thread_id,(void*)(size_t)client_sock);

				if(rid!=0)
				{
		//			printf("pthread_create() failed for Thread # %d",id);
					return 0;
				}

				 if(n_threads <= 0){
					pthread_exit(NULL);
					return 0;
				}
			}

			else
			{
				 client_sock = accept(sockfd, (struct sockaddr )&client, (socklen_t)&c);

			    if (client_sock < 0)
			    {
		//		printf("Accept Failed\n");
				return 0;
			    }

				printf("New request is denied! Server is full\n");

				strcpy(client_message,"Server overloaded\n");

					//Send the message back to client
					write(client_sock , client_message, strlen(client_message));


			}
		//pthread_join(thread[id],NULL);


		    //Receive a message from client

		//count--;
    recv(sockfd, buffer,1,0);
    int rand = rand() % 15;
    answer=words[rand];
    char temp*[8];
    for(int i = 0; answer.charAt(i)!='*'; i++){
      if(answer.charAt(i)!= '0'){
        temp.charAt(i)='_';
      }
    }
    temp+='*';

    strcat(answer, '*');
cont:
    recv(sockfd, buffer, 1, 0);
    char guess = buffer;
    bzero(&buffer, sizeof(buffer));
    send(sockfd, temp, sizeof(temp)+1, 0);
    send(sockfd, inc, 2, 0);
    for(int i = 0; temp.charAt(i)!='*'; i++){
    if(guess==answer.charAt(i)){
      temp.charAt(i)=guess;
      flag=1;
    //  inc++;
    }
  }
  if(flag==0){
    inc++;
  }
  for(int i = 0; temp.charAt(i)!='*'; i++){
    if(temp.charAt(i)!='_'){
      won=true;
    }
  }
    send(sockfd, won, sizoeof(won)+1, 0);
    bzero(&result, sizeof(result));
    recv(sockfd, result,sizeof(receive),0 )
    if(result=="won"){
      pthread_ext(NULL);
      n_threads--;
    }
    else if (result=="lose"){
      pthread_ext(NULL);
      n_threads--;
    }
    else{
      goto cont;
    }


	}



    return 0;
}
/*
void *print_thread_id (void *id)
{

  srand(time(NULL));
	int client_sock = (int)id;
	int read_size =0;
  char client_msg[2000],  word[2000];
  char trivia[2000] ;
    memset(trivia, '\0', sizeof(trivia));
      memset(client_msg, '\0', sizeof(client_msg));

  int word_index=getRand();
  strcpy(word, words[word_index]);

  for(int i=0;i<strlen(word);i++)
  {
    trivia[i] = '_';
  }

  write(client_sock , trivia, strlen(trivia));

  int end = 0;



     printf("Game Start Client %i\n",n_threads);
      	while(end == 0){
      		if( (read_size = recv(client_sock , client_msg, 2000 , 0)) > 0 )
      		    {


                  checkGuess(client_msg[0], word, trivia);
                  if(strcmp(client_msg,"end")==0)
                    {
                      write(client_sock , word, strlen(word));
                      n_threads--;
                    	pthread_exit(NULL);
                    }

                  if(checkWin(trivia))
                    end=1;
            			//Send the message back to client
            			write(client_sock , trivia, strlen(trivia));

      		    }

      		 else if(read_size == 0)
      		    {
      			//printf("Client disconnected \n");
      		    }

      		    else
      		    {
      			       perror("Recv Failed\n");
      		    }

      	   }


	n_threads--;
	pthread_exit(NULL);
}

int getRand()
{
  int r = rand() % 15;
  return r;
}


void checkGuess(char guess, char w[], char trivia[])
{
  int check=0;

    for(int i=0;i<strlen(w);i++)
    {
      if(w[i] == guess)
      {
        trivia[i] = w[i];
      }
    }

}

int checkWin(char trivia[])
{
  int check=1;
  for(int i=0;i<strlen(trivia);i++)
  {
    if(trivia[i] == '_')
      check=0;
  }
    return check;
}
*/
