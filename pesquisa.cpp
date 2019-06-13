#include <sstream>
#include <map>
#include <string>
#include <fstream>
#include <cmath>
#include <iostream>
#include <vector>
#include "pesquisa.h"

using namespace std;

pesquisa::pesquisa(){ //Usado para colocar na memória as palavras que aparecem nos respectivos documentos
	indice.clear();
	w.clear();
	q.clear();
	idf.clear();
	int i, j;
	tamanho_ = 0;
	string f, t = "23", s;
	ifstream d0, d1;
	d1.open("arquivos.txt");
	if(!d1.is_open()){
		cout << "Erro no arquivo de indexacao!" << endl;
		exit (1);
	}
	while(!d1.eof()){
		tamanho_++;
		getline(d1, f);
		d0.open(f);
		while(!d0.eof()){
			getline(d0, t); //Primeiro pega a linha e depois filtra a linha, separando as palavras
			stringstream h;
			h << t;
			while(getline(h, s, ' ')){
				for(j = 0; j < s.size(); j++){
					if((s[j] > 64) && (s[j] < 91)){ //Transforma maiusculas em minusculas
						s[j] += 32;
					}
					if(!((s[j] > 96) && (s[j] < 123))){ //Retira acentos e simbolos
						s.erase(j, 1);
						j--;
					}
				}
				if(s[0] != '\0'){ //Testa se a string possui algo
					indice[s][f]++;
				}
			}
		}
		d0.close();
	}
}

void pesquisa::consulta(string s){
	map<string, double> np;
	int i = 0, j = 0, n = 0;
	for(i = 0; i < s.size(); i++){
		if(s[i] == ' '){
			n++;
		}
	}
	n++;
	string aux;
	stringstream h;
	h << s;
	for(i = 0; getline(h, aux, ' '); i++){
		for(j = 0; j < aux.size(); j++){
			if((aux[j] > 64) && (aux[j] < 91)){ //Transforma maiusculas em minusculas
				aux[j] += 32;
			}
			if(!((aux[j] > 96) && (aux[j] < 123))){ //Retira acentos e simbolos
				aux.erase(j, 1);
				j--;
			}
		}
		if(aux[0] != '\0'){ //Testa se a string possui algo
			idf[aux] = 0.0;
			np[aux] += 1.0;
		}
	}
	for(map<string, double>::iterator it = np.begin(); it != np.end(); ++it){
		for(map<string, map<string, double>>::iterator it1 = indice.begin(); it1 != indice.end(); ++it1){
			if(it->first == it1->first){
				q.push_back(it->second);
			}
		}
	}
	i = 0;
	for(map<string, double>::iterator it_idf = idf.begin(); it_idf != idf.end(); ++it_idf){ //Cria o idf e o vetor q
		for(map<string, map<string, double>>::iterator it = indice.begin(); it != indice.end(); ++it){
			if(it_idf->first == it->first){
				for(map<string, double>::iterator it1 = it->second.begin(); it1 != it->second.end(); ++it1){
					it_idf->second = it_idf->second + 1.0;
					w[it1->first];
				}
				it_idf->second = log(tamanho_ / it_idf->second);
				q[i] *= it_idf->second;
				i++;
			}
		}
		if(it_idf->second == 0){
			idf.erase(it_idf->first);
		}
	}
	generate_w();
}

void pesquisa::generate_w(){
	int i;
	for(map<string, vector<double>>::iterator it_w = w.begin(); it_w != w.end(); ++it_w){ //Cria o vetor w
		i = 0;
		for(map<string, double>::iterator it_idf = idf.begin(); it_idf != idf.end(); ++it_idf){
			for(map<string, map<string, double>>::iterator it = indice.begin(); it != indice.end(); ++it){
				if(it_idf->first == it->first){ //Localiza a palavra do idf no indice
					it_w->second.push_back(0);
					for(map<string, double>::iterator it1 = it->second.begin(); it1 != it->second.end(); ++it1){
						if(it_w->first == it1->first){
							it_w->second[i] = it1->second * it_idf->second; //Se a palavra existe no documento, calcula sua coordenada
						}
					}
				}
			}
			i++;
		}
	}
	resultado();
}

void pesquisa::resultado(){
	map<string, double> resultado;
	int i;
	double qf, wf;
	string aux;
	for(map<string, vector<double>>::iterator it_w = w.begin(); it_w != w.end(); ++it_w){
		qf = 0;
		wf = 0;
		for(i = 0; i < it_w->second.size(); i++){
			resultado[it_w->first] += it_w->second[i] * q[i];
		}
		for(i = 0; i < it_w->second.size(); i++){
			wf += (it_w->second[i] * it_w->second[i]);
			qf += (q[i] * q[i]);
		}
		qf = sqrt(qf);
		wf = sqrt(wf);
		resultado[it_w->first] = resultado[it_w->first]/(qf * wf);
	}
	while(resultado.size()){
		qf = 0;
		for(map<string, double>::iterator it = resultado.begin(); it!= resultado.end(); ++it){
			if(it->second >= qf){
				aux = it->first;
				qf = it->second;
			}
		}
		cout << aux << endl;
		resultado.erase(aux);
	}
}

void pesquisa::apagar(){
	w.clear();
	idf.clear();
	q.clear();
}