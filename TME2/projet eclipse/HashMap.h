/*
 * HashMap.h
 *
 *  Created on: 29 sept. 2023
 *      Author: 28708645
 */
// ON MET TOUT DANS LE .h RIEN NE MARCHE (ACCORD DU PROF)

#ifndef HASHMAP_H_
#define HASHMAP_H_
#include <vector>
#include <utility>

using namespace std;

template <typename K,typename V>

class HashMap {
	vector<pair<K,V>> hm;
	public:

		HashMap(size_t size){

		}
		pair<K,V> operator[](int index);
		void addPair(pair<K,V> p);
		void deletePair(pair<K,V>p);
		pair<K,V> getPair(int x);
		pair<K,V> getByKey(K k);
		virtual ~HashMap();
};


#endif /* HASHMAP_H_ */
