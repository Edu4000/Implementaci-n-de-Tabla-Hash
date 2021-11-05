#include <iostream>
#include <list>
#include <functional>
#include "hashtable.h"

using namespace std;

int main(){
	cout << "Hello World\n";
	hash<string> hstring;
	cout << hstring("L009966007") << endl;

	int llaves[] = {9818, 9342, 5812, 5607, 2388, 9035, 6575, 8363, 6610, 191};
	HashTable<int,int> tabla(11);
	hash<int> hint;
	
	for(int i =0; i < 10; i++){
		tabla.put(hint(llaves[i]), llaves[i]);
	}

	tabla.put(1191, 500);
	tabla.print();

	cout << tabla.get(1191) << endl;
	cout << tabla.get(500) << endl;

	tabla.clear();
	tabla.print();

	list<int>* lista = new list<int>[10];
	lista->push_back(10);
}