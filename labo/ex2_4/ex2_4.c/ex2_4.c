#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int menu(void)
{
	int in_answer;
	printf("\n1.Conversion °F => C°\n2.Conversion °C => °F\n3.Conversion in => cm\n4.Conversion cm => in\n5.Quitter\nVotre choix? : ");
	scanf("%d%*c", &in_answer);
	return in_answer;
}

float take_float_input(char text[255]) 
{
	float input;
	printf("%s : ", text);
	scanf("%f%*c", &input);
	return input;
}

float temperature_convertion(float toConvert, int isInCelcius)
{
	
	float result;

	if(isInCelcius)
	{

		/*In celcius*/
		float left = (toConvert *  (9.0/5.0));
		float right = 32;
		result = left + right;

		
	}else
	{

		/*In Fahreineit*/
		float left = (toConvert-32);
                float right = 5.0/9.0;
                result = left * right;

	}

	return result;

}


float distance_convertion(float toConvert, int isInCm)
{

	float result;

	if(isInCm)
	{		

		/*In cm*/
		result = toConvert/2.54;

	}else
	{

		/*In in*/
		result = toConvert*2.54;

	}
	
	return result;
}

int main(void)
{	
	
	int answer;
	
	do
	{
		answer = menu();	
		
		switch(answer)
		{
			case 1: 
				{	
					/*°F => °C*/
					float toConvert = take_float_input(">>Enter a °F temperature to convert to °C");
					printf(">>>>%f °F is equal to %f °C\n", toConvert, temperature_convertion(toConvert, 0));
					break;
				}
			case 2: {
					float toConvert = take_float_input(">>Enter a °C temperature to convert to °F");
					printf(">>>>%f °C is equal to %f °F\n", toConvert, temperature_convertion(toConvert, 1));
					break;
				}
			case 3: {
					float toConvert = take_float_input(">>Enter a in distance to convert to cm");
					printf(">>>>%f in is equal to %f cm\n", toConvert, distance_convertion(toConvert, 0));
					break;
				}
			case 4: {	
					float toConvert = take_float_input(">>Enter a cm distance to convert to in");
					printf(">>>>%f cm si equal to %f in\n", toConvert, distance_convertion(toConvert, 1));
					break;
				}
			case 5: printf("Bye!\n"); break;
			default: printf("Option not available.\n");				

		}
		
	}while(answer != 5);
	
	return EXIT_SUCCESS;
	
}
