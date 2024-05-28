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

class clsDepositScreen :protected clsScreen
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

	static void UpdateClienBalanceDepositInfo()
	{
		_DrawScreenHeader("\t     Deposit Screen\n\n");

		string AccountNumber = clsInputValidation::ReadString("Please Enter Client Account Number: ");

		while (!clsBankClient::isClientExists(AccountNumber))
		{
			cout << "\nClient With Account Number (" << AccountNumber << ") Not Found!\n";
			cout << "\n-------------------------------------------------------------------\n";

			AccountNumber = clsInputValidation::ReadString("Please Enter Client Account Number: ");
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		float DepoistAmount = clsInputValidation::ReaddoubleNumber("Please Enter Depoist Amount :");

		char Answer = 'N';

		cout << "Are You Sure You Want To Perform This Transaction ? [Y/N]";
		cin >> Answer;
			
		if (toupper(Answer) == 'Y')
		{
			Client.Depoist(DepoistAmount);

			cout << "Done Successfully\n\n";
			cout << "New Balance : {" << Client.Balance<<"}";
		}
		else
		{
			cout << "\nOperation Was Cancelled...\n";
		}
	}
};
