#include<stdio.h>
#include<stdlib.h>

typedef struct ponto{
  int x;
  int y;
}Ponto;

int compara(Ponto * a, Ponto * b){
    if(b->x > a->x || (b->x == a->x && b->y > a->y)) return 1; // caso b seja maior que a, retorna 1
    if(a->x == b->x && a->y == b->y) return 0; // caso sejam iguais retorna 0
    else return -1 ; // caso a seja maior que b retorna -1
}
// funcao que troca pontos
void troca(Ponto * a, Ponto *b){
    Ponto aux = *a;
    *a = *b;
    *b = aux;
}

void sobe_heap(Ponto *heap, int pos){
    if(pos == 0) return; // verifica se ta na raiz
    int pai = (pos-1)/2;
    // verifica se o filho eh maior que o pai, e troca caso sim
    if(compara(&heap[pos], &heap[pai])==-1){
        troca((&heap[pos]), (&heap[pai]));
        sobe_heap(heap, pai);
    }
}

// insere ponto na ultima posicao do vetor
void insere(Ponto *heap, int n, Ponto *valor){
    heap[n] = * valor;
    sobe_heap(heap, n);
    return;
}

void desce_heap(Ponto * heap, int n, int pos){
    int esq = 2*pos + 1;
    int dir = 2*pos + 2;
    int maior_filho ;
    if (esq>=n){
        return ;
    }
    // verifica quem eh o maior filho
    if(dir < n && compara(&heap[esq], &heap[dir])== -1) {
        maior_filho = esq;
    }
    else {
        maior_filho=dir ;
    }

    // verifica se o maior filho eh maior que o pai e troca caso sim
    if(compara(&heap[maior_filho], &heap[pos])==-1){
        troca(&heap[pos], &heap[maior_filho]);
        desce_heap(heap, n, maior_filho);
    }
}

// extrai a raiz e adiciona o ultimo valor do vetor nela
Ponto extrair(Ponto *heap, int n){
    Ponto maior = heap[0];
    heap[0] = heap[n-1];
    desce_heap(heap, n-1, 0);
    return maior;
}

int main(int argc, char* argv[]){
  int tamanho, tam_final;
  scanf("%d", &tamanho);
  Ponto * heap = (Ponto *) malloc(sizeof(Ponto)*tamanho);

  srand(tamanho);
  printf("Inserindo %d pontos\n", tamanho/2);
  for(int i = 0; i < tamanho/2; i++){
    Ponto valor;
    valor.x = rand()%tamanho;
    valor.y = rand()%tamanho;
    insere(heap,i,&valor) ;
  }

  printf("Extraindo os %d maiores\n", tamanho/4);
  for(int i = 0; i < tamanho/4; i++){

    Ponto maior = extrair(heap,tamanho/2-i) ;
    printf("(%d, %d) ", maior.x, maior.y);
    tam_final = tamanho/2-i ;
  }
  printf("\n");

   printf("Inserindo %d pontos\n", 3*tamanho/4);
  for(int i = 0; i < 3*tamanho/4; i++){
    Ponto valor;
    valor.x = rand()%tamanho;
    valor.y = rand()%tamanho;
    insere(heap,tam_final++,&valor) ;
  }


  printf("Extraindo os %d maiores\n", tamanho/2);
  for(int i = 0; i < tamanho/2; i++){


        Ponto maior = extrair(heap,tam_final--) ;
        printf("(%d, %d) ", maior.x, maior.y);
  }
  printf("\n");
  free(heap);

  return 0;

}
