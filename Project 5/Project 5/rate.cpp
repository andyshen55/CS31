#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cctype>
#include <cstring>
#include <assert.h>
using namespace std;

const int MAX_WORD_LENGTH = 20;
const int MAX_DOCUMENT_LENGTH = 250;

int makeProper(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns);
int rate(const char document[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1], const int separation[], int nPatterns);
void makeLower(char word[], int& nonAlpha);
void removePattern(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns, int position);
void setWord(const char tempDoc[], char tempWord[], int& j);

int main()
{
	const int TEST1_NRULES = 4;
	char test1w1[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"mad",       "deranged", "nefarious", "have"
	};
	char test1w2[TEST1_NRULES][MAX_WORD_LENGTH + 1] = {
		"scientist", "robot",    "plot",      "mad"
	};
	int test1dist[TEST1_NRULES] = {
		1,           3,          0,           12
	};
	assert(rate("The mad UCLA scientist", test1w1, test1w2, test1dist, 0) == 0);
	assert(rate("The mad UCLA scientist", test1w1, test1w2, test1dist, -99) == 0);
	assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.", test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("The mad UCLA scientist unleashed    a deranged robot.", test1w1, test1w2, test1dist, TEST1_NRULES) == 2);
	assert(rate("**** 2018 ****", test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	assert(rate("  That plot: NEFARIOUS!", test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("deranged deranged robot deranged robot robot", test1w1, test1w2, test1dist, TEST1_NRULES) == 1);
	assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.", test1w1, test1w2, test1dist, TEST1_NRULES) == 0);
	cout << "All tests succeeded" << endl;
}

int makeProper(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns)
{
	if (nPatterns < 0)
		nPatterns = 0;

	int i = 0, nonAlpha = 0;
	for (i = 0; i < nPatterns; i++)
	{
		makeLower(word1[i], nonAlpha);
		makeLower(word2[i], nonAlpha);
		//if nonAlpha is unchanged, should evaluate false because 0 = false.
		if (nonAlpha || separation[i] < 0 || strlen(word1[i]) == 0 || strlen(word2[i]) == 0)
		{
			removePattern(word1, word2, separation, nPatterns, i);
			//Both indexes are decremented to account for everything being shifted left. The index of the removed pattern now contains an unchecked pattern pair.
			i--;
			nPatterns--;
			//Resets nonAlpha to 0 so it evaluates false.
			nonAlpha = 0;
		}
	}
	for (i = 0; i < nPatterns; i++)
	{
		//j initialized to one more than i because every element only needs to be compared once against every other element.
		for (int j = i + 1; j < nPatterns; j++)
		{
			//!strcmp() is same as strcmp() == 0.
			if ((!strcmp(word1[i], word1[j]) && !strcmp(word2[i], word2[j])) ||
				(!strcmp(word1[i], word2[j]) && !strcmp(word2[i], word1[j])))
			{
				if (separation[i] < separation[j])
					removePattern(word1, word2, separation, nPatterns, i);
				else
					removePattern(word1, word2, separation, nPatterns, j);
				nPatterns--;
			}
		}
	}
	return nPatterns;
}

int rate(const char document[], const char word1[][MAX_WORD_LENGTH + 1], const char word2[][MAX_WORD_LENGTH + 1], const int separation[], int nPatterns)
{
	if (nPatterns < 0)
		nPatterns = 0;

	char tempDoc[MAX_DOCUMENT_LENGTH + 1], tempWord[MAX_WORD_LENGTH + 1];
	//tempIndex used to keep track of position of temporary word to be assigned char.
	int tempIndex = 0, i = 0, rate = 0;
	while (document[i] != '\0')
	{
		if (isalpha(document[i]) || isspace(document[i]))
		{
			tempDoc[tempIndex] = tolower(document[i]);
			tempIndex++;
		}
		i++;
	}
	//When while loop breaks, tempIndex will still be incremented. Null byte is appended to turn into C-string.
	tempDoc[tempIndex] = '\0';

	for (i = 0; i < nPatterns; i++)
	{
		int j = 0, k;
		//The number of whitespace characters is one more than the separator. 
		int numSpaces = (separation[i] + 1);
		//boolean value used to form break condition for while loop. break; will only break out of for loop.
		bool noPattern = true;
		while (noPattern && tempDoc[j] != '\0')
		{
			//Every time setWord is called, it stores the next word in the temporay word array. 
			setWord(tempDoc, tempWord, j);
			if (!strcmp(word1[i], tempWord))
			{
				//calls setWord numSpaces times, compares numSpaces words after matched word.
				for (k = 0; k < numSpaces; k++)
				{
					setWord(tempDoc, tempWord, j);
					if (!strcmp(word2[i], tempWord))
					{
						noPattern = false;
						rate++;
						break;
					}
				}
			}
			else if (!strcmp(word2[i], tempWord))
			{
				for (k = 0; k < numSpaces; k++)
				{
					setWord(tempDoc, tempWord, j);
					if (!strcmp(word1[i], tempWord))
					{
						noPattern = false;
						rate++;
						break;
					}
				}
			}
		}
	}
	return rate;
}

void makeLower(char word[], int& nonAlpha)
{
	int n = 0;
	while (word[n] != '\0')
	{
		if (!(isalpha(word[n])))
		{
			//increments nonAlpha so it will evaluate to true in makeProper.
			nonAlpha++;
			break;
		}
		word[n] = tolower(word[n]);
		n++;
	}
	word[n] = '\0';
}

void removePattern(char word1[][MAX_WORD_LENGTH + 1], char word2[][MAX_WORD_LENGTH + 1], int separation[], int nPatterns, int position)
{
	//nPatterns - 1 is the condition to prevent accessing beyond the null byte.
	for (int k = position; k < nPatterns - 1; k++)
	{
		//removes pair at index k by reassigning it to the pair to the right repeatedly.
		strcpy(word1[k], word1[k + 1]);
		strcpy(word2[k], word2[k + 1]);
		separation[k] = separation[k + 1];
	}
}

void setWord(const char tempDoc[], char tempWord[], int& j)
{
	int wordIndex = 0;
	//ignores whitespace characters
	while (isspace(tempDoc[j]))
		j++;
	while (isalpha(tempDoc[j]))
	{
		tempWord[wordIndex] = tempDoc[j];
		j++;
		wordIndex++;
	}
	tempWord[wordIndex] = '\0';
}