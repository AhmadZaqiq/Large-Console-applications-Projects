#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsDate.h"
#include "clsScreen.h"
#include "clsUser.h"
#include "Global.h"

using namespace std;

class clsScreen
{
protected:

	static void _DrawScreenHeader(string Title,string SubTitle="")
	{
		cout << setw(30) << "" << "-----------------------------------------------------------\n\n";
		cout << setw(47) << "" << Title;
		cout << setw(51) << "" << SubTitle;
		cout<<"\n" << setw(30) << "" << "-----------------------------------------------------------\n\n";

		cout << setw(40) << "" << "______________________________________\n";
		cout << setw(40) << "" << "User: " << CurrentUser.Username << "\n";
		cout << setw(40) << "" << "Date: " << clsDate::DateToString(clsDate())<< "\n";
		cout << setw(40) << "" << "______________________________________\n\n\n";
	}

	static bool CheckAccessRights(clsUser::enMainMenuPermissions Permissions)
	{
		if (!CurrentUser.CheckAccessPermissions(Permissions))
		{
			cout << setw(30) << "" << "-----------------------------------------------------------\n\n";
			cout << setw(40) << "" << "Access denied...Please contact the admin          \n\n";
			cout << setw(30) << "" << "-----------------------------------------------------------\n\n";

			return false;
		}

		else
		{
			return true;
		}
	}

};

