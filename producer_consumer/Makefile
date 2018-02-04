default target: all

producer.o: producer.cpp producer.h
	g++ -g -c -std=c++11 producer.cpp -o producer.o

consumer.o: consumer.cpp consumer.h
	g++ -g -c -std=c++11 consumer.cpp -o consumer.o

main.o: main.cpp
	g++ -g -c -std=c++11 main.cpp -o main.o

all: producer.o consumer.o main.o
	g++ main.o producer.o consumer.o -lpthread -o producer_consumer

clean:
	rm -f *.o producer_consumer



