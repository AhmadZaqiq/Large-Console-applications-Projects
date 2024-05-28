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

class clsDeleteUserScreen : protected clsScreen
{
private:

	static void _PrintUser(clsUser User)
	{
		cout << "\n{User Card}\n\n";
		cout << "====================================================\n";
		cout << "Username        :      " << User.Username << "\n";
		cout << "First Name      :      " << User.FirstName << "\n";
		cout << "Last Name       :      " << User.LastName << "\n";
		cout << "Full Name       :      " << User.FullName() << "\n";
		cout << "Email           :      " << User.Email << "\n";
		cout << "Phone           :      " << User.Phone << "\n";
		cout << "Password        :      " << User.Password << "\n";
		cout << "Permissions     :      " << User.Permissions << "\n";
		cout << "====================================================\n";
	}

public:

	static void DeleteUser()
	{
		_DrawScreenHeader("\t  Delete User Screen\n\n");

		string Username = clsInputValidation::ReadString("Please Enter Username: ");

		while (!clsUser::isUserExists(Username))
		{
			cout << "{" << Username << "} Not Found!\n";
			cout << "\n-------------------------------------------------------------------\n";

			Username = clsInputValidation::ReadString("Please Enter Username: ");
		}

		clsUser User = clsUser::Find(Username);

		_PrintUser(User);

		cout << "Delete User     :-\n";
		cout << "-----------------------------\n";

		cout << "Are You Sure You Want To Delete This User [Y/N] ? ";

		char Answer = 'Y';

		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			if (User.Delete())
			{
				cout << "User Deleted Successfully\n";

				_PrintUser(User);
			}

			else
				cout << "\n Error, Account Was Not Deleted";
		}

		else
			cout << "No User Deleted\n";

	}
};


