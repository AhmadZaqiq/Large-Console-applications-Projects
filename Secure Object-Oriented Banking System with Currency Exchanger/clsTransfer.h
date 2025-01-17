#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsTransfer :protected clsScreen
{
private:

	static void _PrintClient(clsBankClient Client)
	{
		cout << "\n{Client Card}\n\n";
		cout << "====================================================   \n";
		cout << "Full Name       :      " << Client.FullName() << "\n";
		cout << "Acc. Number     :      " << Client.AccountNumber() << "\n";
		cout << "Balance         :      " << Client.Balance << "\n";
		cout << "====================================================   \n";
	}

	static string _ReadAccountNumber()
	{
		string AccountNumber=clsInputValidation::ReadString("Enter Account Number To Transfer From: ");

		while (!clsBankClient::isClientExists(AccountNumber))
		{
			cout << "\nClient With Account Number (" << AccountNumber << ") Not Found!\n";
			cout << "\n-------------------------------------------------------------------\n";

			AccountNumber = clsInputValidation::ReadString("Please Enter Client Account Number: ");
		}

		return AccountNumber;
	}


public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\t    Transfer Screen\n\n");

		clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(SourceClient);

		clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber());
		_PrintClient(DestinationClient);

		float Amount = clsInputValidation::ReaddoubleNumber("Enter The Transfer Amount : ");

		cout << "Are You Sure You Want To Perform This Transaction [Y/N] ??? ";
		char Answer = 'N';
		cin>>Answer;

		if (toupper(Answer) == 'Y')
		{
			if (SourceClient.Transfer(Amount, DestinationClient))
			{
				cout<<"\n Transfer Done Successfully...\n";

				_PrintClient(SourceClient);
				_PrintClient(DestinationClient);
			}
			else
			{
				cout << "\nSorry Amount Exceeds The Balance...\n";
			}
		}	

		else
		{
			cout << "\nTransfer Cancelled...\n";
		}
		
	}


};

