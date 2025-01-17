#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsUtil.h"

using namespace std;

class clsTotalBalances : protected clsScreen
{
private:

	static void _PrintClientRecordBalanceLine(clsBankClient Client)
	{
		cout << setw(11) << "" << "| " << left << setw(15) << Client.AccountNumber();
		cout << "| " << left << setw(42) << Client.FullName();
		cout << "| " << left << setw(12) << Client.Balance;
	}

public:

	static void ShowTotalBalancesScreen()
	{
		vector <clsBankClient> vClients = clsBankClient::GetClientList();

		string Title = "Total Balances Screen\n";
		string SubTitle = "(" + to_string(vClients.size()) + ") Client(s).\n";

		_DrawScreenHeader(Title, SubTitle);

		if (vClients.size() == 0)
			cout << "\t\t\t\t Sorry, No Avilable Users In The System...";

		cout << setw(11) << "" << "___________________________________________________________________________________________________\n\n";
		cout << setw(11) << "" << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(42) << "Client Name";
		cout << "| " << left << setw(12) << "Balance\n";
		cout << setw(7) << "" << "___________________________________________________________________________________________________\n\n";

		if (vClients.size() == 0)
			cout << "\t\t\t\t Sorry, No Avilable Users In The System...";

		else
		{
			for (clsBankClient& C : vClients)
			{
				_PrintClientRecordBalanceLine(C);
				cout << "\n";
			}
		}

		cout << setw(11) << "" << "_____________________________________________________________________________________________________\n\n";

		double TotalBalanes = clsBankClient::GetTotalBalances();

		cout << left << setw(37) << " " << "Total Balances = {" << clsBankClient::GetTotalBalances() << "}\n";

		cout << left << setw(37) << " " << clsUtil::NumberToText(TotalBalanes);
	}

};

