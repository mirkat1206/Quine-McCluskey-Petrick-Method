CC = g++

hw1.o : main.cpp Quine_McCluskey.o Petrick_Method.o
	$(CC) -o hw1.o main.cpp Quine_McCluskey.o Petrick_Method.o

Quine_McCluskey.o : Quine_McCluskey.h Quine_McCluskey.cpp
	$(CC) -c Quine_McCluskey.cpp

Petrick_Method.o : Petrick_Method.h Petrick_Method.cpp
	$(CC) -c Petrick_Method.cpp

clean :
	rm *.o
