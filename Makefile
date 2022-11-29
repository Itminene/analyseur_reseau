test_analyse_trame: test_analyse_trame.o lecture_trame.o analyse_trame.o
	gcc -Wall -o test_analyse_trame $^

test_lecture_trame: test_lecture_trame.o lecture_trame.o
	gcc -Wall -o test_lecture_trame $^

test_analyse_trame.o: test_analyse_trame.c analyse_trame.h lecture_trame.h
	gcc -Wall -c test_analyse_trame.c

test_lecture_trame.o: test_lecture_trame.c lecture_trame.h
	gcc -Wall -c test_lecture_trame.c

lecture_trame.o: lecture_trame.c lecture_trame.h
	gcc -Wall -c lecture_trame.c

analyse_trame.o: analyse_trame.c analyse_trame.h
	gcc -Wall -c analyse_trame.c

clean :
	rm -f *.o main