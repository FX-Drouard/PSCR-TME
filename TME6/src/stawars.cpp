/*
 * stawars.cpp
 *
 *  Created on: 27 oct. 2023
 *      Author: 28708645
 */



#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

handlerInt(int sig){
	if()
}

void attaque (pid_t adversaire){
	//PHASE 1 : gestion signal
	signal(SIGINT,[&](int sig));
	//PHASE 2 : envoie un signal SIGINT à l'adversaire
	//PHASE 3 : le processus s'endort
}


void defense(){
	//PHASE 1 :  désarmer le signal SIGINT
	//PHASE 2 : le processus s'endort
}
void combat(pid_t adversaire) {
	while(true){
		defense();
		attaque(adversaire);
	}
}


int main () {
	int pv=3;
	pid_t cible, luc;
	sigset set;
	SIGPROCMASK;
	pid_t luke= fork();
	if(luke== 0){
		std::cout<< "I am Luke of pid "<<getpid()<<std::endl;
		sleep(1);
		cible=getppid();
	}else{
		std::cout<< "I am Vador of pid "<<getpid()std::endl;
		sleep(1);
		cible=luke;
	}
	combat(cible);




}

