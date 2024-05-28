#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidation.h"

class clsUpdateCurrencyRate :protected clsScreen
{
private:

	static float _ReadNewCurrencyRate()
	{
		 return clsInputValidation::ReaddoubleNumber("\nEnter New Rate   :  ");
	}

	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\n{Currency Card}\n\n";
		cout << "====================================================\n";
		cout << "Country Name        :      " << Currency.Country() << "\n";
		cout << "Currency Code       :      " << Currency.CurrencyCode() << "\n";
		cout << "Currency Name       :      " << Currency.CurrencyName() << "\n";
		cout << "Rate($) =           :      " << Currency.Rate() << "\n";
		cout << "====================================================\n";
	}


public:

	static void UpdateCurrency()
	{
	
		_DrawScreenHeader("\t     Update Currency Info\n\n");

		string Code = clsInputValidation::ReadString("Please Enter Currency Code: ");

		while (!clsCurrency::IsCurrencyExists(Code))
		{
			cout << "\nCurrency With Code (" << Code << ") Not Found!\n";
			cout << "\n-------------------------------------------------------------------\n";

			Code = clsInputValidation::ReadString("Please Enter Currency Code: ");
		}

		clsCurrency Currency = clsCurrency::FindByCode(Code);

		_PrintCurrency(Currency);

		char Answer = 'N';

		cout << "\nAre You Sure You Want To Update This Currency Rate ???\n";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			cout << "Update Currency Rate     :-\n";
			cout << "-----------------------------\n";

			Currency.UpdateRate(_ReadNewCurrencyRate());

			cout << "\nCurrency Rate Updated Successfully...\n";

			_PrintCurrency(Currency);
		}

		else
			cout << "Operation Has Been Cancelled...";
	}

};

