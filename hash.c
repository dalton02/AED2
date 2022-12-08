#include <stdlib.h>
#include <stdio.h>

struct hash{
	int* valor;
	int m; // Zona normal
	int n; // Zona de conflito
};

typedef struct hash Hash;

Hash* criar(int m,int n){
	Hash* tabela = (Hash*) malloc(sizeof(Hash));
	tabela->valor = (int*) malloc((n+m)*sizeof(int));
	for(int i=0;i<(m+n);i++)
		tabela->valor[i] = NULL;
	tabela->m = m;
	tabela->n = n;
	return tabela;
}

void inserir(Hash* tabela,int x,int y){
	
	int posicao = gerarHash(x,y);
	if( tabela->valor[posicao] == NULL )
		tabela->valor[posicao] = x;
	else{
		int n = tabela->n;
		int m = tabela->m;
		if(tabela->valor[m] == NULL)
			tabela->valor[m] = x;
		else{
			while( tabela->valor[m] != NULL)
				m++;
			if(m<(n+m))
				tabela->valor[m] = x;			
		}
	}
}

void imprimir(Hash* tabela){
	int n = tabela->n;
	int m = tabela->m;
	printf("\n --------------TABELA HASH------------------- \n");
	int i=0;
	while(i<(m)){	
		printf(" %d ",tabela->valor[i]);
		i++;
	}
	printf("\n --------------ZONA DE COLISAO------------------- \n");
	i=m;
	while(i<(m+n)){
		printf(" %d ",tabela->valor[i]);
		i++;
	}
}

void deletar(Hash* tabela, int x,int y){
	int posicao = buscar(tabela,x,y);
	if(posicao != NULL)
	tabela->valor[posicao] = NULL;

}

int buscar(Hash* tabela, int x,int y){
	int posicao = gerarHash(x,y);
	if(tabela->valor[posicao] == x)
		return posicao;		
	else{
		int m = tabela->m;
		int n = tabela->n;
		while(tabela->valor[m] != x && m<(n+m))
			m++;
		if(tabela->valor[m] == x)
			return m;		
	}
	return NULL;
}

int gerarHash(int valor,int modulo){
	int posicao = valor % modulo;
	return posicao;
}

int main(){
	Hash* tabela = criar(3,5);	//Inserimos o tamanho da zona normal e o tamanho da zona de colisão
	int modulo=4;
	inserir(tabela,48,modulo); //(Inserir tabela,Inserir valor,Inserir modulo da função)
	inserir(tabela,49,modulo);
	inserir(tabela,4,modulo);
	inserir(tabela,50,modulo);
	inserir(tabela,8,modulo);
	imprimir(tabela);
	printf("\nvalor 8 esta na posicao: %d ",buscar(tabela,8,4));
	
	
}
