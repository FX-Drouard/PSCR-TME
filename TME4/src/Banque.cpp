#include "Banque.h"

#include <iostream>

using namespace std;

namespace pr {

void Banque::transfert(size_t deb, size_t cred, unsigned int val) {
	Compte & debiteur = comptes[deb];
	Compte & crediteur = comptes[cred];
	std::recursive_mutex & deb_mtx= debiteur.getMutex();
	std::recursive_mutex & cre_mtx= crediteur.getMutex();
	deb_mtx.lock();
	cre_mtx.lock();
	if (debiteur.debiter(val)) {
		crediteur.crediter(val);
	}
	deb_mtx.unlock();
	cre_mtx.unlock();
	return;
}
size_t Banque::size() const {
	return comptes.size();
}
bool Banque::comptabiliser (int attendu) const {
	int bilan = 0;
	int id = 0;
	for (const auto & compte : comptes) {
		Compte c=(Compte)compte;
		std::recursive_mutex & mtx= c.getMutex();
		mtx.lock();
		//mtx->lock();
		if (compte.getSolde() < 0) {
			cout << "Compte " << id << " en négatif : " << compte.getSolde() << endl;
		}
		bilan += compte.getSolde();
		id++;
		mtx.unlock();
		//mtx->unlock();
	}
	if (bilan != attendu) {
		cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << endl;
	}
	return bilan == attendu;
}
}
