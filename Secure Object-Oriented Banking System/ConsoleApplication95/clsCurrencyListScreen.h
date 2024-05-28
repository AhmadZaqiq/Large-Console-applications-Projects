#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsString.h"
#include "clsCurrency.h"
#include "clsScreen.h"


class clsCurrencyListScreen: protected clsScreen
{
private:

	static void _PrintCurrencyRecordLine(clsCurrency Currency)
	{
		cout << setw(11) << "" << "| " << left << setw(30) << Currency.Country();
		cout << "| " << left << setw(5) << Currency.CurrencyCode();
		cout << "| " << left << setw(30) << Currency.CurrencyName();
		cout << "| " << left << setw(12) << Currency.Rate();
	}

public:

	static void ShowCurrencyList()
	{
		vector <clsCurrency> vCurrency = clsCurrency::GetCurrenciesList();

		string Title = "Currency List Screen\n";
		string SubTitle = "(" + to_string(vCurrency.size()) + ") Currencies.\n";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(11) << "" << "______________________________________________________________________________________________________\n\n";
		cout << setw(11) << "" << "| " << left << setw(30) << "Country Name";
		cout << "| " << left << setw(5) << "Code";
		cout << "| " << left << setw(30) << "Currency Name";
		cout << "| " << left << setw(12) << "Rate/(1$)\n";
		cout << setw(9) << "" << "______________________________________________________________________________________________________\n\n";

		if (vCurrency.size() == 0)
			cout << "\t\t\t\t Sorry, No Avilable Currencies In The System...";

		else
		{
			for (clsCurrency& C : vCurrency)
			{
				_PrintCurrencyRecordLine(C);
				cout << "\n";
			}
		}
	}
};