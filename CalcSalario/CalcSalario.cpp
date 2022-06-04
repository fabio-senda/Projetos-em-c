#include <stdio.h>
#include <stdlib.h>

void quickSort(double vet[], int esq, int dir);
void Calculo(double SalBruto, double *AliqINSS, double *ValINSS, double *IR, double *AliqIR, double *ValIR, double *SalLiquido);

int main(){
	FILE *entrada, *saida;
	int cont=0, i;
	double a,b,c,d,e,f,g;
	
	double *SalBruto, *AliqINSS = &b, *ValINSS = &c, *IR = &d;
	double *AliqIR = &e, *ValIR = &f, *SalLiquido = &g;
	
	entrada = fopen("SALARIO.TXT", "r");
	if(entrada == NULL){
		printf("Erro ao abrir o arquivo de entrada");
		exit(1);
	}
	
	saida = fopen("CALCULOS.TXT", "w");
	if(saida == NULL){
		printf("Erro ao criar o arquivo de saída");
		exit(1);
	}
		
	while(fscanf(entrada, "%lf", &a) != EOF){
		cont++;
		SalBruto = (double *) realloc(SalBruto, sizeof(double)*cont);
		SalBruto[cont-1] = a;
	}
	
	quickSort(SalBruto, 0, cont-1);
	
	fprintf(saida, "    Bruto  AliqINSS   Val.INSS  Base I.R.  AliqIR   Val.IR   Liquido");
	for(i = 0; i < cont; i++){
		Calculo(SalBruto[i], AliqINSS, ValINSS, IR, AliqIR, ValIR, SalLiquido);
		fprintf(saida,"\n%9.2lf %9.1lf %10.2lf %10.2lf %7.1lf %8.2lf %9.2lf", SalBruto[i], *AliqINSS*100, *ValINSS, *IR, *AliqIR*100, *ValIR, *SalLiquido);
	}
	return 0;
}

void quickSort(double vet[], int esq, int dir){
    int pivo = esq, i, j;
	double ch;         
    for(i=esq+1;i<=dir;i++){        
        j = i;                      
        if(vet[j] < vet[pivo]){     
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
        quickSort(vet,esq,pivo-1);      
    }
    if(pivo+1 <= dir){              
        quickSort(vet,pivo+1,dir);      
    }
}

void Calculo(double SalBruto, double *AliqINSS, double *ValINSS, double *IR, double *AliqIR, double *ValIR, double *SalLiquido){
	double DeducaoIR;
	
	// Tabela 1
	if(SalBruto <= 1751.81)
		*AliqINSS = 0.08;
	else if(SalBruto > 1751.81 && SalBruto <= 2919.72)
		*AliqINSS = 0.09;
	else if(SalBruto >= 5839.46)
		*AliqINSS = 0;
	else
		*AliqINSS = 0.11;
	
	// Valor do INSS
	if (*AliqINSS == 0)
		*ValINSS = 642.34;
	else
		*ValINSS = SalBruto * *AliqINSS;
	
	
	// Imposto de renda
	*IR = SalBruto - *ValINSS;
	
	// Tabela 2
	if(*IR <= 1903.98){
		*AliqIR = DeducaoIR = 0;
	}
	else if(*IR > 1903.98 && *IR <= 2826.65){
		*AliqIR = 0.075;
		DeducaoIR = 142.80;
	}
	else if(*IR > 2826.65 && *IR <= 3751.05){
		*AliqIR = 0.15;
		DeducaoIR = 354.80;
	}
	else if(*IR > 4664.68){
		*AliqIR = 0.275;
		DeducaoIR = 869.36;
	}
	else{
		*AliqIR = 0.225;
		DeducaoIR = 636.13;
	}
	
	//Calculo do Salario Líquido e Valor IR
	*ValIR = *IR * *AliqIR - DeducaoIR;
	if(*ValIR < 10){
		*ValIR = 0;
	}
	*SalLiquido = *IR - (*ValIR);
	
}
