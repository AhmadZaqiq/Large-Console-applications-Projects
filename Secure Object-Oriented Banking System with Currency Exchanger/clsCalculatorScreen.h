#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsString.h"
#include "clsInputValidation.h"
#include "clsCurrency.h"
#include "clsScreen.h"

class clsCalculatorScreen : protected clsScreen
{
private:

	static void _PrintCurrencyCard(clsCurrency Currency, string Message)
	{
		cout<<"\n" << Message << "     \n\n";
		cout << "====================================================\n";
		cout << "Country Name        :      " << Currency.Country() << "\n";
		cout << "Currency Code       :      " << Currency.CurrencyCode() << "\n";
		cout << "Currency Name       :      " << Currency.CurrencyName() << "\n";
		cout << "Rate($) =           :      " << Currency.Rate() << "\n";
		cout << "====================================================\n";
	}

	static void _PrintCalculationResults(float Amount, clsCurrency Currency1, clsCurrency Currency2)
	{
		_PrintCurrencyCard(Currency1, "Convert From:");


		if (Currency1.CurrencyCode() != "USD")
		{
			float AmountInUSD = Currency1.ConvertToUSD(Amount);

			cout << Amount << " " << Currency1.CurrencyCode()
				<< " = " << AmountInUSD << " USD\n";

			if (Currency2.CurrencyCode() == "USD")
			{
				return;
			}

		}
			_PrintCurrencyCard(Currency2, "Converting From USD To:");

		float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);

		cout << Amount << " " << Currency1.CurrencyCode()
			<< " = " << AmountInCurrency2 <<  Currency2.CurrencyCode()<<"\n";
	}

	static clsCurrency _ReadCurrency()
	{
		string Code = clsInputValidation::ReadString("Please Enter Currency Code:");

		while (!clsCurrency::IsCurrencyExists(Code))
		{
			cout << "\nCurrency With Code (" << Code << ") Not Found!\n";
			cout << "\n-------------------------------------------------------------------\n";

			Code = clsInputValidation::ReadString("Please Enter Currency Code: ");
		}

		 clsCurrency Currency = clsCurrency::FindByCode(Code);

		 return Currency;
	}

public:

	static void CalculatorScreen()
	{
		char Answer = 'N';

		do
		{
			system("cls");

			_DrawScreenHeader("\t     Calculator Screen\n");

			cout << "\nConvert From:-\n";
			clsCurrency CurrencyFrom = _ReadCurrency();

			cout << "\nConvert To:-\n";
			clsCurrency CurrencyTo = _ReadCurrency();

			double Amoumt = clsInputValidation::ReaddoubleNumber("\nPlease Enter Amount To Exchange: ");

			_PrintCalculationResults(Amoumt, CurrencyFrom, CurrencyTo);

			cout << "\n\nDo You Want To Perform Another Calculation??? [Y/N] ";
			cin >> Answer;

		} while (toupper(Answer) == 'Y');
		
	}

};

