#pragma once

#include <iostream>
#include <string>
#include <map>
#include <algorithm>


#include "defs.h"
#include "Data.h"
#include "Cliente.h"
#include "Produto.h"
#include "Transacao.h"
//#include "Recomendacoes.h"


#include "utils.h"


using namespace std;

class VendeMaisMais{
 private:
  string loja; // nome da loja
  string fichClientes, fichProdutos, fichTransacoes; // nome dos
						     // ficheiros de
						     // clientes,
						     // produtos e
						     // transacoes
  bool transacoesAlterdas; // flag que fica a true se for preciso guardar no final as transacoes
  bool clientesAlterados; // flag que fica a true se for preciso guardar no final os clienets
  unsigned int maxClientesId; // variavel que guarda o identificador unico do cliente com o maior identiicador
  vector<Cliente> clientes; // vetor que guarda a informacao dos clientes existentes
  vector<Produto> produtos; // vetor que guarda a informacao dos produtos disponiveis
  vector<Transacao> transacoes; // vetor que guarda a informacao das ttransacoes efetuadas
  map<string, int> clienteIdx;  // map para "traduzir" nome do cliente no indice dele no vetor de clientes
  map<string, int> produtoIdx;  // map para "traduzir" nome do produto no indice dele no vetor de produtos
  multimap<int, int> transacaoIdx; // multima para "traduzir" o identificador do
				   // cliente nos indices das suas
				   // transacoes no vetor de
				   // transacoes

 public:
  VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes);
  
  void listarClientesOrdemAlfa() const;
  void mostraInformacaoCliente(string nome);
  void criar_cliente();
  void editar_cliente();
  void remover_cliente();

  void listarProdutos() const;
  
  void listar_Transacoes_Cliente() ;
  void listar_Transacoes_dia() const;
  void listar_Transacoes_intervalo_de_tempo() const;
  void listar_Transacoes() const;
  void adiciona_transacao();

  void saveChanges() const;

  friend ostream& operator<<(ostream& out, const VendeMaisMais & supermercado);
  friend void recomendar(const VendeMaisMais &supermercado);

 
  friend void bottom10(const VendeMaisMais &supermercado);
  friend int escolher_cliente(const VendeMaisMais &supermercado);
  friend pair<int, string>  escolher_cliente2(const VendeMaisMais &supermercado);
};

