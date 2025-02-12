#include <forward_list>
#include "tools.h"
#include <cstddef>
#include <ostream>
#include <forward_list>
#include <vector>

namespace pr {


    template <typename K, typename V>
    class HashMap{
        public:
        class Entry {
            public:
                const K key;
                V value;

                // Ctor
                Entry(const K key, V value): key(key), value(value) {};
        };
        private:
            typedef std::vector<std::forward_list<Entry> > buckets_t;
            buckets_t buckets;
            size_t siz;
        public:
        class iterator{
        		public:
                template<typename iterator>
                typename buckets_t::iterator vit;
                typename std::forward_list<Entry>::iterator lit;

    			iterator & operator++(){
                    if(lit++==nullptr){
                        vit++;
                        iterator tmp=vit;
                        for (int i=0;i<vit.size();i++){
                            if (tmp!=nullptr){
                                lit=vit[i];
                                break;
                            }
                            tmp++;
                        }
                    }else{
                        lit;
                    }
        		}

                bool operator!=(const iterator &other){
                    return lit!=*other;
                }
                Entry & operator*(){
                    return *lit;
                }
                iterator begin() {
                    typename buckets_t::iterator vit = buckets.begin();
                    while (vit->empty() && vit != buckets.end()) {
                        ++vit;
                    }
                    if (vit != buckets.end()) {
                        return iterator(buckets.end(),vit,vit->begin());
                    } else {
                        return end();
                    }
                }
                iterator end() {
                    return iterator(buckets.end(),buckets.end(),buckets.front().end());
                }
        };
        ///
    public:
        // CONSTRUCTEURS

        // Ctor
        HashMap(){}

        // Ctor
        HashMap(size_t size) {
            for(size_t i=0; i<size; ++i){
                buckets.push_back(std::forward_list<Entry>());
            }
        }

        // METHODES

        // get Value
        V* get(const K& key){
            size_t h = std::hash<K>()(key);
            size_t target = h % buckets.size();
            for(Entry &ent : buckets[target]) {
                if(ent.key == key)
                    return &ent.value;
            }
            return nullptr;
        }

        // put Value
        // retourne true si la valeur associée à jey a été mise à jour dans la table
        // retourne false si on a réalisé une insertion (clef pas encore dans la table)
        bool put(const K& key, const V& value){
            size_t h = std::hash<K>()(key);
            size_t target = h % buckets.size();
            // parcours des buckets (recherche si un bucket a pour clef : key)
            for(Entry &ent : buckets[target]) {
                if(ent.key == key){ // s'il existe déjà une entrée avec key pour clef
                    ent.value = value;
                    return true;
                }
            }
            // ajout de la nouvelle entrée pour key non présente dans la table dans le bucket adéquat (bon hash) ajout ds forward list
            buckets[target].push_front(Entry(key, value));
            return false;
        }

        // get Size
        size_t size() const {
            return buckets.size();
        }

        // get Begin
        auto begin() const {
            return buckets.begin();
        }

        // get End
        auto end() const {
            return buckets.end();
        }
        /// TME 3

    };


} // namespace pr
