#include <iostream>
#include <fstream> // leer el archivo
#include <sstream>// tokenizar el string
#include <vector>
#include <string>
#include <unordered_map>

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
		cout << dato.first << "->" << dato.second << endl;
	}
}

int main() {

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
			cout << dato.first << " " << dato.second << endl;
		}
	}

	cout << "\nTabla con las A" << endl;
	for (auto dato : codones){
		if (dato.first[0] == 'A')
		{
			cout << dato.first << " " << dato.second << endl;
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
