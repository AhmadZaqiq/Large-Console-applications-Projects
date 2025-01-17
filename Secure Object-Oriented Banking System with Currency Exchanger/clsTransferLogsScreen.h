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

class clsTransferLogsScreen : protected clsScreen
{
private:

	static void _PrintTransferLogLine(clsBankClient::stTransferLog Logs)
	{
		cout << setw(9) << "" << "| " << left << setw(20) << Logs.CurrentTime;
		cout << "| " << left << setw(6) << Logs.SourceClientNum;
		cout << "| " << left << setw(6) << Logs.SourceClientNum;
		cout << "| " << left << setw(15) << Logs.Amount;
		cout << "| " << left << setw(15) << Logs.SourceClientBalnce;
		cout << "| " << left << setw(15) << Logs.DestinationClientBalance;
		cout << "| " << left << setw(15) << Logs.User;

	}

public:

	static void ShowTransferLogsScreen()
	{

		vector <clsBankClient::stTransferLog> vTransferLog = clsBankClient::LoadTranferLogDataFromFile();

		string Title = "     Transfer Logs Screen\n";
		string SubTitle = "(" + to_string(vTransferLog.size()) + ") Log(s).\n";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(9) << "" << "______________________________________________________________________________________________________\n\n";
		cout << setw(9) << "" << "| " << left << setw(20) << "Date/Time";
		cout << "| " << left << setw(6) << "S.AccN";
		cout << "| " << left << setw(6) << "D.AccN";
		cout << "| " << left << setw(15) << "Amount";
		cout << "| " << left << setw(15) << "S.AccB";
		cout << "| " << left << setw(15) << "D.AccB";
		cout << "| " << left << setw(15) << "User";
		cout << setw(14) << "" << "______________________________________________________________________________________________________\n\n";

		if (vTransferLog.size() == 0)
			cout << "\t\t\t\t Sorry, No Avilable Logs In The System...";

		else
		{
			for (clsBankClient::stTransferLog& C : vTransferLog)
			{
				_PrintTransferLogLine(C);
				cout << "\n";
			}
		}
	}
};

