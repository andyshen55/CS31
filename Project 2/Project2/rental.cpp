#include <iostream>
#include <string>
using namespace std;

int main()
{
	// Sets number of decimal places for output to 2.
	cout.setf(ios::fixed);								
	cout.precision(2);

	int odometerStart, odometerEnd, rentalDays, month;
	string name, luxury;

	cout << "Odometer at start: ";
	cin >> odometerStart;

	cout << "Odometer at end: ";
	cin >> odometerEnd;

	cout << "Rental days: ";
	cin >> rentalDays;

	// Clears newline characters from line 20 for future getline(cin, var).
	cin.ignore(1000, '\n');								

	cout << "Customer name: ";
	getline(cin, name);

	cout << "Luxury car? (y/n): ";
	getline(cin, luxury);

	cout << "Month (1=Jan, 2=Feb, etc.): ";
	cin >> month;

	cout << "---";

	int milesTraveled = odometerEnd - odometerStart;
	double nonLuxuryBaseCharge = 33.0, luxuryBaseCharge = 61.0, baseCharge, variableCharge, totalCharge;

	// Sets base charge depending on whether or not the rented car is luxury.
	if (luxury == "y")
		baseCharge = rentalDays * luxuryBaseCharge;
	else
		baseCharge = rentalDays * nonLuxuryBaseCharge;

	double chargeFirst100 = 0.27, chargeOver400 = 0.19, chargeNext300;

	// Checks if car was rented between Dec-March.
	if (month < 4 || month == 12)						
		chargeNext300 = 0.27;
	else
		chargeNext300 = 0.21;

	double first100 = 100 * chargeFirst100, next300 = 300 * chargeNext300;

	// Calculates variable charge based on miles traveled.
	if (milesTraveled <= 100)
	{
		variableCharge = milesTraveled * chargeFirst100;
	}
	else if (milesTraveled <= 400)
	{
		variableCharge = first100 + ((milesTraveled - 100) * chargeNext300);
	}
	else
	{
		variableCharge = first100 + next300 + ((milesTraveled - 400) * chargeOver400);
	}

	totalCharge = variableCharge + baseCharge;

	// Outputs either the rental charge or an error message if user input was wrong.
	if (odometerStart < 0)
	{
		cout << endl << "The starting odometer reading must be nonnegative.";
	}
	else if (odometerEnd < odometerStart)
	{
		cout << endl << "The final odometer reading must be at least as large as the starting reading.";
	}
	else if (rentalDays <= 0)
	{
		cout << endl << "The number of rental days must be positive.";
	}
	else if (name == "")
	{
		cout << endl << "You must enter a customer name.";
	}
	else if (not (luxury == "y" || luxury == "n"))
	{
		cout << endl << "You must enter y or n.";
	}
	else if (month < 1 || month > 12)
	{
		cout << endl << "The month number must be in the range 1 through 12.";
	}
	else
	{
		cout << endl << "The rental charge for " << name << " is $" << totalCharge;
	}
}