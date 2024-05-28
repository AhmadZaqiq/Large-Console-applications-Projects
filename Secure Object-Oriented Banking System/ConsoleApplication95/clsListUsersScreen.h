#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidation.h"

using namespace std;

class clsListUsersScreen :protected clsScreen
{
private:

	static void _PrintUserRecordLine(clsUser User)
	{
		cout << setw(11) << "" << "| " << left << setw(15) << User.Username;
		cout << "| " << left << setw(17) << User.FullName();
		cout << "| " << left << setw(10) << User.Phone;
		cout << "| " << left << setw(20) << User.Email;
		cout << "| " << left << setw(9) << User.Password;
		cout << "| " << left << setw(12) << User.Permissions;
	}

public:

	static void ShowUserList()
	{
		vector <clsUser> vUsers = clsUser::GetUserList();

		string Title = "Users List Screen\n";
		string SubTitle = "(" + to_string(vUsers.size()) + ") User(s).\n\n";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(11) << "" << "______________________________________________________________________________________________________\n\n";
		cout << setw(11) << "" << "| " << left << setw(15) << "Username";
		cout << "| " << left << setw(17) << "User Name";
		cout << "| " << left << setw(10) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(9) << "Password";
		cout << "| " << left << setw(12) << "Permissions\n";
		cout << setw(11) << "" << "______________________________________________________________________________________________________\n\n";

		if (vUsers.size() == 0)
			cout << "\t\t\t\t Sorry, No Avilable Users In The System...";

		else
		{
			for (clsUser& C : vUsers)
			{
				_PrintUserRecordLine(C);
				cout << "\n";
			}
		}
	}
};

