#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>

struct Ttrocas{
	int tipo;
	char lado;
	int qnt;
};

void contaItensIguais(int *lista, int *contador, int tamanho);
void quickSort(Ttrocas vet[], int esq, int dir);

int main(int argc, char **argv){
	setlocale(LC_ALL, "portuguese");
	FILE *entrada, *saida;
	char nome_arquivo[] = "?_in.txt";
	int *e, *d, *c, tam, i, cont = 0, j, flag = 0;
	Ttrocas *n;

	n = NULL;
	
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("|                                  Projeto Programa 3 - Chinelândia                                   |\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("|                     Adilson de Jesus Candido Oliveira - N° Matrícula/RA: 21207318                   |\n");
	printf("|                     Carina Roberta Rodrigues da Silva - N° Matrícula/RA: 20200081                   |\n");
	printf("|                     Diego Silva e Sousa               - N° Matrícula/RA: 21207407                   |\n");
	printf("|                     Fabio Hideki Kina Senda           - N° Matrícula/RA: 21207120                   |\n");
	printf("|                     Mogica Catarino Ianson            - N° Matrícula/RA: 22119766                   |\n");
	printf("|                     Pedro Pires Ianson                - N° Matrícula/RA: 22119770                   |\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	
	// Recebe o número do arquivo
	printf("|                        Número do arquivo de entrada (?_in.txt): ");
	nome_arquivo[0] = getche();
	printf("                                   |\n");
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	// Abre os arquivos de entrada e saída
	entrada = fopen(nome_arquivo, "r");
	saida = fopen("saida.txt", "w");
	if (entrada == NULL){
		printf("\n Erro ao tentar abrir o arquivo de entrada !!!!");
		exit(1);
	}
	if (saida == NULL){
		printf("Erro ao tentar criar o arquivo de saída");
		exit(1);
	}
	
	// Lê a quantidade de registros do arquivo
	fscanf(entrada, "%d", &tam);
	e = (int *) malloc(sizeof(int)*tam);
	d = (int *) malloc(sizeof(int)*tam);
	c = (int *) malloc(sizeof(int)*tam);
	
	// Lê os registros do arquivo e transfere os dados para listas
	for(i = 0; i < tam; i++){
		fscanf(entrada, "%d %d", e+i, d+i);
	}
	
	// Conta o número de chinelos iguais do lado esquerdo
	contaItensIguais(e, c, tam);
	for(i = 0; i < tam; i++){
		if(c[i] != 0){
			cont++;
			n = (Ttrocas *) realloc(n, sizeof(Ttrocas)*cont);
			n[cont-1].tipo = e[i];
			n[cont-1].lado = 'E';
			n[cont-1].qnt = c[i];
						
			for(j = 0; j < cont-1; j++){
				if(n[cont-1].tipo == n[j].tipo && n[cont-1].lado == n[j].lado)
					cont--;
					n = (Ttrocas *) realloc(n, sizeof(Ttrocas)*cont);
			}
		}
	}
	
	// Conta o número de chinelos iguais do lado direito
	contaItensIguais(d, c, tam);
	for(i = 0; i < tam; i++){
		if(c[i] != 0){
			cont++;
			n = (Ttrocas *) realloc(n, sizeof(Ttrocas)*cont);
			n[cont-1].tipo = d[i];
			n[cont-1].lado = 'D';
			n[cont-1].qnt = c[i];
			
			for(j = 0; j < cont-1; j++){
				if(n[cont-1].tipo == n[j].tipo && n[cont-1].lado == n[j].lado)
					cont--;
					n = (Ttrocas *) realloc(n, sizeof(Ttrocas)*cont);
			}
		}
	}
	
	// Ordena os itens e escreve no arquivo de saída
	if (cont == 0){
		fprintf(saida, "SEM TROCAS DESTA VEZ\n");
	}else {
		quickSort(n, 0, cont-1);
		for(i = 0; i < cont; i++){
			fprintf(saida, "%d %c %d\n", n[i].tipo, n[i].lado, n[i].qnt);
		}
	}
	
	free(e);
	free(d);
	free(c);
	free(n);
	fclose(entrada);
	fclose(saida);
	
	return 0;
}

void contaItensIguais(int *lista, int *contador, int tamanho){
	int i, j;
	for(i = 0; i < tamanho; i++){
		contador[i] = -1;
		for(j = 0; j < tamanho; j++){
			if(lista[i] == lista[j])
				contador[i]++;
		}
	}
}

void quickSort(Ttrocas vet[], int esq, int dir){
    int pivo = esq, i, j;
	Ttrocas ch;         
    for(i= esq+1; i <= dir; i++){
        j = i;
        if(vet[j].tipo < vet[pivo].tipo){     
            ch = vet[j];               
            while(j > pivo){
                vet[j] = vet[j-1];
                j--;
            }
            vet[j] = ch;
            pivo++;                    
        }
    }
    if(pivo-1 >= esq){              
        quickSort(vet, esq, pivo-1);      
    }
    if(pivo+1 <= dir){              
        quickSort(vet, pivo+1, dir);      
    }
}
