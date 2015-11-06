#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int numgen(char mynum[]);
int redcheck(char *changingNum, char *input);
int whitecheck(char *changingNum, char *input);

int playself(char *changingNum, char *values);
int FindAnswer(char *values, char *guess, int guesses, char *changingNum, char *answer);

	
int main(void)
{
int game = 0;
do
{
	char number[5]={'x', 'x', 'x', 'x', '\0'};
	char values[5]={'x', 'x', 'x', 'x', '\0'};
	char guess [5]= {'\0'};
        char answer[5]={'x','x','x','x','\0'};
	int guesses=0;
        char malnumber[5] = {'\0'};
        //Get random number
        numgen(number);
	//Assign malleable number to be same as random number
	for (int x = 0; x < 4; x++)
               malnumber[x]=number[x];

	//Until they guess the number
	
	for(;;)
	{
	//Assign malleable number to be same as random number
	guesses = playself(malnumber, values);

        for (int x = 0; x < 4; x++)
               malnumber[x]=number[x];

	guesses = FindAnswer(values, guess, guesses, malnumber, answer);
	
	for (int x = 0; x < 4; x++)
               malnumber[x]=number[x];
	printf("The answer is: %s\n", answer);
	if (!(strncmp(number, answer, sizeof(answer))))
		break;
	}
	printf("You Win!  It took you %d guesses.\n", guesses);
	//Play it Again Sports
	printf("Would you like to play again? (0 for no)\n");
	scanf("%2d", &game);
} while(game != 0);
}






//As the name suggests, generate random number
int numgen(char mynum[])
	{
	srand(time(NULL)+clock());
	int x=0;
	//Assign random number in to character arrays, for ease of mutation + checking
	for (x = 0; x < 4; x++)
		mynum[x]=rand()%9 + '0';
	mynum[x]='\0';
	return 0;
	}

//Check values for 'red' pegs
int redcheck(char *changingNum, char *input)
	{
	int x = 0, red=0;
	//For each value in guess / number, if they're the same, +1 red peg
	for (x=0; x<4; x++)
		{
		if (changingNum[x]==input[x])
			{
			red++; 
			//Mutate the guess and the variable for 
			//the number I'm working with to avoid duplicate checks
			changingNum[x]='x';
			input[x]='y';
			}
		}
	return red;
	}

int whitecheck(char *changingNum, char *input)
	{
	int white = 0, x = 0, y = 0;
	//For each value in input, if it matches
	//any value in the number, increment white
	for (x=0; x<4; x++)
		{
		for (y=0; y<4; y++)
			{
			if (changingNum[y]==input[x])
				{
				//Mutate guess and the number
				//I'm working with.
				changingNum[y]='x';
				input[x]='y';
				white++;
				}
			}
		}
	return white;
	}



//This gets the values stored in the answer.
int playself(char *changingNum, char *values)
{
	//set asside storage for ints and arrays and what have you
	int y = 0, guesses = 0,red = 0;
	char answer[5]={'x', 'x', 'x', 'x', '\0'};
	char guess[5] = {'0','0','0','0','\0'};
//	char values[5] = {'x', 'x', 'x', 'x', '\0'};
	char wrong = 'w';
	//for each number
	for (int x = 0; x < 10; x++)
		{
		//Guess = 4 of that number
		for (int z = 0; z < 4; z++)
			guess[z]=x+'0';
		printf("Guessing: %s\n", guess);
		red = redcheck(changingNum,guess);
		printf("Got: %d Reds\n", red);
		guesses++;
		//If guess = answer, break, break, break.
		if (red == 4)
			{
			strncpy(answer, guess, sizeof(answer));
			break;
			}
		//Else, store that number into hte next 'y' spots of 'values'
		int z = y + red;
		for (y=y;y<z;y++)
			{
			values[y]=x+'0';
			}
		if (values[3]!='x')
			break;
		//if there is no reds, store that value at "wrong"
		if (!red)
			wrong = x + '0';
		}
	//Set all digits in guess to wrong
	for (int x = 0; x<4; x++)
		guess[x]=wrong;
	//Go through each value stored at Values in each location guess
	return guesses;
}
//I don't think I needed ot pass all of these in but...whatever.
int FindAnswer(char *values, char *guess, int guesses, char *changingNum, char *answer)
{
	
	for (int x = 0; x<4; x++){
		for (int y = 0; y < 4; y ++){
			//For each value in Values, assign to Guess[0],guess[1]...etc
			guess[x]=values[y];
			guesses++;
			//Check for reds in RXXX, then repeat on 2nd value.
			printf("Guessing: %s\n", guess);
			if(redcheck(changingNum,guess))
				{
				answer[x]=values[y];
				break;
				}
				//When last number is put in, exit for loop.
			if(answer[3]!='x')
				break;
		}
		
		if (answer[3]!='x')
			break;
	}
	return guesses;
}

