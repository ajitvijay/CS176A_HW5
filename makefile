hangman_server: hangman_server.c
	gcc -o hangman_server hangman_server.c 

hangman_client: hangman_client.c
	gcc -o hangman_client hangman_client.c

all: hangman_server hangman_client

clean:
	rm -f *.o hangman_client *~
	rm -f *.o hangman_server *~
