#include "Transacao.h"



unsigned int Transacao::getIdCliente() const{
  return idCliente;
}

vector<string> Transacao::get_v_produtos() const{
	return produtos;
}

Data Transacao::get_data() const{
	return data;
}


Transacao::Transacao(ifstream & in){ // le uma transacao na forma de  idcliente ; data ; lista produtos


	string data_aux;
	string lista_prod_aux;
	vector<string> produtos_aux;
	string prod_individual;
	//int id_aux;
	
	//string lixo;
	//getline(in, lixo);

	//idcliente
	//getline(in, data_aux); 
	in >> idCliente; in.ignore(100, ';');


	//data
	getline(in, data_aux, ';');
	data_aux.erase(data_aux.begin()); data_aux.erase(data_aux.end() - 1);               //apaga 1 e último espaço
	Data data(data_aux);
	this->data = data;

	//lista de produtos
	getline(in, lista_prod_aux);

	istringstream instr(lista_prod_aux);
	while (getline(instr, prod_individual, ','))
	{
		prod_individual.erase(0, prod_individual.find_first_not_of(' '));			//remove espacos iniciais
		produtos_aux.push_back(prod_individual);
	}
	produtos = produtos_aux;


}

Transacao::Transacao(unsigned int idCliente, Data data, vector<string> produtos){
	this->idCliente = idCliente;
	this->data = data;
	this->produtos = produtos;
}

void Transacao::save(ofstream & out) const{ // transacao guardada como na forma de  idcliente ; data ; lista produtos
	out << idCliente << " ; ";

	data.save(out); // na forma DD/MM/AAAAA
	out << " ; ";
	
	for (unsigned int i = 0; i < produtos.size(); i++)
	{
		out << produtos[i];
		if (i != produtos.size() - 1)             // so poe a virgula se nao for o ultimo
			out << ", ";
	}

}


ostream& operator<<(ostream& out, const Transacao & trans){

	out << "| " << setw(6) << trans.idCliente
		<< left << "| " << setw(15) << trans.data << " | ";
	for (unsigned int j = 0; j < trans.produtos.size(); j++)
	{
		out << trans.produtos[j];
		if (j != trans.produtos.size() - 1)
			out << ", ";
	}
	out << endl;
	
	return out;
}

bool operator<(const Transacao &trans1, const  Transacao &trans2){
	return concatenar_data(trans1.data) < concatenar_data(trans2.data);

}


//////////////////////
// Leitura ficheiro //
//////////////////////

vector<Transacao> le_fichTransacoes(string fichTransacoes){
	ifstream f_transacoes;
	vector<Transacao> v_transacoes;
	int num_transacoes;

	f_transacoes.open(fichTransacoes);

	f_transacoes >> num_transacoes; f_transacoes.ignore();

	while (num_transacoes)
	{
		Transacao trans(f_transacoes);
		v_transacoes.push_back(trans);
		num_transacoes--;
	}
	f_transacoes.close();

	return v_transacoes;
}
