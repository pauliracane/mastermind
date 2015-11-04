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
	char number[5]={'\0'};
	char malnumber[5]={'\0'};
	char guess[5]={'\0'};
	int red = 0, white=0, guesses=0;

        //Get random number
        numgen(number);
	//Until they guess the number
	for(;;)
	{
TOP:
	printf("Go ahead and guess, I dare you: ");
	//Check for appropriate input
	scanf("%20s", guess);
	//If it's too long, don't prompt again, until you're done going through 	what they input
	//The current issue: If guess length % 5 == 4, it'll run, if guess 		length %5 = 0, it'll "hang" on the scan, and wait on input...
	if (strlen(guess)!=4)
		goto TOP;
	for (int x = 0; x < 4; x ++)
		if (isalpha(guess[x]))
			goto TOP;

	guesses++;
	
	//Assign malable number to be same as random number
	for (int x = 0; x < 4; x++)
		malnumber[x]=number[x];
	
	//Check their value for red numbers	
	red=redcheck(malnumber,guess);
	//check for white numbers.
	white = whitecheck(malnumber,guess);
	//Exit Condition
	if (red==4)
		goto WIN;
	printf("Red:%d,  White:%d\n\n", red, white);
	}
WIN:
	printf("You Win!  It took you %d guesses.\n", guesses);
}


int numgen(char mynum[])
	{
	srand(time(NULL)+clock());
	int x=0;
	for (x = 0; x < 4; x++)
		mynum[x]=rand()%9 + '0';
	mynum[x]='\0';
	return 0;
	}


int redcheck(char *changingNum, char *input)
	{
	int x = 0, red=0;
	for (x=0; x<4; x++)
		{
		if (changingNum[x]==input[x])
			{
			red++;
			changingNum[x]='x';
			input[x]='y';
			}
		}
	return red;
	}

int whitecheck(char *changingNum, char *input)
	{
	int white = 0, x = 0, y = 0;
	for (x=0; x<4; x++)
		{
		for (y=0; y<4; y++)
			{
			if (changingNum[y]==input[x])
				{
				changingNum[y]='x';
				input[x]='y';
				white++;
				}
			}
		}
	return white;
	}

