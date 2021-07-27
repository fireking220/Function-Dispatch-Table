/*Scott Patterson
5/28/17
Assignment 4
Mark Morresy
This program takes in from the user a series of decimal numbers or hex values and either
adds, subtracts, or multiplies all the numbers from left to right. It will also
mod or divide the first two argv values. Lastly, it will print out the values in reverse order
e.g. 1 3 56 -> 65 3 1, this program will also make use of a function dispatch table to call functions
to eliminate pushing function calls onto the stack*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Code partially taken and modified from Mark Morresy for dispatch table and structs

#define maxItems 7

//struct for our menu
typedef struct _Menu{
	int numChoices;
	const char ** items;
} Menu;

//Parameter list for our functions
typedef struct {
        int argc;
        char ** argv;
} funcParam_t;

//pointer to our function with our parameters
typedef void funcPtr_t(funcParam_t *);

//Dispatch table
typedef struct {
        char * description;
        funcPtr_t * name;
} dispatchTableEntry_t;

//prototypes
void Exit(funcParam_t * param);
void add(funcParam_t * param);
void sub(funcParam_t * param);
void mult(funcParam_t * param);
void divide(funcParam_t * param);
void modulo(funcParam_t * param);
void reverse(funcParam_t * param);
void displayMenu(Menu * myMenu);

int main(int argc, char * argv[])
{
	if(argc == 1 || argc > 16)
	{
		printf("Enter the correct amount of arguments (1-15)\n");
		exit(0);
	}

	//dispatch table declaration
	dispatchTableEntry_t fdt[] = {
		{"Exit", Exit},
		{"Addition", add},
		{"Subtracttion", sub},
		{"Multiplication", mult},
		{"Division", divide},
		{"Modulo", modulo},
		{"Reverse Input", reverse}
	};
	Menu myMenu;
	int FDTcount = sizeof(fdt) / sizeof(fdt[0]);
	funcParam_t * paramList[FDTcount];
	char c;
	int func = 0;

	const char * choices[] = {"Exit", 
		   		"Addition", 
		   		"Subtraction",
		   		"Multiplication", 
		   		"Division",
		   		"Modulo",
		   		"Reverse Input"};
	myMenu.items = choices;
	myMenu.numChoices = sizeof(choices)/sizeof(choices[0]);
	do {
		displayMenu(&myMenu);
		printf("Enter a number: ");
		scanf("%c", &c);
		func = atoi(&c);

		if(isdigit(c) && (func >= 0 && func <= 6))
		{
			//code to call our function through our dispatch table
			paramList[func] = (funcParam_t *)malloc(sizeof(funcParam_t));
			paramList[func]->argc = argc;
			paramList[func]->argv = argv;
			printf("Invoking, %s\n", fdt[func].description);
			(*fdt[func].name)(paramList[func]);
			free (paramList[func]);
		}
		else
		{
			printf("Enter a valid menu choice (0-6)\n\n");
		}
		//loop to clear our buffer
		while(getchar() != '\n')
		{
			;
		}
	}while(c != '0');
	
	exit(0);
}

//function to exit
void Exit(funcParam_t * dummy)
{
	printf("Exiting...\n");
}

//function to add decimal or hexadecimal values
void add(funcParam_t * param)
{
	int sum = 0;
	int hexSum = 0;
	int argc = param->argc;

	for(int i = 1; i < argc; ++i)
	{
		char * argv = param->argv[i];
		int len = strlen(argv);

		//check if hex
		if(argv[0] == '0' && len > 2)
		{
			if(argv[1] == 'x' || argv[1] == 'X')
			{
				hexSum += (int)strtol(argv, NULL, 0);
			}
		}

		//check if digit
		else if(isdigit(*argv))
		{
			sum += atoi(argv);
		}
	}

	if(hexSum == 0)
	{
		printf("Sum: %d\n", sum);
	}
	else if(sum == 0)
	{
		printf("Sum: 0x%x\n", hexSum);
	}
	else
	{
		printf("Sum: %d + 0x%x\n", sum, hexSum);
	}
}

//function to subtract decimal or hexadecimal values
void sub(funcParam_t * param)
{
	int diff = 0;
	int hexDiff = 0;
	int argc = param->argc;

	//loop through our args
	for(int i = 1; i < argc; ++i)
	{
		char * argv = param->argv[i];
		int len = strlen(argv);

		//check if hex
		if(argv[0] == '0' && len > 2)
		{
			if(argv[1] == 'x' || argv[1] == 'X')
			{
				//if first hex encountered, set intitial value
				if(hexDiff == 0)
				{
					hexDiff = (int)strtol(argv, NULL, 0);
				}
				else
				{
					hexDiff -= (int)strtol(argv, NULL, 0);
				}
			}
		}

		//check if digit
		else if(isdigit(*argv))
		{
			//if first digit encountered, set initial value
			if(diff == 0)
			{
				diff = atoi(argv);
			}
			else
			{
				diff -= atoi(argv);
			}
		}
	}

	//decide how to display our data
	if(hexDiff == 0)
	{
		printf("Difference: %d\n", diff);
	}
	else if(diff == 0)
	{
		printf("Difference: 0x%x\n", hexDiff);
	}
	else
	{
		printf("Difference: %d - 0x%x\n", diff, hexDiff);
	}
}

//function to multiply decimal or hexadecimal values
void mult(funcParam_t * param)
{
	int product = 0;
	int hexProduct = 0;
	int argc = param->argc;

	for(int i = 1; i < argc; ++i)
	{
		char * argv = param->argv[i];
		int len = strlen(argv);

		//check if hex
		if(argv[0] == '0' && len > 2)
		{
			if(argv[1] == 'x' || argv[1] == 'X')
			{
				//if first hex encountered, set initial value
				if(hexProduct == 0)
				{
					hexProduct = (int)strtol(argv, NULL, 0);
				}
				else
				{
					hexProduct *= (int)strtol(argv, NULL, 0);
				}
			}
		}

		//check if digit
		else if(isdigit(*argv))
		{
			//if first digit encountered, set initial value
			if(product == 0)
			{
				product = atoi(argv);
			}
			else
			{
				product *= atoi(argv);
			}
		}
	}

	//decide how to display our data
	if(hexProduct == 0)
	{
		printf("Product: %d\n", product);
	}
	else if(product == 0)
	{
		printf("Product: 0x%x\n", hexProduct);
	}
	else
	{
		printf("Product: %d * 0x%x\n", product, hexProduct);
	}
}

//function to divide the first 2 decimal or hexadecimal values
void divide(funcParam_t * param)
{
	float quotient = 0;
	float nums[2] = {0, 0};
	int argc = param->argc;
	
	//calculate only if there exists 2 or more values
	if(argc > 2)
	{
		for(int i = 1; i < 3; ++i)
		{
			char * argv = param->argv[i];

			//if hex value
			if(argv[0] == '0' && (argv[1] == 'x' || argv[1] == 'X'))
			{
				nums[i - 1] = (float)strtol(argv, NULL, 0);
			}
			//if digit
			else
			{
				nums[i - 1] = atof(argv);
			}
		}
		quotient = nums[0] / nums[1];
		printf("Quotient: %f\n", quotient);
	}
	else
	{
		printf("Not enough values, at least 2 values needed to use divide\n");
	}
}

//function to mod the first 2 decimal or hexadecimal values
void modulo(funcParam_t * param)
{
	int remainder = 0;
	int nums[2] = {0, 0};
	int argc = param->argc;
	
	//calculate only if there exists 2 or more values
	if(argc > 2)
	{
		for(int i = 1; i < 3; ++i)
		{
			char * argv = param->argv[i];

			//if hex value
			if(argv[0] == '0' && (argv[1] == 'x' || argv[1] == 'X'))
			{
				nums[i - 1] = (int)strtol(argv, NULL, 0);
			}
			//if digit
			else
			{
				nums[i - 1] = atoi(argv);
			}
		}
		remainder = nums[0] % nums[1];
		printf("Modulo: %d\n", remainder);
	}
	else
	{
		printf("Not enough values, at least 2 values nedded to use modulo\n");
	}
}

//function to reverse the order of the arg list
void reverse(funcParam_t * param)
{
	int len = 0;
	int argc = param->argc;

	for(argc; argc > 1; --argc)
	{
		char * argv = param->argv[argc - 1];
		len = strlen(argv);
		for(len; len >= 0; --len)
		{
			printf("%c", argv[len]);
		}
		printf(" ");
	}
	printf("\n");
}

void displayMenu(Menu * myMenu)
{
	int max = myMenu->numChoices;

	for(int i = 0; i < max; ++i)
	{
		printf("%d. %s\n", i, myMenu->items[i]);
	} 
}
