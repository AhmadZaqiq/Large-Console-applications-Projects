#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsUtil.h"
#include "clsScreen.h"
#include "clsUser.h"
#include "clsInputValidation.h"

using namespace std;

class clsAddUserScreen :public clsScreen
{
private:

	static void _ReadUserInfo(clsUser& User)
	{
		User.FirstName = clsInputValidation::ReadString("\nEnter First Name   :  ");

		User.LastName = clsInputValidation::ReadString("\nEnter Last  Name    :  ");

		User.Email = clsInputValidation::ReadString("\nEnter Email            :  ");

		User.Phone = clsInputValidation::ReadString("\nEnter Phone            :  ");

		User.Password = clsInputValidation::ReadString("\nEnter Password      :  ");

		User.Permissions = _GetPermissions();
	}

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

	static short _GetPermissions()
	{
		short PermissionNumber = 0;

		char Access = 'N';

		cout << "Do You Want To Give Full Access? Y/N ";
		cin >> Access;

		if (toupper(Access) == 'Y')
			return clsUser::Pall;

		cout << "Do You Want To Give Access To:- \n\n";

		cout << "Show Client List ? Y/N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			PermissionNumber += clsUser::PClintList;

		cout << "Add New Client ? Y/N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			PermissionNumber += clsUser::PAddClient;

		cout << "Delete Client ? Y/N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			PermissionNumber += clsUser::PDeleteClient;

		cout << "Update Client Info ? Y/N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			PermissionNumber += clsUser::PUpdateClient;

		cout << "Find Client ? Y/N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			PermissionNumber += clsUser::PFindClient;

		cout << "Transactions ? Y/N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			PermissionNumber += clsUser::PTransactions;

		cout << "Manage Users ? Y/N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			PermissionNumber += clsUser::PManageUsers;

		cout << "Login Register ? Y/N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			PermissionNumber += clsUser::PLoginRegister;

		cout << "Currency Exchange ? Y/N ";
		cin >> Access;
		if (toupper(Access) == 'Y')
			PermissionNumber += clsUser::PCurrencyExchange;

		return PermissionNumber;
	}

public:

	static void AddNewUser()
	{
		_DrawScreenHeader("Add New User Screen\n\n");

		string Username = clsInputValidation::ReadString("Please Enter Username: ");

		while (clsUser::isUserExists(Username))
		{
			cout << "{" << Username << "} Is Already Used!\n";
			cout << "\n-------------------------------------------------------------------\n";

			Username = clsInputValidation::ReadString("Please Enter Username: ");
		}

		clsUser NewUser = clsUser::GetAddNewUserObject(Username);

		cout << "Add User Info     :-\n";
		cout << "-----------------------------\n";

		_ReadUserInfo(NewUser);

		clsUser::enSaveResults SaveResults;

		SaveResults = NewUser.Save();

		switch (SaveResults)
		{
		case clsUser::svSucceesed:
		{
			cout << "User Added Successfully";

			_PrintUser(NewUser);

			break;
		}

		case clsUser::svFaildEmptyObject:

			cout << "\n Error Account Was Not Saved Because it is Empty";
			break;

		case clsUser::svFaildAccNumberExists:

			cout << "\n{" << Username << "} Is Already Used!\n";
			break;
		}
	}
};

