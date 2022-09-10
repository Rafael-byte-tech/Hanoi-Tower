#include "hanoi.h"
#include "conv.h"

/*Funcao principal chama funcao da torre de hanoi*/
int main(int argc, char **argv)
{
	
	/*Declaracao de variaveis*/
	int dn;							/*Numero de discos*/
	short unsigned int f;	/*Flag indica se hanoi() deve imprimir o puzzle*/				
	
	/*Retorna funcao se nao houve entrada*/
	if (argv[1] == NULL)
	{
		
		return -1;
		
	}
	
	/*converte argv[1] para int*/
	dn = stoi(argv[1]);			
	
	/*atribui 1 para flag se a string argv[2] for igual "-v". Atribui 0 caso o contrario*/
	if (argv[2] != NULL && argv[2][0] == '-' && argv[2][1] == 'v')
	{
		
		f = 1; 
		
	}
	
	else 
	{
		
		f = 0;
		
	}
	
	hanoi(dn, &f);	/*funcao que simula a torre de hanoi*/
		
	return 0;

}/*Fim de main()*/