#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>

void GeraSenha(int tam, char tipo, char *senha);

int main(){
	setlocale(LC_ALL, "portuguese");
	FILE *entrada, *saida;
	char tipo, *senhas, aux;
	int tamanho, i, m;
	
	entrada = fopen("MATR.TXT", "r");
	saida = fopen("SENHAS.TXT", "w");
	if(entrada == NULL || saida == NULL){
		printf("Erro ao abrir os arquivos!");
		exit(1);
	}
	
	
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	printf("|                                         Tipos de Senha:                                             |\n");
	printf("|-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
	printf("|   a. Numérica – conterá apenas algarismos;                                                          |\n");
	printf("|   b. Alfabética – conterá apenas letras maiúsculas e minúsculas;                                    |\n");
	printf("|   c. Alfanumérica 1 – conterá letras maiúsculas e algarismos;                                       |\n"); 
	printf("|   d. Alfanumérica 2 – conterá letras maiúsculas, minúsculas e algarismos;                           |\n");
	printf("|   e. Geral – conterá algarismos, letras e os caracteres \"-\", \"_\", \":\", \"@\", \"#\", \"$\", \"&\", \"?\"      |\n");
	printf("|-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
	printf("|                                  Escolha um tipo de senha: ");
	tipo = getche();
	printf("                                        |\n");
	printf("|-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-|\n");
	printf("|                                 Escolha o tamanho da senha: ");
	scanf("%d", &tamanho);
	printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	
	senhas = (char *) malloc(sizeof(char)*tamanho);
	
	while(fscanf(entrada, "%d", &m) != EOF){
		GeraSenha(tamanho, tipo, senhas);
		fprintf(saida, "%d;", m);
		for(i = 0; i < tamanho; i++){
			fprintf(saida, "%c", senhas[i]);
		}
		fprintf(saida, "\n");
	}
	
	return 0;
}

void GeraSenha(int tam, char tipo, char *senha){
	char aux;
	int i, a = 0;
	switch(tipo){
		case 'a':
			//alg  48-57
			for(i = 0; i < tam; i++){
				senha[i] = rand() % 10 + 48; // apenas numeros
			}
			break;
		case 'b':
			//mai  65-90    min 97-122
			for(i = 0; i < tam; i++){
				aux = rand() % (26 + 26); // maiusculas e minusculas
				if(aux < 26)
					aux += 65;
				else
					aux += 97 - 26;
				senha[i] = aux;
			}
			break;
		case 'c':
			for(i = 0; i < tam; i++){
				aux = rand() % (10 + 26); // numeros e maiusculas
				if(aux < 10)
					aux += 48;
				else
					aux += 65 - 10;
				senha[i] = aux;
			}
			break;
		case 'd':
			for(i = 0; i < tam; i++){
				aux = rand() % (10 + 26 + 26); // numeros, maiusculas e minusculas
				if(aux < 10)
					aux += 48;
				else if(aux < 10+26)
					aux += 65 - 10;
				else
					aux += 97 - 10 - 26;
				senha[i] = aux;
			}
			break;
		case 'e':
			//35 36 38 45 58 63 64 95
			// #  $  &  -  :  ?  @  _
			for(i = 0; i < tam; i++){
				aux = rand() % (10 + 26 + 26 + 8); // numeros, maiusculas e minusculas e caracteres
				if(aux < 10)
					aux += 48;
				else if(aux < 10+26)
					aux += 65 - 10;
				else if(aux < 10+26+26)
					aux += 97 - 10 - 26;
				else if(aux < 10+26+26+2)
					aux += 35 - 10 - 26 -26;
				else {
					aux -= (10 + 26 + 26 + 2);
					switch(aux){
						case 0:
							aux = 38;
							break;
						case 1:
							aux = 45;
							break;
						case 2:
							aux = 58;
							break;
						case 3:
							aux = 63;
							break;
						case 4:
							aux = 64;
							break;
						case 5:
							aux = 95;
							break;
						default:
							printf("algo deu errado");
							break;
					}
				}
				senha[i] = aux;
			}
			break;
		default:
			printf("|                                         TIPO INVÁLIDO!!!                                            |\n");
			printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
			exit(0);
			break;
	}
}
