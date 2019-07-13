#include "Menus.h"


void infoInicial(string & loja, string & fichClientes, string & fichProdutos, string & fichTransacoes){

	ifstream ficheiro;

	cout << "Introduza o nome da loja: ";
	getline(cin, loja);


	//Verificar ficheiro de clientes

	cout << "\nIntroduza o nome do ficheiro de clientes: ";

	while (true)
	{
		getline(cin, fichClientes);
		ficheiro.open(fichClientes);
		if (ficheiro)
		{
			ficheiro.close();
			break;
		}
		else cerr << "Esse ficheiro nao existe. Introduza o nome de um ficheiro de clientes existente: ";
	}

	//Verificar ficheiro de produtos

	cout << "\nIntroduza o nome do ficheiro de produtos: ";

	while (true)
	{
		getline(cin, fichProdutos);
		ficheiro.open(fichProdutos);
		if (ficheiro)
		{
			ficheiro.close();
			break;
		}
		else cerr << "Esse ficheiro nao existe. Introduza o nome de um ficheiro de produtos existente: ";
	}

	//Verificar ficheiro de transacoes

	cout << "\nIntroduza o nome do ficheiro de transacoes: ";

	while (true)
	{
		getline(cin, fichTransacoes);
		ficheiro.open(fichTransacoes);
		if (ficheiro)
		{
			ficheiro.close();
			break;
		}
		else cerr << "Esse ficheiro nao existe. Introduza o nome de um ficheiro de transacoes existente: ";
	}

	clearScreen(); //limpa ecra
}


/******************************************
 * Gestao de Clientes
 ******************************************/
unsigned short int menuGestaoClientes(){
	int opcao;

	clearScreen();
	cout << TAB_BIG << "Menu Gestao Clientes" << endl;
	cout << endl;
	cout << TAB << "1 - Listar clientes" << endl;
	cout << TAB << "2 - Ver informacao cliente" << endl;
	cout << TAB << "3 - Criar cliente" << endl;                                    //faltava criar cliente!!!
	cout << TAB << "4 - Editar cliente" << endl;
	cout << TAB << "5 - Remover cliente" << endl;
	cout << TAB << "6 - Voltar ao menu inicial" << endl << endl;
	cout << TAB << "Qual a sua opcao: ";
	opcao = leInteiro(1, 6);

	if (opcao == 6)
		return 0;

	return opcao;
}


void opcoesGestaoClientes(VendeMaisMais & supermercado){
	unsigned int opcao;
	string nome;

	while ((opcao = menuGestaoClientes()))
		switch (opcao){
		case 1: supermercado.listarClientesOrdemAlfa();
			break;
		case 2: cout << "Qual o nome do cliente: ";
			getline(cin, nome);
			supermercado.mostraInformacaoCliente(nome);
			break;
		case 3: supermercado.criar_cliente();
			break;
		case 4: supermercado.editar_cliente();
			break;
		case 5: supermercado.remover_cliente();
			break;
	}
}

/******************************************
 * Gestao de Transacoes
 ******************************************/
unsigned short int menuGestaoTransacoes(){
	int opcao;

	clearScreen();
	cout << TAB_BIG << "Menu Gestao Transacoes" << endl;
	cout << endl;
	cout << TAB << "1 - Listar por ordem cronologica as transacoes de um cliente" << endl;
	cout << TAB << "2 - Listar todas as transacoes num dia" << endl;
	cout << TAB << "3 - Listar todas as transacoes num intervalo de tempo" << endl;
	cout << TAB << "4 - Listar todas as transacoes" << endl;
	cout << TAB << "5 - Adicionar transacoes" << endl;                              
	cout << TAB << "6 - Voltar ao menu inicial" << endl << endl;
	cout << TAB << "Qual a sua opcao: ";
	opcao = leInteiro(1, 6);

	if (opcao == 6)
		return 0;

	return opcao;
}

void opcoesGestaoTransacoes(VendeMaisMais & supermercado){
	unsigned int opcao;

	while ((opcao = menuGestaoTransacoes()))
		switch (opcao){
		case 1: supermercado.listar_Transacoes_Cliente();
			break;
		case 2:supermercado.listar_Transacoes_dia();
			break;
		case 3:supermercado.listar_Transacoes_intervalo_de_tempo();
			break;
		case 4: supermercado.listar_Transacoes();
			break;
		case 5:supermercado.adiciona_transacao();
			break;
	}
}

/******************************************
 * Recomendacoes		                                 //alterado o titulo
 ******************************************/
unsigned short int menuRecomendacao(){
	int opcao;

	clearScreen();
	cout << TAB_BIG << "Menu Gestao Transacoes" << endl;
	cout << endl;
	cout << TAB << "1 - Recomendar um cliente" << endl;
	cout << TAB << "2 - Campanha Bottom 10" << endl;
	cout << TAB << "3 - Voltar ao menu inicial" << endl << endl;
	cout << TAB << "Qual a sua opcao: ";
	opcao = leInteiro(1, 3);

	if (opcao == 3)
		return 0;

	return opcao;
}

void opcoesRecomendacao(VendeMaisMais & supermercado){
	unsigned int opcao;

	while ((opcao = menuRecomendacao()))
		switch (opcao){
		case 1: recomendar(supermercado);
			break;
		case 2: bottom10(supermercado);
			break;
	
	}

}

/******************************************
 * Menu Inicial
 ******************************************/
unsigned short int menuInicial(){
	int opcao;

	clearScreen();
	cout << TAB_BIG << "Menu Inicial" << endl;
	cout << endl;
	cout << TAB << "1 - Gestao de clientes" << endl;
	cout << TAB << "2 - Lista produto disponiveis" << endl;
	cout << TAB << "3 - Gestao de transacoes" << endl;
	cout << TAB << "4 - Recomendacoes" << endl;
	cout << TAB << "5 - Sair do programa" << endl << endl;
	cout << TAB << "Qual a sua opcao: ";
	opcao = leInteiro(1, 5);

	if (opcao == 5)
		return 0;

	return opcao;
}

void opcoesIniciais(VendeMaisMais & supermercado){
	unsigned int opcao;


	while ((opcao = menuInicial()))
		switch (opcao){
		case 1: opcoesGestaoClientes(supermercado);
			break;
		case 2: supermercado.listarProdutos();
			break;
		case 3: opcoesGestaoTransacoes(supermercado);
			break;
		case 4: opcoesRecomendacao(supermercado);
			break;
	}

	supermercado.saveChanges();
}
