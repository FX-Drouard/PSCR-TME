#include "Banque.h"
#include "unistd.h"
#include <iostream>
using namespace std;
using namespace pr;

const int NB_THREAD = 10;

void work (Banque & b){
	size_t i = std::rand() % b.size();
	size_t j = std::rand() % b.size();
	unsigned int m = std::rand() % 100+1;
	b.transfert(i,j,m);
	size_t t= std::rand() % 20;
	std::this_thread::sleep_for(std::chrono::milliseconds(t));

}

void shift(int id,Banque & b){
	std::cout<<"Start Shift "<<id<<std::endl;
	for(int i=0;i<1000;i++){
		work(b);
	}
	std::cout<<"End Shift "<<id<<std::endl;
}

void comptable(Banque & b){
	std::cout<<"\tStart Shift COMPTABLE "<<std::endl;
	for (int i=0;i<10;i++){
		b.comptabiliser(2000*100);
	}
	std::cout<<"\tEND Shift COMPTABLE "<<std::endl;
}
int main () {
	Banque bank= Banque(2000, 100);
	std::cout << "banqye created" << std::endl;
	vector<thread> threads;
	// TODO : creer des threads qui font ce qui est demandé
	std::cout<<"I START"<<std::endl;

	for (int i=0; i<NB_THREAD; ++i){
		std::cout<<"CREATE "<<i<<std::endl;
		threads.emplace_back(shift, i, std::ref(bank));
	}
	threads.emplace_back(comptable,std::ref(bank));
	for (auto & t : threads) {
		t.join();
	}

	// TODO : tester solde = NB_THREAD * JP
	return 0;
}
