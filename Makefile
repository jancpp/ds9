Lab09: main.o  MinHeap.o MaxHeap.o BST.o Node.o
	g++ -g -std=c++11 -Wall main.o  MinHeap.o MaxHeap.o BST.o Node.o -o Lab09

main.o: main.cpp
	g++ -g -std=c++11 -Wall -c main.cpp

MinHeap.o: MinHeap.h MinHeap.cpp
	g++ -g -std=c++11 -Wall -c MinHeap.cpp

MaxHeap.o: MaxHeap.h MaxHeap.cpp
	g++ -g -std=c++11 -Wall -c MaxHeap.cpp

BST.o: BST.h BST.cpp
	g++ -g -std=c++11 -Wall -c BST.cpp

Node.o: Node.cpp Node.h
	g++ -g -std=c++11 -Wall -c Node.cpp

clean:
	rm *.o
