build:
	gcc hashFile.c rsa.c main.c -o main.o
	chmod 777 ./main.o

clean:
	rm -f *.o

sign:
	./main.o 0 $(INPUT) signature.enc rsa.private

validate_signature:
	./main.o 1 $(INPUT) signature.enc rsa.public

generate_keys:
	./main.o 2 rsa.private rsa.public
