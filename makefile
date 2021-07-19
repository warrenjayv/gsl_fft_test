SRC = main.c

install : 
	gcc -Wall -L/usr/local/include -L/usr/local/lib -lgsl -lgslcblas -lc -lgcc -lm -o main main.c 
