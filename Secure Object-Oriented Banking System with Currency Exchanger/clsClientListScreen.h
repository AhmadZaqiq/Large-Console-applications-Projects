#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsScreen.h"
#include "clsBankClient.h"

using namespace std;

class clsClientListScreen : protected clsScreen
{
private:

	static void _PrintClientRecordLine(clsBankClient Client)
	{
		cout << setw(11) << "" << "| " << left << setw(15) << Client.AccountNumber();
		cout << "| " << left << setw(17) << Client.FullName();
		cout << "| " << left << setw(10) << Client.Phone;
		cout << "| " << left << setw(30) << Client.Email;
		cout << "| " << left << setw(9) << Client.PinCode;
		cout << "| " << left << setw(12) << Client.Balance;
	}

public:

	static void ShowClientList()
	{
		if (!CheckAccessRights(clsUser::PClintList))
		{
			return ;
		}

		vector <clsBankClient> vClients = clsBankClient::GetClientList();

		string Title = "Client List Screen\n";
		string SubTitle = "(" + to_string(vClients.size()) + ") Client(s).\n";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(11) << "" << "______________________________________________________________________________________________________\n\n";
		cout << setw(11) << "" << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(17) << "Client Name";
		cout << "| " << left << setw(10) << "Phone";
		cout << "| " << left << setw(30) << "Email";
		cout << "| " << left << setw(9) << "PIN Code";
		cout << "| " << left << setw(12) << "Balance\n";
		cout << setw(7) << "" << "______________________________________________________________________________________________________\n\n";

		if (vClients.size() == 0)
			cout << "\t\t\t\t Sorry, No Avilable Clients In The System...";

		else
		{
			for (clsBankClient& C : vClients)
			{
				_PrintClientRecordLine(C);
				cout << "\n";
			}
		}
	}
};

