#pragma once

#include "Queue.h"
#include "Job.h"
#include <vector>
#include <thread>

namespace pr {

class Pool {
	Queue<Job> queue;
	std::vector<std::thread> threads;
public:
	Pool(int qsize);
	void start (int nbthread);
	void submit (Job * job) ;
	void stop(){
		queue.isBlocking(false);
		for (auto &t:threads){
			t.join();
		}
		threads.clear();
	}
	void poolWorker (Queue<Job> & queue){
		while(true){
			Job *j=queue.pop();
			if(!j){
				return;
			}
			j->run();
			delete j;
		}
	}
	~Pool() ;

};

}
