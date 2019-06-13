#ifndef PESQUISA_H
#define PESQUISA_H

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

class pesquisa{
	public:
	//Construtor para a classe
	pesquisa();
	//Cria o idf e o vetor Q e inicia o processo até mostrar o resultado
	void consulta(string s);
	//Cria os vetores W
	void generate_w();
	//Printa o resultado
	void resultado();
	//Apaga todos os dados, com excessão do indice e do tamanho
	void apagar();
	
	private:
	//Quantidade de arquivos indexados
	int tamanho_;
	//Indice invertido
	map<string, map<string, double>> indice;
	//Inverse document frequency
	map<string, double> idf;
	//Vetores W
	map<string, vector<double>> w;
	//Vetor Q
	vector<double> q;
	
	friend class teste;
};
#endif