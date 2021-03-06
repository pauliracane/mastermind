#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

int numgen(char mynum[]);
int redcheck(char *changingNum, char *input);
int whitecheck(char *changingNum, char *input);


int main(void)
{
	int game = 0;

	do
	{
		char number[5]={'\0'};
		char malnumber[5]={'\0'};
		char guess[5]={'\0'};
		int red = 0, white=0, guesses=0;

		//Get random number
		numgen(number);

		//Assign malleable number to be same as random number
		for (int x = 0; x < 4; x++)
			malnumber[x]=number[x];

		//Until they guess the number
		for(;;)
		{

TOP:
			printf("Go ahead and guess, I dare you: ");
			//Check for appropriate input; If malicious users want to break my code, they can break it here.
			scanf("%100s", guess);
			//If it's too long, don't prompt again, until you're done going through	what they input
			if (strlen(guess)!=4)
				goto TOP;

			for (int x = 0; x < 4; x ++)
				if (!isdigit(guess[x]))
					goto TOP;

			guesses++;
			//Assign malleable number to be same as random number

			//Check their value for red numbers	
			red=redcheck(malnumber,guess);
			//check for white numbers.
			white = whitecheck(malnumber,guess);
			//Exit Condition
			if (red==4)
				goto WIN;
			printf("Red:%d,  White:%d\n\n", red, white);
                        //Assign malleable number to be same as random number
	                for (int x = 0; x < 4; x++)
                                malnumber[x]=number[x];

		}
WIN:
		printf("You Win!  It took you %d guesses.\n", guesses);
		//Play it Again Sports
		printf("Would you like to play again? (0 for no)\n");
		scanf("%2d", &game);
	}while(game != 0);

}






//As the name suggests, generate random number
int numgen(char mynum[])
{
	srand(time(NULL)+clock());
	int x=0;
	//Assign random number in to character arrays, for ease of mutation + checking
	for (x = 0; x < 4; x++)
		mynum[x]=rand()%10 + '0';
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

