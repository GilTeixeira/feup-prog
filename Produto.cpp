#include "Produto.h"

//alt 10/05
Produto::Produto(ifstream & in){ // nome ; custo
	string nome_aux;
	getline(in, nome_aux, ';');
	nome_aux.erase(nome_aux.end() - 1); //apaga o espaco final
	//nome_aux.at(0) = toupper(nome_aux.at(0)); // converte a 1ª letra para maiscula
	nome = nome_aux;
	in >> custo;  in.ignore();

}

string Produto::getNome() const {
	return nome;
}

float Produto::getCusto() const {
	return custo;
}


//incompleto ???
ostream& operator<<(ostream& out, const Produto & prod){
	out << prod.getNome() << " ; " << prod.getCusto();
	return out;
}

//alt 10/05
bool operator<(const Produto &prod1, const Produto &prod2){
	char p1 = prod1.getNome().at(0); //1 letra do prod1
	char p2 = prod2.getNome().at(0); //1 letra do prod2

	return p1 < p2;

	/*
	if ((int)p1 > (int)p2)
		return true;
	else return false;
	*/
}


//////////////////////
// Leitura ficheiro //
//////////////////////

vector<Produto> le_fichProdutos(string fichProdutos){
	ifstream f_produtos;
	vector<Produto> v_produtos;
	int num_produtos;

	f_produtos.open(fichProdutos);

	f_produtos >> num_produtos; f_produtos.ignore();

	while (num_produtos)
	{
		Produto prod(f_produtos);
		v_produtos.push_back(prod);
		num_produtos--;
	}
	f_produtos.close();

	return v_produtos;
}
