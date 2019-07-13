#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "Data.h"

using namespace std;


class Cliente {
 private:
  unsigned int id;
  string nome;
  Data cartaoCliente;
  float volCompras;

 public:
  Cliente(ifstream & in);
  Cliente(unsigned int id, string nome, Data cartaoCliente, float volCompras);
  string getNome() const;
  unsigned int getId() const;
  float getVolCompras() const;
  void acrescentar_quantia(float preco_prod);
  void set_cartaoCliente(Data cartaoCliente);
  void set_nome(string nome);
  void save(ofstream & out) const;
  friend ostream& operator<<(ostream& out, const Cliente & cli);  // mostra informacao do cliente no ecra
  friend bool operator<(const Cliente &cli1, const Cliente &cli2); // compara 2 clientes (1 cleinte e menor que outro se o seu nome for "alfabeticamente" inferior)
};

