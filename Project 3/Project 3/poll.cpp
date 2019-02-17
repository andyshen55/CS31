#include <iostream>
#include <cctype>
#include <string>
#include <cassert>
using namespace std;

void makeUpper(string& pollData);								// changes all lowercase letters to upper case within a given string
bool hasProperSyntax(string pollData);							// function 1 in project 3 spec
bool isValidUppercaseStateCode(string stateCode);				// checks if state codes are valid
bool validStateForecastSyntax(string tempString);				// checks if stateforecast (the substring following the state code) is valid
int tallySeats(string pollData, char party, int& seatTally);	// function 2 in project 3 spec

int main()
{
	assert(hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00D"));
	assert(!hasProperSyntax(",CT5D,NY9R17D1I,VT,ne3r00D"));
	assert(!hasProperSyntax("CT5D,NY9R17&1I,VT,ne3r00D"));
	assert(!hasProperSyntax("CT5D,NY9 R17D1I,VT,ne3r0 0D"));
	assert(!hasProperSyntax("CT5D,NY9 R17D1I,VT,ne3r00 D"));
	assert(!hasProperSyntax("    "));
	assert(!hasProperSyntax("NY9R17D1I, Vt, NJ3d5r4D, KS4R"));
	assert(!hasProperSyntax("TY9R17D1I,Vt,NJ3d5r4D,KS4R"));
	assert(!hasProperSyntax("NY922R17D1I,Vt,NJ3d5r4D,KS4R"));
	assert(hasProperSyntax("NY"));
	assert(!hasProperSyntax("CA32"));
	assert(!hasProperSyntax("NYd"));
	int seats = -999;
	assert(tallySeats("CT5d,NY9R17D1I,VT,ne3r00d", 'd', seats) == 0 && seats == 22);
	seats = -999;
	assert(tallySeats("CT5D,NY9R17D1I,VT,ne3r00D", '%', seats) == 2 && seats == -999);
	assert(tallySeats("CA32", 'D', seats) == 1 && seats == -999);
	assert(tallySeats("CA", 'D', seats) == 0 && seats == 0);
	seats = -999;
	assert(tallySeats("", 'D', seats) == 0 && seats == 0);
	assert(hasProperSyntax("MA9D,KS4R") && hasProperSyntax("KS4R,MA9D"));
	assert(hasProperSyntax("MA9D,,KS4R") == hasProperSyntax("KS4R,,MA9D"));
	assert(hasProperSyntax("CT5D,NY9R17D1I,VT,ne3r00D"));
	assert(!hasProperSyntax(",CT5D,NY9R17D1I,VT,ne3r00D"));
	assert(!hasProperSyntax(" CT5D,NY9R17D1I,VT,ne3r00D"));
	assert(!hasProperSyntax("!CT5D,NY9R17D1I,VT,ne3r00D"));
	assert(!hasProperSyntax("CT5DNY9R17D1IVTne3r00D"));
	assert(!hasProperSyntax("CT5D5,NY9R17D1I,VT,ne3r00D"));
	assert(!hasProperSyntax("CT5D5, NY9R17D1I,VT,ne3r00D"));
	assert(!hasProperSyntax("CT5D5 ,NY9R17D1I,VT,ne3r00D"));
	assert(!hasProperSyntax("CT5D5, NY9R17D1I ,VT,ne3r00D"));
	assert(!hasProperSyntax("KS4R, NV3D1R "));
	assert(!hasProperSyntax("aaaaaaa"));
	assert(!hasProperSyntax("a"));
	assert(!hasProperSyntax("NY, ,"));
	assert(!hasProperSyntax("KS 4R"));
	assert(hasProperSyntax("KS4R"));
	assert(hasProperSyntax("KS4r"));
	assert(!hasProperSyntax("KS4R,"));
	assert(hasProperSyntax("KS4R"));
	assert(!hasProperSyntax("ne3r00"));
	assert(!hasProperSyntax("ne3r000D"));
	assert(!hasProperSyntax("3r00D"));
	assert(!hasProperSyntax("ner000D"));
	assert(!hasProperSyntax("ne3r 000D"));
	assert(!hasProperSyntax("ne3rr00D"));
	assert(!hasProperSyntax("ne3rD"));
	assert(!hasProperSyntax("ne3r00D3"));
	assert(!hasProperSyntax("ex3r00D3"));
	assert(!hasProperSyntax("ne3r00DD"));
	assert(!hasProperSyntax("ne3"));
	assert(!hasProperSyntax("ne3r9"));
	assert(hasProperSyntax(""));
	assert(hasProperSyntax("NY"));
	assert(!hasProperSyntax("N7Y"));
	assert(!hasProperSyntax("NY4"));
	assert(!hasProperSyntax("NY4 "));
	assert(!hasProperSyntax(" NY4"));
	assert(!hasProperSyntax("$$,!!,6I"));
	assert(!hasProperSyntax("ny,!!,6I"));
	assert(!hasProperSyntax("ny09I,!!,6I"));

	int seatTally = 0;
	tallySeats("VA7R,KS4R", 'r', seatTally);
	assert(seatTally == 11);
	tallySeats("VA7R,KS4R4", 'r', seatTally);
	assert(seatTally == 11);
	tallySeats("VA71R,KS4R", 'r', seatTally);
	assert(seatTally == 75);
	tallySeats("NY", 'r', seatTally);
	assert(seatTally == 0);

	assert(tallySeats("NY", '@', seatTally) == 2);
	assert(seatTally == 0);

	assert(tallySeats("NY3", 'r', seatTally) == 1);
	assert(seatTally == 0);
	seatTally = 3;
	assert(tallySeats("", 'r', seatTally) == 0);
	assert(seatTally == 0);
	assert(tallySeats("CA99D", 'D', seatTally) == 0);
	assert(seatTally == 99);

	assert(tallySeats("CAD", 'D', seatTally) == 1);
	assert(seatTally == 99);
	assert(tallySeats("", 'D', seatTally) == 0);
	assert(seatTally == 0);
	assert(tallySeats("CA99D", '6', seatTally) == 2);
	assert(seatTally == 0);
	cout << "All tests succeeded" << endl;
}

bool hasProperSyntax(string pollData)
{
	if (pollData == "")
		return true;

	makeUpper(pollData);

	int j = 0;
	while (j < pollData.size())
	{
		string tempString = "";	// stores all non-comma values into a temporary string.
		while (pollData[j] != ',' && j != pollData.size())
		{
			tempString += pollData[j];
			j++;
		}

		if (!(validStateForecastSyntax(tempString)))
		{
			return false;
		}
		else if (j == pollData.size() - 1 && pollData[j] == ',')
			return false;

		j++;	// increments j to avoid infinite loop where pollData[j] == ','
	}
	return true;
}

int tallySeats(string pollData, char party, int& seatTally)
{
	if (!(hasProperSyntax(pollData)))
		return 1;
	else if (!(isalpha(party)))
		return 2;
	else if (pollData.size() <= 2)
	{
		seatTally = 0;	// sets seatTally = 0 when function returns 0
		return 0;
	}

	makeUpper(pollData);
	char upperParty = toupper(party);			// parses pollData for uppercase version of party because when hasProperSyntax
	seatTally = 0;								// is called it makes everything uppercase.
	for (int l = 3; l != pollData.size(); l++)	// l initialized to 3 because it's impossible for the first 3 chars in pollData
	{											// to have returned true for hasProperSyntax if they were a party code.
		string tempSeats = "";

		if (pollData[l] == upperParty)
		{
			if (isdigit(pollData[l - 2]))	// Checks to make sure party code isnt part of a state code. Also checks number of digits
			{								// preceeding the party code.
				tempSeats += pollData[l - 2];
				tempSeats += pollData[l - 1];
				seatTally += stoi(tempSeats);	// stoi converts string to integer
			}
			else
			{
				tempSeats += pollData[l - 1];
				seatTally += stoi(tempSeats);
			}
		}
	}
	return 0;
}


bool validStateForecastSyntax(string tempString)
{
	if (!(isValidUppercaseStateCode(tempString.substr(0, 2))))
		return false;
	else if (tempString.size() == 2)	// checks if given string is just a state code (which should return true)
		return true;

	int k = 2;							// k initialized at 2 because first two indexes are the state code
	while (k < tempString.size())
	{
		string partySeats = "";
		while (isdigit(tempString[k]) && k != tempString.size() - 1 && partySeats.size() < 2)	// checks for digits as well as only two digits max
		{
			partySeats += tempString[k];
			k++;
		}

		if (!(isalpha(tempString[k])) || (isalpha(tempString[k]) && !isdigit(tempString[k - 1])))	// checks for cases where the char following digits
			return false;																			// is non-alphabetical or where no digits separate
		else if (partySeats == "" && k != tempString.size() - 1)									// two alphabetical characters
		{
			k++;
			continue;
		}
		else
		{
			k++;
			continue;
		}
	}
	return true;
}

void makeUpper(string& pollData)
{
	for (int i = 0; i != pollData.size(); i++)
	{
		pollData[i] = toupper(pollData[i]);
	}
}

bool isValidUppercaseStateCode(string stateCode)
{
	const string codes =
		"AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
		"LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
		"OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
	return (stateCode.size() == 2 &&
		stateCode.find('.') == string::npos  &&  // no '.' in stateCode
		codes.find(stateCode) != string::npos);  // match found
}