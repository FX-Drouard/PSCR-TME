/*
 * pipe.cpp
 *
 *  Created on: 17 nov. 2023
 *      Author: 28708645
 */
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <sys/wait.h>
using namespace std;
int main(int argc, char** argv){
	char* c0[argc];
	char* c1[argc];
	//PARSING
	int i=1;

	int ind = 0;
	while(argv[++ind][0] != '|');
	cout << argv[1] << endl;
	cout << argv[ind+1] << endl;
	argv[ind]=NULL;

	int tubeDesc[2];pid_t pid_fils;
	
	if (pipe(tubeDesc) == -1) {
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	
	//EXEC
	pid_t fils1=fork();
	if (fils1==-1){
		perror("fork");
		exit(EXIT_FAILURE);
	}	
	else if(fils1==0){
		dup2(tubeDesc[1],STDOUT_FILENO);
		close(tubeDesc[0]);
		close(tubeDesc[1]);
		if(execv(argv[1],(argv+i))==-1){
			perror("execv");
			exit(EXIT_FAILURE);
		}
		exit(EXIT_SUCCESS);
	}else{
		pid_t fils2=fork();
		if (fils2==-1){
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if(fils2==0){
			dup2(tubeDesc[0],STDIN_FILENO);
			close(tubeDesc[0]);
			close(tubeDesc[1]);
			if(execv(argv[ind+1],(argv+i))==-1){
				perror("execv");
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
	}
	}
	close(tubeDesc[0]);
	close(tubeDesc[1]);
	wait(NULL);
	wait(NULL);
return EXIT_SUCCESS;}
