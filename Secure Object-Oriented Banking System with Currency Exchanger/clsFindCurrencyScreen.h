#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidation.h"

class clsFindCurrencyScreen :protected clsScreen
{
private:

	enum enFindBy { enCode = 1, enCountry = 2 };

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

	static short _ReadOption()
	{
		return  (clsInputValidation::ReadIntNumberBetween
		(0, 3, "Find By [1]: Code Or [2]: Country ??? ", "\nInvalid Choice...Try Again\n"));
	}

	static void _FindCurrencyByCode()
	{

		string Code = clsInputValidation::ReadString("Please Enter Currency Code: ");

			clsCurrency Currency = clsCurrency::FindByCode(Code);

			if (!Currency.IsEmpty())
			{
				cout << "\Currency Found\n";
			}

			else
			{
				cout << "\Currency Was Not Found\n";
			}

			_PrintCurrency(Currency);
		
	}

	static void _FindCurrencyByCountry()
	{
		string Country = clsInputValidation::ReadString("Please Enter Country Name: ");

		clsCurrency Currency = clsCurrency::FindByCountry(Country);

		if (!Currency.IsEmpty())
		{
			cout << "\Currency Found\n";
		}

		else
		{
			cout << "\Currency Was Not Found\n";
		}

		_PrintCurrency(Currency);
	}

public:

	static void FindCurrency()

	{
		_DrawScreenHeader("\t     Find Currency Screen\n\n");

		enFindBy FindBy = enFindBy(_ReadOption());

		switch (FindBy)
		{
		case clsFindCurrencyScreen::enCode:

			_FindCurrencyByCode();

			break;

		case clsFindCurrencyScreen::enCountry:

			_FindCurrencyByCountry();

			break;
		}

	}
};

