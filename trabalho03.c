#include<stdio.h>
#include<stdlib.h>

typedef struct ponto{
  int x;
  int y;
}Ponto;

 int compara(Ponto * a, Ponto * b){
    if(b->x > a->x || (b->x == a->x && b->y > a->y)) return 1; // caso b seja maior que a, retorna 1
    if(a->x == b->x && a->y == b->y) return 0; // caso sejam iguais retorna 0
    else
        return -1 ; // caso a seja maior que b retorna -1
}
// funcao que troca pontos
void troca(Ponto * a, Ponto *b){
    Ponto aux = *a;
    *a = *b;
    *b = aux;
}


void desce_heap(Ponto * v, int n, int pos){

    int esq = 2*pos + 1;
    int dir = 2*pos + 2;
    int maior_filho=dir ;

    if (esq>=n){
        return ;
    }
    // verifica quem eh o maior filho
    if(compara(&v[esq], &v[dir])== -1) {
        maior_filho = esq;
    }

    // verifica se o maior filho eh maior que o pai e troca caso sim
    if(compara(&v[maior_filho], &v[pos])==-1){
        troca(&v[pos], &v[maior_filho]);
        desce_heap(v, n, maior_filho);
    }
}

// extrai a raiz e adiciona o ultimo valor do vetor nela
Ponto extrair(Ponto *v, int n){
    Ponto maior = v[0];
    v[0] = v[n-1];
    desce_heap(v, n-1, 0);
    return maior ;
}
 //recebe um vetor qualquer, e transforma em um v
void constroi_heap(Ponto *v, int n){
    for(int i = n/2 ; i >= 0; i--){
      desce_heap(v, n, i);
    }
}

void HeapSort(Ponto *v, int tamanho){
    constroi_heap(v,tamanho) ; //transforma vetor em heap

    // extrai a raiz e realoca na ultima posicao da heap
    for(int i = 0; i < tamanho; i++){
        Ponto maior = extrair(v,tamanho-i) ;
        troca(&v[tamanho-i-1], &maior) ;
    }
}





//************* NAO MODIFIQUE A MAIN ****************/
int main(int argc, char * argv[]){
  int tamanho;
  scanf("%d", &tamanho);
  Ponto * v = (Ponto *) malloc(sizeof(Ponto)*tamanho);

  srand(tamanho);
  for(int i = 0; i < tamanho; i++){
    v[i].x = rand()%tamanho;
    v[i].y = rand()%tamanho;
  }

  HeapSort(v, tamanho);

  //imprimido a cada 1% (mais ou menos)
  for(int i = 0; i < tamanho; i += (tamanho/100) + 1){
    printf("(%d, %d) ", v[i].x, v[i].y);
  }
  printf("\n");
}

