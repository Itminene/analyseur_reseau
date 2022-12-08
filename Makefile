test_analyse_trame: test_analyse_trame.o lecture_trame.o analyse_trame.o analyse_trame_bis.o
	gcc -Wall -o test_analyse_trame $^ -lm

test_lecture_trame: test_lecture_trame.o lecture_trame.o
	gcc -Wall -o test_lecture_trame $^

test_print_graph.o: test_print_graph.c print_graph.h
	gcc -Wall -c test_print_graph.c

test_analyse_trame.o: test_analyse_trame.c analyse_trame.h lecture_trame.h
	gcc -Wall -c test_analyse_trame.c 

test_lecture_trame.o: test_lecture_trame.c lecture_trame.h
	gcc -Wall -c test_lecture_trame.c

print_graph.o: print_graph.c print_graph.h
	gcc -Wall -c print_graph.c 

lecture_trame.o: lecture_trame.c lecture_trame.h
	gcc -Wall -c lecture_trame.c

analyse_trame.o: analyse_trame.c analyse_trame.h
	gcc -Wall -c analyse_trame.c 

analyse_trame_bis.o: analyse_trame_bis.c analyse_trame_bis.h
	gcc -Wall -c analyse_trame_bis.c 

clean :
	rm -f *.o main test_analyse_trame test_lecture_trame