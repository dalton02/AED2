#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct heap{
int max;
int pos; // Indica a posi??o do vetor
int* prior;	
};

typedef struct heap Heap;

Heap* criar(int max,int n){
	Heap* vetor =  (Heap*)malloc(sizeof(Heap));
	vetor->max = max;
	vetor->pos = 0;
	vetor->prior = (int*) malloc(max*sizeof(int));
	for(int i=n;i<max;i++){
		vetor->prior[i] = NULL;
	}
	return vetor;
}


void subir(Heap* vetor, int posicao,int x){
	vetor->prior[posicao]= x;
	int pai = posicao/2;		
	if(pai>=0){
	
		if(vetor->prior[posicao] > vetor->prior[pai]){
			int aux = vetor->prior[pai];
			vetor->prior[pai] = vetor->prior[posicao];
			vetor->prior[posicao] = aux;
			subir(vetor,pai,x);
		}
	}		
} 

void inserir(Heap* vetor, int x){
	if(vetor->pos < vetor->max){
		
		vetor->prior[vetor->pos] = x;
		subir(vetor,vetor->pos,x);
		vetor->pos++;
	
	}
}

void descer(Heap* vetor,int posicao,int n){
	int filho = (2*posicao)+1;
	if(filho<n){		
		if(filho+1 <n){
			if(vetor->prior[filho+1] > vetor->prior[filho])
					filho = filho+1;
			if(vetor->prior[posicao] < vetor->prior[filho]){
			int aux = vetor->prior[filho];
			vetor->prior[filho] = vetor->prior[posicao];
			vetor->prior[posicao] = aux;
			descer(vetor,filho,n);
			}
	}
}

}


int tamanho(Heap*vetor){
	int i=0;
	while(vetor->prior[i]!=NULL)
		i++
	return i;
	
}
void remocao(Heap*vetor){	
	if(vetor->pos>0){
		int raiz = vetor->prior[0];
		vetor->prior[0] = vetor->prior[vetor->pos-1];
		vetor->prior[vetor->pos-1] = NULL;
		vetor->pos--;
		descer(vetor,0,tamanho(vetor));
	}
	
}

Heap* construirHeap(int* v,int n){	
	Heap* vetor = criar(n*2,n);
	int a=0;
	while(a<n){
		inserir(vetor,v[a]);
		a++;
	}
	return vetor;
}

int trocas(Heap*vetor,int n){
	if (n<=0)
	return -1;
	int top = vetor->prior[0];
	vetor->prior[0] = vetor->prior[n-1];
	descer(vetor,0,n-1);
	return top;
}

void heapsort(Heap*vetor){
	int n = tamanho(vetor);
	int i = (floor((n - 2)/2))-1;
	while(i>=0){
		descer(vetor,i,n);
		i--;
	}
	while(n!=0){
    	vetor->prior[n-1] = trocas(vetor,n);
		n--;
	}
	if(vetor->prior[1]<vetor->prior[0]){
		int temp = vetor->prior[0];
		vetor->prior[0] = vetor->prior[1];
		vetor->prior[1] = temp;
	}
}

void imprimir(Heap* vetor){
	vetor->pos = 0;
	while(vetor->prior[vetor->pos] != NULL){
		printf(" %d ",vetor->prior[vetor->pos]);
		vetor->pos++;
	}
}

int main(){
	int heap[4] = {2,15,20,23,12};
	Heap* vetor = construirHeap(heap,4);
	printf("Heap formado pelo vetor acima: ");
	imprimir(vetor);
	printf("\nApos inserir novos elementos: ");
	inserir(vetor,24);
	inserir(vetor,19);
	inserir(vetor,7);
	imprimir(vetor);
	printf("\nVetor apos Heapsort: ");
	heapsort(vetor);
	imprimir(vetor);
	return 0;
}
