#include "Stack.h"
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



using namespace std;
using namespace pr;
bool interrupt = false;

//handler de signal pour le ctrl c
void handler(int sig) {
	cout << "Signal " << sig << " reçu" << endl;
	interrupt = true;
}


void producteur (Stack<char> * stack) {
	cout << "producteur" << endl;
	char c ;
	while (cin.get(c)) {
		cout<<"push " << c <<endl;
		stack->push(c);

		
	}
}

void consomateur (Stack<char> * stack) {
	cout << "consomateur" << endl;
	while (true) {
		if (interrupt) {
			cout << "Fin du consomateur" << endl;
			return;
		}
		char c = stack->pop();
		cout << c << flush ;
		cout<<"pop"<<endl;
	}
}

int main () {
	//allocation memoire partager nommer
	int fd;
	void *ptr;
	if ((fd = shm_open("/myshm", O_RDWR|O_CREAT, 0666)) == -1) {
		perror("shm_open");
		exit(EXIT_FAILURE);
	}
	if (ftruncate(fd, sizeof(Stack<char>)) == -1) {
		perror("ftruncate");
		exit(EXIT_FAILURE);
	}
	
	if ((ptr = (Stack<char>*)mmap(NULL, sizeof(Stack<char>), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}
	Stack<char> * s = new (ptr)  Stack<char>();

	pid_t pp = fork();
	if (pp==0) {
		producteur(s);
		return 0;
	}
	cout << "fork ok prod" << endl;
	pid_t pc = fork();
	if (pc==0) {
		consomateur(s);
		return 0;
	}
	cout << "fork ok" << endl;
	wait(0);
	wait(0);

	delete s;
	munmap (s, sizeof(int));
	shm_unlink("/myshm");
	return 0;
}

