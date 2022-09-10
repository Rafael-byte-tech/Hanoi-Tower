#include <stdio.h>
#include "stack.h"
#include "conv.h"
#include "rod.h"

/*Funcao imprime configuracao das varas e discos no momento em que eh chamada*/
void printconfig(rd a, rd b, rd c)
{
	printf("\n   A: ");
	a->print(a);
	
	printf("\n   B: ");
	b->print(b);
	
	printf("\n   C: ");
	c->print(c);	
}/*Fim de printconfig*/

/*Funcao move qualquer disco, exceto 1, entre as duas pilhas que nao possuem 1 no topo (movimento par)
  rd1: vara a direita, rd2: vara a esquerda, flag: indica se imprime movimento(1) ou nao(0)*/
void evenmov(rd rd1, rd rd2, short unsigned int *flag)
{
	/*Declaracao de variaveis*/
	int rd1top, rd2top;	/*Discos no topo de cada pilha*/
	
	/*Instanciamento de variaveis*/
	rd1top = rd1->disks->peek(rd1->disks);
	rd2top = rd2->disks->peek(rd2->disks);
	
	/*	Move disco de rd2 para rd1 caso: "rd1 esteja vazia" ou
		"rd1 e rd2 nao estao vazias e o topo de rd1 > topo de rd2"	*/
	if (size(rd1->disks) == 1 || (size(rd2->disks) > 1 && rd1top > rd2top))
	{							
		rd1->disks->push(rd1->disks, rd2top);
		rd2->disks->pop(rd2->disks);
		
		/*Imprime movimento*/
		if (*flag == 1)
		{
			printf("\n   Move disk%d from %s to %s", rd2top, rd2->name, rd1->name);	
		}
	}
	
	/*	Move disco de rd2 para rd1 caso: "rd2 esteja vazia" ou
		"rd1 e rd2 nao estao vazias e o topo de rd2 > topo de rd1"	*/
	else 
	{
		rd2->disks->push(rd2->disks, rd1top);
		rd1->disks->pop(rd1->disks);
		
		/*Imprime movimento*/
		if (*flag == 1)
		{
			printf("\n   Move disk%d from %s to %s", rd1top, rd1->name, rd2->name);	
		}	
	}	
}/*Fim de evenmov*/

/*Move disco de valor 1 (movimento impar)
  rd1: vara a direita, rd2: vara a esquerda, pivot: vara com disco 1, flag: indica se imprime movimento(1) ou nao(0)*/
void oddmov(rd rd1, rd rd2, rd pivot, short unsigned int *flag)
{
	
	/*Declaracao de variaveis*/
	int pvtop;	/*Topo da pilha com disco 1*/
	
	/*Instanciamento de variaveis*/
	pvtop = pivot->disks->peek(pivot->disks);
	
	/*	Move disco 1 de pivot para rd1 caso:
		"rd1 esteja vazia e topo de rd2 eh impar", ou "rd1 tem topo par"	*/
	if((rd1->disks->get_size(rd1->disks) == 1 && rd2->disks->peek(rd2->disks) % 2 != 0) || (rd1->disks->peek(rd1->disks) % 2 == 0))
	{
		rd1->disks->push(rd1->disks, pvtop);
		
		/*Imprime movimento*/
		if (*flag == 1)
		{
			printf("\n   Move disk%d from %s to %s", pvtop, pivot->name, rd1->name);	
		}
	}
	
	/*	Move disco 1 de pivot para rd2 caso:
		"rd2 esteja vazia e topo de rd1 eh impar" ou "rd2 tenha topo par"	*/
	else 
	{
		rd2->disks->push(rd2->disks, pvtop);
		
		/*Imprime movimento*/
		if (*flag == 1)
		{
			printf("\n   Move disk%d from %s to %s", pvtop, pivot->name, rd2->name);	
		}
	}
	
	pop(pivot->disks);
}/*Fim de oddmov*/

/*Funcao simula torre de Hanoi
  dn: numero de discos, flag: indica se imprime movimento(1) ou nao(0)*/
void hanoi(int dn, short unsigned int *flag)
{
	/*Declaracao de variaveis*/
	rd a, b, c;	/*Pilha simula as varas (rods ou rd)*/
	
	/*Instanciamento de variaveis*/
	a = initrod();
	b = initrod();
	c = initrod();
	
	/*Nome das posicoes*/
	a->name = "A";
	b->name = "B";
	c->name = "C";
	
	/*Coloca os discos na pilha A de acordo com dn (numero de discos)*/
	for (int i=dn; i>0; i--)	
	{
		a->disks->push(a->disks, i);
	}
	
	/*Imprime apresentacao do problema*/
	if (*flag == 1)
	{
		printf("=> Solving the Tower of Hanoi with %d disks.\n=> Initial configuration:", dn);
		printconfig(a, b, c);
		printf("\n=> Moves:");	
	}
	
	/*Nao ha discos*/
	if (dn <= 0)
	{
		a->disks->push(a->disks, -1);
	}
	
	/*Se o dn eh par, o primeiro movimento serah disco 1 para a pilha B*/
	else if (dn % 2 == 0)	
	{
		b->disks->push(b->disks, a->disks->peek(a->disks));
		
		/*Imprime movimento*/
		if (*flag == 1)
		{
			printf("\n   Move disk%d from %s to %s", b->disks->peek(b->disks), a->name, b->name);	
		}
	}
	
	/*Se dn eh impar, o primeiro movimento serah disco 1 para a pilha C*/
	else 		
	{
		c->disks->push(c->disks, a->disks->peek(a->disks));
		
		/*Imprime movimento*/
		if (*flag == 1)
		{
			printf("\n   Move disk%d from %s to %s", c->disks->peek(c->disks), a->name, c->name);	
		}
	}
	
	a->disks->pop(a->disks);
		
	/*A iteracao continua enquanto o tamanho da pilha C (excluindo o -1 da base) for menor que o numero de discos*/
	while ((c->disks->get_size(c->disks) - 1) < dn)
	{	
		if (a->disks->peek(a->disks) == 1)	/*Verifica se topo de A eh 1*/
		{	
			evenmov(b, c, flag);	
			oddmov(b, c, a, flag);	
		}
		
		else if (b->disks->peek(b->disks) == 1)	/*Verifica se topo de B eh 1*/
		{
			evenmov(a, c, flag);
			oddmov(a, c, b, flag);
		}
		
		else	/*Topo de C eh 1*/
		{
			evenmov(a, b, flag);
			oddmov(a, b, c, flag);	
		}
	}/*Fim do while*/
		
	/*Imprime configuracao final das pilhas*/
	if (*flag == 1)
	{
		printf("\n=> Final configuration:");
		printconfig(a, b, c);
	}
	
	/*Libera as varas*/
	a->del(a);
	b->del(b);
	c->del(c);
}/*Fim de hanoi()*/