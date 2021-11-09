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
		int hF(K key){
			hash<K> khash;
			int index = (khash(key)) % num_buckets;
			if (num_buckets > 80) {
				while (table[index].size() > 0){
					if (table[index].front()->key == key){
						return index;
					}
					index++;
				}
			}
			return index;
		}

	public:
		list<HashPair<K,T>*> * table;
		
		// O(1)
		HashTable(int num_buckets = 10){ 
			this->num_buckets = num_buckets;
			table = new list<HashPair<K,T>*>[num_buckets];
		}
		
		// O(1)
		~HashTable(){ 
			delete &num_buckets;
			delete table;
		}

		// O(n)
		void clear(){ 
			for (int i = 0; i < this->num_buckets; i++){
				table[i].clear();
			}
		}

		// O(n)
		bool contains_keys(K key){ 
			for (int i = 0; i < num_buckets; i++){
				if (table[i].front() == key){
					return true;
				}
			}
			return false;
		}

		// O(n)
		T get(K key){
			HashPair<K,T>* aux = new HashPair<K,T> ();
			int index = hF(key);
			try
			{
				for (int i = 0; i < table[index].size(); i++){
					aux = table[index].front();
					table[index].pop_front();
					if (aux->key == key){
						return aux->value;
					}
				}
			}
			catch(const std::invalid_argument& e)
			{
				std::cerr << e.what() << '\n';
			}
		}

		// O(n)
		T get_or_default(K key, T default_value){
			HashPair<K,T>* aux = new HashPair<K,T> ();
			int index = hF(key);
			for (int i = 0; i < table[index].size(); i++){
				aux = table[index].front();
				table[index].pop_front();
				if (aux->key == key){
					return aux->value;
				}
			}
			return default_value;
		}
		
		// O(n)
		bool is_empty(){ 
			for (int i = 0; i < num_buckets; i++){
				if(table[i].size() > 0){
					return false;
				}
			}
			return true;
		}

		// O(n^2)
		vector<K> keys (){ 
			vector<K> k_values = vector<K>();
			for (int i = 0; i < num_buckets; i++){
				for(auto dato: table[i]){
					k_values.push_back(dato->key);
				}
			}
			sort(k_values.begin(), k_values.end());
			return k_values;
		}

		// O(n) if replace is TURE and O(1) if replace is FALSE
		bool put(K key, T value){ 
			int posicion = hF(key);
			table[posicion].push_back(new HashPair<K,T>(key, value));
			return true;
		}

		// O(n)
		void put_all (const HashTable<K,T>& other){
			for(int i = 0; i < other.num_buckets; i++){
				for(auto dato : other.table[i]){
					this->put(dato->key, dato->value);
				}
			}
		}

		// O(n)
		bool remove (K key){ 
			HashPair<K,T>* aux = new HashPair<K,T> ();
			int index = hF(key);
			for (int i = 0; i < table[index].size(); i++){
				aux = table[index].front();
				table[index].pop_front();
				if (aux->key == key){
					return true;
				} else {
					table[index].push_back(aux);
				}
			}
			return false;
		}

		// O(1)
		bool remove_all (K key){ 
			HashPair<K,T>* aux = new HashPair<K,T> ();
			int index = hF(key);
			table[index].clear();
			return true;
		}

		// O(1)
		int size(){ 
			return this->num_buckets;
		}

		// O(n^2)
		bool operator ==(const HashTable<K,T>& other){ 
			HashPair<K,T>* aux1 = new HashPair<K,T>();
			HashPair<K,T>* aux2 = new HashPair<K,T>();

			if (this->num_buckets == other.num_buckets){
				for(int i = 0; i < num_buckets; i++){
					if (this->table[i].size() == other.table[i].size()){
						for (int j = 0; j < table[i].size(); j++){
							aux1 = this->table[i].front();
							this->table[i].pop_front();
							this->table[i].push_back(aux1);

							aux2 = other.table[i].front();
							other.table[i].pop_front();
							other.table[i].push_back(aux2);

							if (aux1->key != aux2->key || aux1->value != aux2->value){
								return false;
							}
						}
					}else{
						return false;
					}
				}
				return true;
			}
			return false;
		}

		// O(n^2)
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

		// O(n^2)
		void print_key(){ 
			for(int i = 0; i < num_buckets; i++){
				cout << "i: " << i;
				if (table[i].size() > 0) {
					cout << " k: " << table[i].front()->key;
					cout << " count: " << table[i].size();
				}
				cout << endl;
			}
		}

		// O(n^2)
		void print_value(){ 
			for(int i = 0; i < num_buckets; i++){
				cout << "i: " << i;
				if (table[i].size() > 0) {
					cout << " k: " << table[i].front()->value;
					cout << " count: " << table[i].size();
				}
				cout << endl;
			}
		}

		// O(n^2)
		void print_value(int lower_bound, int upper_bound){ 
			for(int i = lower_bound; i < upper_bound; i++){
				cout << "i: " << i;
				if (table[i].size() > 0) {
					cout << " k: " << table[i].front()->value;
					cout << " count: " << table[i].size();
				}
				cout << endl;
			}
		}
};