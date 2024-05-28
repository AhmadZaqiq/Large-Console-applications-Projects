#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsScreen.h"
#include "clsPerson.h"
#include "clsString.h"

#include "Global.h"

using namespace std;

class clsBankClient :public clsPerson
{
private:

	struct stTransferLog;

	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2 };

	enMode _Mode;

	string _ConvertTransferLogToLine(double Amount, clsBankClient DestinationClient, string Separator = "#//#")
	{
		string StringTranferLog = "";

		StringTranferLog = StringTranferLog + clsDate::GetCurrentTime() + Separator;
		StringTranferLog = StringTranferLog + AccountNumber() + Separator;
		StringTranferLog = StringTranferLog + DestinationClient.AccountNumber() + Separator;
		StringTranferLog = StringTranferLog + to_string(Amount) + Separator;
		StringTranferLog = StringTranferLog + to_string(Balance) + Separator;
		StringTranferLog = StringTranferLog + to_string(DestinationClient.Balance) + Separator;
		StringTranferLog = StringTranferLog + CurrentUser.Username;

		return StringTranferLog;
	}

	static stTransferLog _ConvertLineToTranferLog(string Line, string Separator = "#//#")
	{
		stTransferLog TransferLog;

		vector <string> vTransferLog = clsString::Split(Line,Separator);

		TransferLog.CurrentTime = vTransferLog[0];
		TransferLog.SourceClientNum = vTransferLog[1];
		TransferLog.DestinationClientNum = vTransferLog[2];
		TransferLog.Amount = vTransferLog[3];
		TransferLog.SourceClientBalnce = vTransferLog[4];
		TransferLog.DestinationClientBalance = vTransferLog[5];
		TransferLog.User = vTransferLog[6];

		return TransferLog;
	}

	void _SaveTransferDataToFile(double Amount, clsBankClient DestinationClient, string Separator = "#//#")
	{
		fstream MyClientsFile;

		MyClientsFile.open("Transfer.txt", ios::out | ios::app);

		string DataLine;

		if (MyClientsFile.is_open())
		{
			DataLine = _ConvertTransferLogToLine(Amount, DestinationClient);
			MyClientsFile << DataLine << endl;
		}

		MyClientsFile.close();
	}

	string _AccountNumber;
	string _PinCode;
	float _Balance;
	bool _MarkForDelete = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Separator = "#//#")
	{
		vector <string> vClientData = clsString::Split(Line, Separator);

		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], vClientData[5], stof(vClientData[6]));
	}

	static  string _ConvertClientObjectToLine(clsBankClient Client, string Separator = "#//#")
	{
		string StringClientData = "";

		StringClientData = StringClientData + Client.FirstName + Separator;
		StringClientData = StringClientData + Client.LastName + Separator;
		StringClientData = StringClientData + Client.Email + Separator;
		StringClientData = StringClientData + Client.Phone + Separator;
		StringClientData = StringClientData + Client.AccountNumber() + Separator;
		StringClientData = StringClientData + Client.PinCode + Separator;
		StringClientData = StringClientData + to_string(Client.Balance);

		return StringClientData;
	}

	static vector <clsBankClient> _LoadClientsDataFromFile()
	{
		fstream MyFile;

		vector <clsBankClient> vClients;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vClients.push_back(_ConvertLineToClientObject(Line));
			}
		}
		return vClients;
	}

	static void _SaveClientsDataToFile(vector <clsBankClient> vClients)
	{
		fstream MyClientsFile;

		MyClientsFile.open("Clients.txt", ios::out);

		string DataLine;

		if (MyClientsFile.is_open())
		{
			for (clsBankClient& C : vClients)
			{
				if (C._MarkForDelete == false)
				{
					DataLine = _ConvertClientObjectToLine(C);
					MyClientsFile << DataLine << endl;
				}
			}
			MyClientsFile.close();
		}
	}

	void _Update()
	{
		vector <clsBankClient> _vClient;
		_vClient = _LoadClientsDataFromFile();

		for (clsBankClient& C : _vClient)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClient);
	}

	void _AddNew()
	{
		_AddDataLineToFile(_ConvertClientObjectToLine(*this));
	}

	void _AddDataLineToFile(string  stDataLine)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);

		if (MyFile.is_open())
		{

			MyFile << stDataLine << endl;

			MyFile.close();
		}

	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(EmptyMode, "", "", "", "", "", "", 0);
	}

public:

	struct stTransferLog
	{
		string CurrentTime, SourceClientNum, DestinationClientNum, Amount,
			SourceClientBalnce, DestinationClientBalance, User;
	};

	bool Delete()
	{
		vector <clsBankClient> vClients = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkForDelete = true;
				break;
			}
		}

		_SaveClientsDataToFile(vClients);

		*this = _GetEmptyClientObject();

		return true;
	}

	void Depoist(float DepoistAmount)
	{
		_Balance += DepoistAmount;
		Save();
	}

	bool Withdraw(float WithdrawAmount)
	{
		if (WithdrawAmount > _Balance)
		{
			return false;
		}
		else
		{
			_Balance -= WithdrawAmount;
			Save();
			return true;
		}
	}

	enum enSaveResults { svSucceesed = 0, svFaildEmptyObject = 1, svFaildAccNumberExists = 2 };

	clsBankClient(enMode Mode, string FirstName, string LastName, string Email,
		string Phone, string AccountNumber, string PinCode, float Balance)
		:clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_Balance = Balance;
	}

	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	void SetBalance(float Balance)
	{
		_Balance = Balance;
	}

	string AccountNumber()
	{
		return _AccountNumber;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	float GetBalance()
	{
		return _Balance;
	}

	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;
	__declspec(property(get = GetBalance, put = SetBalance)) float Balance;

	static clsBankClient GetAddNewClientObject(string AccoutNumber)
	{
		return clsBankClient(AddNewMode, "", "", "", "", AccoutNumber, "", 0);
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;

		vector <clsBankClient> vClients;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();

					return Client;
				}

				vClients.push_back(Client);
			}
			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream MyFile;

		vector <clsBankClient> vClients;

		MyFile.open("Clients.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);

				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();

					return Client;
				}

				vClients.push_back(Client);
			}
			MyFile.close();
		}

		return _GetEmptyClientObject();
	}

	static bool isClientExists(string AccountNumber)
	{
		clsBankClient Client = clsBankClient::Find(AccountNumber);

		return (!Client.IsEmpty());
	}

	enSaveResults Save()
	{
		switch (_Mode)
		{

		case clsBankClient::EmptyMode:
		{
			return svFaildEmptyObject;
		}

		case clsBankClient::UpdateMode:
		{
			_Update();

			return svSucceesed;
		}

		case clsBankClient::AddNewMode:

			if (clsBankClient::isClientExists(_AccountNumber))
				return enSaveResults::svFaildAccNumberExists;

			else
			{
				_AddNew();

				_Mode = UpdateMode;
				return svSucceesed;
			}

		}
	}

	static vector <clsBankClient> GetClientList()
	{
		return _LoadClientsDataFromFile();
	}

	static double GetTotalBalances()
	{
		double TotalBalances = 0;

		vector <clsBankClient> vClient = _LoadClientsDataFromFile();

		for (clsBankClient& C : vClient)
		{
			TotalBalances += C.Balance;
		}

		return TotalBalances;
	}

	bool Transfer(float Amount, clsBankClient& DestinationClient)
	{
		if (Amount > Balance)
		{
			return false;
		}

		Withdraw(Amount);
		DestinationClient.Depoist(Amount);
		_SaveTransferDataToFile(Amount, DestinationClient);
		return true;

	}

	static vector <stTransferLog> LoadTranferLogDataFromFile()
	{
		fstream MyFile;

		vector <stTransferLog> vTranferLogs;

		MyFile.open("Transfer.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vTranferLogs.push_back(_ConvertLineToTranferLog(Line));
			}
		}
		return vTranferLogs;
	}
};

