#include <iostream>
#include <list>
#include <functional>
#include "hashtable.h"

using namespace std;

int main(){
	/*cout << "Hello World\n";
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
	lista->push_back(10);*/

	HashTable<double, bool> a(25);
    HashTable<string, int> b(7);
    b.put("one", 1);
    b.put("two", 2);
    b.put("three", 3);
    b.put("four", 4);
    b.put("five", 5);
    b.put("six", 6);
    b.put("seven", 7);
	b.print();

    HashTable<int, string> c(99);
    c.put(1, "I");
    c.put(2, "II");
    c.put(3, "III");
    c.put(4, "IV");
    c.put(5, "V");
    c.put(6, "VI");
    c.put(7, "VII");
    c.put(8, "VIII");
    c.put(9, "IX");
    c.put(10, "X");
    c.put(11, "XI");
    c.put(12, "XII");
    c.put(13, "XIII");
    c.put(14, "XIV");
    c.put(15, "XV");
    c.put(16, "XVI");
    c.put(17, "XVII");
    c.put(18, "XVIII");
    c.put(19, "XIX");
    c.put(20, "XX");
    c.put(50, "L");
    c.put(100, "C");
    c.put(500, "D");
    c.put(1'000, "M");
	c.print();

    HashTable<int, int> d(1'000);
    for (int i = 0; i < 100'000; ++i) {
        d.put(i, i * 2 - 1);
    }
	d.print();

}