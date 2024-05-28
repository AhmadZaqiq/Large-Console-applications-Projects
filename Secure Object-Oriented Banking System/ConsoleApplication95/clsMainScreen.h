#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsScreen.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsLoginRegister.h"
#include "clsCurrencyExchangeScreen.h"

#include "Global.h"

using namespace std;

class clsMainScreen : protected clsScreen
{
private:

	enum _enMainMenuOption
	{
		ShowClientData = 1, enAddNewClients = 2, enDeleteClient = 3, UpdateClientInfo = 4,
		enFindClient = 5, Transactions = 6, Manageusers = 7,LoginRegister=8,CurrencyExchange=9,Logout = 10
	};

	static void _ShowClientList()
	{
		clsClientListScreen::ShowClientList();
	}

	static void _AddClient()
	{
		clsAddNewClientScreen::AddNewClient();
	}

	static void _DeleteClient()
	{
		clsDeleteClientScreen::DeleteClient();
	}

	static void	_UpdateClienInfo()
	{
		clsUpdateClientScreen::UpdateClient();
	}

	static void _FindClient()
	{
		clsFindClientScreen::FindCient();
	}

	static void _ChooseTransaction()
	{
		clsTransactionsScreen::ShowTransactionsMenuScreen();
	}

	static void _ChooseUserOption()
	{
		clsManageUsersScreen::ShowMangeUsersMenuScreen();
	}

	static void _LoginRegister()
	{
		clsLoginRegister::ShowLoginRegisterScreen();
	}

	static void _CurrencyExchange()
	{
		clsCurrencyExchangeScreen::ShowCurrencyMenuScreen();
	}

	static void _LogoutScreen()
	{
		CurrentUser = clsUser::Find("", "");
	}

	static  void _GoBackToMainMenue()
	{
		cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...\n";

		system("pause>0");

		ShowMainMenuScreen();
	}

	static void _ChooseOption(_enMainMenuOption Option)
	{
		switch (Option)
		{
		case _enMainMenuOption::ShowClientData:

			system("cls");
			_ShowClientList();
			_GoBackToMainMenue();
			break;

		case _enMainMenuOption::enAddNewClients:

			system("cls");
			_AddClient();
			_GoBackToMainMenue();
			break;

		case _enMainMenuOption::enDeleteClient:

			system("cls");
			_DeleteClient();
			_GoBackToMainMenue();
			break;

		case _enMainMenuOption::UpdateClientInfo:

			system("cls");
			_UpdateClienInfo();
			_GoBackToMainMenue();
			break;

		case _enMainMenuOption::enFindClient:

			system("cls");
			_FindClient();
			_GoBackToMainMenue();
			break;

		case _enMainMenuOption::Transactions:

			system("cls");
			_ChooseTransaction();
			_GoBackToMainMenue();
			break;

		case _enMainMenuOption::Manageusers:

			system("cls");
			_ChooseUserOption();
			_GoBackToMainMenue();
			break;

		case _enMainMenuOption::LoginRegister:

			system("cls");
			_LoginRegister();
			_GoBackToMainMenue();
			break;

		case _enMainMenuOption::CurrencyExchange:

			system("cls");
			_CurrencyExchange();
			_GoBackToMainMenue();
			break;

		case _enMainMenuOption::Logout:

			system("cls");
			_LogoutScreen();

		}	
	}

public:

	static void ShowMainMenuScreen()
	{
		system("cls");

		clsScreen::_DrawScreenHeader("Welcome To InterNational Bank\n\n");

		cout << setw(30) << "" << "       =============================================\n";
		cout << setw(30) << "" << "                          Main Menu                 \n";
		cout << setw(30) << "" << "       =============================================\n";
		cout << setw(30) << "" << "         [1]  Show Client List.                     \n";
		cout << setw(30) << "" << "         [2]  Add New Client.                       \n";
		cout << setw(30) << "" << "         [3]  Delete Client.                        \n";
		cout << setw(30) << "" << "         [4]  Update Client Info                    \n";
		cout << setw(30) << "" << "         [5]  Find Client.                          \n";
		cout << setw(30) << "" << "         [6]  Transactions.                         \n";
		cout << setw(30) << "" << "         [7]  Manage Users.                         \n";
		cout << setw(30) << "" << "         [8]  Login Register.                       \n";
		cout << setw(30) << "" << "         [9]  Currency Exchange.                    \n";
		cout << setw(30) << "" << "         [10] Logout.                               \n";
		cout << setw(30) << "" << "       =============================================\n";

		_ChooseOption(_enMainMenuOption(clsInputValidation::ReadIntNumberBetween
		(0, 11, "\t\t\t\t\tChoose What You Want To Do [1] to [10]: ",
			"\t\t\t\t\tInvalid Choice")));

	}

};


