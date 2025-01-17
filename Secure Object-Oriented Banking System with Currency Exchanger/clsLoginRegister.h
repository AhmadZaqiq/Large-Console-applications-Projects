#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsScreen.h"

using namespace std;

class clsLoginRegister : protected clsScreen
{
private:

	static void _PrintLoginLogLine(clsUser::stLoginLogs Logs)
	{
		cout << setw(9) << "" << "| " << left << setw(40) << Logs.CurrentTime;
		cout << "| " << left << setw(10) << Logs.Username;
		cout << "| " << left << setw(20) << Logs.Password;
		cout << "| " << left << setw(11) << Logs.Permissions;
	}

public:

	static void ShowLoginRegisterScreen()
	{
		if (!CheckAccessRights(clsUser::PLoginRegister))
		{
			return;
		}

		vector <clsUser::stLoginLogs> vLoginLogs = clsUser::LoadLoginLogFromFile();

		string Title = "     Login Register Screen\n";
		string SubTitle = "(" + to_string(vLoginLogs.size()) + ") Log(s).\n";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(9) << "" << "______________________________________________________________________________________________________\n\n";
		cout << setw(11) << "| " << left << setw(40) << "Date/Time";
		cout << "| " << left << setw(10) << "Username";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(11) << "Permissins\n";
		cout << setw(9) << "" << "______________________________________________________________________________________________________\n\n";

		if (vLoginLogs.size() == 0)
			cout << "\t\t\t\t Sorry, No Avilable Logs In The System...";

		else
		{
			for (clsUser::stLoginLogs& C : vLoginLogs)
			{
				_PrintLoginLogLine(C);
				cout << "\n";
			}
		}
	}
};