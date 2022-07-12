#include <stdio.h>
#include <stdlib.h>

//NAO ALTERE OS PONTOS SORTEADOS PARA OS BARCOS E TIROS
//Procure mexer o minimo possivel na main.
//basicamente voce precisa implementar as funcoes
//"adiciona_ponto" e "busca_ponto"


#define M 501409

typedef struct celula{
  int x;
  int y;
  struct celula * prox;
}celula;


int hash(int x, int y, int dimensao){
  if (dimensao > 40000){
    return (x + y)  % M;
  }
  else{
    return (x * y)  % M;
  }
   
}

int busca_ponto(celula ** oceano, int x, int y, int dimensao){
  int h = hash(x, y, dimensao);
  celula *p = oceano[h];
  while(p != NULL && (p->x != x || p->y != y)){
    p = p->prox;
    // passa para o proximo ponto ate chegar no final ou no ponto x e y 
  }
  if(p == NULL){
    return 0 ;
    //nao tem barco em x e y 
  }
  else{
    return 1 ;
    //tem barco em x e y
  }
}



 void adiciona_ponto(celula ** oceano, int x, int y, int dimensao){
  if(busca_ponto(oceano, x, y, dimensao) == 0){
    //local livre pra adicionar barco
    int h = hash(x, y, dimensao);
    celula * novo = (celula*) malloc(sizeof(celula));
    novo->x = x;
    novo->y = y;
    novo->prox = oceano[h];
    oceano[h] = novo;
  }
   else{
     // ja existe barco nesse local 
   }
}
void libera_oceano(celula ** oceano){
  free(oceano) ;
}


int main(int argc, char * argv[]){

  
  int dimensao;
  int num_pontos;
  int num_tiros;
  
  
  
  
  
  scanf("%d %d %d", &dimensao, &num_pontos, &num_tiros);
  printf("Campo %d x %d\nCada jogador coloca %d barcos\n\n", dimensao, dimensao, num_pontos);
  
  //Definindo uma semente para gerar os mesmos pontos
  srand(dimensao);

  
 //GUARDAR OS OCEANOS DE A E B, 
  celula **pontosJA = (celula**) malloc(M * sizeof(celula*));
  for(int i = 0; i < M; i++) pontosJA[i] = NULL;

  celula **pontosJB = (celula**) malloc(M * sizeof(celula*));
  for(int i = 0; i < M; i++) pontosJB[i] = NULL;
  
  //Jogador A gera pontos para colocar os barcos
  printf("Jogador A coloca barcos:\n");
  for(int i = 0; i < num_pontos; i++){
    int x, y;

    //sorteia um ponto que ja nao tenha um barco
    do{
      x = rand() % dimensao;
      y = rand() % dimensao; 
    }while(busca_ponto(pontosJA, x, y, dimensao) != 0); // Procura no oceano A se x, y ja tem barco
    
  
    if(i<5) printf("(%d, %d)\n", x, y);
    
   adiciona_ponto(pontosJA, x, y, dimensao); // Adiciona x, y no oceano A
  }
  
  
  //Jogador 2 gera pontos, com a estrategia (duvidosa) de colocar os pontos 
  //em mais ou menos em ordem crescente.
  printf("...\n\nJogador B coloca barcos:\n");
  for(int i = 0; i < num_pontos; i++){
    int x, y;
    //sorteia um ponto que ja nao tenha um barco
    do{
      x = i % dimensao;
      y = rand() % dimensao;
    }while(busca_ponto(pontosJB, x, y, dimensao) != 0); // Procura no oceano B se x, y ja tem barco
      
    if(i<5) printf("(%d, %d)\n", x, y);
    
  adiciona_ponto(pontosJB, x,y , dimensao); //Adiciona x, y no oceano B
  }
  
  printf("...\n\nCada jogador vai dar %d tiros\n", num_tiros);
  
  
  //Jogador 1 ataca pontos (aleatorios)
  int acertosJA = 0;
  printf("\nJogador A atira:\n");
  for(int i = 0; i < num_tiros; i++){
    int x = rand() % dimensao;
    int y = rand() % dimensao;
    if(i<5) printf("(%d, %d)\n", x, y);
    
    //Jogador A ataca os pontos de B
    if(busca_ponto(pontosJB, x, y, dimensao) == 1) acertosJA++; // Procura no oceano B se x, y tem barco
  }
  
  //Jogador B ataca pontos (aleatorios)
  int acertosJB = 0;
  printf("...\n\nJogador B atira:\n");
  for(int i = 0; i < num_tiros; i++){
    int x = rand() % dimensao;
    int y = rand() % dimensao;
    if(i<5) printf("(%d, %d)\n", x, y);

    //Jogador B ataca os pontos de A
    if(busca_ponto(pontosJA, x, y,dimensao) == 1) acertosJB++;
    // Procura no oceano A se x, y ja tem barco
  }
  
  printf("...\n\nResultado: Jogador A acertou %d e Jogador B %d\n", acertosJA, acertosJB);
  
  libera_oceano(pontosJA); libera_oceano(pontosJB); // Liberar memorias
  return 0;
}
