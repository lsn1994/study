default targe: all

client.o: client.cpp
	gcc -c -g client.cpp

client: client.o
	gcc -o client client.o -lstdc++

server.o: server.cpp
	gcc -c -g server.cpp

server: server.o
	gcc -o server server.o -lstdc++

all: client server
   

clean:
	rm -f *.o server client

