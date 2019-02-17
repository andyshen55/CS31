#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int divide(string a[], int n, string divider);

int main()
{
	string h[7] = { "greg", "gavin", "ed", "xavier", "", "eleni", "fiona" };
	assert(lookup(h, 7, "eleni") == 5);
	assert(lookup(h, 7, "ed") == 2);
	assert(lookup(h, 2, "ed") == -1);
	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "greg", "gavin", "fiona", "kevin" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "greg?" && g[3] == "kevin?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "fiona?" && g[3] == "gavin?");

	string e[4] = { "ed", "xavier", "", "eleni" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "gavin", "gavin", "gavin", "xavier", "xavier" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "fiona", "ed", "john" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "john" && f[2] == "fiona");

	assert(divide(h, 7, "fiona") == 3);
	
	cout << "All tests succeeded" << endl;
}

int appendToAll(string a[], int n, string value)
{
	if (n < 0)
		return -1;

	for (int i = 0; i < n; i++)
	{
		a[i] += value;
	}
	return n;
}

int lookup(const string a[], int n, string target)
{
	if (n < 0)
		return -1;

	for (int i = 0; i < n; i++)
	{
		if (a[i] == target)
			return i;
	}

	return -1;										//only returns -1 if none of the if statements in the for loop returns i.
}

int positionOfMax(const string a[], int n)
{
	if (n < 0)
		return -1;

	string currentMax = a[0];						//initializes currentMax outside of for loop so it doesnt get rewritten every iteration.

	for (int i = 0; i < n; i++)
	{
		if (a[i] >= currentMax)
			currentMax = a[i];
	}

	return lookup(a, n, currentMax);				//function finds position of biggest string then calls lookup with that position.
}

int rotateLeft(string a[], int n, int pos)
{
	if (n < 0 || n <= pos || pos < 0)
		return -1;

	string temp = a[pos];							//stores a[pos] in a temporary string before its overwritten in loop.
	int i = 0;

	while (i < (n - 1))
	{
		if (i < pos)
		{
			i++;
			continue;
		}

		if (i == pos)
		{
			while (i < (n - 1))
			{
				a[i] = a[i + 1];
				i++;
			}
		}
	}

	a[i] = temp;									//i will be last index at the end of looping. Stores temp back into a[i].
	return pos;
}

int countRuns(const string a[], int n)				//Ask smallberg about interaction with n = 0. edit: should return 0.
{
	if (n < 0)
		return -1;
	else if (n == 0)
		return 0;

	int count = 0;

	for (int i = 0; i < (n - 1); i++)
	{
		if (a[i] == a[i + 1])
			continue;
		else
			count++;
	}

	count++;										//previous for loop only checks second to last index. if last index is equal
													//to second last, count should be incremented because for loop makes it continue
	return count;									//without modifying count. if last index isnt, count should still be incremented.
}

int flip(string a[], int n)
{
	if (n < 0)
		return -1;

	string temp;									//initialize temp string to store copy of values being swapped in loops.

	for (int i = 0; i < (n / 2); i++)
	{
		temp = a[i];
		a[i] = a[(n - i) - 1];
		a[(n - i) - 1] = temp;
	}

	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return -1;

	int posOfDiffer = -1, smallerArray;				//-1 is chosen arbitrarily as a number < 0 (because 0 can be the position of a nonmatching pair).
													
	if (n1 <= n2)									//in the case n1 == n2, whichever array size is used as the number of
		smallerArray = n1;							//of iterations in the following for loop is arbitrary.
	else
		smallerArray = n2;

	for (int i = 0; i < smallerArray; i++)
	{
		if (a1[i] == a2[i])
			continue;
		else
			posOfDiffer = i;
		break;
	}

	if (posOfDiffer == -1)
		return smallerArray;
	else
		return posOfDiffer;
}

int subsequence(const string a1[], int n1, const string a2[], int n2) //Ask smallberg about interaction with n1 == 0. ie. size of examined array a1 = 0. edit. should return -1.
{
	if (n1 < 0 || n2 < 0)
		return -1;

	int k = 1;

	for (int j = 0; j < n1; j++)
	{
		if (a1[j] == a2[0])
		{
			while (k < n2)
			{
				if (a1[k + j] == a2[k])
				{
					k++;
				}
				else
					break;
			}

			if (k == n2)
				return j;
		}
	}

	if (n2== 0 || (n2 == 0 && n1 == 0))
		return 0;
	
	return -1;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2)
{
	if (n1 < 0 || n2 < 0)
		return -1;

	for (int i = 0; i < n1; i++)					//calls lookup on every element in a1.
	{
		if (lookup(a2, n2, a1[i]) != -1)
			return i;
	}

	return -1;
}

int divide(string a[], int n, string divider)		//Ask smallberg how divide handles multiple instances of the divider. edit: should be next to each other.
{
	if (n < 0)
		return -1;

	int leftOfDivider = 0, rightOfDivider = 0, nDividers = 0;	

	for (int i = 0; i < n; i++)						//Counts number of elements that should be in the left, middle and right of array.
	{
		if (a[i] < divider)
			leftOfDivider++;
		else if (a[i] == divider)
			nDividers++;
		else
			rightOfDivider++;
	}

	int currentIndex = 0;

	for (int j = 0; j < leftOfDivider; j++)
	{
		for (; currentIndex < n; currentIndex++)
		{
			if (a[currentIndex] < divider)
			{
				a[j] = a[currentIndex];				
				break;
			}
		}
	}

	currentIndex = 0;

	for (int j = leftOfDivider; j < (leftOfDivider + nDividers); j++)
	{
		for (; currentIndex < n; currentIndex++)
		{
			if (a[currentIndex] == divider)
			{
				a[j] = a[currentIndex];
				break;
			}
		}
	}

	currentIndex = 0;							

	for (int j = (leftOfDivider + nDividers); j < n; j++)
	{
		for (; currentIndex < n; currentIndex++)
		{
			if (a[currentIndex] > divider)
			{
				a[j] = a[currentIndex];		
				break;
			}
		}
	}

	if (rightOfDivider == 0 && nDividers != n)		//for when every element in array is divider.
		return n;
	else
		return leftOfDivider;
}