#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <vector>
#include <string>
#include <utility>

int main () {
	using namespace std;
	using namespace std::chrono;

	ifstream input = ifstream("./WarAndPeace.txt");

	auto start = steady_clock::now();
	cout << "Parsing War and Peace" << endl;

	size_t nombre_lu = 0;
	// prochain mot lu
	string word;
	// une regex qui reconnait les caractères anormaux (négation des lettres)
	regex re( R"([^a-zA-Z])");
	//////////////////////////////////////////////////////////////////////////
	vector<pair<string,int>> v(20);


	while (input >> word) {
		// élimine la ponctuation et les caractères spéciaux
		word = regex_replace ( word, re, "");
		// passe en lowercase
		transform(word.begin(),word.end(),word.begin(),::tolower);
		int test=-1;

		for(int i=0;i<v.size();++i){
			if(word == v[i].first){
				test=i;
				break;
			}
		}
		if(test>=0){
			v[test].second++;
		}
		else{
			pair<string,int> p=make_pair(word,1);
			v.push_back(p);
		}
		// word est maintenant "tout propre"
		if (nombre_lu % 100 == 0)
			// on affiche un mot "propre" sur 100
			cout << nombre_lu << ": "<< word << endl;
		nombre_lu++;
	}
	input.close();

	cout << "Finished Parsing War and Peace" << endl;

	auto end = steady_clock::now();
    cout << "Parsing took "
              << duration_cast<milliseconds>(end - start).count()
              << "ms.\n";
    for (pair<string,int> p : v){
    	if((p.first=="toto")||(p.first=="war")||(p.first=="peace")){
    		cout<<p.first<<" : "<<p.second<<" occurrences." <<endl;
    	}
    }
    cout << "Found a total of " << v.size() << " words." << endl;

    return 0;
}


