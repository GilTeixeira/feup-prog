# pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include "utils.h"

using namespace std;


class Data {
 private:
  int dia;
  int mes;
  int ano;

 public:
  Data(){};
  Data(string data); // data na forma DD/MM/AAA
  Data(int dia, int mes, int ano);
  int getDia() const;
  int getMes() const;
  int getAno() const;
  void setDia(int dia);
  void setMes(int mes);
  void setAno(int ano);
  void save(ofstream & out) const;

  //acrescentado
  friend int concatenar_data(const Data& data_a_conc);
  friend bool comparador_data(const Data& data_comp, const Data& data_inf, const Data& data_sup);


  friend ostream& operator<<(ostream& out, const Data & data);
  
  friend Data le_data();
};


