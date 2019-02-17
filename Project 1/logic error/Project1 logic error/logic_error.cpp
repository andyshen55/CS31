// Code for Project 1
// Report poll results

#include <iostream>
using namespace std;   // pp. 38-39 in Savitch 6/e explains this line

int main()
{
	int numberSurveyed;
	int forNewsom;
	int forCox;

	cout << "How many registered voters were surveyed? ";
		cin >> numberSurveyed;
	cout << "How many of them say they will vote for Newsom? ";
	cin >> forNewsom;
	cout << "How many of them say they will vote for Cox? ";
	cin >> forCox;

	int pctNewsom = 100 / forNewsom / numberSurveyed; //logic error: changed double to int, changed multiplied by to divided by
	double pctCox = 100.0 * forCox / numberSurveyed;

	cout.setf(ios::fixed);       // see pp. 32-33 in Savitch 6/e
	cout.precision(1);

	cout << endl;
	cout << pctNewsom << "% say they will vote for Newsom." << endl;
	cout << pctCox << "% say they will vote for Cox." << endl;

	if (forNewsom < forCox)		//logic error: changed greater than to less than sign
		cout << "Newsom is predicted to win the election." << endl;
	else
		cout << "Cox is predicted to win the election." << endl;
}