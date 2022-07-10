# Projetos
Projetos da disciplina de LAOC(Laboratório de arquitetura e organização de computadores).  
## Cálculo de Salários
O projeto realiza a leitura de um arquivo de texto de entrada contendo os salários brutos dos funcionários de uma empresa, sendo um salário em cada linha do arquivo. A partir disso, gerará um arquivo de saída com os salários ordenados e os resultados dos cálculos de descontos de INSS(previdência social), IR(imposto de renda) e salário líquido em formato de tabela. Sendo:  
* SalBruto é o valor oriundo do arquivo de entrada;  
* AliqINSS é o percentual para cálculo do INSS  
Valor do Salário Bruto|Percentual
---|:---:
até 1.751,81|8%
de 1.751,82 até 2.919,72|9%
de 2.919,73 até 5.839,45|11%
A partir de 5.839,46|0%  
* ValINSS é o valor do INSS, sendo ValINSS = salBruto*AlqINSS;  
* Base IR é o valor do salário bruto - o valor a ser recolhido pelo INSS;  
* AliqIR é o percentual usado para cálculo do valor do IR  
Base IR|Percentual|Dedução
---|:---:|---:
até 1.903,98|0,0%|0,00
De 1.903,99 até 2.826,65|7,5%|142,80
De 2.826,66 até 3.751,05|15,0%|354,80
De 3.751,06 até 4.664,68|22,5%|636,13
Acima de 4.664,68|27,5%|869,36
* ValIR é o valor do IR, sendo ValIR = Base IR \* AliqIR - Dedução
* SalLiquido é o valor do salário líquido, sendo SalLiquido = SalBruto - ValINSS - ValIR
## Chinelândia
Problema da 9ª Maratona InterFatec em 2020 de autoria do prof. Sérgio Luiz Banin, FatecSP.  
O programa lê um arquivo que contém na primeira linha um número inteiro N que é a quantidade de pares de chinelos. Em seguida, N linhas contendo o tipo de chinelo esquerdo e direito. O programa, então, calcula o número de chinelos repetidos e grava no arquivo de saída em ordem crescente. Exemplo:
Entrada|Saída|Obs. da saída
---|---|---
4|2 E 1|O tipo 2 esquerdo tem 1 repetição
1 4|3 D 1|O tipo 3 direito tem 1 repetição
2 3| | 
3 1| | 
2 3| | 
### Estoque operacional
O projeto faz a leitura de 2 arquivos texto(csv) de entrada um contendo os dados de produtos (Código;Qtd em estoque;Qtde mínima sugerida no estoque) e outro os dados de vendas (Código do produto;Qtde vendida;Situação de venda;Canal de venda)e gera 3 relatórios, os produtos que faltam em estoque, divergencias e da quantidades de vendas por canal. 

### Gerador de senhas
O projeto lê um arquivo contendo o número de matrícula dos alunos de uma escola e gera um arquivo contendo uma senha para cada aluno, de acordo com a escolha do tipo e tamanho da senha.
