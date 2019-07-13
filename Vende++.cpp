#include "Vende++.h"

using namespace std;

VendeMaisMais::VendeMaisMais(string loja, string fichClients, string fichProdutos, string fichTransacoes){
	this->loja = loja;
	this->fichClientes = fichClients;
	this->fichProdutos = fichProdutos;
	this->fichTransacoes = fichTransacoes;




	//ficheiro clientes para vetor
	int num_cli;
	ifstream f_clientes;

	f_clientes.open(fichClients);

	f_clientes >> num_cli; f_clientes.ignore();

	for (int i = 0; i < num_cli; i++)
	{
		Cliente cliente_lido(f_clientes);
		clientes.push_back(cliente_lido);

		clienteIdx[cliente_lido.getNome()] = i;   //criacao do map
	}

	f_clientes.close();





	//ficheiro produtos para vetor
	int num_prod;
	ifstream f_produtos;

	f_produtos.open(fichProdutos);

	f_produtos >> num_prod; f_produtos.ignore();

	for (int i = 0; i < num_prod; i++)
	{
		Produto produto_lido(f_produtos);
		produtos.push_back(produto_lido);

		produtoIdx[produto_lido.getNome()] = i;   //criacao do map
	}

	f_produtos.close();




	//ficheiro transacoes para vetor
	int num_trans;
	transacoesAlterdas = false;
	ifstream f_transacoes;

	f_transacoes.open(fichTransacoes);

	f_transacoes >> num_trans; f_transacoes.ignore();

	///acrecentar multimap
	for (int i = 0; i < num_trans; i++)
	{
		Transacao trans_lida(f_transacoes);
		transacoes.push_back(trans_lida);

		transacaoIdx.insert(make_pair(trans_lida.getIdCliente(), i));  //criacao multimap
	}

	f_transacoes.close();

	//determinar id do maior cliente
	unsigned int id_max_temp = 0;
	for (int i = 0; i < transacoes.size(); i++)
	{
		if (transacoes[i].getIdCliente() > id_max_temp)
			id_max_temp = transacoes[i].getIdCliente();
	}
	for (int i = 0; i < clientes.size(); i++)
	{
		if (clientes[i].getId() > id_max_temp)
			id_max_temp = clientes[i].getId();
	}
	maxClientesId = id_max_temp;
}



int escolher_cliente(const VendeMaisMais &supermercado){
	int pos_cliente_a_recom;
	int id_cliente_a_recom;
	string nome_cliente_a_recom;



	while (true)
	{
		cout << "Introduza o nome do cliente: ";
		getline(cin, nome_cliente_a_recom);

		//verificar se existe

		if (supermercado.clienteIdx.find(nome_cliente_a_recom) == supermercado.clienteIdx.end())
			cout << "Esse cliente nao existe. ";
		else {
			pos_cliente_a_recom = supermercado.clienteIdx.at(nome_cliente_a_recom);
			id_cliente_a_recom = supermercado.clientes[pos_cliente_a_recom].getId();
			break;
		}
	}

	return id_cliente_a_recom;

}

pair<int, string>  escolher_cliente2(const VendeMaisMais &supermercado){
	int pos_cliente_a_recom;
	int id_cliente_a_recom;
	string nome_cliente_a_recom;



	while (true)
	{
		cout << "Introduza o nome do cliente: ";
		getline(cin, nome_cliente_a_recom);

		//verificar se existe

		if (supermercado.clienteIdx.find(nome_cliente_a_recom) == supermercado.clienteIdx.end())
			cout << "Esse cliente nao existe. ";
		else {
			pos_cliente_a_recom = supermercado.clienteIdx.at(nome_cliente_a_recom);
			id_cliente_a_recom = supermercado.clientes[pos_cliente_a_recom].getId();
			break;
		}
	}

	return make_pair(id_cliente_a_recom, nome_cliente_a_recom);

}
/*********************************
 * Gestao de Clientes
 ********************************/

// lista os cleinets por ordem alfabetica crescente
void VendeMaisMais::listarClientesOrdemAlfa() const{
	vector<Cliente> v_clientes_copia = clientes;
	if (v_clientes_copia.size() == 0)
	{
		cout << endl << "Nao existem clientes";
		espera_input;
	}

	sort(v_clientes_copia.begin(), v_clientes_copia.end());


	linha();
	cout << left << "| " << setw(6) << "Id" << setw(41) << "Nome do Cliente" << setw(17) << "Data de Adesao" << setw(5) << "Montante\n";
	linha();

	
	for (unsigned short int i = 0; i < v_clientes_copia.size(); i++)
	{
		cout << v_clientes_copia[i];
	}

	linha();

	espera_input();


}

// mostra a informacao individual de um cliente
void VendeMaisMais::mostraInformacaoCliente(string nome){
	if (clienteIdx.find(nome) == clienteIdx.end()) {
		cout << "Esse cliente nao existe.";
		espera_input();
	}
	else {
		linha();
		cout << left << "| " << setw(6) << "Id" << setw(41) << "Nome do Cliente" << setw(17) << "Data de Adesao" << setw(5) << "Montante\n";
		linha();
		int pos_vec = clienteIdx[nome];
		cout << clientes[pos_vec];
		linha();
		espera_input();
	}

}

void VendeMaisMais::criar_cliente(){

	int id_cli = maxClientesId + 1;
	maxClientesId = maxClientesId + 1;

	cout << "Introduza nome do cliente: ";
	string nome_lido = le_string();

	cout << "Introduza a data de adesao:\n";
	Data data_lida = le_data();

	float volCompras_lido = 0;

	Cliente cliente_lido(id_cli, nome_lido, data_lida, volCompras_lido);

	clienteIdx[nome_lido] = clientes.size();
	clientes.push_back(cliente_lido);



	clientesAlterados = true;
}

void VendeMaisMais::editar_cliente(){
	string nome_lido = escolher_cliente2(*this).second;
	int pos_vec = clienteIdx[nome_lido];
	Data data_lida;


	cout << "O que pretende alterar:" << endl;
	cout << "1) A data de adesao." << endl;
	cout << "2) O nome do cliente." << endl;
	int opcao = leInteiro(1, 2);
	switch (opcao){
	case 1: data_lida = le_data();
		clientes[pos_vec].set_cartaoCliente(data_lida);
		break;
	case 2:
		cout << "Introduza nome do cliente: ";
		string novo_nome = le_string();
		clientes[pos_vec].set_nome(novo_nome);
		clienteIdx.erase(nome_lido);                 //atualizar map
		clienteIdx[nome_lido] = pos_vec;
		break;
	}


	clientesAlterados = true;
}

void VendeMaisMais::remover_cliente(){
	if (clientes.size() == 0)
	{
		cout << "Impossivel remover clientes.";
		espera_input();
		return;

	}
	cout << "Introduza nome do cliente: ";
	string nome_lido = le_string();

	int pos_cli = clienteIdx[nome_lido];
	clientes.erase(clientes.begin() + pos_cli);
	clienteIdx.erase(nome_lido);

	clientesAlterados = true;
}


/*********************************
 * Gestao de Produtos
 ********************************/

// lisat os produto por ordem alfabetica crescente
void VendeMaisMais::listarProdutos() const{
	vector<Produto> produtos_copia = produtos;
	int num_prod = produtos_copia.size();

	sort(produtos_copia.begin(), produtos_copia.end());
	cout << " ------------------------------------------------------" << endl
		<< "|      Nome do Produto          |        Preco        |" << endl
		<< " -------------------------------+----------------------" << endl;
	for (unsigned short int i = 0; i < produtos_copia.size(); i++)
		cout << "|" << left << setw(31) << produtos[i].getNome() << "|" << setw(21) << produtos[i].getCusto() << "|" << endl;
	cout << " ------------------------------------------------------";


	espera_input();

}


/*********************************
* Gestao de Transacoes
********************************/

void VendeMaisMais::listar_Transacoes_Cliente() {
	vector<Transacao> transacoes_crono;
	int id_cliente_listar = escolher_cliente(*this);


	if (transacaoIdx.count(id_cliente_listar) == 0)
	{
		cout << "Esse cliente nao efetuou transacoes.";
		espera_input();
		return;
	}

	linha();
	cout << "| " << left << setw(8) << "Id" << setw(13) << "Data" << setw(37) << "Lista de Produtos" << endl;
	linha();



	multimap<int, int>::iterator it;
	for (it = transacaoIdx.begin(); it != transacaoIdx.end(); ++it)
	{
		if ((*it).first == id_cliente_listar)
			transacoes_crono.push_back(transacoes[(*it).second]);
	}

	sort(transacoes_crono.begin(), transacoes_crono.end());

	for (unsigned short int i = 0; i < transacoes_crono.size(); i++)
	{
		cout << transacoes_crono[i];
	}

	linha();
	espera_input();


}

void VendeMaisMais::listar_Transacoes_dia() const{
	Data data_lida = le_data();
	int data_lida_conc = concatenar_data(data_lida);
	bool houve_trans = false;
	bool mostrar_menu = true;


	for (unsigned short int i = 0; i < transacoes.size(); i++)
	{
		if (concatenar_data(transacoes[i].get_data()) == data_lida_conc)
		{
			if (mostrar_menu)
			{
				linha();
				cout << "| " << left << setw(8) << "Id" << setw(13) << "Data" << setw(37) << "Lista de Produtos" << endl;
				linha();
				mostrar_menu = false;
				houve_trans = true;
			}
			cout << transacoes[i];
		}
	}
	if (houve_trans)
		linha();
	else cout << "Nao ocorreram transacoes nesse dia.";


	espera_input();

}

void VendeMaisMais::listar_Transacoes_intervalo_de_tempo() const{
	bool houve_trans = false;
	bool mostrar_menu = true;

	cout << "Introduza o limite inferior do intervalo:\n";
	Data data_lida_inf = le_data();
	int data_lida_conc_inf = concatenar_data(data_lida_inf);

	cout << "Introduza o limite superior do intervalo:\n";
	Data data_lida_sup = le_data();
	int data_lida_conc_sup = concatenar_data(data_lida_sup);

	if (data_lida_conc_inf > data_lida_conc_sup)
	{
		cout << "\nO limite inferior e maior que o superior.";
		espera_input();
		return;

	}
	else if (data_lida_conc_inf == data_lida_conc_sup)
	{
		cout << "\nO limite superior e igual ao limite inferior.";
		espera_input();
		return;
	}


	for (unsigned short int i = 0; i < transacoes.size(); i++)
	{
		if (concatenar_data(transacoes[i].get_data()) >= data_lida_conc_inf && concatenar_data(transacoes[i].get_data()) <= data_lida_conc_sup)
		{
			if (mostrar_menu)
			{
				linha();
				cout << "| " << left << setw(8) << "Id" << setw(13) << "Data" << setw(37) << "Lista de Produtos" << endl;
				linha();
				mostrar_menu = false;
				houve_trans = true;
			}
			cout << transacoes[i];
		}
	}
	if (houve_trans)
		linha();
	else cout << "\nNao ocorreram transacoes nesse intervalo de tempo.\n";


	espera_input();

}

void VendeMaisMais::listar_Transacoes() const {
	if (!transacoes.size())     //verifica se houve pelo menos 1 transacao
	{
		cout << "Nao se efetuaram transacoes.";
		espera_input();
		return;
	}


	linha();
	cout << "| " << left << setw(8) << "Id" << setw(13) << "Data" << setw(37) << "Lista de Produtos" << endl;
	linha();

	for (unsigned short int i = 0; i < transacoes.size(); i++)
	{
		cout << transacoes[i];
	}
	linha();
	espera_input();

}

void VendeMaisMais::adiciona_transacao()
{
	pair<int, string> cli = escolher_cliente2(*this);

	int id_cliente_ad_trans = cli.first;
	string nome_cliente_ad_trans = cli.second;


	cout << "Introduza a data:\n";
	Data data_lida = le_data();

	string prod_lido;
	vector<string> lista_prod_lida;

	cout << "Introduza a lista de produtos(separados por Enter, introduza -1 para terminar): ";
	while (true)
	{
		getline(cin, prod_lido);
		if (prod_lido == "-1")
			break;

		if (produtoIdx.find(prod_lido) == produtoIdx.end())
		{
			cout << "Esse produto nao existe nao existe.\n";
			cout << "Introduza proximo produto: ";
			continue;
		}

		lista_prod_lida.push_back(prod_lido);
		cout << "Introduza proximo produto: ";
	}

	if (lista_prod_lida.size() != 0)
	{
		//atualizar cliente
		for (int i = 0; i < lista_prod_lida.size(); i++)
		{
			int pos_vec = clienteIdx[nome_cliente_ad_trans];
			float preco_prod = produtos[produtoIdx[lista_prod_lida[i]]].getCusto();
			clientes[pos_vec].acrescentar_quantia(preco_prod);

		}


		transacaoIdx.insert(make_pair(id_cliente_ad_trans, transacoes.size())); //atualizar multimap

		Transacao trans_lida(id_cliente_ad_trans, data_lida, lista_prod_lida);
		transacoes.push_back(trans_lida);  //atualizar vetor transacoes

		clientesAlterados = true;
		transacoesAlterdas = true;

	}
}



/*********************************
 * Preservar Informacao
 ********************************/

// guarda apenas a informacao de clientes e/ou de transacoes que foi alterada
void VendeMaisMais::saveChanges() const{

	//abrir ficheiro
	ofstream f_clientes;


	if (clientesAlterados)
	{
		f_clientes.open(fichClientes);
		f_clientes << clientes.size() << endl;
		for (unsigned short int i = 0; i < clientes.size(); i++)
		{
			clientes[i].save(f_clientes);
			if (i != clientes.size() - 1)
				f_clientes << endl;
		}

		f_clientes.close();
	}




	//abrir ficheiro
	ofstream f_transacoes;

	if (transacoesAlterdas)
	{
		f_transacoes.open(fichTransacoes);
		f_transacoes << transacoes.size() << endl;
		for (unsigned short int i = 0; i < transacoes.size(); i++)
		{
			transacoes[i].save(f_transacoes);
			if (i != transacoes.size() - 1)
				f_transacoes << endl;
		}
		f_transacoes.close();
	}


}

/*********************************
 * Mostrar Loja
 ********************************/

// mostra o conteudo de uma loja
ostream& operator<<(ostream& out, const VendeMaisMais & supermercado){
	out << "  ________________________________________________________ \n";
	out << " /|  __      ________ _   _ _____  ______                 |\n";
	out << "| |  \\ \\    / /  ____| \\ | |  __ \\|  ____|    _     _     |\n";
	out << "| |   \\ \\  / /| |__  |  \\| | |  | | |__     _| |_ _| |_   |\n";
	out << "| |    \\ \\/ / |  __| | . ` | |  | |  __|   |_   _|_   _|  |\n";
	out << "| |     \\  /  | |____| |\\  | |__| | |____    |_|   |_|    |\n";
	out << "| |      \\/   |______|_| \\_|_____/|______|                |\n";
	out << "| |_______________________________________________________|\n";
	out << "|/_______________________________________________________/ \n\n";
	out << "Numero de clientes: " << supermercado.clientes.size() << endl;
	out << "Numero de produtos: " << supermercado.produtos.size() << endl;
	out << "Transacoes efetuadas: " << supermercado.transacoes.size() << endl << endl;
	espera_input();

	return out;
}
