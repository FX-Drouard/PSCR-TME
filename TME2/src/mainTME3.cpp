#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <utility>
#include "hashmap.h"	
#include "tools.h"
using namespace std;


// Fonction qui récupère le nombres d'occurences d'un mot dans le vecteur vec
// retourne le nombre de mots
int getCountForWord(const std::string word, const std::vector<std::pair<std::string, int>>* vec) {
	// Vérification de la présence du mot word dans vec
	for(unsigned int i=0; i<vec->size(); ++i){
		if(vec->at(i).first == word){
			// Le mot existe
			return vec->at(i).second;
		}
	}
	// Le mot n'existe pas
	return 0;
}

// Fonction qui vérifie si un mot est présent dans le vecteur (en parcourant le vecteur)
// Incrémente le compte de 1 si le mot existe déjà
// retourne 1 si mot déjà lu
// retourne 0 sinon
bool isWordAlreadyRead(std::string word, std::vector<std::pair<std::string, int>> * vec){
	// Vérification de la présence du mot word dans vec
	for(unsigned int i=0; i<vec->size(); ++i){
		if(vec->at(i).first == word){
			// Le mot existe
			vec->at(i).second++;
			return true;
		}
	}
	return false;
}

int main () {
	using namespace std;
	using namespace std::chrono;

	vector<string> vec;
	vec.push_back("obo");
	vec.push_back("ababab");
	vec.push_back("ab");
	vec.push_back("iibibi");
	vec.push_back("ababab");
	cout<<"size egale: "<<vec.size()<<" et count egale: "<< pr::count(vec.begin(), vec.end())<<endl;
	

	// Vecteur qui contient les mots déjà lus avec leur nombre d'occurences
	vector<pair<string, int>> readWords;
	vector<string> tabString(10);
	// HashMap comportant les mots (key : mot, value : nb d'occurences)
	pr::HashMap<string, int> wordsMap = pr::HashMap<string, int>(600000);

	ifstream input = ifstream("../tmp/WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);

		// UTILISATION HASHMAP
		// Vérification si le mot est déjà lu et récupération de son nombre d'occurences
		int wordCount;
		if (wordsMap.get(word) != nullptr) { // le mot est dans la table
			wordCount = *wordsMap.get(word);
		} else { // le mot n'est pas dans la table
			wordCount = 0;
		}

		// Ajout du mot dans la table (ou mise à jour de l'entrée) avec son nombre d'occurences
		wordsMap.put(word, ++wordCount);
		tabString.push_back(word);
		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;

		// AVANT UTILISATION DU HASHMAP
		/*
		// Vérification si le mot est déjà lu (dans le vecteur readWords)
		if(isWordAlreadyRead(word, &readWords)) {
			continue; // l'incrément du compte de 1 se fait dans la fonction
		} else {
			// Ajout du nouveau mot dans le vecteur (compte de 1)
			readWords.push_back(make_pair(word, 1));
		}
		*/
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";

    cout << "Found a total of " << nombre_lu << " words." << endl;

	return 0;
}


