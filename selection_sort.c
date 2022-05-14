#include<stdio.h>
#include<stdlib.h>

typedef struct ponto{
  int x;
  int y;
}Ponto;


int compara(Ponto * a, Ponto * b){
    if(b->x > a->x || (b->x == a->x && b->y > a->y)) return 1; // caso b seja maior que a, retorna 1
    if(a->x == b->x && a->y == b->y) return 0; // caso sejam iguais retorna 0
    else return -1 ; // caso a seja maior que b retorna 1
}

int encontra_max(Ponto *v, int esq, int dir){

    if (dir<=esq){ // para a recursividade quando o indice da esquerda e direita forem iguais
        return esq ;
    }
    if (compara (&v[esq], &v[dir]) == -1) { // caso o valor da esquerda seja maior que o da direita
         int maxx = encontra_max(v, esq, dir-1) ; // testa a proxima vez usando o valor da esquerda com direita -1
         return maxx ;
    }
    if (compara (&v[esq], &v[dir]) == 1){ // caso o valor da direita seja maior que o da esquerda
        int maxx = encontra_max(v, esq+1, dir) ;//testa o proximo com o valor da direita com esquerda -1
        return maxx ;
    }
return 0 ;
}

void selection_sort(Ponto *v, int tamanho){
    for(int i=tamanho-1 ; i>=0 ; i--){ // roda o vetor inteiro, da direita para esquerda, diminuindo uma posicao
        int max = encontra_max(v,0,i); // encontra o maior valor
        Ponto aux=v[max]  ; // coloca o maior valor na ultima posicao
        v[max]=v[i] ;
        v[i]= aux ;
    }
}

int main(int argc, char * argv[]){
  int tamanho;
  scanf("%d", &tamanho);
  Ponto * v = (Ponto *) malloc(sizeof(Ponto)*tamanho);

  srand(tamanho);
  for(int i = 0; i < tamanho; i++){
    v[i].x = rand()%tamanho;
    v[i].y = rand()%tamanho;
  }

  int indice_maior = encontra_max(v, 0, tamanho-1);

  printf("O maior é (%d, %d) ", v[indice_maior].x, v[indice_maior].y);
  printf("\n");

  selection_sort(v, tamanho);

  for(int i = 0; i < tamanho; i++){
    printf("(%d, %d) ", v[i].x, v[i].y);
  }
  printf("\n");
}

