#ifndef __BLOCKING_QUEUE_H__
#define __BLOCKING_QUEUE_H__

#include <queue>
#include <thread>
#include <string>
#include <list>
#include <iostream>

using namespace std;

template<class T>
class BlockingQueue
{

private:
	queue<T> theQueue;
	pthread_mutex_t mutex_queue;
	pthread_cond_t cond;
public:
	BlockingQueue(){
			pthread_mutex_init(&mutex_queue, NULL);
			pthread_cond_init(&cond, NULL);
		}

	T pop() {
		//cout << "POP - locking mutex" << endl;
		pthread_mutex_lock(&mutex_queue);
		if (theQueue.empty()) { //we need to wait if there is nothing in the queue!
			//cout << "POP - waiting..." << endl;
			pthread_cond_wait(&cond, &mutex_queue);
		}
		//cout << "POP - reading front" << endl;
		T ret = theQueue.front();
		theQueue.pop();
		//cout << "POP - unlocking mutex" << endl;
		pthread_mutex_unlock(&mutex_queue);
		return ret;
	}

	void push(T object) {
		pthread_mutex_lock(&mutex_queue);

		theQueue.push(object);
		//cout << "PUSH - Queue length: " << theQueue.size() << endl;

		//cout << "PUSH - unlocking mutex" << endl;
		pthread_mutex_unlock(&mutex_queue);
		//cout << "PUSH - signaling unlock" << endl;
		pthread_cond_signal(&cond);
	}

};

#endif
