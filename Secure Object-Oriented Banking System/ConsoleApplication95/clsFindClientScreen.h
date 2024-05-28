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

class clsFindClientScreen : protected clsScreen
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

	 static void FindCient()
	{
		 if (!CheckAccessRights(clsUser::PFindClient))
		 {
			 return;
		 }

		 _DrawScreenHeader("\t     Find Client Screen\n\n");

		 string AccountNumber = clsInputValidation::ReadString("Please Enter Client Account Number: ");

		 while (!clsBankClient::isClientExists(AccountNumber))
		 {
			 cout << "Acc. Number Was Not Found...\n";

			 AccountNumber = clsInputValidation::ReadString("Please Enter Client Account Number: ");
		 }
		 clsBankClient Client = clsBankClient::Find(AccountNumber);

		 if (!Client.IsEmpty())
		 {
			 cout << "\nClient Found\n";
		 }
		 
		 else
		 {
			 cout << "\nClient Was Not Found\n";
		 }
		 
		 _PrintClient(Client);
	}

};

