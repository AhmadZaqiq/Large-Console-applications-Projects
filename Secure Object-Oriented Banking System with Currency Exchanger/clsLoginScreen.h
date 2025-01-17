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
#include "clsMainScreen.h"
#include "Global.h"

using namespace std;

class clsLoginScreen :protected clsScreen
{
private:

	static bool _Login()
	{
		bool LoginFaild = false;
		short LoginFaildCount = 0;

		string Username = "", Password = "";

		do
		{
			if (LoginFaild)
			{
				LoginFaildCount++;
				cout << "\n\t\t\t\t\tInvalid Username & Password, Try Agian...\n";
				cout << "\n\t\t\t\t\tYou Have [" << 3 - LoginFaildCount << "] Trailis To Login...\n";
			}

			if (LoginFaildCount == 3)
			{
				cout << "\n\nSorry, You Are Locked After 3 Faild Trails...Please contact the admin\n\n";
				system("pause>0");
				return false;
			}

			Username = clsInputValidation::ReadString("\n\t\t\t\t\tPlease Enter Username: ");
			Password = clsInputValidation::ReadString("\n\t\t\t\t\tPlease Enter Password: ");

			CurrentUser = clsUser::Find(Username, Password);

			LoginFaild = CurrentUser.IsEmpty();

		} while (LoginFaild);


		CurrentUser.SaveLoginLogDataToFile();
		system("cls");
		clsMainScreen::ShowMainMenuScreen();

	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");

		_DrawScreenHeader("\tLogin Screen\n\n");

		return _Login();
	}

};

