#include "Data.h"


Data::Data(string dataStr){ // data na forma DD/MM/AAA
	
	istringstream line(dataStr);
	line >> dia; line.ignore();
	line >> mes; line.ignore();
	line >> ano;
}

Data::Data(int dia, int mes, int ano){
	this->dia = dia;
	this->mes = mes;
	this->ano = ano;
}


int Data::getDia() const{
	return dia;
}

int Data::getMes() const{
	return mes;
}

int Data::getAno() const{
	return ano;
}

void Data::setDia(int dia){
	this->dia = dia;
}

void Data::setMes(int mes){
	this->mes = mes;
}

void Data::setAno(int ano){
	this->ano = ano;
}

void Data::save(ofstream & out) const{
	out << dia << "/" << mes << "/" << ano;
}

ostream& operator<<(ostream& out, const Data & data){
	out << setfill('0') << setw(2) << right << data.dia << "/" 
		<< setw(2) << data.mes << "/" 
		<< setw(4) << data.ano;
	out << setfill(' ') << left;
	return out;
}

Data le_data()
{
	
	bool bissexto;
	cout << "Introduza o ano: ";
	int ano_intro = leInteiro(0, numeric_limits<int>::max());
	if (ano_intro % 4 != 0)
		bissexto = false;
	else bissexto = true;
	
	cout << "Introduza o mes: ";
	int mes_intro = leInteiro(1, 12);

	int dia_intro;

	cout << "Introduza o dia: ";
	if (mes_intro == 4 || mes_intro == 6 || mes_intro == 9 || mes_intro == 11)
		dia_intro = leInteiro(1, 30);
	else if (mes_intro == 1 || mes_intro == 3 || mes_intro == 5 || mes_intro == 7 || mes_intro == 8 || mes_intro == 10 || mes_intro == 12)
		dia_intro = leInteiro(1, 31);
	else if ((mes_intro == 2) && bissexto)
		dia_intro = leInteiro(1, 29);
	else dia_intro = leInteiro(1, 28);

	Data data_intro(dia_intro, mes_intro, ano_intro);
	return data_intro;
}





/////////// comparador de datas imcompleto

int concatenar_data(const Data& data_a_conc)
{
	int data_conc;

	ostringstream data_conc_oss;

	data_conc_oss << data_a_conc.ano;

	if (data_a_conc.mes < 10)
		data_conc_oss << 0 << data_a_conc.mes;
	else data_conc_oss << data_a_conc.mes;

	if (data_a_conc.dia < 10)
		data_conc_oss << 0 << data_a_conc.dia;
	else data_conc_oss << data_a_conc.dia;

	istringstream data_conc_iss(data_conc_oss.str());

	data_conc_iss >> data_conc;

	return data_conc;
}


bool comparador_data(Data data_comp, Data data_inf, Data data_sup)
{
	if (concatenar_data(data_comp) >= concatenar_data(data_inf) && concatenar_data(data_comp) <= concatenar_data(data_comp))
		return true;
	else return false;
}