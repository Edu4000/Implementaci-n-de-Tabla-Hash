/*----------------------------------------------------------
 * Práctica #5: Tablas hash
 * Implementación de la clase HashTable.
 *
 * Fecha: 05-Nov-2021
 * Autores:
 *           A01653868 Eduardo Angeles Guerrero
 *           A01654419 Luis Ernesto Ladrón de Guevara González
 *----------------------------------------------------------*/

#include <iostream>
#include <list>
#include <functional>
#include <vector>
using namespace std;

template<typename K, typename T>
class HashPair{
	public:
		K key;
		T value;

		HashPair(){
		}
		
		HashPair(K key, T value){
			this->key = key;
			this->value = value;
		}

		~HashPair(){
			delete &key;
			delete &value;
		}

		void print_value(){
			cout << "[" << key << "," << value << "]";;
		}

		bool operator ==(const HashPair<K,T>& other){
			return (other.key == this->key) && (other.value == this->value);
		}
};

template<typename K, typename T>
class HashTable{
	private:
		int num_buckets;
		list<HashPair<K,T>*> * table;
		int hF(K key){
			hash<K> khash;
			return (khash(key)) % num_buckets;
		}

	public:
		
		HashTable(int num_buckets = 10){ // O(1)
			this->num_buckets = num_buckets;
			table = new list<HashPair<K,T>*>[num_buckets];
		}

		~HashTable(){ // O(1)
			delete &num_buckets;
			delete table;
		}

		void clear(){ // O(n)
			for (int i = 0; i < this->num_buckets; i++){
				table[i].clear();
			}
		}

		bool contains_keys(K key){ // O(n)
			for (int i = 0; i < num_buckets; i++){
				if (table[i].fornt() == key){
					return true;
				}
			}
			return false;
		}

		T get(K key){

		}

		// TODO
		T get_or_default(K key, T default_value){

		}

		bool is_empty(){ // O(n)
			for (int i = 0; i < num_buckets; i++){
				if(table[i].size() > 0){
					return false;
				}
			}
			return true;
		}

		vector<K> keys (){ // O(n^2)
			vector<K> k_values = vector<K>();
			for (int i = 0; i < num_buckets; i++){
				for(auto dato: table[i]){
					k_values.push_back(dato->key);
				}
			}

			sort(k_values.begin(), k_values.end());
			return k_values;
		}

		bool put(K key, T dato){ // O(1)
			int posicion = hF(key);
			table[posicion].push_back(new HashPair<K,T>(key, dato));
			return true;
		}

		void put_all (const HashTable<K,T>& other){

		}

		bool remove (K key){

		}

		int size(){
			return this->num_buckets;
		}

		bool operator ==(const HashTable<K,T>& other){
			if (this->num_buckets == other.num_buckets){
				for(int i = 0; i < num_buckets; i++){
					if (this->table[i].size() == other.table[i].size()){
						if (!(this->table[i] == other.table[i])){
							return false;
						}
					}else{
						return false;
					}
				}
				return true;
			}
			return false;
		}

		void print(){
			for(int i = 0; i < num_buckets; i++){
				cout << "i: " << i;
				for(auto dato: table[i]){
					cout << "-->";
					dato->print_value();
				}
				cout << endl;
			}
		}

		void print_num(){
			for(int i = 0; i < num_buckets; i++){
				cout << "i: " << i;
				if (table[i].size() > 0) {
					cout << " k: " << table[i].front()->key;
					cout << " count: " << table[i].size();
				}
				cout << endl;
			}
		}
};