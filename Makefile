CCFLAGS = -std=c++0x

main.exe:  main.o
	g++ main.o -o main.exe

main.o: main.cpp nodes.h
	g++ $(CCFLAGS) -c main.cpp -o main.o

clean:
	rm *.o *.exe