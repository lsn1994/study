#include <iostream>
#include <unistd.h>
#include <queue>
#include <pthread.h>
#include <stdlib.h>
#include <string>

using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t emp = PTHREAD_COND_INITIALIZER;   

const int queue_length = 100;
queue<int> product;

void* producer(void *arg);
void* consumer(void *arg);

int main(int argc, char* argv[]){
    pthread_t producer_id;
    pthread_t consumer_id;
    int producer_amount = atoi(argv[1]);
    int consumer_amount = atoi(argv[2]);

    cout << "Producer amount:" << producer_amount << endl;
    cout << "Consumer amount:" << consumer_amount << endl;

    for(int i = 0; i < producer_amount; i++){
        string s = "producer" + to_string(i);
        pthread_create(&producer_id, NULL, producer,(void*)&s);        
    }

    for(int i = 0; i < consumer_amount; i++){
        string s = "consumer" + to_string(i);
        pthread_create(&consumer_id, NULL, consumer, (void*)&s);
    }

    sleep(10);
    return 0;
}

void *producer(void *arg){
    pthread_detach(pthread_self());
    string username = *(string*)arg;

    while(true){
        pthread_mutex_lock(&mutex);
        while(product.size() == queue_length){
            cout << "The buffer is full. Producer is waiting..." << endl;
            pthread_cond_wait(&full, &mutex);
        }
        product.push(random()%10000);
        usleep(1000);
        cout << "Producer " << username <<" creates No." << product.size() << ": " << product.back() << endl; 
        if(product.size() == 1){
            pthread_cond_broadcast(&emp);
        } 
        pthread_mutex_unlock(&mutex); 
    }	
}

void *consumer(void *arg){
    pthread_detach(pthread_self());
    string username = *(string *)arg;

    while(true){
        pthread_mutex_lock(&mutex);
        while(product.size() == 0){
            cout << "There is no product in buffer. Consumer is waiting...." << endl;
            pthread_cond_wait(&emp, &mutex);
        }

        cout << "Consumer " << username << " consumes No." << product.size() << ": " << product.front()<< endl;		
        product.pop();
        usleep(1000);
        if(product.size() == queue_length - 1){
            pthread_cond_broadcast(&full);
        }
        pthread_mutex_unlock(&mutex);

    }
}
