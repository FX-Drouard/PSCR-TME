#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
int main () {
	const int N = 3;
	std::cout << "main pid=" << getpid() << std::endl;
	int cpt=1;
	for (int i=1, j=N; i<=N && j==N && fork()==0 ; i++ ) {
		cpt=0;
		bool moi=true;
		int tmp=j;
		std::cout << " i:j " << i << ":" << j << std::endl;
		//std::cout<<"mon pid (LA) est le : "<< getpid()<< " et mon pere est : "<< getppid()<<std::endl;
		for (int k=1; k<=i && j==N ; k++) {
			if ( fork() == 0) {
				cpt=0;
				moi=false;
				//std::cout<<"mon pid est le : "<< getpid()<< " et mon pere est : "<< getppid()<<std::endl;
				j=0;
				std::cout << " k:j " << k << ":" << j << std::endl;
			}else{
				std::cout<<"je suis en plus le "<< getpid()<< " et j'ai cree un fils"<<std::endl;
				cpt++;
			}
		}
		if (1<=i && i<=N && tmp==N && moi){
			cpt++;
		}

	}
	std::cout<<"je suis : " << getpid()<< " et mon pere est : "<< getppid()<<std::endl;
	for (int i=0; i<cpt; i++){
		if(wait(nullptr)==-1){
			std::cout<<"J'ai trop attendu et je suis "<<getpid()<<std::endl;
		}else{
		std::cout << "je suis " << getpid()<< " et j'ai attendu mon fils"<< std::endl;}
	}
	if(wait(nullptr)!=-1){
				std::cout<<"J'ai pas assez attendu"<<std::endl;
	}
	return 0;
}
*/
