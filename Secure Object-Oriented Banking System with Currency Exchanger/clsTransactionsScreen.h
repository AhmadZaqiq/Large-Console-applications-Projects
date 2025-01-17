#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalances.h"
#include "clsTransfer.h"
#include "clsTransferLogsScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:

	enum _enTransactionsOptions
	{
		enDeposit = 1, enWithdraw = 2, enTotalBalances = 3, enTransfer=4,enTransferLog=5,enMainMenu = 6
	};

	static void _UpdateClienBalanceDepositInfo()
	{
		clsDepositScreen::UpdateClienBalanceDepositInfo();
	}

	static void _UpdateClienBalanceWithdrawInfo()
	{
		clsWithdrawScreen::UpdateClienBalanceWithdrawInfo();
	}

	static void _ShowBalancesList()
	{
		clsTotalBalances::ShowTotalBalancesScreen();
	}

	static void _ShowTransferScreen()
	{
		clsTransfer::ShowTransferScreen();
	}

	static void _ShowTransferLogScreen()
	{
		clsTransferLogsScreen::ShowTransferLogsScreen();
	}

	static void _GoBackToTransactionsMenue()
	{
		cout << "\n\nPress any key to go back to Transactions Menue...";
		system("pause>0");
		ShowTransactionsMenuScreen();
	}

	static void _ChooseTransaction(_enTransactionsOptions choice)
	{
		_enTransactionsOptions TransOption = _enTransactionsOptions(choice);

		switch (TransOption)
		{
		case _enTransactionsOptions::enDeposit:

			system("cls");
			_UpdateClienBalanceDepositInfo();
			_GoBackToTransactionsMenue();
			break;

		case _enTransactionsOptions::enWithdraw:

			system("cls");
			_UpdateClienBalanceWithdrawInfo();
			_GoBackToTransactionsMenue();
			break;

		case _enTransactionsOptions::enTotalBalances:

			system("cls");
			_ShowBalancesList();
			_GoBackToTransactionsMenue();
			break;

		case _enTransactionsOptions::enTransfer:

			system("cls");
			_ShowTransferScreen();
			_GoBackToTransactionsMenue();
			break;

		case _enTransactionsOptions::enTransferLog:

			system("cls");
			_ShowTransferLogScreen();
			_GoBackToTransactionsMenue();
			break;

		case _enTransactionsOptions::enMainMenu:

			break;

		}		
	}

public:

	static void ShowTransactionsMenuScreen()
	{
		system("cls");

		if (!CheckAccessRights(clsUser::PTransactions))
		{
			return;
		}

		_DrawScreenHeader("\t   Transactions Screen\n\n");

		cout << setw(39) << "" << "=========================================\n";
		cout << setw(39) << "" << "         Transactions Menu Screen        \n";
		cout << setw(39) << "" << "=========================================\n";
		cout << setw(39) << "" << "        [1] Deposit.                     \n";
		cout << setw(39) << "" << "        [2] Withdraw.                    \n";
		cout << setw(39) << "" << "        [3] Total Balances.              \n";
		cout << setw(39) << "" << "        [4] Transfer.                    \n";
		cout << setw(39) << "" << "        [5] Transfer Log.                \n";
		cout << setw(39) << "" << "        [6] Main Menu.                   \n";
		cout << setw(39) << "" << "=========================================\n";

		_ChooseTransaction(_enTransactionsOptions(clsInputValidation::ReadIntNumberBetween
		(0, 7, "\t\t\t\t\tChoose What You Want To Do [1] to [6]: ",
			"\t\t\t\t\tInvalid Choice")));
	}

};

