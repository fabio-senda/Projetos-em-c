#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct Tprod{
	int codigo;
	int estoque;
	int minimo;
	int qntVendas;
	int posVendas;
	int reposicao;
	int transferencia;
};

void relatorioCanais(FILE *arq, int *dados);
void relatorioTransfere(FILE *arq, Tprod *dados, int tam);

int main(int argc, char **argv){
	setlocale(LC_ALL, "portuguese");
	
	FILE *produtos, *vendas, *transfere, *divergencias, *canal;
	int aux1, aux2, aux3, aux4;
	int i, cont = 0, cont2 = 0;
	int qntCanais[] = {0, 0, 0, 0, 0};
	Tprod *prod;
	
	prod = NULL;
	
	// Abrir arquivos de entrada e criar arquivos de saída
	produtos = fopen("c2_produtos.txt", "r");
	vendas = fopen("c2_vendas.txt", "r");
	transfere = fopen("transfere.dat", "w");
	divergencias = fopen("diverge.dat", "w");
	canal = fopen("canal.dat", "w");
	if(produtos == NULL || vendas == NULL){
		printf("Erro ao abrir os arquivos de entrada");
		exit(1);
	}
	if(transfere == NULL || divergencias == NULL || canal == NULL){
		printf("Erro ao criar os arquivos de saída");
		exit(1);
	}
	
	// Guarda os dados do primeiro arquivo
	while(fscanf(produtos, "%d;%d;%d",&aux1,&aux2,&aux3) != EOF){
		cont++;
		prod = (Tprod *) realloc(prod, sizeof(Tprod) * cont);
		prod[cont-1].codigo = aux1;
		prod[cont-1].estoque = aux2;
		prod[cont-1].posVendas = aux2;
		prod[cont-1].minimo = aux3;
	}
	
	// Relatório de Divergências
	while(fscanf(vendas, "%d;%d;%d;%d",&aux1,&aux2,&aux3,&aux4) != EOF){
		cont2++;
		switch(aux3){
			case 135:
				fprintf(divergencias, "Linha %d - Venda cancelada\n", cont2);
				break;
			case 190:
				fprintf(divergencias, "Linha %d - Venda não finalizada\n", cont2);
				break;
			case 999:
				fprintf(divergencias,"Linha %d - Erro desconhecido. Acionar equipe de TI\n", cont2);
				break;
			default:
				switch(aux4){
					case 1:
						qntCanais[0] += aux2;
						break;
					case 2:
						qntCanais[1] += aux2;
						break;
					case 3:
						qntCanais[2] += aux2;
						break;
					case 4:
						qntCanais[3] += aux2;
						break;
				}
				break;
		}
		for(i = 0; i < cont; i++){
			if(aux1 == prod[i].codigo){
				if(aux3 == 100 || aux3 == 102)
					prod[i].posVendas -= aux2;
				break;
			}
			else{
				if(i == cont - 1){
					fprintf(divergencias, "Linha %d - Código de Produto não encontrado %d\n", cont2, aux1);
				}
			}
		}
	}
	
	// Relatório de Canais
	relatorioCanais(canal, qntCanais);
	
	//Relatório de Transferências
	relatorioTransfere(transfere, prod, cont);
	
	return 0;
}

void relatorioCanais(FILE *arq, int *dados){
	fprintf(arq, "Quantidades de Vendas por canal\n");
	fprintf(arq, "Canal                  QtVendas\n");
	fprintf(arq, "1 – Representantes        %5d\n", dados[0]);
	fprintf(arq, "2 – Website               %5d\n", dados[1]);
	fprintf(arq, "3 - App móvel Android     %5d\n", dados[2]);
	fprintf(arq, "4 - App móvel iPhone      %5d\n", dados[3]);
}
void relatorioTransfere(FILE *arq, Tprod *dados, int tam){
	int i;
	
	fprintf(arq, "Necessidade de Transferência Armazém para CO\n\n");
	fprintf(arq, "Produto  QtCO  QtMin  QtVendas  Estq.após  Necess.  Transf. de\n");
	fprintf(arq, "                                   Vendas            Arm p/ CO\n");
	for(i = 0; i < tam; i++){
		dados[i].qntVendas = dados[i].estoque - dados[i].posVendas;
		if(dados[i].minimo > dados[i].posVendas)
			dados[i].reposicao = dados[i].minimo - dados[i].posVendas;
		else
			dados[i].reposicao = 0;
		if(dados[i].reposicao >= 1 && dados[i].reposicao < 10)
			dados[i].transferencia = 10;
		else
			dados[i].transferencia = dados[i].reposicao;
		fprintf(arq, "\n%5d %7d %6d %9d %10d %8d %11d",dados[i].codigo, dados[i].estoque, dados[i].minimo, dados[i].qntVendas, dados[i].posVendas, dados[i].reposicao, dados[i].transferencia);	
	}
}

