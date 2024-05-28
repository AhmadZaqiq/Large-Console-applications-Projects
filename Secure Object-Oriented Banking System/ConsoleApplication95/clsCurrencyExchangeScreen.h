#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsCurrencyListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRate.h"
#include "clsCalculatorScreen.h"

class clsCurrencyExchangeScreen :protected clsScreen
{

private:

	enum _enCurrencyExchangeOptions
	{
		enListCurencceies = 1, enFindCurrency = 2, enUpdateRate = 3, enCurrencyCalculator = 4, enMainMenu = 5
	};

	static void _ListCurencceies()
	{
		clsCurrencyListScreen::ShowCurrencyList();
	}

	static void _FindCurrency()
	{
		clsFindCurrencyScreen::FindCurrency();
	}

	static void _UpdateRate()
	{
		clsUpdateCurrencyRate::UpdateCurrency();
	}

	static void _CurrencyCalculator()
	{
		clsCalculatorScreen::CalculatorScreen();
	}

	static void _GoBackToTransactionsMenue()
	{
		cout << "\n\nPress any key to go back to Transactions Menue...";
		system("pause>0");
	    ShowCurrencyMenuScreen();
	}

	static void _ChooseCurrencyOption(_enCurrencyExchangeOptions choice)
	{
		_enCurrencyExchangeOptions CurrencyOption = _enCurrencyExchangeOptions(choice);

		switch (CurrencyOption)
		{
		case _enCurrencyExchangeOptions::enListCurencceies:

			system("cls");
			_ListCurencceies();
			_GoBackToTransactionsMenue();
			break;

		case _enCurrencyExchangeOptions::enFindCurrency:

			system("cls");
			_FindCurrency();
			_GoBackToTransactionsMenue();
			break;

		case _enCurrencyExchangeOptions::enUpdateRate:

			system("cls");
			_UpdateRate();
			_GoBackToTransactionsMenue();
			break;

		case _enCurrencyExchangeOptions::enCurrencyCalculator:

			system("cls");
			_CurrencyCalculator();
			_GoBackToTransactionsMenue();
			break;

		case _enCurrencyExchangeOptions::enMainMenu:

			break;

		}
	}

public:

	static void ShowCurrencyMenuScreen()
	{
		system("cls");

		if (!CheckAccessRights(clsUser::PCurrencyExchange))
		{
			return;
		}

		_DrawScreenHeader("\tCurrency Exchange Main Screen\n\n");

		cout << setw(39) << "" << "=========================================\n";
		cout << setw(39) << "" << "         Currency Exchange Menu          \n";
		cout << setw(39) << "" << "=========================================\n";
		cout << setw(39) << "" << "        [1] List Curencceies.            \n";
		cout << setw(39) << "" << "        [2] Find Currency.               \n";
		cout << setw(39) << "" << "        [3] Update Rate.                 \n";
		cout << setw(39) << "" << "        [4] Currency Calculator.         \n";
		cout << setw(39) << "" << "        [5] Main Menu.                   \n";
		cout << setw(39) << "" << "=========================================\n";

		_ChooseCurrencyOption(_enCurrencyExchangeOptions(clsInputValidation::ReadIntNumberBetween
		(0, 6, "\t\t\t\t\tChoose What You Want To Do [1] to [5]: ",
			"\t\t\t\t\tInvalid Choice")));
	}
};

