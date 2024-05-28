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
class clsFindUserScreen : protected clsScreen
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

	static void FindUser()
	{
		_DrawScreenHeader("\t Find User Screen\n\n");

		string Username = clsInputValidation::ReadString("Please Enter Username: ");

		while (!clsUser::isUserExists(Username))
		{
			cout << "Username Was Not Found...\n";

			Username = clsInputValidation::ReadString("Please Enter Username: ");
		}
		clsUser User = clsUser::Find(Username);

		if (!User.IsEmpty())
		{
			cout << "\nUser Found\n";
		}

		else
		{
			cout << "\nUser Was Not Found\n";
		}

		_PrintUser(User);
	}

};

