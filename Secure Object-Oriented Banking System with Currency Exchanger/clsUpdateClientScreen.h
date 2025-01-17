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

class clsUpdateClientScreen : protected clsScreen
{
private:

	static void _ReadClientInfo(clsBankClient& Client)
	{
		Client.FirstName = clsInputValidation::ReadString("\nEnter First Name   :  ");

		Client.LastName = clsInputValidation::ReadString("\nEnter Last  Name   :  ");

		Client.Email = clsInputValidation::ReadString("\nEnter Email        :  ");

		Client.Phone = clsInputValidation::ReadString("\nEnter Phone        :  ");

		Client.PinCode = clsInputValidation::ReadString("\nEnter PinCode      :  ");

		Client.Balance = clsInputValidation::ReaddoubleNumber("\nEnter Acc. Balance :  ");
	}

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

	static void UpdateClient()
	{
		if (!CheckAccessRights(clsUser::PUpdateClient))
		{
			return;
		}

		_DrawScreenHeader("\t     Update Client Info\n\n");

		string AccountNumber = clsInputValidation::ReadString("Please Enter Client Account Number: ");

		while (!clsBankClient::isClientExists(AccountNumber))
		{
			cout << "\nClient With Account Number (" << AccountNumber << ") Not Found!\n";
			cout << "\n-------------------------------------------------------------------\n";

			AccountNumber = clsInputValidation::ReadString("Please Enter Client Account Number: ");
		}

		clsBankClient Client = clsBankClient::Find(AccountNumber);

		_PrintClient(Client);

		cout << "Update Client Info     :-\n";
		cout << "-----------------------------\n";

		_ReadClientInfo(Client);

		clsBankClient::enSaveResults SaveResults;

		SaveResults = Client.Save();

		switch (SaveResults)
		{
		case clsBankClient::svSucceesed:
		{
			cout << "Client Updated Successfully";

			_PrintClient(Client);

			break;
		}

		case clsBankClient::svFaildEmptyObject:

			cout << "\n Error Account Was Not Saved Because it is Empty";
			break;
		}
	}

};

