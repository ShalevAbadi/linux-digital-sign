build:
	gcc rsa.c main.c -o main.o
	chmod 777 ./main.o

clean:
	rm -f *.o

run:
	./main.o
