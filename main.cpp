#include <iostream>
#include <fstream> // leer el archivo
#include <sstream>// tokenizar el string 
#include <vector>
#include <string>
#include <math.h>
#include <unordered_map>
#include <list>
#include "hashtable.h"

using namespace std;

void cargaWuhanFasta(vector<string> & datos){
  string archivo = "wuhan.fasta";
  ifstream lector(archivo);
  if(lector.fail()){
    cout << "error ";
    return;
  }

  string linea;
  getline(lector, linea); // salta el primer renglón.
  while( getline(lector, linea)){
      datos.push_back(linea);
  }
  lector.close();
}

int index_convert(char letter, int exp){
	if (letter == 'A') {
		return 0;
	} else if (letter == 'C') {
		return 1 * pow(4,exp);
	} else if (letter == 'G') {
		return 2 * pow(4,exp);
	} else {
		return 3 * pow(4,exp);
	}
}

int main() {

	/* 
	*	Llamado de funciones y ejemplos de Practica 5
	*/
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

    /*HashTable<int, int> d(1'000);
    for (int i = 0; i < 100'000; ++i) {
        d.put(i, i * 2 - 1);
    }
	d.print();*/

	
	int size = 10;
	HashTable<string, int> ba(7); // O(1)
	HashTable<string, int> aa(7); // O(1)
	// O(1)
	ba.put("hola", 10);
	ba.put("hola", 11);
	ba.put("adios", 20);
	aa.put("hola", 10);
	aa.put("hola", 11);
	aa.put("adios", 20);

	cout << (ba == aa) << endl;

	b.print(); // O(n)
	cout << "\nClearing hash table" << endl;
	b.clear(); // O(n)
	b.print(); // O(n^2)
	cout << endl;


	/* 
	*	Laboratorio de ADN
	*/
	unordered_map <int, int> mapa;
	mapa[10] = 100;
	mapa[20] = 200;
	for(auto dato : mapa){
		cout << dato.first << " " << dato.second << endl;
	}

	cout << mapa[10] << endl;
	cout << "Hello World!\n";
	vector<string> genoma;

	cargaWuhanFasta(genoma);
	cout << genoma.size() << endl;

	// Hash Table de los nucleotidos del FASTA
	cout << "\nPor analizar archivo FASTA por nucleotidos\n" << endl;
	HashTable<char, int> wuhan_bases(5);

	for (int i = 0; i < genoma.size(); i++){
		for (char ch : genoma[i]){
			wuhan_bases.put(ch,1);
		}
	}
	// Impresión de la cuenta de los nucleotidos
	wuhan_bases.print_key();
	
	// Hash Table de los codones del FASTA
	cout << "\nPor analizar archivo FASTA por codones" << endl;

	// Ejercicio 1.1
	HashTable<int, string> wuhan_codones(64); // O(1)
	int counter = 0;
	int index = 0;
	int exponent = 2;
	string aux;
	// Complejidad de ejercicio O(n^2)
	for (int i = 0; i < genoma.size(); i++){ // O(n)
		for (char ch : genoma[i]){ // O(n)
			// Usa las letras para encontrar un indice (base 4)
			index += index_convert(ch, exponent);
			exponent--;
			aux.push_back(ch);
			counter++;
			if (counter == 3){ // O(1)
				// Agrega codon a Tabla Hash
				wuhan_codones.put(index,aux); // O(1)
				// Reinicia variables auxiliares
				counter = 0;
				index = 0;
				exponent = 2;
				// Deja el string auxiliar vacio
				aux.pop_back();
				aux.pop_back();
				aux.pop_back();
			}
		}
	}

	// Ejercicio 1.2
	cout << "\nRecuento de codones" << endl;
	wuhan_codones.print_value();

	// Ejercicio 1.3
	cout << "\nImpresion de tabla hash completa" << endl;
	wuhan_codones.print();

	// Ejercicio 1.4
	
	/*
	Laboratorio del Genoma del SARS-COV2 & HashTable
	Ejercicio 1:
	Usando una tabla hash crea un contador del total de número de bases de toda la secuencia. ¿Recuerdas cuáles son los nucleótidos en un genoma?

	Ejercicio 2:

	¿Recuerdas el dogma central de la biología molecular?
	Revisa los conceptos:
	https://www.nature.com/scitable/topicpage/translation-dna-to-mrna-to-protein-393/#:~:text=During%20transcription%2C%20the%20enzyme%20RNA,encoded%20by%20the%20original%20gene.

	Revisa una transcripción -> traducción:
	http://biomodel.uah.es/en/lab/cybertory/analysis/trans.htm

	Utilizando una tabla hash:
	1. Llena la tabla con los codones (o tripletes permitidos SIN repetidos). Cada codón es una llave en una tabla hash. Imprime todas las llaves de la tabla.
	2. Encuentra todas las repeticiones de cada codón utilizando la tabla hash.
	3. Imprime el contenido de toda la tabla.
	4. Borra los codones que no tengan más de 100 repeticiones.
	5. Imprime la tabla.
	6. Imprime las repeticiones de todos los codones que inicien con A.
	*/
}