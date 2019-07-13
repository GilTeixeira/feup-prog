#include "Cliente.h"


Cliente::Cliente(ifstream & in){
	string data_aux;
	string nome_aux;

	in >> id; in.ignore(100, ';'); //id

	getline(in, nome_aux, ';'); //nome
	nome_aux.erase(nome_aux.begin()); nome_aux.erase(nome_aux.end() - 1);               //apaga 1 e último espaço
	nome = nome_aux;

	getline(in, data_aux, ';'); //data
	data_aux.erase(data_aux.begin()); data_aux.erase(data_aux.end() - 1);               //apaga 1 e último espaço
	Data data(data_aux);
	cartaoCliente = data;

	in >> volCompras; //montante
}

Cliente::Cliente(unsigned int id, string nome, Data cartaoCliente, float volCompras)
{
	this->id = id;
	this->nome = nome;
	this->cartaoCliente = cartaoCliente;
	this->volCompras = volCompras;

}
string Cliente::getNome() const{
	return nome;
}

unsigned int Cliente::getId() const{
	return id;
}

float Cliente::getVolCompras() const{
	return volCompras;
}

void Cliente::set_cartaoCliente(Data cartaoCliente){
	this->cartaoCliente = cartaoCliente;
}
void Cliente::set_nome(string nome){
	this->nome = nome;
}


void Cliente::acrescentar_quantia(float preco_prod){
	volCompras = volCompras + preco_prod;
}

void Cliente::save(ofstream & out) const{
	out << id << " ; " << nome << " ; " << cartaoCliente << " ; " << volCompras;
}

ostream& operator<<(ostream& out, const Cliente & cli){
	//out << cli.id << " ; " << cli.nome << " ; " << cli.cartaoCliente << " ; " << cli.volCompras;
	//return out;


	out << "| " << setw(5) << cli.id
		<< left << "| " << setw(40) << cli.nome << "| "
	<< setw(31) << cli.cartaoCliente << "    | "
	<< setw(7) << cli.volCompras;
	
	out << endl;

	return out;
}


bool operator<(const Cliente &cli1, const Cliente &cli2){
	char c1 = cli1.nome.at(0); //1 letra do prod1
	char c2 = cli2.nome.at(0); //1 letra do prod2

	return c1 < c2;
}
