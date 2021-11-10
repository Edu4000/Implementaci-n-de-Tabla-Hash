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

template <typename T, typename K>
void printMap(unordered_map <T, K> & map)
{
	for (auto dato : map)
	{
		cout << "key " << dato.first << "->" << "count " << dato.second << endl;
	}
}

int main() {
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
	cout << "\nPara analizar archivo FASTA por nucleotidos" << endl;

	string bases [] = {"A", "C", "G", "T"};
	string aux;
	vector<string> genoma;
	cargaWuhanFasta(genoma);

	unordered_map <char, int> nucleotides;
	unordered_map <string, int> codones;

	nucleotides['A'] = 0;
	nucleotides['C'] = 0;
	nucleotides['G'] = 0;
	nucleotides['T'] = 0;

	for (int i = 0; i < genoma.size(); i++) // Where genoma.size() is the number of nucleotide lines of the vector
	{
		for (char ch : genoma[i])
		{
			nucleotides[ch] += 1;
		}
	}

	printMap(nucleotides);

	for (string prim : bases) {
		aux.append(prim);
		for (string seg : bases) {
			aux.append(seg);
			for (string ter : bases) {
				aux.append(ter);
				codones[aux] = 0;
				aux.pop_back();
			}
			aux.pop_back();
		}
		aux.pop_back();
	}

	string aux2 = "";
	for (int i = 0; i < genoma.size(); i++)
	{
		for (int j = 0; j < genoma[i].size();  j++)
		{
			if (aux2.length() == 3)
			{
				codones[aux2] += 1;
				aux2 = "";
			}
			aux2 += genoma[i][j];
		}
	}

	cout << "\nImprimir toda la tabla" << endl;
	printMap(codones);

	cout << "\nImprimir tabla con codones de mas de 100 repeticiones" << endl;
	for (auto dato : codones){
		if (dato.second > 100)
		{
			cout << "key " << dato.first << "->" << "count " << dato.second << endl;
		}
	}

	cout << "\nTabla con las A" << endl;
	for (auto dato : codones){
		if (dato.first[0] == 'A')
		{
			cout << "key " << dato.first << "->" << "count " << dato.second << endl;
		}
	}
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
