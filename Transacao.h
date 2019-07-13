#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

#include "Data.h"



using namespace std;


class Transacao {
 private:
  unsigned int idCliente;
  Data data; // na forma DD/MM/AAAAA
  vector<string> produtos;

 public:
  Transacao(ifstream & in); // trabsacao na forma de  idCliente ; data ; lista de produtos
  Transacao(unsigned int idCliente,  Data data, vector<string> produtos);
  unsigned int getIdCliente() const;
  vector<string> get_v_produtos() const;
  Data get_data() const; 
  void save(ofstream & out) const; // guarda a transacao
  friend ostream& operator<<(ostream& out, const Transacao & trans); // mostra a transacao
  friend bool operator<(const Transacao &trans1, const  Transacao &trans2); // compara 2 transacoes 1 Transacao e menor que outra se for mais antiga)
};


//////////////////////
// Leitura ficheiro //
//////////////////////

vector<Transacao> le_fichTransacoes(string fichTransacoes);

