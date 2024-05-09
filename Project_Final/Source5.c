#include "general_functions.h"
#include "source5.h"

void saveListToBinFile(char* fileName, chessPosList* pos_list)
{
	unsigned char bytes[3];
	int i, remainder, count = 0;
	short size;
	unsigned int row, col, finalLocation = 0, temp, currLocation = 0;
	chessPosCell* cell = pos_list->head;
	FILE* file;
	file = fopen(fileName, "wb");

	size = sizeOfChessPossList(pos_list);
	fwrite(&size, sizeof(size), 1, file);

	while (cell != NULL)
	{
		//מיקום אחד, נאחד את השורות והעמודות לידי משתנה אחד
		row = ((LetterToNumber(cell->position[0]) - '0') - 1) << 5;
		col = ((cell->position[1] - '0') - 1) << 2;
		currLocation = row | col;

		if (count == 0) //אם המשתנה ריק
		{
			finalLocation = currLocation;
			count++;
		}
		else if (count == 1 || count == 2)
		{
			finalLocation = finalLocation << 6;
			finalLocation = finalLocation | currLocation;
			count++;
		}
		else if (count == 3) //אם כבר יש 4 מיקומים במשתנה נרוקן את המשתנה ונכתוב לקובץ
		{
			finalLocation = finalLocation << 6;
			finalLocation = finalLocation | currLocation;
			finalLocation = finalLocation >> 2;

			bytes[0] = (finalLocation >> 16) & 0xFF;
			bytes[1] = (finalLocation >> 8) & 0xFF;
			bytes[2] = (finalLocation) & 0xFF;

			fwrite(&(bytes[0]), sizeof(char), 1, file);
			fwrite(&(bytes[1]), sizeof(char), 1, file);
			fwrite(&(bytes[2]), sizeof(char), 1, file);
			fflush(file);

			count = 0;
			finalLocation = 0;
		}

		cell = cell->next;
	}



	if (count == 1)
	{
		bytes[0] = (finalLocation) & 0xFF;
		fwrite(&(bytes[0]), sizeof(char), 1, file);
	}
	else if (count == 2)
	{
		bytes[0] = (finalLocation >> 6) & 0xFF;
		bytes[1] = (finalLocation << 2) & 0xFF;
		fwrite(&(bytes[0]), sizeof(char), 1, file);
		fwrite(&(bytes[1]), sizeof(char), 1, file);
	}
	else if (count == 3)
	{
		bytes[0] = (finalLocation >> 12) & 0xFF;
		bytes[1] = (finalLocation >> 4) & 0xFF;
		bytes[2] = ((finalLocation) & 0xFF) << 4;

		fwrite(&(bytes[0]), sizeof(char), 1, file);
		fwrite(&(bytes[1]), sizeof(char), 1, file);
		fwrite(&(bytes[2]), sizeof(char), 1, file);
	}



	fclose(file);
}

short int sizeOfChessPossList(chessPosList* pos_list)
{
	short int size = 0;
	chessPosCell* cell = pos_list->head;

	while (cell != NULL)
	{
		size++;
		cell = cell->next;
	}
	return size;
}

