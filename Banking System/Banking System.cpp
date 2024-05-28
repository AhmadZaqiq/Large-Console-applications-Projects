//Ahmad JR

/*

*important Note:-
You must place the Users.txt file in the project file...

To enter the system for the first time...Use:

Username: Admin
Password: 1234


Instructions:-

1.Run the Program.
2.Add Clients: Use the menu to enter client details.
3.View Clients: Select the option to view the list of all clients.
4.Update Clients: Choose the update option to modify existing client information, by entering the account number and new details.
5.Delete Clients: Remove a client by selecting the delete option and providing the account number.
6.Add Users: Add system users with specific permissions.
7.View Users: Display all system users and their permissions by selecting the appropriate menu option.
8.Update Users: Modify user details and permissions by selecting the update option and providing the username and new details.
9.Delete Users: Remove a system user by entering their username. The user's record will be marked for deletion and updated in Users.txt.
10.Permissions Management: Assign specific permissions to users for tasks like viewing, adding, updating, or deleting client records. Permissions are managed through a binary system to specify different levels of access.
11.Transactions Menu: Use the Transactions Menu to perform banking operations such as deposits, withdrawals, and transfers between accounts. Transactions are logged and can be viewed for each client. Ensure the Transactions.txt file is in the same directory for logging purposes.

*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include<iomanip>

using namespace std;

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";


//CommonClient&Userfunctions

string ReadString(string Message)
{
	string String = "";

	cout << Message;
	cin >> String;

	return String;
}

vector <string> SplitString(string S1, string delim)
{
	vector <string> vString;

	short pos = 0;
	string Sword;

	while ((pos = S1.find(delim)) != std::string::npos)
	{
		Sword = S1.substr(0, pos);

		if (Sword != "")
		{
			vString.push_back(Sword);
		}
		S1.erase(0, pos + delim.length());
	}

	if (S1 != "")
	{
		vString.push_back(S1);
	}
	return vString;
}



//CommonClientfunctions

struct stClient
{
	string AccountNumber = "", Name = "", Phone = "", PINCode = "";
	double AccountBalance = 0;
	bool MarkForDelete = false;
};

string ConvertRecordToLine(stClient Client, string delim)
{
	string StringClientData = "";

	StringClientData = StringClientData + Client.AccountNumber + delim;
	StringClientData = StringClientData + Client.PINCode + delim;
	StringClientData = StringClientData + Client.Name + delim;
	StringClientData = StringClientData + Client.Phone + delim;
	StringClientData = StringClientData + to_string(Client.AccountBalance);

	return StringClientData;
}

stClient ConvertLineToRecord(string Line)
{
	stClient Client;
	vector <string> vClientData = SplitString(Line, "#//#");

	Client.AccountNumber = vClientData[0];
	Client.PINCode = vClientData[1];
	Client.Name = vClientData[2];
	Client.Phone = vClientData[3];
	Client.AccountBalance = stod(vClientData[4]);

	return Client;
}

void SaveClientToFile(string FileName, string ClientLine)
{
	fstream MyClientsFile;

	MyClientsFile.open(FileName, ios::out | ios::app);

	if (MyClientsFile.is_open())
	{
		MyClientsFile << ClientLine << endl;

		MyClientsFile.close();
	}
}

vector <stClient> SaveClientsDataToFile(string FileName, vector <stClient> vClients)
{
	fstream MyClientsFile;

	MyClientsFile.open(FileName, ios::out);

	string DataLine;

	if (MyClientsFile.is_open())
	{
		for (stClient& C : vClients)
		{
			if (C.MarkForDelete == false)
			{
				DataLine = ConvertRecordToLine(C, "#//#");
				MyClientsFile << DataLine << endl;
			}
		}

		MyClientsFile.close();
	}
	return vClients;
}

vector <stClient> LoadClientsDataFromFile(string FileName)
{
	fstream MyFile;

	vector <stClient> vClients;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stClient Client;

		while (getline(MyFile, Line))
		{
			vClients.push_back(ConvertLineToRecord(Line));
		}
	}
	return vClients;
}

stClient ReadNewClient()
{
	stClient Client;

	cout << "please Enter Client Data     :-\n\n";

	cout << "Enter Account Number         : ";
	getline(cin >> ws, Client.AccountNumber);
	cout << "Enter PIN Code               : ";
	getline(cin, Client.PINCode);
	cout << "Enter Name                   : ";
	getline(cin, Client.Name);
	cout << "Enter Phone                  : ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance         : ";
	cin >> Client.AccountBalance;

	return Client;
}

bool CheckIfClientAccountExist(stClient& Client, string UserAccountNumber)
{
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	for (stClient C : vClients)
	{
		if (UserAccountNumber == C.AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool CheckIfClientAccountExist(stClient& Client, string UserAccountNumber, vector <stClient> vClients)
{
	for (stClient C : vClients)
	{
		if (UserAccountNumber == C.AccountNumber)
		{
			Client = C;
			return true;
		}
	}
	return false;
}

bool CheckIfClientAccountExist(string UserAccountNumber)
{
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	for (stClient C : vClients)
	{
		if (UserAccountNumber == C.AccountNumber)
		{
			return true;
		}
	}
	return false;
}

void PrintClientByAccountNumber(stClient Client)
{
	cout << "\nThe Follwing Are The Client Details:-\n\n";

	cout << "Account Number :" << Client.AccountNumber << "\n";
	cout << "PIN Code       :" << Client.PINCode << "\n";
	cout << "Client Name    :" << Client.Name << "\n";
	cout << "Phone          :" << Client.Phone << "\n";
	cout << "Balance        :" << Client.AccountBalance << "\n";
}

string AskUserToEnterClientNumberWithLoop()
{
	stClient Client;
	string UserAccountNumber = "";

	do
	{
		UserAccountNumber = ReadString("please Enter Account Number ? ");

		if (!CheckIfClientAccountExist(Client, UserAccountNumber))
			cout << "Client With Account Number (" << UserAccountNumber << ") Does Not Exist.\n\n";

	} while (!CheckIfClientAccountExist(Client, UserAccountNumber));

	return UserAccountNumber;
}



//CommonUsersfunctions

struct stUser
{
	string AccountName, Password;
	short Permissions;
	bool MarkUserForDelete = false;
};

stUser ConvertUserLineToRecord(string Line)
{
	stUser User;
	vector <string> vUserData = SplitString(Line, "#//#");

	User.AccountName = vUserData[0];
	User.Password = vUserData[1];
	User.Permissions = stoi(vUserData[2]);

	return User;
}

vector <stUser> LoadUsersDataFromFile(string FileName)
{
	fstream MyFile;

	vector <stUser> vUsers;

	MyFile.open(FileName, ios::in);

	if (MyFile.is_open())
	{
		string Line;
		stUser User;

		while (getline(MyFile, Line))
		{
			vUsers.push_back(ConvertUserLineToRecord(Line));
		}
	}
	return vUsers;
}

bool CheckIfUserAccountExist(string Username)
{
	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

	for (stUser U : vUsers)
	{
		if (Username == U.AccountName)
		{
			return true;
		}
	}
	return false;
}

void SaveUserToFile(string FileName, string UserLine)
{
	fstream MyUsersFile;

	MyUsersFile.open(FileName, ios::out | ios::app);

	if (MyUsersFile.is_open())
	{
		MyUsersFile << UserLine << endl;

		MyUsersFile.close();
	}
}

string ConvertUserRecordToLine(stUser User, string delim)
{
	string StringClientData = "";

	StringClientData = StringClientData + User.AccountName + delim;
	StringClientData = StringClientData + User.Password + delim;
	StringClientData = StringClientData + to_string(User.Permissions);

	return StringClientData;
}

bool CheckIfUserAccountExist(stUser& User, string Username, vector <stUser> vUsers)
{
	for (stUser U : vUsers)
	{
		if (Username == U.AccountName)
		{
			User = U;
			return true;
		}
	}
	return false;
}

void PrintUserByUsername(stUser User)
{
	cout << "\nThe Follwing Are The User Details:-\n\n";

	cout << "----------------------------------------" << "\n";
	cout << "Usename        :" << User.AccountName << "\n";
	cout << "Password       :" << User.Password << "\n";
	cout << "Permissions    :" << User.Permissions << "\n";
	cout << "----------------------------------------" << "\n\n";
}

vector <stUser> SaveUsersDataToFile(string FileName, vector <stUser> vUser)
{
	fstream MyUsersFile;

	MyUsersFile.open(FileName, ios::out);

	string DataLine;

	if (MyUsersFile.is_open())
	{
		for (stUser& U : vUser)
		{
			if (U.MarkUserForDelete == false)
			{
				DataLine = ConvertUserRecordToLine(U, "#//#");
				MyUsersFile << DataLine << endl;
			}
		}

		MyUsersFile.close();
	}
	return vUser;
}

bool CheckIfUserAccountExist(stUser& User, string username)
{
	vector <stUser> vUser = LoadUsersDataFromFile(UsersFileName);

	for (stUser U : vUser)
	{
		if (username == U.AccountName)
		{
			User = U;
			return true;
		}
	}
	return false;
}

stUser CurrentUser;



//[1] ShowUserList
void PrintUsersHeadar(vector <stUser>);

void PrintUser(stUser Users)
{
	cout << "| " << left << setw(15) << Users.AccountName;
	cout << "| " << left << setw(10) << Users.Password;
	cout << "| " << left << setw(40) << Users.Permissions;
}

void PrintUsers(vector <stUser> vUsers)
{
	for (stUser U : vUsers)
	{
		PrintUser(U);
		cout << "\n";
	}
}

//[2] AddUser

enum enMainMenuPermissions
{
	Pall = -1, PClintList = 1, PAddClient = 2, PDeleteClient = 4, PUpdateClient = 8
	, PFindClient = 16, PTransactions = 32, PManageUsers = 64
};

short GetPermissions()
{
	short PermissionNumber = 0;

	char Access = 'N';

	cout << "Do You Want To Give Full Access? Y/N ";
	cin >> Access;

	if (toupper(Access) == 'Y')
		return enMainMenuPermissions::Pall;

	cout << "Do You Want To Give Access To:- \n\n";

	cout << "Show Client List ? Y/N ";
	cin >> Access;
	if (toupper(Access) == 'Y')
		PermissionNumber += enMainMenuPermissions::PClintList;

	cout << "Add New Client ? Y/N ";
	cin >> Access;
	if (toupper(Access) == 'Y')
		PermissionNumber += enMainMenuPermissions::PAddClient;

	cout << "Delete Client ? Y/N ";
	cin >> Access;
	if (toupper(Access) == 'Y')
		PermissionNumber += enMainMenuPermissions::PDeleteClient;

	cout << "Update Client Info ? Y/N ";
	cin >> Access;
	if (toupper(Access) == 'Y')
		PermissionNumber += enMainMenuPermissions::PUpdateClient;

	cout << "Find Client ? Y/N ";
	cin >> Access;
	if (toupper(Access) == 'Y')
		PermissionNumber += enMainMenuPermissions::PFindClient;

	cout << "Transactions ? Y/N ";
	cin >> Access;
	if (toupper(Access) == 'Y')
		PermissionNumber += enMainMenuPermissions::PTransactions;

	cout << "Manage Users ? Y/N ";
	cin >> Access;
	if (toupper(Access) == 'Y')
		PermissionNumber += enMainMenuPermissions::PManageUsers;


	return PermissionNumber;
}

bool CheckAccessPermissions(enMainMenuPermissions Permissions)
{
	if (CurrentUser.Permissions == enMainMenuPermissions::Pall)
		return true;

	return ((Permissions & CurrentUser.Permissions) == Permissions);
}

stUser ReadNewUser(string Username)
{
	stUser User;

	do
	{
		if (CheckIfUserAccountExist(Username))
		{
			cout << "User With Username [" << Username << "] Already Exists, Enter Another Username ?";
			getline(cin >> ws, Username);
		}

	} while (CheckIfUserAccountExist(Username));

	User.AccountName = Username;

	cout << "Enter Password: ";
	cin >> User.Password;

	User.Permissions = GetPermissions();

	return User;
}

void AddNewUser()
{
	stUser User;
	string Username;

	cout << "Enter Username: ";

	getline(cin >> ws, Username);

	User = ReadNewUser(Username);

	SaveUserToFile(UsersFileName, ConvertUserRecordToLine(User, "#//#"));
}


//[3] DeleteUser
bool MarkUserForDeleteByUsername(string Username, vector <stUser>& vUser)
{
	for (stUser& U : vUser)
	{
		if (Username == U.AccountName)
		{
			U.MarkUserForDelete = true;
			return true;
		}
	}
	return false;
}

bool DeleteUserByUsername(string Username, vector <stUser>& vUser)
{
	stUser User;
	char Answer = 'N';

	if (CheckIfUserAccountExist(User, Username, vUser))
	{
		PrintUserByUsername(User);

		cout << "Are You Sure you want to delete this User [Y/y] ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			MarkUserForDeleteByUsername(Username, vUser);

			SaveUsersDataToFile(UsersFileName, vUser);

			vUser = LoadUsersDataFromFile(UsersFileName);

			cout << "User Deleted Successfully";
			return true;
		}
	}
	else
	{
		cout << "User With Username  (" << Username << ") Not Found!";
		return false;
	}
}


//[4] UpdateUserInfo
stUser ChangeUserRecord(string Username)
{
	stUser User;

	cout << "please Enter New User " << Username << " Data :-\n\n";


	User.AccountName = Username;

	cout << "Enter Password: ";
	cin >> User.Password;

	User.Permissions = GetPermissions();

	return User;
}

bool UpdateUserByUsername(string Username, vector <stUser>& vUser)
{
	stUser User;
	char Answer = 'N';

	if (CheckIfUserAccountExist(User, Username, vUser))
	{
		PrintUserByUsername(User);

		cout << "Are You Sure you want to Update this User [Y/y] ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			for (stUser& U : vUser)
			{
				if (U.AccountName == Username)
				{
					U = ChangeUserRecord(Username);
					break;
				}
			}

			SaveUsersDataToFile(UsersFileName, vUser);

			cout << "User Updated Successfully";
			return true;
		}
	}
	else
	{
		cout << "User With Username (" << Username << ") Not Found!";
		return false;
	}
}


//ManageUsersMenu
void PrintUsersHeadar(vector <stUser>);

void ShowUsersList()
{
	stUser User;
	vector <stUser> vUsers = LoadUsersDataFromFile(UsersFileName);

	PrintUsersHeadar(vUsers);

	PrintUsers(vUsers);
}

void AddUser()
{
	char AddNew = 'Y';

	do
	{
		AddNewUser();

		cout << "User Added Successfully, Do You Want To Add More Users [Y/y] ? ";
		cin >> AddNew;

	} while (toupper(AddNew) == 'Y');
}

void DeleteUser()
{
	stUser User;
	string Username = ReadString("please Enter Username? ");

	if (Username != "Admin")
	{
		vector <stUser> vUser = LoadUsersDataFromFile(UsersFileName);

		DeleteUserByUsername(Username, vUser);
	}

	else
		cout << "\nYou Cannot Delete This User...";
}

void UpdateUserInfo()
{
	stUser User;
	string Username = ReadString("please Enter Username ? ");
	vector <stUser> vUser = LoadUsersDataFromFile(UsersFileName);

	UpdateUserByUsername(Username, vUser);
}

void FindUser()
{
	stUser User;
	string Username = ReadString("please Enter User Name ? ");


	if (CheckIfUserAccountExist(User, Username))
		PrintUserByUsername(User);
	else
		cout << "User With Username (" << Username << ") Not Found!";
}


//ManageUsersHeaders
void PrintUsersHeadar(vector <stUser> vUsers)
{
	cout << "                                    User list (" << vUsers.size() << ") User(s)\n\n";

	cout << "_______________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "User Name";
	cout << "| " << left << setw(10) << "Password";
	cout << "| " << left << setw(40) << "Permissions";
	cout << "\n_______________________________________________________________________________________________\n\n";
}

void AddNewUsersHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "          Add New User Screen\n";
	cout << "-----------------------------------------\n";
	cout << "Adding New User:-\n";
}

void DeleteUserHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "          Delete User Screen\n";
	cout << "-----------------------------------------\n";
}

void UpdateUserHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "          Update User Screen\n";
	cout << "-----------------------------------------\n";
}

void FindUserHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "           Find User Screen\n";
	cout << "-----------------------------------------\n";
}


//[1] ShowClientList
void PrintHedar(vector <stClient>);

void PrintClient(stClient Clients)
{
	cout << "| " << left << setw(15) << Clients.AccountNumber;
	cout << "| " << left << setw(10) << Clients.PINCode;
	cout << "| " << left << setw(40) << Clients.Name;
	cout << "| " << left << setw(12) << Clients.Phone;
	cout << "| " << left << setw(12) << Clients.AccountBalance;
}

void PrintClients(vector <stClient> vClients)
{
	for (stClient C : vClients)
	{
		PrintClient(C);
		cout << "\n";
	}
}


//[2] AddClient
stClient ReadNewClient(string UserAccountNumber)
{
	stClient Client;

	do
	{
		if (CheckIfClientAccountExist(UserAccountNumber))
		{
			cout << "Client With Accoutnt [" << UserAccountNumber << "] Already Exists, Enter Another Account Number?";
			getline(cin >> ws, UserAccountNumber);
		}

	} while (CheckIfClientAccountExist(UserAccountNumber));

	Client.AccountNumber = UserAccountNumber;

	cout << "please Enter Client Data     :-\n\n";

	cout << "Enter PIN Code               : ";
	getline(cin >> ws, Client.PINCode);
	cout << "Enter Name                   : ";
	getline(cin, Client.Name);
	cout << "Enter Phone                  : ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance         : ";
	cin >> Client.AccountBalance;

	return Client;
}

void AddNewClient()
{
	stClient Client;
	string UserAccountNumber;

	cout << "Enter Account Number : ";

	getline(cin >> ws, UserAccountNumber);

	Client = ReadNewClient(UserAccountNumber);

	SaveClientToFile(ClientsFileName, ConvertRecordToLine(Client, "#//#"));
}


//[3] DeleteClient
bool MarkClientForDeleteByAccountNumber(string UserAccountNumber, vector <stClient>& vClients)
{
	for (stClient& C : vClients)
	{
		if (UserAccountNumber == C.AccountNumber)
		{
			C.MarkForDelete = true;
			return true;
		}
	}
	return false;
}

bool DeleteClientByAccountNumber(string UserAccountNumber, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'N';

	if (CheckIfClientAccountExist(Client, UserAccountNumber, vClients))
	{
		PrintClientByAccountNumber(Client);

		cout << "Are You Sure you want to delete this Client [Y/y] ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			MarkClientForDeleteByAccountNumber(UserAccountNumber, vClients);

			SaveClientsDataToFile(ClientsFileName, vClients);

			vClients = LoadClientsDataFromFile(ClientsFileName);

			cout << "Client Deleted Successfully";
			return true;
		}

	}
	else
	{
		cout << "Client With Account Number (" << UserAccountNumber << ") Not Found!";
		return false;
	}
}


//[4] UpdateClientInfo
stClient ChangeClientRecord(string UserAccountNumber)
{
	stClient Client;

	cout << "please Enter New Client Data     :-\n\n";


	Client.AccountNumber = UserAccountNumber;

	cout << "Enter PIN Code               : ";
	getline(cin >> ws, Client.PINCode);
	cout << "Enter Name                   : ";
	getline(cin, Client.Name);
	cout << "Enter Phone                  : ";
	getline(cin, Client.Phone);
	cout << "Enter AccountBalance         : ";
	cin >> Client.AccountBalance;

	return Client;
}

bool UpdateClientByAccountNumber(string UserAccountNumber, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'N';

	if (CheckIfClientAccountExist(Client, UserAccountNumber, vClients))
	{
		PrintClientByAccountNumber(Client);

		cout << "Are You Sure you want to Update this Client [Y/y] ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			for (stClient& C : vClients)
			{
				if (C.AccountNumber == UserAccountNumber)
				{
					C = ChangeClientRecord(UserAccountNumber);
					break;
				}
			}

			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "Client Updated Successfully";
			return true;
		}
	}
	else
	{
		cout << "Client With Account Number (" << UserAccountNumber << ") Not Found!";
		return false;
	}
}


//ClientOptionsMenu
void PrintHeadar(vector <stClient>);

void ShowClientList()
{
	stClient Client;
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	PrintHeadar(vClients);

	PrintClients(vClients);
}

void AddClient()
{
	char AddNew = 'Y';

	do
	{
		AddNewClient();

		cout << "Client Added Successfully, Do You Want To Add More Client [Y/y] ? ";
		cin >> AddNew;

	} while (toupper(AddNew) == 'Y');
}

void DeleteClient()
{
	stClient Client;
	string UserAccountNumber = ReadString("please Enter Account Number ? ");
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	DeleteClientByAccountNumber(UserAccountNumber, vClients);
}

void UpdateClienInfo()
{
	stClient Client;
	string UserAccountNumber = ReadString("please Enter Account Number ? ");
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	UpdateClientByAccountNumber(UserAccountNumber, vClients);
}

void FindClient()
{
	stClient Client;
	string UserAccountNumber = ReadString("please Enter Account Number ? ");


	if (CheckIfClientAccountExist(Client, UserAccountNumber))
		PrintClientByAccountNumber(Client);
	else
		cout << "Client With Account Number (" << UserAccountNumber << ") Not Found!";
}


//ClientOptionsHeaders
void PrintHeadar(vector <stClient> vClients)
{
	cout << "                                    Client list (" << vClients.size() << ") Client(s)\n\n";

	cout << "_______________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(10) << "PIN Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________________________________________________\n\n";
}

void AddNewClientsHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "          Add New Clients Screen\n";
	cout << "-----------------------------------------\n";
	cout << "Adding New Client:-\n";
}

void DeleteClientHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "          Delete Client Screen\n";
	cout << "-----------------------------------------\n";
}

void UpdateClientInfoHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "          Update Client Info Screen\n";
	cout << "-----------------------------------------\n";
}

void FindClientHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "           Find Client Screen\n";
	cout << "-----------------------------------------\n";
}



//[1]Deposit
stClient UpdateClientDepositAmount(stClient& Client, string UserAccountNumber)
{
	double DepositAmount = 0;

	cout << "\nplease Enter Deposit Amount ?";
	cin >> DepositAmount;

	Client.AccountBalance += DepositAmount;

	return Client;
}

bool UpdateClientAmountDepositByAccountNumber(string UserAccountNumber, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'N';

	if (CheckIfClientAccountExist(Client, UserAccountNumber, vClients))
	{
		PrintClientByAccountNumber(Client);

		cout << "Are You Sure you want to Perform This Transaction [Y/y] ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			for (stClient& C : vClients)
			{
				if (C.AccountNumber == UserAccountNumber)
				{
					C = UpdateClientDepositAmount(Client, UserAccountNumber);
					break;
				}
			}
			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "Done Successfully\n\n";
			cout << "New Balance : " << Client.AccountBalance;
			return true;
		}
	}
	else
	{
		cout << "Client With Account Number (" << UserAccountNumber << ") Not Found!";
		return false;
	}
}


//[2]Withdraw
stClient UpdateClientWithdrawAmount(stClient& Client, string UserAccountNumber)
{
	double WithdrawAmount = 0;

	do
	{
		cout << "\nplease Enter Withdraw Amount ?";
		cin >> WithdrawAmount;

		if (Client.AccountBalance < WithdrawAmount)
			cout << "Amount Exceeds The Balance, You Can Withdraw up to : " << WithdrawAmount << "\n";

	} while (Client.AccountBalance < WithdrawAmount);

	Client.AccountBalance -= WithdrawAmount;

	return Client;
}

bool UpdateClientAmountWithdrawByAccountNumber(string UserAccountNumber, vector <stClient>& vClients)
{
	stClient Client;
	char Answer = 'N';

	if (CheckIfClientAccountExist(Client, UserAccountNumber, vClients))
	{
		PrintClientByAccountNumber(Client);

		cout << "Are You Sure you want to Perform This Transaction [Y/y] ? ";
		cin >> Answer;

		if (toupper(Answer) == 'Y')
		{
			for (stClient& C : vClients)
			{
				if (C.AccountNumber == UserAccountNumber)
				{
					C = UpdateClientWithdrawAmount(Client, UserAccountNumber);
					break;
				}
			}
			SaveClientsDataToFile(ClientsFileName, vClients);

			cout << "\nDone Successfully\n\n";
			cout << "New Balance : " << Client.AccountBalance;
			return true;
		}
	}
	else
	{
		cout << "Client With Account Number (" << UserAccountNumber << ") Not Found!";
		return false;
	}
}


//[3]BalanceList
void PrintBalance(stClient Clients)
{
	cout << "| " << left << setw(15) << Clients.AccountNumber;
	cout << "| " << left << setw(40) << Clients.Name;
	cout << "| " << left << setw(12) << Clients.AccountBalance;
}

void PrintBalances(vector <stClient> vClients)
{
	for (stClient C : vClients)
	{
		PrintBalance(C);
		cout << "\n";
	}
}

void PrintBalancesListHedar(vector <stClient> vClients)
{
	cout << "                                    Balances list (" << vClients.size() << ") Client(s)\n\n";

	cout << "_______________________________________________________________________________________________\n\n";
	cout << "| " << left << setw(15) << "Account Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________________________________________________\n\n";
}

double CalculateTotalBalances(vector <stClient> vClients)
{
	double TotalBalances = 0;

	for (stClient C : vClients)
	{
		TotalBalances += C.AccountBalance;
	}
	return TotalBalances;
}

void ShowfooterAndTotalBalances(double TotalBalances)
{
	cout << "\n_______________________________________________________________________________________________\n\n";

	cout << "\t\t\t\tTotal Balances =" << TotalBalances << "\n\n";
}



//TransactionsMenu
void UpdateClienBalanceDepositInfo()
{
	stClient Client;
	string UserAccountNumber = AskUserToEnterClientNumberWithLoop();
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	UpdateClientAmountDepositByAccountNumber(UserAccountNumber, vClients);
}

void UpdateClienBalanceWithdrawInfo()
{
	stClient Client;
	string UserAccountNumber = AskUserToEnterClientNumberWithLoop();
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	UpdateClientAmountWithdrawByAccountNumber(UserAccountNumber, vClients);
}

void ShowBalancesList()
{
	stClient Client;
	vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

	double TotalBalances = CalculateTotalBalances(vClients);

	PrintBalancesListHedar(vClients);

	PrintBalances(vClients);

	ShowfooterAndTotalBalances(TotalBalances);
}



//TransactionsHeaders
void DepositHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "          Deposit Screen\n";
	cout << "-----------------------------------------\n";
}

void WithdrawHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "          Withdraw Screen\n";
	cout << "-----------------------------------------\n";
}



//OperationsonTransactionsMenu
void ShowMainMenuScreen();

void ChooseOption();

void ShowTransactionsMenuScreen()
{
	cout << "=========================================\n";
	cout << "         Transactions Menu Screen\n";
	cout << "=========================================\n";
	cout << "        [1] Deposit.\n";
	cout << "        [2] Withdraw.\n";
	cout << "        [3] Total Balances\n";
	cout << "        [4] Main Menu.\n";
	cout << "=========================================\n";
}

enum enTransactionsOptions
{
	enDeposit = 1, enWithdraw = 2, enTotalBalances = 3, enMainMenu = 4
};

short ReadTransactionsNumber(string Message)
{
	short Number = 3;

	do
	{
		if (Number < 1 || Number >4)
		{
			cout << "Invalid Try Again...\n";
		}

		cout << Message;
		cin >> Number;

	} while (Number < 1 || Number >4);
	return Number;
}

void ChooseTransaction()
{
	short Number = 0;

	do
	{
		Number = ReadTransactionsNumber("Choose What Do You Want To do[1 to 4] ? ");

		enTransactionsOptions TransOption = enTransactionsOptions(Number);

		switch (TransOption)
		{
		case enTransactionsOptions::enDeposit:

			system("cls");

			DepositHeader();
			UpdateClienBalanceDepositInfo();

			cout << "\nPress Any Key To Go back To Transactions Menu...";
			system("pause>0");

			break;
		case enTransactionsOptions::enWithdraw:

			system("cls");

			WithdrawHeader();
			UpdateClienBalanceWithdrawInfo();

			cout << "\nPress Any Key To Go back To Transactions Menu...";
			system("pause>0");

			break;
		case enTransactionsOptions::enTotalBalances:

			system("cls");

			ShowBalancesList();

			cout << "\nPress Any Key To Go back To Transactions Menu...";
			system("pause>0");

			break;
		case enTransactionsOptions::enMainMenu:

			system("cls");

			ShowMainMenuScreen();
			ChooseOption();

			system("pause>0");

			break;
		}

		system("cls");

		ShowTransactionsMenuScreen();

	} while (Number != 4);
}



//OperationsonMangeUsersMenu

void ShowMangeUsersMenuScreen()
{
	cout << "=========================================\n";
	cout << "         Manage Users Menu Screen\n";
	cout << "=========================================\n";
	cout << "        [1] List Users.\n";
	cout << "        [2] Add New User.\n";
	cout << "        [3] Delete User.\n";
	cout << "        [4] Update User.\n";
	cout << "        [5] Find User.\n";
	cout << "        [6] Main Menu.\n";
	cout << "=========================================\n";
}

enum enManageUsersOptions
{
	ListUsers = 1, enAddNewUser = 2, enDeleteUser = 3, UpdateUser = 4, enFindUser = 5, MainMenu = 6
};

short ReadUserOptionsNumber(string Message)
{
	short Number = 4;

	do
	{
		if (Number < 1 || Number >6)
		{
			cout << "Invalid Try Again...\n";
		}

		cout << Message;
		cin >> Number;


	} while (Number < 1 || Number >6);
	return Number;
}

void ChooseUserOption()
{
	short Number = 0;

	do
	{
		Number = ReadUserOptionsNumber("Choose What Do You Want To do[1 to 6] ? ");

		enManageUsersOptions UsereOptions = enManageUsersOptions(Number);

		switch (UsereOptions)
		{
		case enManageUsersOptions::ListUsers:

			system("cls");

			ShowUsersList();

			cout << "\nPress Any Key To Go back To Manage Users Menu...";
			system("pause>0");

			break;
		case enManageUsersOptions::enAddNewUser:

			system("cls");
			AddNewUsersHeader();

			AddUser();

			cout << "\nPress Any Key To Go back To Manage Users Menu...";
			system("pause>0");

			break;
		case enManageUsersOptions::enDeleteUser:

			system("cls");
			DeleteUserHeader();

			DeleteUser();

			cout << "\nPress Any Key To Go back To Manage Users Menu...";
			system("pause>0");

			break;
		case enManageUsersOptions::UpdateUser:

			system("cls");
			UpdateUserHeader();

			UpdateUserInfo();

			cout << "\nPress Any Key To Go back To Manage Users Menu...";
			system("pause>0");

			break;
		case enManageUsersOptions::enFindUser:

			system("cls");
			FindUserHeader();

			FindUser();

			cout << "\nPress Any Key To Go back To Manage Users Menu...";
			system("pause>0");

			break;
		case enManageUsersOptions::MainMenu:

			system("cls");

			ShowMainMenuScreen();
			ChooseOption();

			system("pause>0");

			break;

		}

		system("cls");

		ShowMangeUsersMenuScreen();

	} while (Number != 6);
}



//OperationsonMainMenu
void LoginScreen();

void ShowAccessDeniedMessage()
{

	cout << "\n\n-----------------------------------------\n";
	cout << "Access denied...\nPlease contact the admin\n";
	cout << "-----------------------------------------\n";

}

void ShowMainMenuScreen()
{
	cout << "=========================================\n";
	cout << "            Main Menu Screen\n";
	cout << "=========================================\n";
	cout << "        [1] Show Client List.\n";
	cout << "        [2] Add New Client.\n";
	cout << "        [3] Delete Client.\n";
	cout << "        [4] Update Client Info.\n";
	cout << "        [5] Find Client.\n";
	cout << "        [6] Transactions.\n";
	cout << "        [7] Manage Users.\n";
	cout << "        [8] Logout.\n";
	cout << "=========================================\n";
}

enum enMainMenuOption
{
	ShowClientData = 1, enAddNewClients = 2, enDeleteClient = 3, UpdateClientInfo = 4, enFindClient = 5, Transactions = 6, Manageusers = 7, Logout = 8
};

short ReadOptionsNumber(string Message)
{
	short Number = 5;

	do
	{
		if (Number < 1 || Number >8)
		{
			cout << "Invalid Try Again...\n";
		}

		cout << Message;
		cin >> Number;


	} while (Number < 1 || Number >8);
	return Number;
}

void EntryDenied()
{
	ShowAccessDeniedMessage();

	cout << "\nPress Any Key To Go back To Main Menu...";
	system("pause>0");

	system("cls");
	ShowMainMenuScreen();
	ChooseOption();
}

void ChooseOption()
{
	short Number = 0;

	do
	{
		Number = ReadOptionsNumber("Choose What Do You Want To do[1 to 8] ? ");

		enMainMenuOption Option = enMainMenuOption(Number);

		switch (Option)
		{
		case enMainMenuOption::ShowClientData:

			system("cls");

			if (!CheckAccessPermissions(enMainMenuPermissions::PClintList))
				EntryDenied();

			ShowClientList();

			cout << "\nPress Any Key To Go back To Main Menu...";
			system("pause>0");

			break;
		case enMainMenuOption::enAddNewClients:

			system("cls");

			if (!CheckAccessPermissions(enMainMenuPermissions::PAddClient))
				EntryDenied();

			AddNewClientsHeader();

			AddClient();

			cout << "\nPress Any Key To Go back To Main Menu...";
			system("pause>0");

			break;
		case enMainMenuOption::enDeleteClient:

			system("cls");

			if (!CheckAccessPermissions(enMainMenuPermissions::PDeleteClient))
				EntryDenied();

			DeleteClientHeader();

			DeleteClient();

			cout << "\nPress Any Key To Go back To Main Menu...";
			system("pause>0");

			break;
		case enMainMenuOption::UpdateClientInfo:

			system("cls");

			if (!CheckAccessPermissions(enMainMenuPermissions::PUpdateClient))
				EntryDenied();

			UpdateClientInfoHeader();

			UpdateClienInfo();

			cout << "\nPress Any Key To Go back To Main Menu...";
			system("pause>0");

			break;
		case enMainMenuOption::enFindClient:

			system("cls");

			if (!CheckAccessPermissions(enMainMenuPermissions::PFindClient))
				EntryDenied();

			FindClientHeader();

			FindClient();

			cout << "\nPress Any Key To Go back To Main Menu...";
			system("pause>0");

			break;
		case enMainMenuOption::Transactions:

			system("cls");

			if (!CheckAccessPermissions(enMainMenuPermissions::PTransactions))
				EntryDenied();

			ShowTransactionsMenuScreen();

			ChooseTransaction();

			system("pause>0");

			break;
		case enMainMenuOption::Manageusers:

			system("cls");

			if (!CheckAccessPermissions(enMainMenuPermissions::PManageUsers))
				EntryDenied();

			ShowMangeUsersMenuScreen();

			ChooseUserOption();

			system("pause>0");

			break;
		case enMainMenuOption::Logout:

			system("cls");

			LoginScreen();

			system("pause>0");

			break;
		}
		system("cls");
		ShowMainMenuScreen();

	} while (Number != 8);
}


//OperationsonLoginScreen

void LoginScreenHeader()
{
	cout << "\n\n-----------------------------------------\n";
	cout << "          Loging Screen\n";
	cout << "-----------------------------------------\n";
}

bool findUserByUsernameAndPassword(string Username, string Password, stUser& User)
{
	vector <stUser> vUser = LoadUsersDataFromFile(UsersFileName);

	for (stUser& U : vUser)
	{
		if (U.AccountName == Username && U.Password == Password)
		{
			User = U;
			return true;
		}
	}
	return false;
}

bool LoadUsersFromFile(string Username, string Password)
{
	return  findUserByUsernameAndPassword(Username, Password, CurrentUser);
}

void LoginScreen()
{
	LoginScreenHeader();

	string Username = "", Password = "";

	bool LoginFaild = false;

	do
	{
		system("cls");

		LoginScreenHeader();

		if (LoginFaild)
			cout << "Invalid Username/Password!\n";


		Username = ReadString("Enter Username? ");
		Password = ReadString("Enter Password? ");

		LoginFaild = !LoadUsersFromFile(Username, Password);

	} while (LoginFaild);

	system("cls");

	ShowMainMenuScreen();

	ChooseOption();
}



void PrintResults()
{
	LoginScreen();
}

int main()
{
	PrintResults();

	return 0;
}
