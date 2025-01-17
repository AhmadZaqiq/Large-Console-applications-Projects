#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsUtil.h"
#include "clsPerson.h"
#include "clsString.h"

using namespace std;

class clsUser : public clsPerson
{
private:

	struct stLoginLogs;

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	string _ConvertLoginLogToLine(string Separator = "#//#")
	{
		string StringLoginLog = "";

		StringLoginLog = StringLoginLog + clsDate::GetCurrentTime() + Separator;
		StringLoginLog = StringLoginLog + Username + Separator;
		StringLoginLog = StringLoginLog + clsUtil::EncryptText(Password,6) + Separator;
		StringLoginLog = StringLoginLog + to_string(Permissions);

		return StringLoginLog;
	}

	enMode _Mode;
	string _Username;
	string _Password;
	short _Permissions;
	bool _MarkForDelete = false;

	static clsUser _ConvertLineToUsersObject(string Line, string Separator = "#//#")
	{
		vector <string> vUsersData = clsString::Split(Line, Separator);

		return clsUser(enMode::UpdateMode, vUsersData[0], vUsersData[1], vUsersData[2],
			vUsersData[3], vUsersData[4], clsUtil::DecryptText(vUsersData[5],6), stoi(vUsersData[6]));
	}
	
	static  string _ConvertUserObjectToLine(clsUser User, string Separator = "#//#")
	{
		string StringUserData = "";

		StringUserData = StringUserData + User.FirstName + Separator;
		StringUserData = StringUserData + User.LastName + Separator;
		StringUserData = StringUserData + User.Email + Separator;
		StringUserData = StringUserData + User.Phone + Separator;
		StringUserData = StringUserData + User.Username + Separator;
		StringUserData = StringUserData + clsUtil::EncryptText(User.Password,6) + Separator;
		StringUserData = StringUserData + to_string(User.Permissions);

		return StringUserData;
	}

	static vector <clsUser> _LoadUsersDataFromFile()
	{
		fstream MyFile;

		vector <clsUser> vUsers;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vUsers.push_back(_ConvertLineToUsersObject(Line));
			}
		}
		return vUsers;
	}

	static void _SaveUsersDataToFile(vector <clsUser> vUsers)
	{
		fstream MyUsersFile;

		MyUsersFile.open("Users.txt", ios::out);

		string DataLine;

		if (MyUsersFile.is_open())
		{
			for (clsUser& U : vUsers)
			{
				if (U._MarkForDelete == false)
				{
					DataLine = _ConvertUserObjectToLine(U);
					MyUsersFile << DataLine << endl;
				}
			}
			MyUsersFile.close();
		}
	}

	void _Update()
	{
		vector <clsUser> _vUsers;
		_vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : _vUsers)
		{
			if (U.Username == Username)
			{
				U = *this;
				break;
			}
		}
		_SaveUsersDataToFile(_vUsers);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertUserObjectToLine(*this));
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Users.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	static clsUser _GetEmptyUserObject()
	{
		return clsUser(EmptyMode, "", "", "", "", "", "", 0);
	}

	static stLoginLogs _ConvertLineToLoginLog(string Line, string Separator = "#//#")
	{
		stLoginLogs LoginLogs;

		vector <string> vLoginLog = clsString::Split(Line, Separator);

		LoginLogs.CurrentTime = vLoginLog[0];
		LoginLogs.Username = vLoginLog[1];
		LoginLogs.Password = clsUtil::DecryptText(vLoginLog[2],6);
		LoginLogs.Permissions = vLoginLog[3];

		return LoginLogs;
	}

public:

	struct stLoginLogs
	{
		string CurrentTime, Username, Password, Permissions;
	};

	enum enMainMenuPermissions
	{
		Pall = -1, PClintList = 1, PAddClient = 2, PDeleteClient = 4, PUpdateClient = 8
		, PFindClient = 16, PTransactions = 32, PManageUsers = 64, PLoginRegister = 128,
		PCurrencyExchange = 256
	};

	bool Delete()
	{
		vector <clsUser> vUsers = _LoadUsersDataFromFile();

		for (clsUser& U : vUsers)
		{
			if (U.Username == _Username)
			{
				U._MarkForDelete = true;
				break;
			}
		}

		_SaveUsersDataToFile(vUsers);

		*this = _GetEmptyUserObject();

		return true;
	}

	enum enSaveResults { svSucceesed = 0, svFaildEmptyObject = 1, svFaildAccNumberExists = 2 };

	clsUser(enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string Username, string Password, short Permissions)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_Username = Username;
		_Password = Password;
		_Permissions = Permissions;
	}

	void SetPassword(string Password)
	{
		_Password = Password;
	}

	void SetPermissions(short Permissions)
	{
		_Permissions = Permissions;
	}

	void SetUsername(string Username)
	{
		_Username = Username;
	}

	string GetPassword()
	{
		return _Password;
	}

	float GetPermissions()
	{
		return _Permissions;
	}

	string GetUsername()
	{
		return _Username;
	}

	__declspec(property(get = GetPassword, put = SetPassword)) string Password;
	__declspec(property(get = GetPermissions, put = SetPermissions)) float Permissions;
	__declspec(property(get = GetUsername, put = SetUsername)) string Username;

	static clsUser GetAddNewUserObject(string Username)
	{
		return clsUser(AddNewMode, "", "", "", "", Username, "", 0);
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static clsUser Find(string Username)
	{
		fstream MyFile;

		vector <clsUser> vUsers;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUsersObject(Line);

				if (User.Username == Username)
				{
					MyFile.close();

					return User;
				}

				vUsers.push_back(User);
			}
			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static clsUser Find(string Username, string Password)
	{
		fstream MyFile;

		vector <clsUser> vUsers;

		MyFile.open("Users.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsUser User = _ConvertLineToUsersObject(Line);

				if (User.Username == Username && User.Password == Password)
				{
					MyFile.close();

					return User;
				}

				vUsers.push_back(User);
			}
			MyFile.close();
		}

		return _GetEmptyUserObject();
	}

	static bool isUserExists(string AccountNumber)
	{
		clsUser User = clsUser::Find(AccountNumber);

		return (!User.IsEmpty());
	}

	enSaveResults Save()
	{
		switch (_Mode)
		{

		case clsUser::EmptyMode:
		{
			return svFaildEmptyObject;
		}

		case clsUser::UpdateMode:
		{
			_Update();

			return svSucceesed;
		}

		case clsUser::AddNewMode:

			if (clsUser::isUserExists(_Username))
				return enSaveResults::svFaildAccNumberExists;

			else
			{
				_AddNew();

				_Mode = UpdateMode;
				return svSucceesed;
			}

		}
	}

	static vector <clsUser> GetUserList()
	{
		return _LoadUsersDataFromFile();
	}

	bool CheckAccessPermissions(enMainMenuPermissions Permission)
	{
		if (this->_Permissions == enMainMenuPermissions::Pall)
			return true;

		return ((Permission & this->_Permissions) == Permission);
	}

	void SaveLoginLogDataToFile()
	{
		fstream MyClientsFile;

		MyClientsFile.open("LoginLog.txt", ios::out | ios::app);

		string DataLine;

		if (MyClientsFile.is_open())
		{
			DataLine = _ConvertLoginLogToLine();
			MyClientsFile << DataLine << endl;
		}

		MyClientsFile.close();
	}

	static vector <stLoginLogs> LoadLoginLogFromFile()
	{
		fstream MyFile;

		vector <stLoginLogs> vLoginLogs;

		MyFile.open("LoginLog.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vLoginLogs.push_back(_ConvertLineToLoginLog(Line));
			}
		}
		return vLoginLogs;
	}

};

