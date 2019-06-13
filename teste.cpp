#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "pesquisa.h"

#include <string>
#include <map>
#include <cmath>
#include <vector>

using std::string;
using std::vector;
using std::map;

class teste{
	public:
	static map<string, map<string, double>> indice_(pesquisa p){
		return p.indice;
	}
	static map<string, double> idf_(pesquisa p){
		return p.idf;
	}
	static map<string, vector<double>> w_(pesquisa p){
		return p.w;
	}
	static vector<double> q_(pesquisa p){
		return p.q;
	}
	static int tamanho(pesquisa p){
		return p.tamanho_;
	}
};

TEST_SUITE("pesquisa"){
	TEST_CASE("pesquisa::pesquisa()"){
		pesquisa p;
		map<string, map<string, double>> x = teste::indice_(p);
		CHECK(x["a"]["a0.txt"] == 3.0);
		CHECK(x["a"]["a1.txt"] == 2.0);
		CHECK(x["a"]["a2.txt"] == 2.0);
		CHECK(x["b"]["a0.txt"] == 1.0);
		CHECK(x["b"]["a3.txt"] == 2.0);
		CHECK(x["c"]["a1.txt"] == 1.0);
		CHECK(x["d"]["a4.txt"] == 2.0);
		CHECK(x["e"]["a4.txt"] == 1.0);
		CHECK(teste::tamanho(p) == 5);
	}
	TEST_CASE("void consulta(string)"){
		pesquisa p;
		p.consulta("a b g");
		map<string, double> i = teste::idf_(p);
		vector<double> qx = teste::q_(p);
		CHECK(i["a"] >= 0.51);
		CHECK(i["b"] >= 0.91);
		CHECK(qx[0] >= 0.51);
		CHECK(qx[1] >= 0.91);
	}
	TEST_CASE("void generate_w()"){
		pesquisa p;
		p.consulta("a b g");
		map<string, vector<double>> wx = teste::w_(p);
		CHECK(wx["a0.txt"][0] >= 1.53);
		CHECK(wx["a0.txt"][1] >= 0.91);
		CHECK(wx["a1.txt"][0] >= 1.02);
		CHECK(wx["a1.txt"][1] == 0.0);
		CHECK(wx["a2.txt"][0] >= 1.02);
		CHECK(wx["a2.txt"][1] == 0.0);
		CHECK(wx["a3.txt"][0] == 0.0);
		CHECK(wx["a3.txt"][1] >= 1.83);
	}
	TEST_CASE("void apagar()"){
		pesquisa p;
		p.consulta("a b g");
		p.apagar();
		CHECK(teste::q_(p).size() == 0.0);
		CHECK(teste::idf_(p).size() == 0.0);
		CHECK(teste::w_(p).size() == 0.0);
	}
}
