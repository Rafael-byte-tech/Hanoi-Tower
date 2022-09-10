#ifndef __stack_h_
#define __stack_h_

#define SPECIFIER "%d"
/*------------------------------------------------------------------------------------------------------------------*/

int typedef type_info;

struct		node 
{
	type_info	*data;	
	struct node	*next;
}typedef	node_t;

struct		ADT_stack
{
	int		*size;	
	node_t	*head;
	
	void				(*del)(struct ADT_stack *);
	void				(*print)(struct ADT_stack *);
	short unsigned int	(*push)(struct ADT_stack *, type_info);
	short unsigned int	(*pop)(struct ADT_stack *);
	type_info			(*peek)(struct ADT_stack *);
	int					(*get_size)(struct ADT_stack *);
	short unsigned int	(*unstack)(struct ADT_stack *);
}typedef	*stack_t;

/*------------------------------------------------------------------------------------------------------------------*/

stack_t	create(void);

short unsigned int	push(stack_t stack, type_info newdata);

short unsigned int	pop(stack_t stack);

type_info			peek(stack_t stack);

int					size(stack_t stack);

void				print(stack_t stack);

short unsigned int	unstack(stack_t stack);

void				erase(stack_t stack);

/*------------------------------------------------------------------------------------------------------------------*/
#endif