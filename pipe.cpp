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

using namespace std;
int main(int argc, char** argv){
	vector<char**> cmd;
	//PARSING
	for (int i=0;i<argc;i++){
		string test=argv[i];
		if (i>0){
			string test2=argv[i-1];
			if(test.compare("|") && !(test2.compare("\\"))){
				char* newCmd[i+1];
				for (int j=0;j<i;j++){
					newCmd[j]=argv[j];
				}
				cmd.push_back(newCmd);
			}
		}

	}

	for(char** t:cmd){
		for (auto c :t){
			cout<<c<<endl;
		}
	}
	//EXEC
	return 0;
}

