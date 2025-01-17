#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"

using namespace std;

class clsDeleteClientScreen :  protected clsScreen
{
private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\n{Client Card}\n\n";
		cout << "====================================================\n";
		cout << "First Name      :      " << Client.FirstName << "\n";
		cout << "Last Name       :      " << Client.LastName << "\n";
		cout << "Full Name       :      " << Client.FullName() << "\n";
		cout << "Email           :      " << Client.Email << "\n";
		cout << "Phone           :      " << Client.Phone << "\n";
		cout << "AccountNumber   :      " << Client.AccountNumber() << "\n";
		cout << "PinCode         :      " << Client.PinCode << "\n";
		cout << "Balance         :      " << Client.Balance << "\n";
		cout << "====================================================\n";
	}

public:

	static void DeleteClient()
	{
		if (!CheckAccessRights(clsUser::PDeleteClient))
		{
			return;
		}

		_DrawScreenHeader("\t  Delete Client Screen\n\n");

		string AccountNumber = clsInputValidation::ReadString("Please Enter Client Account Number: ");

		while (!clsBankClient::isClientExists(AccountNumber))
		{
			cout << "{" << AccountNumber << "} Not Found!\n";
			cout << "\n-------------------------------------------------------------------\n";

			AccountNumber = clsInputValidation::ReadString("Please Enter Client Account Number: ");
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		cout << "Delete Client     :-\n";
		cout << "-----------------------------\n";

		cout << "Are You Sure You Want To Delete This Client [Y/N] ? ";

		char Answer = 'Y';

		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (Client.Delete())
			{
				cout << "Client Deleted Successfully\n";

				_PrintClient(Client);
			}

			else
				cout << "\n Error, Account Was Not Deleted";
		}

		else
			cout << "No Client Deleted\n";

	}
};

