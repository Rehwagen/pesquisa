#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include "fatorial.h"
#include <algorithm>

using namespace std;

int main(){
	string s;
	unsigned int i, t;
	cout << "Digite as letras (no numero de vezes de cada letra) que voce quer que sejam emaranhadas (sem espacos): " << endl;
	cin >> s;
	ofstream lista;
	lista.open("nomes.txt");
	if(!lista.is_open()){
		cout << "Problema na criação/manipulacao do arquivo!" << endl;
		return 1;
	}
	t = fatorial(s.size());
	cout << "Numero de palavras: " << t << endl;
	i = 1;
	sort(s.begin(), s.end());
	lista << s << '\n';
	while(next_permutation(s.begin(), s.end())){
		lista << s << '\n';
		i++;
		if(i == t/100){
			cout << '*';
			i = 0;
		}
	}
	lista.close();
	return 0;
}