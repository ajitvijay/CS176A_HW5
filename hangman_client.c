//Authors: Ajita Vijakumar and Shu Yang

#include <stdio.h> //printf
#include <string.h>    //strlen
#include <sys/socket.h>    //socket
#include <arpa/inet.h> //inet_addr
#include <stdlib.h> //atoi
#include <fcntl.h> //for open
#include <unistd.h> //for close

//int checkGuess(char g, char trivia[]);
//int checkWin(char trivia[]);

int main(int argc, char* argv[]){

    if (argc < 3){
      perror("Please enter 3 arguments. Don't forget server and port number");
      exit(EXIT_FAILURE);
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int port = htons(atoi(argv[2]));
    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_port=port;
    server_addr.sin_family = AF_INET;
    server_addr.sin_inaddr.s_addr=inet_addr(argv[1]);

    char buffer[128]={0};
    char answer[8]={0};
    char inc[10000];
    char numClients[10000];

  //  char message[1000] , server_reply[2000], incorrect_guesses[50], guess[50], trivia [50] ={'\0'};
    //memset(incorrect_guesses, '\0', sizeof(incorrect_guesses));

    //Create socket
  //  sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sockfd < 0)
    {
        perror("Could not create socket\n");
        exit(EXIT_FAILURE);
    }
  //  printf("Socket created\n");
/*
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));*/

    //Connect to remote server
    if (connect(sockfd , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        perror("Server connection failed");
        exit(EXIT_FAILURE);
    }

/*	if( recv(sock , server_reply , 2000 , 0) < 0)
		    {
			 puts("recv failed\n");*/

	//if((strcmp(server_reply,"Server is full") == 0))
	//{
	//		printf("Server reply :");
	//	    printf("%s\n",server_reply);

  if(strcmp(numClients,"Server has too many clients\n") == 0)
  {
    close(sock);
    return 0;
  }
  //gets(server_reply);
//  fgets(server_reply, sizeof(server_reply), stdin);
  if (server_reply[strlen(server_reply) - 1] == '\n'){
    server_reply[strlen(server_reply) - 1] = '\0';
  }

	//}

	//else
	//{

  //  		printf("Connected\n");
	//}
char a = 0;

while(1){
  wronginput:
    printf("Ready to start game? (y/n): ");
    bzero(&buffer, sizeof(buffer));
    fgets(buffer, sizeof(buffer), stdin);

    if(buffer[0] == 'n'){
      close(sockfd);
      return 1;
    }

    else if (buffer[0] == 'y'){
      send(sockfd,&a, 1, 0);
      break;
    }

    else{
      printf("Invalid input. Please try again!");
      goto wronginput;
    }
  }

  int numInc = 0;
  int received, wordLength;
//  int numZeros=8;
//reac numInc, check, add
keepplaying:
  while(numInc <= 5){
    bzero(&buffer, sizeof(buffer));
    printf("Letter to guess: ");
    fgets(buffer, 128, stdin);
    buffer[strcspn(buffer, "\n")] = 0;

    if(strlen(buffer) != 1){
      printf("Error! Please guess one letter. \n");
    }
    else{
      if(isalpha(buffer[0])){
        buffer[0]=tolower(buffer[0]);
      }
      send(sockfd, buffer, 2, 0);
  //    recv(sockfd, buffer, 1, 0);
    }

    recv(sockfd, temp, sizeof(temp), 0);
    for(char i = 0; temp.charAt(i)!='*'; i++){
      wordLength++;
    }

    for(int i = 0; i<=wordLength; i++){
    /*  if(temp.charAt(i)==0){
      printf("_");
    //  numZeros--;
  }*/
      printf(temp.charAt(i));
    }
    printf("\n");

    bzero(&inc, sizeof(inc));
    recv(sockfd, inc, 1, 0);
    printf("Number Incorrect:");
    printf(inc);
    printf("\n");

    bzero(&won, sizeof(won),0);
    recv(sockfd, won, sizeof(won),0);

    if(won==true){
      send(sockfd, "won", 4, 0);
      printf("The word was");
      printf("%s\n",answer);
      printf("\n");
      printf("You Win!\n");
      printf("Game Over!");
    }

    if(inc<5){
      goto keepplaying;
    }
  }

  if(inc==5){
    send(sockfd, "lose", 5, 0);
    printf("The word was");
    printf("%s\n",answer);
    printf("\n");
    printf("You Lose.\n");
    printf("Game Over!");
  }

}
    /*  received = buffer[0];

      if(received == 0){
        recv(sockfd, buffer, 1, 0);
        wordLength=buffer[0];

        recv(sockfd, buffer, 1, 0);

      }
    }
  /*  int check=1;
    for(int i=0;i<strlen(trivia);i++)
    {
      if(trivia[i] == '_')
        check=0;
    }
      return check;
  }
  /*if( send(sock , server_reply , strlen(server_reply) , 0) < 0)
  {
     printf("Send failed\n");
     return 1;
  }*/
/*
    int count = 7;

  	while(count > 0 )
    {

            if( recv(sock , trivia , 2000 , 0) < 0)
           {
          puts("recv failed\n");
           }

           if(checkWin(trivia))
              break;

           if(!checkGuess(guess[0],trivia)){
              strcat(incorrect_guesses,guess);
		          count--;
		       }

           printf("%s\n",trivia);
  		    printf("Incorrect Guesses: ");
            printf("%s\n\n",incorrect_guesses);

          printf("Letter to Guess: ");
  		    //gets(guess);
          fgets(guess, sizeof(server_reply), stdin);
          if (guess[strlen(guess) - 1] == '\n'){
            guess[strlen(guess) - 1] = '\0';
          }

          int wrong = 0;
        while(wrong == 0)
        {
          if(strlen(guess)==1 && ((guess[0]>=65 && guess[0]<=90) || (guess[0]>=97 && guess[0]<=122)) )
          {
      		    //Send some data
              //printf("Sent guess\n");
      		    if( send(sock , guess , strlen(guess) , 0) < 0)
      		    {
          			 printf("Send failed\n");
          			 return 1;
      		    }
              //count--;
              wrong = 1;
          }

          else
          {
              printf("Error! Please guess one letter.\n");
              printf("Letter to Guess: ");
              //gets(guess);
              fgets(guess, sizeof(guess), stdin);
              if (guess[strlen(guess) - 1] == '\n'){
                guess[strlen(guess) - 1] = '\0';
              }
          }
        }

  		    //Receive a reply from the server

       }

       if(checkWin(trivia)){
         printf("The Word: %s\n",trivia);
       printf("You Win!\nGame Over!\n");
     }

       else if(count==0)
       {
           printf("You Lose :(\nGame Over!\n");
           strcpy(guess,"end");
           if( send(sock , guess , strlen(guess) , 0) < 0)
           {
              printf("Send failed\n");
              return 1;
           }

           if( recv(sock , guess , 2000 , 0) < 0)
          {
              puts("recv failed\n");
          }

          printf("Correct Word was: %s",guess);


        }



   }
    close(sock);
    return 0;
}

int checkGuess(char g, char trivia[])
{
  int check=0;
  for(int i=0;i<strlen(trivia);i++)
  {
    if(trivia[i] == g)
      check=1;
  }
    return check;
}*/

/*int checkWin(char trivia[])
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
