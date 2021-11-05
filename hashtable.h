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

	~HashPair(){
		delete this->key;
		delete this->value;
	}
};

template<typename K, typename T>
class HashTable{
	private:
		int size;
		list<HashPair<K,T>> * table;
		int h(K key){
			hash<K> khash;
			return (khash(key) * 3) % size;
		}

	public:
		
		HashTable(int num_buckts){
			this->size = num_buckts;
			table = new list<HashPair<K,T>>[size];
		}

		~HashTable(){
			for (int i = 0; i < this->size; i++){
				for (auto hPair : table){
					~hPair;
				}
			}
			delete this->size;
			delete this->table;
		}

		void clear(){
			for (int i = 0; i < this->size; i++){
				for (auto hPair : table){
					~hPair;
				}
			}
		}

		bool contains_keys(K key){

		}

		T get (K key){

		}

		T get_or_default(K key, T default_value){

		}

		bool is_empty(){

		}

		std::vector<K> keys(){

		}

		bool put (K key, Y values){

		}

		void put_all (const HashTable<K,T>& other){

		}

		bool remove (K key){

		}

		int size(){

		}

		bool operator ==(const HashTable<K,T>& other){

		}



		bool put(K key, T dato){
			int posicion = h(key);
			table[posicion] = HashPair<K,T>(key, dato);
			return true;
		}

		T get(K key){
			return table[h(key)].value;
		}

		void print(){
			for(int i = 0; i < size; i++){
				cout << "i: " << i;
				cout << " k: " << table[i].key;
				cout << " --> " << table[i].value;
				cout << endl;
			}
		}
};