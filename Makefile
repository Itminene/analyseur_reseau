CC = gcc
#le dollar chapeau = tous les fichier.o cités dans les dependances (au dessus)
main : test.o ethernet.o main.o
	$(CC) -Wall -g -o main $^

main.o : main.c 
	$(CC) -Wall -g -o main.o -c $^

test.o : test.c 
	$(CC) -Wall -g -o test.o -c $^

ethernet.o : ethernet.c
	$(CC) -Wall -g -o ethernet.o -c $^

#permet de supprimer les fichier .o et l'executable main
clean :
	rm -f *.o main
	