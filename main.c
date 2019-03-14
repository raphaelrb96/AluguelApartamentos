#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

struct ficha_locacao {
	char locatario[30];
	int num_locacao;
	int num_quarto;
	struct ficha_locacao *esquerda;
	struct ficha_locacao *direita;
};

typedef struct ficha_locacao locacao;

locacao *pRaiz;


//LOGICA PARA CRIACAO DO TRABALHO ARVORE BINARIA

void buscar(locacao **locac, int n) {
	locacao *temp = *locac;
	if(temp == NULL) {
		printf("Nenhum Resultado para a consulta\n");
		return;
	} else if(temp->num_locacao == n) {
		printf("Numero de locacao %d - Numero de quarto %d - Locatario: %s ", temp->num_locacao, temp->num_quarto, temp->locatario);
		return;
	}
	
	if(temp->num_locacao > n) {
		buscar(&temp->esquerda, n);
		return;
	} else {
		buscar(&temp->direita, n);
		return;
	}
}

int maior(int a, int b){
	if(a > b)
		return a;
	else
		return b;
}

int alturaArvore(locacao **pRaiz) {
	if(((*pRaiz) == NULL) || ((*pRaiz)->esquerda == NULL && (*pRaiz)->direita == NULL))
		return 0;
	else
		return 1 + maior(alturaArvore(&(*pRaiz)->esquerda), alturaArvore(&(*pRaiz)->direita));
}

void limparTela() {
	system("cls");
}

void criarArvoreBinaria(locacao **raiz) {
	*raiz = NULL;
}

void inserirNaArvore(locacao **raiz, int nLoc, int nQuart, char loc[30]) {
	if(*raiz == NULL) {
		*raiz = (locacao *) malloc(sizeof(locacao));
		(*raiz)->esquerda = NULL;
		(*raiz)->direita = NULL;
		(*raiz)->num_locacao = nLoc;
		(*raiz)->num_quarto = nQuart;
		strcpy((*raiz)->locatario, loc);
	} else {
		if (nLoc < ((*raiz)->num_locacao)) {
			inserirNaArvore(&((*raiz)->esquerda), nLoc, nQuart, loc);
		} else {
			inserirNaArvore(&((*raiz)->direita), nLoc, nQuart, loc);
		}
	}
}

void coletarDados() {
	
	int q, l;
	char loc[30];
	
	printf("Aluguel de Apartamentos\n\n\n");
	printf("Insira o nome do locatario: ");
	scanf("%s", &loc);
	printf("\nInsira o Numero do quarto de %s: ", loc);
	scanf("%d", &q);
	printf("\nInsira o Numero da locacao de %s: ", loc);		
	scanf("%d", &l);
	
	inserirNaArvore(&pRaiz, l, q, loc);
	
	limparTela();
	
	
}

void exibirEmOrdem(locacao **raiz) {
	if((*raiz) != NULL) {
		exibirEmOrdem(&(*raiz)->esquerda);
		printf("\nNumero de locacao %d - Numero de quarto %d - Locatario: %s ", (*raiz)->num_locacao, (*raiz)->num_quarto, (*raiz)->locatario);
		exibirEmOrdem(&(*raiz)->direita);
	}
}

void exibirPreOrdem(locacao **pRaiz){
	
	if((*pRaiz) != NULL) {
		printf("\nNumero de locacao %d - Numero de quarto %d - Locatario: %s ", (*pRaiz)->num_locacao, (*pRaiz)->num_quarto, (*pRaiz)->locatario);
		exibirPreOrdem(&(*pRaiz)->esquerda);
		exibirPreOrdem(&(*pRaiz)->direita);
	}
}

void exibirPosOrdem(locacao **pRaiz){
	
	if((*pRaiz) != NULL){
		exibirPosOrdem(&(*pRaiz)->esquerda);
		exibirPosOrdem(&(*pRaiz)->direita);
		printf("\nNumero de locacao %d - Numero de quarto %d - Locatario: %s ", (*pRaiz)->num_locacao, (*pRaiz)->num_quarto, (*pRaiz)->locatario);
	}

}

void listaExclusao(locacao **raiz) {
	if((*raiz) != NULL) {
		listaExclusao(&(*raiz)->esquerda);
		printf("\n(%d) > %s, quarto %d ", (*raiz)->num_locacao, (*raiz)->locatario, (*raiz)->num_quarto);
		listaExclusao(&(*raiz)->direita);
	}
}

int contarNos(locacao **pRaiz){
	if((*pRaiz) == NULL)
		return 0;
	else
		return 1 + contarNos(&(*pRaiz)->esquerda) + contarNos(&(*pRaiz)->direita);
}

int contarFolhas(locacao **pRaiz){
	if((*pRaiz) == NULL)
		return 0;
	if((*pRaiz)->esquerda == NULL && (*pRaiz)->direita == NULL)
		return 1;
	return contarFolhas(&(*pRaiz)->esquerda) + contarFolhas(&(*pRaiz)->direita);
}

locacao *MaiorDireita(locacao **loc) {
	if((*loc)->direita != NULL) {
		return MaiorDireita(&(*loc)->direita);
	} else {
		locacao *aux = *loc;
		if((*loc)->esquerda != NULL) 
			*loc = (*loc)->esquerda;
		else 
			*loc = NULL;
		return aux;
	}
}

locacao *MenorEsquerda(locacao **no){
	if((*no)->esquerda != NULL)
		return MenorEsquerda(&(*no)->esquerda);
	else{
		locacao *aux = *no;
		if((*no)->direita != NULL) // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da direita!
			*no = (*no)->direita;
		else
			*no = NULL;
		return aux;
	}
}

int removerDaArvore(locacao **pRaiz, int num_loc) {
	if(*pRaiz == NULL){ 
		// esta verificacao serve para caso o numero nao exista na arvore.
		//printf("Numero de locacao nao existe na arvore!");
		return 0;
	}
	
	if(num_loc < (*pRaiz)->num_locacao) {

		removerDaArvore(&(*pRaiz)->esquerda, num_loc);

	} else if(num_loc > (*pRaiz)->num_locacao) {

		removerDaArvore(&(*pRaiz)->direita, num_loc);

	} else {
		
		// se nao eh menor nem maior, logo, eh o numero que estou procurando! ??
		locacao *pAux = *pRaiz; // quem programar no Embarcadero vai ter que declarar o pAux no inicio do void! :[
		if (((*pRaiz)->esquerda == NULL) && ((*pRaiz)->direita == NULL)){ 

			// se nao houver filhos…
			free(pAux);
			(*pRaiz) = NULL;

		} else { 

			// so tem o filho da direita
			if ((*pRaiz)->esquerda == NULL) {

					(*pRaiz) = (*pRaiz)->direita;
					pAux->direita = NULL;
					free(pAux); pAux = NULL;

			} else { 

				//so tem filho da esquerda
				if ((*pRaiz)->direita == NULL) {

					(*pRaiz) = (*pRaiz)->esquerda;
					pAux->esquerda = NULL;
					free(pAux); pAux = NULL;

				} else { 
					//Escolhi fazer o maior filho direito da subarvore esquerda.
					pAux = MaiorDireita(&(*pRaiz)->esquerda); //se vc quiser usar o Menor da esquerda, so o que mudaria seria isso:
					pAux->esquerda = (*pRaiz)->esquerda; // pAux = MenorEsquerda(&(*pRaiz)->direita);			pAux->direita = (*pRaiz)->direita;
					(*pRaiz)->esquerda = (*pRaiz)->direita = NULL;
					free((*pRaiz)); *pRaiz = pAux; pAux = NULL;
						
				}
			}
		}
		
		return 1;
		
	}
	
}

void interface() {
	int opcao = -1, op = -1, remov = -1;
	do {
		printf("LOCADORA DE APARTAMENTOS\n\n\n");
		printf("(1) > Inserir Apartamentos na Arvore Binaria\n");	
		printf("(2) > Remover Apartamento\n");
		printf("(3) > Exibir Apartamentos Ocupados em Ordem\n");
		printf("(4) > Exibir Apartamentos Ocupados em Pre-Ordem\n");
		printf("(5) > Exibir Apartamentos Ocupados em Pos-Ordem\n");
		printf("(6) > Contar Nos\n");
		printf("(7) > Contar Folhas\n");
		printf("(8) > Altura da Arvore\n");
		printf("(9) > Pesquisar\n");
		printf("(0) > Sair\n");
		printf("\nESCOLHA UMA OPCAO: \n");
		scanf("%d", &opcao);
		limparTela();
		switch(opcao) {
			case 1:
				coletarDados();
				break;
			case 2:
				op = -1;
				do {
					printf("Remover Apartamentos Alugados \n");
					listaExclusao(&pRaiz);
					printf("\n\n(0) > Voltar\n\nESCOLHA UMA OPCAO: ");
					scanf("%d", &op);
					remov = removerDaArvore(&pRaiz, op);
					
					if(remov == 1) {
						op = 0;
						limparTela();
					} else {
						limparTela();
						printf("\nNumero de locacao nao existe na arvore!\n\n");
					}
				
				} while (op != 0);
				limparTela();
				break;
			case 3:
				op = -1;
				do {
					printf("Apartamentos Alugados - Em Ordem \n\n");
					exibirEmOrdem(&pRaiz);
					printf("\n\n(0) > Voltar\n\nESCOLHA UMA OPCAO: ");
					scanf("%d", &op);
					limparTela();
				} while(op != 0);
				break;
			case 4:
				op = -1;
				do {
					printf("Apartamentos Alugados - Pre Ordem \n\n");
					exibirPreOrdem(&pRaiz);
					printf("\n\n(0) > Voltar\n\nESCOLHA UMA OPCAO: ");
					scanf("%d", &op);
					limparTela();
				} while(op != 0);
				break;
			case 5:
				op = -1;
				do {
					printf("Apartamentos Alugados - Pos Ordem \n\n");
					exibirPosOrdem(&pRaiz);
					printf("\n\n(0) > Voltar\n\nESCOLHA UMA OPCAO: ");
					scanf("%d", &op);
					limparTela();
				} while(op != 0);
				break;
			case 6:
				op = -1;
				do {
					printf("Contagem de Nos: %d \n\n", contarNos(&pRaiz));
					printf("\n\n(0) > Voltar\n\nESCOLHA UMA OPCAO: ");
					scanf("%d", &op);
					limparTela();
				} while(op != 0);
				break;
			case 7:
				op = -1;
				do {
					printf("Contagem de Folhas: %d \n\n", contarFolhas(&pRaiz));
					printf("\n\n(0) > Voltar\n\nESCOLHA UMA OPCAO: ");
					scanf("%d", &op);
					limparTela();
				} while(op != 0);
				break;
			case 8:
				op = -1;
				do {
					printf("Altura da Arvore: %d \n\n", alturaArvore(&pRaiz));
					printf("\n\n(0) > Voltar\n\nESCOLHA UMA OPCAO: ");
					scanf("%d", &op);
					limparTela();
				} while(op != 0);
				break;
			case 9:
				op = -1;
				do {
					printf("\nPesquisar por Numero de Locacao: ");
					printf("\n\n(0) > Voltar\n\nINSIRA UM NUMERO: ");
					scanf("%d", &op);
					limparTela();
					if(op != 0) {
						buscar(&pRaiz, op);
					}
					
				} while(op != 0);
				break;
			case 0:
				break;
			default:
				printf("\nEscolha uma Opcao Valida\n");
				break;				
		}
		
		if(opcao != 0) {
			opcao = -1;
		}
		
	} while (opcao != 0);
}


int main(int argc, char** argv) {
	criarArvoreBinaria(&pRaiz);
	interface();
	return 0;
}


//LOGICA DOS TRABALHOS ANTIGOS
/*
void imprimirLista() {
	printf("Lista de Apartamentos Alugados\n\n");
	for(int i = 0; i < 3; i++) {
		printf("Quarto %d esta alugado para %s, numero de locacao: %d \n\n", locacao[i].num_quarto, locacao[i].locatario, locacao[i].num_locacao);
	}
}

int consultaBinaria(int numProcurado, int comeco, int fim) {
	int meio, achou = -1;
	meio = (comeco + fim)/2;
	
	if(comeco <= fim) {
		if(numProcurado == locacao[meio].num_locacao) {
			achou = meio;
			return achou;
		} else {
			if(numProcurado < locacao[meio].num_locacao) {
				consultaBinaria(numProcurado, comeco, meio-1);
			} else {
				consultaBinaria(numProcurado, meio + 1, fim);
			}
		}
	} else {
		return achou;
	}
}

int consultaLinear(int numProcurado) {
	for(int i = 0; i < 3; i++) {
		if(locacao[i].num_locacao == numProcurado) {
			return i;
		}
	}
	return -1;
}

void preencherDados() {
	
	for(int i = 0; i < 3; i++) {
		printf("Aluguel de Apartamentos\n\n\n");
		printf("Insira o nome do locatario %d: ", i + 1);
		scanf("%s", &locacao[i].locatario);
		printf("\nInsira o Numero do quarto de %s: ", locacao[i].locatario);
		scanf("%d", &locacao[i].num_quarto);
		printf("\nInsira o Numero da locacao de %s: ", locacao[i].locatario);
		scanf("%d", &locacao[i].num_locacao);
		system("cls");
	}
	
}

void ordenar() {
	for(int i = 0; i < 3; i++) {
		for(int y = 0; y < 3; y++) {
			if(locacao[i].num_locacao < locacao[y].num_locacao) {
				int numLocacao = locacao[i].num_locacao;
				int numQuarto = locacao[i].num_quarto;
				char locatario[30];
				strcpy(locatario, locacao[i].locatario);
				locacao[i].num_locacao = locacao[y].num_locacao;
				locacao[i].num_quarto = locacao[y].num_quarto;
				strcpy(locacao[i].locatario, locacao[y].locatario);
				locacao[y].num_locacao = numLocacao;
				locacao[y].num_quarto = numQuarto;
				strcpy(locacao[y].locatario, locatario);
			}
		}
	}
}

int pesquisar() {

	int retorno = -1;
	int pesq = -1;
	int resultado;
	printf("Insira o numero da Locacao que deseja procurar: ");
	scanf("%d", &pesq);
	resultado = consultaBinaria(pesq, 0, 3);
	if(resultado == -1) {
		system("cls");
		printf("Nao existe esse numero de Locacao\n\n\n");
	} else {
		system("cls");
		printf("Nome do Locatario: %s", locacao[resultado].locatario);
		printf("\nNumero do quarto: %d", locacao[resultado].num_quarto);
		printf("\nNumero da locacao: %d", locacao[resultado].num_locacao);
		retorno = 1;
	}
	
}

*/

