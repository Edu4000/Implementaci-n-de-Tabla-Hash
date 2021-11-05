/*----------------------------------------------------------
 * Práctica #5: Tablas hash
 * Implementación de la clase HashTable.
 *
 * Fecha: 05-Nov-2021
 * Autores:
 *           A01653868 Eduardo Angeles Guerrero
 *           A01777771 Loki Laufeyson
 *----------------------------------------------------------*/

#include <iostream>
#include <list>
#include <functional>
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

	void print_value(){
		cout << value;
	}

	/*~HashPair(){
		delete this->key;
		delete this->value;
	}*/
};

template<typename K, typename T>
class HashTable{
	private:
		int num_buckts;
		list<HashPair<K,T>> * table;
		int hF(K key){
			hash<K> khash;
			return (khash(key) * 3) % num_buckts;
		}

	public:
		
		HashTable(int num_buckts = 10){
			this->num_buckts = num_buckts;
			table = new list<HashPair<K,T>>[num_buckts];
		}

		/*~HashTable(){
			for (int i = 0; i < this->size; i++){
				for (auto hPair : table){
					~hPair;
				}
			}
			delete this->size;
			delete this->table;
		}*/

		void clear(){
			for (int i = 0; i < this->num_buckts; i++){
				table[i].clear();
			}
		}

		bool contains_keys(K key){

		}

		bool put(K key, T dato){
			int posicion = hF(key);
			table[posicion].push_back(HashPair<K,T>(key, dato));
			return true;
		}

		T get(K key){
			return table[hF(key)].back().value;
		}

		void print(){
			for(int i = 0; i < num_buckts; i++){
				cout << "i: " << i;
				for(auto dato: table[i]){
					cout << "-->";
					dato.print_value();
				}
				cout << endl;
			}
		}

		T get_or_default(K key, T default_value){

		}

		bool is_empty(){

		}

		void put_all (const HashTable<K,T>& other){

		}

		bool remove (K key){

		}

		bool operator ==(const HashTable<K,T>& other){

		}
};