#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <string>
#include <sstream>
#include "pesquisa.h"

using namespace std;

int main(){
	string palavras;
	pesquisa p;
	while(1){
		cout << "Digite o que deseja pesquisar:" << endl;
		getline(cin, palavras);
		p.consulta(palavras);
		p.apagar();
		cout << "-----------------------" << endl;
	}
	return 0;
}