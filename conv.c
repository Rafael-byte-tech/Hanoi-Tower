/*Funcao converte str para int subtraindo cada char por 
valores de 48 a 57 (ASCII) por 48 e multiplicado cada casa por 10*/
int stoi(const char *string)
{
	
	/*Declaracao de variaveis*/
	int integer, counter;
	short int sign;
	
	/*Instanciamento de variaveis*/
	counter = 0;	
	integer = 0; 
	sign = 1;
	
	/*Se string tem sinal de menos, o ponteiro avanca para o proximo char e o sinal eh multiplicado por -1*/
	if (string[0] == '-')
	{
		
		string += 1;
		sign *= -1;
		
	}
	
	/*Cada char eh convertido em int e multiplicado por 10 para ficar em sua respectiva casa decimal*/
	while(string[counter] != '\0')
	{
		
		if ((int)string[counter] < 48 || (int)string[counter] > 57)
		{
			
			return 0;
			
		}
		
		integer = integer * 10 + ((int)string[counter] - 48);
		
		counter++;
		
	}/*Fim de while*/
	
	return integer * sign;
	
}/*Fim de stoi*/

