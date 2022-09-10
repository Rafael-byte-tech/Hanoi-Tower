#include <stdlib.h>
#include "stack.h"
#include <stdio.h>

/*Estrutura simula vara usada para posicionar discos na torre de hanoi*/
struct rod
{
	stack_t disks;		/*Pilha de inteiros simula discos*/
	char *name;		/*Nome da vara para usar na funcao printf*/
	
	void (*del)(struct rod *);
	void (*print)(struct rod *);
}typedef *rd;

/*-----------------------------------------------------------------------------------------------------------------*/
rd initrod(void);
void clearod(rd);
void printrod(rd);
/*-----------------------------------------------------------------------------------------------------------------*/
/*Funcao instancia variavel tipo rd*/
rd initrod(void)
{
	rd newrod;
	
	newrod = (rd)malloc (sizeof (struct rod));
	
	newrod->disks = create();		
	
	newrod->disks->push(newrod->disks, -1);
	
	newrod->del = clearod;
	newrod->print = printrod;
	
	return newrod;
}

/*-----------------------------------------------------------------------------------------------------------------*/

/*Funcao libera variavel do tipo rd*/
void clearod(rd rod)
{
	rod->disks->del(rod->disks);
	free(rod);	
}

/*-----------------------------------------------------------------------------------------------------------------*/

/*Funcao imprime todo o conteudo da vara no terminal*/
void printrod(rd rod)
{
	/*Declaracao de variaveis*/
	int *arr;	/*array para imprimir os discos na ordem desejada*/
	int height;	/*tamanho da pilha de discos*/
	
	/*Instanciamento de variaveis*/
	height = rod->disks->get_size(rod->disks);
	arr = (int *)malloc (height * sizeof(int));
	
	/*Preenche o array com os itens da vara do topo ate a base*/
	for(int i=height-1; i>-1; i--)
	{
		arr[i] = rod->disks->peek(rod->disks);
		rod->disks->pop(rod->disks);		
	}
	
	rod->disks->push(rod->disks, -1);
	
	/*imprime os dados da pilha comecando da base e terminando no topo*/
	for (int i=1; i<height; i++)
	{
		printf("%d", arr[i]);
		printf(" ");
		rod->disks->push(rod->disks, arr[i]);
	}		
	
	free(arr);	/*libera array*/
	
}/*Fim da funcao*/