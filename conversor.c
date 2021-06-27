#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>

int main(int argc, char const *argv[]) {

  char mensagem[5];
  int valor [5];
  int i;
  scanf("%[^\n]",mensagem);

  for (i=0 ;i<5; i++)
  {
    if(mensagem[i]== ' ')
    {
      //printf("mensagem[%d]= %d\n",i,mensagem[i] - 6);
      valor[i]=mensagem[i];
      valor[i]-=6;
      printf("valor[%d] = %d\n",i,valor[i] );
    }
    else
    {
      //printf("mensagem[%d]= %d\n",i,mensagem[i] - 97);
      valor[i]=mensagem[i];
      valor[i]-=97;
      printf("valor[%d] = %d\n",i,valor[i] );
    }

  }

  return 0;
}
