#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsScreen.h"
#include "clsListUsersScreen.h"
#include "clsAddUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen :protected clsScreen
{
private:

	enum _enManageUsersOptions
	{
		ListUsers = 1, enAddNewUser = 2, enDeleteUser = 3, UpdateUser = 4, enFindUser = 5, MainMenu = 6
	};

	static void _ShowUsersList()
	{
		clsListUsersScreen::ShowUserList();
	}

	static void _AddUser()
	{
		clsAddUserScreen::AddNewUser();
	}

	static void _DeleteUser()
	{
		clsDeleteUserScreen::DeleteUser();
	}

	static void _UpdateUserInfo()
	{
		clsUpdateUserScreen::UpdateUser();
	}

	static void _FindUser()
	{
		clsFindUserScreen::FindUser();
	}

	static void _GoBackToManageUsersMenu()
	{
		cout << "\n\nPress any key to go back to Manage Users Menue...";
		system("pause>0");
		ShowMangeUsersMenuScreen();
	}

	static void _ChooseUserOption(_enManageUsersOptions UsereOptions)
	{

		switch (UsereOptions)
		{
		case _enManageUsersOptions::ListUsers:

			system("cls");
			_ShowUsersList();
			_GoBackToManageUsersMenu();
			break;

		case _enManageUsersOptions::enAddNewUser:

			system("cls");
			_AddUser();
			_GoBackToManageUsersMenu();
			break;

		case _enManageUsersOptions::enDeleteUser:

			system("cls");
			_DeleteUser();
			_GoBackToManageUsersMenu();
			break;

		case _enManageUsersOptions::UpdateUser:

			system("cls");
			_UpdateUserInfo();
			_GoBackToManageUsersMenu();
			break;

		case _enManageUsersOptions::enFindUser:

			system("cls");
			_FindUser();
			_GoBackToManageUsersMenu();
			break;
		case _enManageUsersOptions::MainMenu:

			break;
		}
	}

public:

	static void ShowMangeUsersMenuScreen()
	{
		system("cls");

		if (!CheckAccessRights(clsUser::PManageUsers))
		{
			return;
		}

		_DrawScreenHeader("\t   Manage Users Screen\n\n");

		cout << setw(39) << "" << "=========================================\n";
		cout << setw(39) << "" << "         Manage Users Menu Screen        \n";
		cout << setw(39) << "" << "=========================================\n";
		cout << setw(39) << "" << "  [1] List Users.                        \n";
		cout << setw(39) << "" << "  [2] Add New User.                      \n";
		cout << setw(39) << "" << "  [3] Delete User.                       \n";
		cout << setw(39) << "" << "  [4] Update User.                       \n";
		cout << setw(39) << "" << "  [5] Find User.                         \n";
		cout << setw(39) << "" << "  [6] Main Menu.                         \n";
		cout << setw(39) << "" << "=========================================\n";

		_ChooseUserOption(_enManageUsersOptions(clsInputValidation::ReadIntNumberBetween
		(0, 7, "\t\t\t\t\tChoose What Do You Want To do[1 to 6] ? ", "\t\t\t\t\tInvalid Chice,")));
	}

};

