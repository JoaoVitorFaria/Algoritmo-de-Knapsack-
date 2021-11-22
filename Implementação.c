#include<stdio.h>
#include<stdlib.h>
#include <string.h>
//Analise e Projeto de Algoritimos - TP01
//Aluno: João Vitor de Faria
//Matricula:2019006030


//funcao que retorna a combinacao mais lucrativa entre:
//1)Combinacao incluindo item atual;
//2)Combinacao nao considerando o item atual;
int retornaMelhorOpcao(int lucro_incluindo_item, int lucro_calculado_sem_item)
{
	if(lucro_incluindo_item <= lucro_calculado_sem_item)return lucro_calculado_sem_item;
	else return lucro_incluindo_item;
}

//Essa funcao preenche a matriz que contem o lucro para dado numero de placas e dado orcamento
unsigned int preencheMatrizResultado(int** matriz_resultado, unsigned int orcamento, int novo_num_items , unsigned int custo[], unsigned int lucro[])
{
	//caso base
	if (novo_num_items < 0)
		return 0;
	//Se o valor na posicao definida por novo_num_items e orcamento for diferente de -1, significa que a combinacao mais lucrativa ja
	//foi calculada, entao retorna-se esse valor.
	if (matriz_resultado[novo_num_items][orcamento] != -1)
		return matriz_resultado[novo_num_items][orcamento];

	//Se nao foi visitado:

	//1 ) Caso a placa a ser considerada tenha um custo maior que o orcamento disponivel:
	if (custo[novo_num_items] > orcamento)
	{
		//eh salvo na matriz a melhor combinacao calculada previamente, que nao inclui a placa atual
		matriz_resultado[novo_num_items][orcamento] = preencheMatrizResultado(matriz_resultado, orcamento, novo_num_items - 1, custo, lucro );
		//retorna-se o valor salvo
		
		return matriz_resultado[novo_num_items][orcamento];
	}
	//2) Caso a placa a ser considerada tem um custo que cabe no orcamento:
	else
	{
		//eh verificado se a opcao mais lucrativa eh a combinacao que inclui a placa atual ou a combinacao calculada previamente
		matriz_resultado[novo_num_items][orcamento] = retornaMelhorOpcao(lucro[novo_num_items] + preencheMatrizResultado( matriz_resultado, orcamento - custo[novo_num_items], novo_num_items - 1, custo, lucro), preencheMatrizResultado(matriz_resultado, orcamento, novo_num_items - 1, custo, lucro ));
		//retorna-se 0 valor salvo
	
		return matriz_resultado[novo_num_items][orcamento];
	}
		
}


int knapsack(unsigned int orcamento, unsigned  int num_items, unsigned int custo[], unsigned int lucro[])
{
	unsigned int i;
	//declaração de uma matriz, onde, para um dano numero de placas e orcamento, estara salva a opcao mais lucrativa
	int** matriz_resultado;

	//alocacao dinamica da matriz
	matriz_resultado = ( int**)  malloc(sizeof(int*) * num_items+1);
	for (i = 0; i <= num_items; i++)
		matriz_resultado[i] = ( int*)  malloc(sizeof( int) * (orcamento + 1));

	//A matriz eh preenchida com -1. Esse valor serve pra indicar que uma posicao nao foi visitada
	//Ou seja, -1 indica que a melhor opcao para dado numero de itens e dado orcamento nao foi calculada.
	for (i  = 0; i <= num_items; i++)
		memset(matriz_resultado[i], -1, sizeof(int) * (orcamento + 1));
		

	//a funcao preencheMatrizResultado retorna o resultado fazendo o seguinte:
	//1- retorna o lucro da melhor combinacao(caso ja tenha sido calculado previamente) para um numero x de itens ou
	//2- faz o calculo da combinacao com maior lucro para um numero x de itens
	
	return preencheMatrizResultado( matriz_resultado, orcamento, num_items - 1, custo, lucro);


}

int main(int argc, char * argv[])
{
	unsigned int num_items;
	unsigned int orcamento;
	char ** nome;
	unsigned int * custo;
	unsigned int * lucro;

	scanf("%d %d\n", &num_items, &orcamento);
	nome  = (char**)  malloc(sizeof(char*) * num_items + 1);
	custo = (unsigned int*)  malloc(sizeof(unsigned int) * num_items + 1);
	lucro = (unsigned int*)  malloc(sizeof(unsigned int) * num_items + 1);

	//Lendo a entrada para cada vertice
	unsigned int i;
	for(i = 0; i < num_items; i++)
	{
		getchar();
		nome[i] = (char*)  malloc(sizeof(char) * 20);
		fgets(nome[i], 20, stdin);
		scanf("%d %d", &(custo[i]), &(lucro[i]));
	}
	//Nao eh necessário enviar o vetor com o nomes das placas.
	//Pois o algoritmo nao considera uma mesma placa duas vezes, a nao ser que tenha duas entradas com custos e lucros iguais
	printf("%d\n", knapsack(orcamento, num_items , custo, lucro ));

	for( i = 1; i <= num_items; i++) free(nome[i]);
	free(custo);
	free(lucro);
	free(nome);

	return 0;
}
