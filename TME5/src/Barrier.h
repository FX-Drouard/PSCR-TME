/*
 * Barrier.h
 *
 *  Created on: 20 oct. 2023
 *      Author: 28708645
 */

#ifndef BARRIER_H_
#define BARRIER_H_
#include <condition_variable>
#include <vector>
#include <thread>

namespace pr{
	class Barrier{
		mutable std::mutex m;
		std::condition_variable cond;
		int cpt;
		const int goal;
		public :
			void done(){
				std::unique_lock<std::mutex> lg(m);
				cpt++;
				if(cpt==goal){
					cond.notify_all();
				}
			}
			void waitFor(){
				std::unique_lock<std::mutex> lg(m);
				while(cpt !=goal){
					cond.wait(lg);
				}
			}
	};

}



#endif /* BARRIER_H_ */
