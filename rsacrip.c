#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include <time.h>

int mdc(int n1, int n2) //RETORNA O MDC DE DOIS NUMEROS
{
	int resto;

	while(n2 != 0)
	{
		resto = n1 % n2;
		n1 = n2;
		n2 = resto;
	}

	return n1;
}

int primo(int i) 	// Verifica se o número é primo
{
	int resto, j, contador=0, resposta;

	for(j=1; j<=i; j++)
	{
		resto = i%j;

		if(resto==0)
		{
			contador++;
		}
	}

	if(contador == 2)
	{
		resposta = 1;
	}

	else
	{
		resposta = 0;
	}

	return resposta;
}

int inverso(int a, int b) //CALCULA O INVERSO DE (e mod totiente)
{
	int quocientes[100000], i = 0, aux, j, r, resposta[100000], k =0, finala, finalb;
	
	if (b > a)
	{
		aux = b;
		b = a;
		a = aux;
	}
	finala = a;
	finalb = b;
	while (b != 0)
	{
		quocientes[i] = a / b;
		i++;
		r = a % b;
		a = b;
		b = r;
		
	}
	resposta[0] = 1;
	for (j = i-2; j >= 0; j--)
	{
		if (k == 0)
		{
			resposta[k+1] = quocientes[j] * resposta[k];
			k++;
		}
		else
		{
			resposta[k+1] = (quocientes[j] * resposta[k]) + (resposta[k-1]);
			k++;
		}
	}
	if (k % 2 == 0)
	{
		return resposta[k];
	}
	else
	{
		return resposta[k]*(-1);
	}
}

int exp_aleatorio(int totiente) //RETORNA UM VALOR ALEATORIO PARA O (e)
{
	int i, verificacao_primo;
	
	do
	{
		srand(time(NULL));
		
		i=2+rand()% totiente;
		
		if(primo(i)==0)
		{
			do
			{
				i=2+rand()% totiente;
			}
			while(primo(i)==0);
		}

	}while(!((i>1 && i<totiente)&&(mdc(totiente,i) == 1)));
	
	return i;
	
}


int exp_mod_rap(int M[], int posicao, int e, int n) //EXPONENCIACAO MODULAR RAPIDA
{
   int resultado, pt;

  
	 resultado = 1;

	 pt = M[posicao] % n;

  for ( ; e > 0; e /= 2) 
  {
    if (e % 2 == 1)  
      resultado = (resultado * pt) % n;

    pt = (pt * pt) % n;
  }

  return resultado;
}


int main(int argc, char const *argv[])
{
	FILE*arquivo1; //arquivo de texto que recebe as chaves públicas
	FILE*arquivo2; // arquivo de texto que recebe a mensagem criptografada
	FILE*arquivo3; // arquivo de texto que recebe a mensagem discriptografada


	setlocale(LC_ALL, "");

	int opcao, p, q, e, totiente, n, i, d, valor [10000], contador,tamanho, msg_crip[10000];
	char mensagem [10000];

	do
	{
	
		printf("IIII                    IIII         IIIIIIIIIIIIIIIIIIIIII        IIIIIIII            IIII       IIII            IIII\n");
		printf("IIII IIII          IIII IIII         IIIIIIIIIIIIIIIIIIIIII        IIII  IIII          IIII       IIII            IIII\n");
		printf("IIII   IIII      IIII   IIII         IIII	                   IIII     IIII       IIII       IIII            IIII\n");
		printf("IIII     IIII  IIII     IIII         IIIIIIIIIIIIII                IIII       IIII     IIII       IIII            IIII\n");
		printf("IIII       IIII         IIII         IIIIIIIIIIIIII                IIII        IIII    IIII       IIII            IIII\n");
		printf("IIII                    IIII         IIII                          IIII          IIII  IIII       IIII            IIII\n");
		printf("IIII                    IIII         IIIIIIIIIIIIIIIIIIIIII        IIII           IIII IIII       IIII            IIII\n");
		printf("IIII	                IIII         IIIIIIIIIIIIIIIIIIIIII        IIII            IIIIIIII       IIIIIIIIIIIIIIIIIIII\n");


		printf("\n\n\n");
		printf("Escolha uma das opções abaixo:\n\n");

		printf("(1) Gerar chave pública\n");
		printf("(2) Criptografar\n");
		printf("(3) Descriptografar\n");
		printf("(0) Sair\n");

		printf("-->Opção:");
		scanf("%d", &opcao);

		system("clear");

		switch(opcao)
		{
		case 1: //GERANDO CHAVE PÚBLICA
			printf("Digite dois valores primos inteiros para (p), (q):\n");
			scanf("%d%d", &p, &q);

			if(primo(p)!=1 || primo(q)!=1)
			{
				while(primo(p)!=1 || primo(q)!=1)
				{
					printf("Números inválidos, digite apenas primos:\n");
					scanf("%d%d",&p,&q);
				}
			}

			n = p * q;

			totiente = (p - 1) * (q - 1);

			printf("(1) Digitar um valor para o expoente (e):\n");
			printf("(2) Escolher um valor aleatório para o expoente (e):\n");
			printf("-->Opção:");
			scanf("%d", &opcao);
			
			if(opcao==1)
			{
				scanf("%d", &e);
			}
			
			else
			{
				e = exp_aleatorio(totiente);	
			}
			

			arquivo1 = fopen("arquivo1.txt", "a"); //cria arquivo no diretorio do programa
			fprintf(arquivo1, "Chave pública:\nn=%d\ne=%d\n", n, e); // armazena os valores dos numeros primos usados
			fclose(arquivo1); // fecha arquivo

			printf("\n");
			printf("Chave pública (n,e): (%d,%d)\n",n,e);
			printf("Aperte (1) para continuar:");
			scanf("%d",&opcao);
			system("clear");

			break;

		case 2: //CRIPTOGRAFIA

			printf("Digite a Chave pública: (n,e)\n");

			scanf("%d%d",&n,&e);
			
			getchar();
		
			printf("Digite a mensagem:\n");
			scanf("%[^\n]",mensagem);
			
			tamanho = strlen(mensagem);

			for(i=0; i<tamanho; i++) //atribui as posicoes para cada letra
			{
				if(mensagem[i] == ' ')
				{
					valor[i] = mensagem[i] - 6;
				}
		
				else
				{
					valor[i] = mensagem[i] - 97;
				}
			}

			arquivo2 = fopen("arquivo2.txt","a");
			for(i=0; i<tamanho; i++) //criptografa a mensagem
			{
				if(mensagem[i] == ' ')
				{
					valor[i] = exp_mod_rap(valor,i, e , n);
					fprintf(arquivo2, "%d ", valor[i]);
				}
				else
				{
					if(i==tamanho-1)
					{
						valor[i] = exp_mod_rap(valor,i, e , n);
						fprintf(arquivo2, "%d", valor[i]);
					}
					
					else
					{
						valor[i] = exp_mod_rap(valor,i, e , n);
						fprintf(arquivo2, "%d ", valor[i]);
					}
				}
			}

			fclose(arquivo2);

			system("clear");
			printf("Mensagem criptografada: ");
			for (int j = 0; j < i; ++j) //imprime mensagem criptografada na tela
			{
				if (j==(i-1))
				{
					printf("%d", valor[j]);

				}

				else
				{
					printf("%d ", valor[j]);

				}
			}
			
			printf("\n");
			printf("Aperte (1) para continuar:");
			scanf("%d",&opcao);
			system("clear");
			break;

		case 3: //DESCRIPTOGRAFIA

			printf("Digite os valores de p, q, e:\n");
			scanf("%d%d%d",&p,&q,&e);

			n = p * q;

			totiente = (p - 1) * (q - 1);

			d = inverso(e,totiente); // calcula:  e mod [(p-1)*(q-1)]

			system("clear");
			printf("Digite a mensagem criptografada:\n");

			i=0;
			tamanho=0;
			do
			{
				scanf("%d",&msg_crip[i]);
				tamanho++;
				i++;
			}while(msg_crip[i-1]!=272019);

			
			for(i=0; i<tamanho-1; i++) //descriptografa a mensagem
			{
				msg_crip[i] = exp_mod_rap(msg_crip,i, d , n);
				
			}
			
			arquivo3 = fopen("arquivo3.txt","a");
			for(i=0; i<tamanho-1; i++)
			{

				if(msg_crip[i] == 26)
				{
					msg_crip[i]+=6;
					fprintf(arquivo3, "%c", msg_crip[i]);
				}
		
				else
				{
					msg_crip[i]+=97;
					fprintf(arquivo3, "%c", msg_crip[i]);
				}
			}
			fclose(arquivo3); // fecha arquivo

			system("clear");

			printf("Mensagem descriptografada: ");
			for (int j = 0; j < i; ++j)
			{
				printf("%c",msg_crip[j]);
			}

			printf("\n");
			printf("Aperte (1) para continuar:");
			scanf("%d",&opcao);
			system("clear");

			break;
		}

	}
	while(opcao != 0);


	return 0;
}
