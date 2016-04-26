main:main.o 
	gcc -o main main.o

main.o:main.c copy.h get put copy
	gcc -c main.c

get:get.c copy.h
	gcc -o get get.c
copy:copy.c copy.h
	gcc -o copy copy.c
put:put.c copy.h
	gcc -o put put.c
clean:
	rm get put copy main.o main