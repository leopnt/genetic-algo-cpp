CFLAGS = -Wall -g

main : main.o dna.o
	g++ $(CFLAGS) main.o dna.o -o main -I include/

main.o : src/main.cpp
	g++ $(CFLAGS) -c src/main.cpp -I include/

dna.o : src/dna.cpp
	g++ $(CFLAGS) -c src/dna.cpp -I include/