#include <stdlib.h>
#include <stdio.h>
#define SPECIFIER "%d" /*MACRO Contem especificador de tipo a ser usado na funcao printf()*/

/*As funcoes abaixo criam e manipulam pilhas formadas por nohs encadeados
Estrutura: (Topo da pilha)HEAD->NEXT->NEXT->NEXT->...->NEXT->NULL(Base da pilha)*/

/*-----------------------------------------------------------------------------------------------------------------*/

/*Tipo generico que pode ser modificado conforme o tipo de dado que se quer armazenar*/
int typedef type_info;

/*Struct dos nohs da pilha*/
struct node 
{
	
	type_info *data;	/*ponteiro para dado generico*/
	struct node *next;	/*ponteiro para o noh seguinte*/
	
}typedef node_t;

/*Struct da pilha*/
struct ADT_stack
{
	
	int *size;				/*ponteiro para o tamanho atual da pilha*/
	node_t *head;				/*ponteiro para o topo da pilha*/
	
	void (*del)(struct ADT_stack *);
	void (*print)(struct ADT_stack *);
	short unsigned int (*push)(struct ADT_stack *, type_info);
	short unsigned int (*pop)(struct ADT_stack *);
	type_info (*peek)(struct ADT_stack *);
	int (*get_size)(struct ADT_stack *);
	short unsigned int (*unstack)(struct ADT_stack *);
	
}typedef *stack_t;

/*-----------------------------------------------------------------------------------------------------------------*/
/*Pre declaracao das funcoes*/
stack_t create(void);
short unsigned int push(stack_t, type_info);
short unsigned int pop(stack_t);
type_info peek(stack_t);
int size(stack_t);
void print(stack_t);
short unsigned int unstack(stack_t);
void erase(stack_t);
/*-----------------------------------------------------------------------------------------------------------------*/
/*Funcao retorna uma nova pilha*/
stack_t	create(void)
{
	stack_t	newstack;											/*ponteiro para nova pilha*/
	newstack			=	(struct ADT_stack *)malloc (sizeof(struct ADT_stack));	/*aloca memoria para newstack*/
	
	newstack->size		=	(int *)malloc (sizeof(int));			/*aloca memoria para size*/

	*newstack->size		=	0;									/*tamanho atual da nova pilha recebe 0*/
	newstack->head		=	NULL;									/*topo da pilha eh nulo, pois ainda nao foi inserido nenhum dado*/
	
	newstack->push		=	push;
	newstack->pop		=	pop;
	newstack->peek		=	peek;
	newstack->get_size	=	size;
	newstack->print		=	print;
	newstack->unstack	=	unstack;
	newstack->del		=	erase;
	
	return newstack;							
}/*Fim da funcao*/

/*-----------------------------------------------------------------------------------------------------------------*/

/*Funcao adiciona novo elemento ao topo da pilha. Retorna 1 caso haja espaco na memoria, 0 caso o contrario*/
short unsigned int push(stack_t stack, type_info newdata)
{
	
	node_t *newnode;												/*novo noh*/
	newnode = (node_t *)malloc (sizeof(node_t));						/*aloca memoria para o noh*/
	newnode->data = (type_info *)malloc (sizeof (type_info)); 	/*aloca memoria para dado do noh*/
	
	/*Testa se o novo noh eh nulo, ou seja, nao ah mais memoria para adicionar ah pilha*/
	if (newnode == NULL)
	{
		
		return 0;							/*retorna 0 caso a pilha nao possa mais ser incrementada*/
		
	}
	
	*newnode->data = newdata;				/*aramazena o dado no novo noh*/
	newnode->next = stack->head;			/*o novo noh ficarah acima do atual topo da pilha*/
	stack->head = newnode;					/*o topo da pilha serah o novo noh*/
	
	*stack->size = *stack->size + 1;		/*incrementa o tamanho da pilha em 1*/
	
	return 1;								/*retorna 1 caso a pilha tenha sido incrementada com sucesso*/
	
}/*Fim da funcao*/

/*-----------------------------------------------------------------------------------------------------------------*/

/*Remove elemento do topo da pilha*/
short unsigned int pop(stack_t stack)
{
	
	node_t *temp;	/*ponteiro temporario para auxiliar na operacao*/
	
	/*Testa se o topo eh nulo, ou seja,se a pilha estah vazia*/
	if (stack->head == NULL)
	{
		
		return 0;	/*retorna 0 caso a pilha esteja vazia*/
		
	}
	
	temp = stack->head;					/*ponteiro temporario guarda o endereco do topo da pilha*/
	stack->head = stack->head->next;	/*o topo da pilha passa a ser o noh abaixo do atual topo*/

	*stack->size = *stack->size - 1;	/*decrementa o tamanho da pilha*/
	
	free(temp->data);	/*libera o ponteiro para o dado do noh*/
	free(temp);			/*libera o ponteiro temporario*/
	
	return 1;			/*retorna 1 caso o elemento no topo tenha sido removido com sucesso*/
	
}/*Fim da funcao*/

/*-----------------------------------------------------------------------------------------------------------------*/

/*Funcao retorna ponteiro para o dado guardado no topo da pilha*/
type_info peek(stack_t stack)
{
	
	return *stack->head->data;
	
}/*Fim da funcao*/

/*-----------------------------------------------------------------------------------------------------------------*/

/*Funcao retorna o tamanho da pilha*/
int size(stack_t stack)
{

	return *stack->size;
	
}/*Fim da funcao*/

/*-----------------------------------------------------------------------------------------------------------------*/

/*Funcao imprime todo o conteudo da pilha no terminal*/
void print(stack_t stack)
{
	/*Declaracao de variaveis*/
	node_t *content;	/*noh para iterar pilha*/
	
	content = stack->head;
	
	/*Enquanto a pilha nao estiver vazia os nohs serao impressos*/
	while(content != NULL)
	{
		
		printf(SPECIFIER, *content->data);
		printf(" ");
		content = content->next;
	}
	
	free(content);
	
}/*Fim da funcao*/

/*-----------------------------------------------------------------------------------------------------------------*/

/*Funcao libera todos os nohs da pilha*/
short unsigned int unstack(stack_t stack)
{

	/*Retorna 0 caso a pilha esteja vazia*/
	if (stack->head == NULL)
	{
			
		return 0;
		
	}
	
	/*libera os nohs ate a pilha estar vazia*/
	while (stack->head != NULL)
	{
		
		pop(stack);
		
	}
	
	return 1;
	
}/*Fim da funcao*/

/*-----------------------------------------------------------------------------------------------------------------*/

/*Funcao libera pilha*/
void erase(stack_t stack)
{
	
	unstack(stack);		/*limpa a pilha*/
	free(stack->head);	/*libera ponteiro para o topo*/
	free(stack->size);	/*libera ponteiro para o valor do tamanho*/
	free(stack);		/*libera ponteiro para a pilha*/
	
}