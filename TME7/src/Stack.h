#pragma once

#include <cstring> // size_t,memset
//mutex et semafore
#include <mutex>
#include <semaphore.h>
#include <iostream>

namespace pr {
using namespace std;

#define STACKSIZE 100

template<typename T>
class Stack {
	T tab [STACKSIZE];
	size_t sz;
	//generer 3 semafore
	sem_t smutex;
	sem_t sprod;
	sem_t scons;
public :
	Stack () : sz(0) { memset(tab,0,sizeof tab) ;
		sem_init(&smutex,1,1);
		sem_init(&sprod,1,STACKSIZE);
		sem_init(&scons,1,0);
	}

	T pop () {
		// bloquer si vide
		cout<<"scons cons"<<endl;
		sem_wait(&scons);
		cout<<"smutex cons"<<endl;
		sem_wait(&smutex);
		T toret = tab[--sz];
		cout<<"smutexv cons"<<endl;
		sem_post(&smutex);
		cout<<"sprodv cons"<<endl;
		sem_post(&sprod);
		return toret;
	}

	void push(T elt) {
		//bloquer si plein
		cout<<"sprod"<<endl;
		sem_wait(&sprod);
		cout<<"smutex"<<endl;
		sem_wait(&smutex);
		tab[sz++] = elt;
		cout<<"smutexv"<<endl;
		sem_post(&smutex);
		cout<<"sconsv"<<endl;
		sem_post(&scons);

	}
};

}
