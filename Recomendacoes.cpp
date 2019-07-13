#include "Recomendacoes.h"



int prod_mais_freq(vector<int> v)
{
	if (v.size() == 0)
		return -1;
	int anterior = v[0];
	int maximo = v[0];
	int contador = 1;
	int contador_max = 1;

	for (unsigned short int i = 1; i < v.size(); i++)
	{
		if (v[i] == anterior)
			contador++;
		else
		{
			if (contador > contador_max)
			{
				maximo = v[i - 1];
				contador_max = contador;
			}
			anterior = v[i];
			contador = 1;
		}
	}

	return maximo;
}



void recomendar(const VendeMaisMais &supermercado)
{
	int id_cliente_a_recom = escolher_cliente(supermercado);

	bool fez_transacoes = false;				//se nao tiver feito transacoes nao se pode recomendar

	for (unsigned short int i = 0; i < supermercado.transacoes.size(); i++)
	if (id_cliente_a_recom == supermercado.transacoes[i].getIdCliente())
	{
		fez_transacoes = true;
		break;
	}

	if (!fez_transacoes)
	{
		cout << "O cliente nao fez transacoes.\n" << endl;
		espera_input();															//Implementar????
		return;
	}






	//Matriz inicializada com false

	int numero_clientes = supermercado.clientes.size();  //numero de linhas
	int numero_produtos = supermercado.produtos.size();  //numero de colunas


	vector<bool> linha(numero_produtos, false);
	vector< vector<bool> > matriz(numero_clientes, linha);




	//3-map<id_cliente, linha_matriz>
	map<int, int> idcli_lmatriz;

	for (unsigned short int i = 0; i < supermercado.clientes.size(); i++)
	{
		idcli_lmatriz[supermercado.clientes[i].getId()] = i;   //criacao do map
	}



	//4



	for (unsigned short int i = 0; i < supermercado.transacoes.size(); i++)
	{

		int id_cliente_rec = supermercado.transacoes[i].getIdCliente();
		if (!idcli_lmatriz.count(id_cliente_rec)) //se o cliente tiver sido apagado, ou seja, ja nao existir este id
			continue;
		int l_matriz_rec = idcli_lmatriz.at(id_cliente_rec);

		for (unsigned short int j = 0; j < supermercado.transacoes[i].get_v_produtos().size(); j++)
		{
			string prod_rec = supermercado.transacoes[i].get_v_produtos()[j];
			int c_matriz_rec = supermercado.produtoIdx.at(prod_rec);
			matriz[l_matriz_rec][c_matriz_rec] = true;
		}


	}


	//5

	//pair<int, int> prodIgual_prodDif;
	int prod_iguais_melhor_temp = 0;


	vector<int> lista_produtos_recom;

	int prod_igual_cli_analisar = 0;
	int prod_dif_cli_analisar = 0;
	vector<int> lista_produtos_cli_analisar;


	int linha_matriz_cli_alvo = idcli_lmatriz[id_cliente_a_recom];
	//se clinete tiver comprado tudo;
	for (unsigned short int i = 0; i < supermercado.clientes.size(); i++)
	{
		if (linha_matriz_cli_alvo == i)         // salta o cliente a recomendar
			continue;

		for (unsigned short int j = 0; j < supermercado.produtos.size(); j++)
		{
			if (matriz[i][j] && matriz[linha_matriz_cli_alvo][j])           // se o cliente_alvo comprou e o cliente_analisado tambem
				prod_igual_cli_analisar++;

			else if (!matriz[linha_matriz_cli_alvo][j] && matriz[i][j])			//// se o cliente_alvo nao comprou e o cliente_analisado comprou
			{
				prod_dif_cli_analisar++;
				lista_produtos_cli_analisar.push_back(j);                  //produtos a recomendar
			}
		}



		if (prod_dif_cli_analisar > 0)
		{
			if (prod_igual_cli_analisar > prod_iguais_melhor_temp)
			{
				lista_produtos_recom = lista_produtos_cli_analisar;      // atualiza lista de produtos a recomendar
				prod_iguais_melhor_temp = prod_igual_cli_analisar;
			}

			else if (prod_igual_cli_analisar == prod_iguais_melhor_temp)
				lista_produtos_recom.insert(lista_produtos_recom.end(), lista_produtos_cli_analisar.begin(), lista_produtos_cli_analisar.end());  //acrescenta novos produtos


		}

		prod_igual_cli_analisar = 0;																//iguala a zero para proxima iteracao
		prod_dif_cli_analisar = 0;
		lista_produtos_cli_analisar.resize(0);

	}


	sort(lista_produtos_recom.begin(), lista_produtos_recom.end());

	//escreve produtos mais frequentes
	int prod_recom = prod_mais_freq(lista_produtos_recom);
	if (prod_recom != -1)
		cout << "O produto recomendado e: " << supermercado.produtos[prod_recom].getNome() << endl;
	else cout << "Nao e possivel recomendar produto." << endl;

	espera_input();


}


bool ordenar_montante(Cliente &cli1, Cliente &cli2)
{
	return (cli1.getVolCompras() < cli2.getVolCompras());
}

void uniao_vetores(vector<string> &v1, vector<string> v2)
{
	vector<string> v3;
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));
	v1 = v3;
}

bool verifica_cli_int(vector<string> &prod_int, vector<string> prod_bot10)
{

	vector<string> intersecao;

	sort(prod_int.begin(), prod_int.end());
	sort(prod_bot10.begin(), prod_bot10.end());

	set_intersection(prod_int.begin(), prod_int.end(), prod_bot10.begin(), prod_bot10.end(), back_inserter(intersecao));
	if (intersecao.size() != prod_bot10.size())
		return false;                //verifica se cliente comprou todos os produtos do Bot10

	if (prod_int.size() > prod_bot10.size())  //verifica se comprou +1 produto do que o Bot10
		return true;
	else return false;

}



void bottom10(const VendeMaisMais &supermercado)
{
	if (supermercado.clientes.size() <= 10) //se so houver 10 clientes e impossivel recomendar
	{
		cout << "Impossivel recomendar. Nao ha clientes suficientes.";
		espera_input();
		return;
	}

	//Ordenar o vetor por ordem de montante total
	vector<Cliente> clientes_ordenado = supermercado.clientes;
	sort(clientes_ordenado.begin(), clientes_ordenado.end(), ordenar_montante);

	//Bottom 10 e clientes interessantes
	vector<Cliente> v_bot10(clientes_ordenado.begin(), clientes_ordenado.begin() + 10);
	vector<Cliente> v_cli_int(clientes_ordenado.begin() + 10, clientes_ordenado.end());


	//Encontrar produtos comuns aos bottom10
	multimap<int, int> transacaoIdx_copia = supermercado.transacaoIdx;

	vector<string> v_produtos_bot10;

	for (unsigned short int i = 0; i < v_bot10.size(); i++)
	{
		int id_cli_bot10 = v_bot10[i].getId();
		std::pair <std::multimap<int, int>::iterator, std::multimap<int, int>::iterator> ret;
		ret = transacaoIdx_copia.equal_range(id_cli_bot10);

		for (multimap<int, int>::iterator it = ret.first; it != ret.second; ++it)
		{
			uniao_vetores(v_produtos_bot10, supermercado.transacoes[it->second].get_v_produtos());
		}

	}



	vector < pair<string, int>> bot_10_prod_num; //vetor de pares <produto, numero de ocorrencia> do Bot10
	vector < pair<string, int>> cli_int_prod_num; //vetor de pares <produto, numero de ocorrencia> dos cliente importantes
	vector < pair<string, int>> cli_int_prod_num_temp; //vetor de pares <produto, numero de ocorrencia> para verificar se cliente e importante

	//preencher bot_10_prod_num com produtos comprados pelos clientes e 0
	//preencher cli_int_prod_num com produtos comprados pelos clientes e 0
	for (int i = 0; i < v_produtos_bot10.size(); i++)
	{
		bot_10_prod_num.push_back(make_pair(v_produtos_bot10[i], 0));
		cli_int_prod_num.push_back(make_pair(v_produtos_bot10[i], 0));
		cli_int_prod_num_temp.push_back(make_pair(v_produtos_bot10[i], 0));
	}

	//acrescenta ao cli_int_prod_num produtos que nenhum bottom10 comprou
	for (int i = 0; i < supermercado.produtos.size(); i++)
	{
		bool bot10_comprou_produto = find(v_produtos_bot10.begin(), v_produtos_bot10.end(), supermercado.produtos[i].getNome()) != v_produtos_bot10.end();
		if (!bot10_comprou_produto)
		{
			cli_int_prod_num.push_back(make_pair(supermercado.produtos[i].getNome(), 0));
			cli_int_prod_num_temp.push_back(make_pair(supermercado.produtos[i].getNome(), 0));
		}

	}

	//colocar numero de ocorrencias de produtos correto dos Bottom10
	for (unsigned short int i = 0; i < v_bot10.size(); i++)
	{
		int id_cli_bot10 = v_bot10[i].getId();
		pair <multimap<int, int>::iterator, multimap<int, int>::iterator> ret;
		ret = transacaoIdx_copia.equal_range(id_cli_bot10);

		vector<string> v_prod_ja_apareceram; //vetor de produtos de transacoes diferentes de clientes iguais
		//uniao_vetores(v_prod_ja_apareceram, v_aux);

		for (multimap<int, int>::iterator it = ret.first; it != ret.second; ++it)
		{
			vector<string>& v_aux = supermercado.transacoes[it->second].get_v_produtos(); //so para nao usar nome complicado

			for (unsigned short int j = 0; j < v_aux.size(); j++) // precorre transacao
			{

				for (unsigned short int k = 0; k < bot_10_prod_num.size(); k++) // precorre vetor<prod, num> 
				{
					bool produto_ja_apareceu = (find(v_prod_ja_apareceram.begin(), v_prod_ja_apareceram.end(), bot_10_prod_num[k].first) != v_prod_ja_apareceram.end());
					if (bot_10_prod_num[k].first == v_aux[j] && !produto_ja_apareceu)
					{
						bot_10_prod_num[k].second++;
						v_prod_ja_apareceram.push_back(bot_10_prod_num[k].first);
						//produto_ja_apareceu = true;
					}
				}
			}

		}

	}


	//colocar numero de ocorrencias de produtos correto dos Clientes Interessantes
	for (unsigned short int ids = 0; ids < v_cli_int.size(); ids++)
	{
		int id_cli_int = v_cli_int[ids].getId();
		pair <multimap<int, int>::iterator, multimap<int, int>::iterator> ret;
		ret = transacaoIdx_copia.equal_range(id_cli_int);

		vector<string> v_prod_ja_apareceram; //vetor de produtos de transacoes diferentes de clientes iguais

		for (multimap<int, int>::iterator it = ret.first; it != ret.second; ++it)
		{
			vector<string>& v_aux = supermercado.transacoes[it->second].get_v_produtos(); //so para nao usar nome complicado

			for (unsigned short int j = 0; j < v_aux.size(); j++) // precorre transacao
			{

				for (unsigned short int k = 0; k < cli_int_prod_num.size(); k++) // precorre vetor<prod, num> 
				{
					bool produto_ja_apareceu = (find(v_prod_ja_apareceram.begin(), v_prod_ja_apareceram.end(), cli_int_prod_num[k].first) != v_prod_ja_apareceram.end());
					if (cli_int_prod_num[k].first == v_aux[j] && !produto_ja_apareceu)
					{
						cli_int_prod_num_temp[k].second++;
						v_prod_ja_apareceram.push_back(cli_int_prod_num[k].first);
					}
				}
			}

		}
		//so considera clientes que tenham comprado pelo menos todos os produtos comuns aos Bottom10 + 1
		if (verifica_cli_int(v_prod_ja_apareceram, v_produtos_bot10))
		{
			for (int l = 0; l < cli_int_prod_num_temp.size(); l++)
			{
				if (cli_int_prod_num_temp[l].second == 1)
				{
					cli_int_prod_num_temp[l].second--;
					cli_int_prod_num[l].second++;
				}
			}
		}
		else for (int l = 0; l < cli_int_prod_num_temp.size(); l++)  //por a zeros cli_int_prod_num_temp
		{
			cli_int_prod_num_temp[l].second = 0;
			
		}

	}

	// Proponha como promoção o primeiro produto que encontrar e que não tenha sido comprado por nenhum dos Bottom10
	if (cli_int_prod_num.size() > v_produtos_bot10.size())
	{
		cout << "O produto recomendado e: " << cli_int_prod_num[v_produtos_bot10.size()].first;
		espera_input();
		return;
	}


	//remover produtos comprados por todos os Bot10
	for (int i = 0; i < bot_10_prod_num.size(); i++)
	{
		if (bot_10_prod_num[i].second == 10)
		{
			bot_10_prod_num.erase(bot_10_prod_num.begin() + i);
			cli_int_prod_num.erase(cli_int_prod_num.begin() + i);
		}

	}

	//propor o produto que tenha a maior diferença entre compras pelos Clientes Interessantes e compras pelos Bottom10.
	string produto_a_recomendar;
	for (int i = 0; i < bot_10_prod_num.size(); i++)
	{
		
		int maximo = INT_MIN; //comeca com o menor valor possivel
		int diferenca_atual = bot_10_prod_num[i].second - cli_int_prod_num[i].second; //diferenca do produto em analise atual
		if (diferenca_atual > maximo)
		{
			maximo = diferenca_atual;
			produto_a_recomendar = bot_10_prod_num[i].first;
		}

	}
	cout << "O produto recomendado e: " << produto_a_recomendar;
	espera_input();

}