#pragma once

#include "Compte.h"
#include <vector>
#include <iostream>

namespace pr {

class Banque {
	typedef std::vector<Compte> comptes_t;
	comptes_t comptes;
	//mutable std::mutex *mtx;
public :
	Banque (size_t ncomptes, size_t solde) : comptes(ncomptes, Compte(solde)){
		//mtx = new std::mutex();
	}
//	Banque (const Banque & other) {
//		std::cout << "copy called" << std::endl;
//		other.mtx.lock();
////		this->comptes = other.comptes;
//		other.mtx.unlock();
//	}
	void transfert(size_t deb, size_t cred, unsigned int val) ;
	size_t size() const ;
	bool comptabiliser (int attendu) const ;
};

}
