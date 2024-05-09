#include "general_functions.h"
#include "source1.h"
#include "source2.h"
#include "source3.h"
#include "source4.h"
#include "source5.h"
#include "source6.h"
#include "source7.h"

/*____________________________________________________________________________
							 Chess Project

  information: The program is show 6 options for the user.
			   The user is insert a start position of the knight,
			   and than continues with another direction from the menu.

			   **The board is currently formatted to 5 * 5

______________________________________________________________________________
				Names : Bar Solomon |  Einat shahal
				ID :    314882432   |  315839431
______________________________________________________________________________*/

void main()
{
	int num;
	int j=0;
	char row, col;
	chessPos startingPosition;
	pathTree possibleKnight;
	chessPosList* lst = NULL;
	bool alreadyBuilt = false;

	printf(" ____  ____  ____  ____  ____  _________  ____  ____  ____  ____  ____  ____  ____\n ");
	printf("||c ||||h ||||e ||||s ||||s ||||       ||||p ||||r ||||o ||||j ||||e ||||c ||||t ||\n");
	printf("||__||||__||||__||||__||||__||||_______||||__||||__||||__||||__||||__||||__||||__||\n");
	printf("|/__/||/__/||/__/||/__/||/__/||/_______/||/__/||/__/||/__/||/__/||/__/||/__/||/__/|\n");
	printf("\n");
	printMenu();
	scanf("%d", &num);
	printf("\n");
	while (num != 6)
	{	
		if (num == 1)
		{
			printf("Please insert a position of the knight\n");
			scanf(" %c%c",&row, &col);
			while (checkPos(row, col) == false)
			{
				printf("Invalid position!!!!\n");
				printf("Please insert again a position of the knight\n");
				scanf(" %c%c", &row, &col);
			}
			j = 1;
		}
		else if (num == 2)
		{
			if (j !=1 )
			{
				printf("You didn't insert a position of the knight!\n");
				break;
			}

			startingPosition[0] = row;
			startingPosition[1] = col;

			possibleKnight = findAllPossibleKnightPaths(&startingPosition);
			alreadyBuilt = true;
		}
		else if (num == 3)
		{
			if (j!=1)
			{
				printf("You didn't insert a position of the knight!\n");
				break;
			}
			if (!alreadyBuilt)
			{
				startingPosition[0] = row;
				startingPosition[1] = col;

				possibleKnight = findAllPossibleKnightPaths(&startingPosition);
			}

			lst = findKnightPathCoveringAllBoard(&possibleKnight);
			

		}
		else if (num == 4)
		{
			if (j!=1)
			{
				printf("You didn't insert a position of the knight!\n");
				break;
			}

			int i = 0;
			char c;
			char fileName[SIZE];
			if (lst == NULL)
			{
				lst = findKnightPathCoveringAllBoard(&possibleKnight);
			}
			printf("Please enter file name:\n");
			scanf("%s", &fileName);
			saveListToBinFile(fileName, lst);
		}
		else if (num == 5)
		{
			int res;
			int i = 0;
			char c;
			char fileName6[SIZE];

			printf("Please enter file name:\n");
			scanf("%s", fileName6);
			res = checkAndDisplayPathFromFile(fileName6);

			if (res == -1)
			{
				printf("The file doesn't exist\n");
			}
			else if (res == 1)
			{
				printf("The list doesn't inculde a legal path of the knight\n");
			}
			else if (res == 2)
			{
				printf("The board is full\n");
			}
			else if (res == 3)
			{
				printf("The board isn't full\n");
			}
		}
		else
		{
			printf("Invalid choice!!!!");
		}
		printMenu();
		scanf("%d", &num);
	}
	
	if (lst !=NULL)
	{
		freeCpList(*lst);
	}
	freeTree(possibleKnight.root);

	return;
}

void printMenu()
{
	printf("\n");
	printf("1. Enter a knight's starting position\n");
	printf("2. Create all possible knight paths\n");
	printf("3. Find a knight path covering all board\n");
	printf("4. Save knight path covering all board to file\n");
	printf("5. Load and display path from file\n");
	printf("6. Exit\n");
	printf("\n");
}

bool checkPos(char row, char col)
{
	if (row >= 'A' && row <= 'H' && col >= '1' && col <= '8')
	{
		return true;
	}
	else
	{
		return false;
	}
}