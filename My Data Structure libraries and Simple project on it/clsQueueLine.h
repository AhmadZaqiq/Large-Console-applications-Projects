#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include "clsDate.h"
#include <queue>

using namespace std;

class clsQueueLine
{
private:

	struct stTicket
	{
		string _Number = "";
		string _Date = "";
		string _WaitingClient = "";
		string _ServeTime = "";
	};


	string _Prefix = "";
	short _TotalTickets = 0;
	short _WaitingClient = 0;
	short _ServedClient = 0;
	short _ServeTime = 0;
	queue <stTicket> _QueueLine;
	queue <stTicket> _TempQueue;

public:


	clsQueueLine(string Prefix, short AvgServeTime)
	{
		_TotalTickets = 0;
		_Prefix = Prefix;
		_ServeTime = AvgServeTime;
	}

	void IssueTicket()
	{
		_TotalTickets++;

		stTicket Client;

		Client._Number = _Prefix + to_string(_TotalTickets);
		Client._Date = clsDate::GetCurrentTime();
		Client._WaitingClient = to_string(_WaitingClient);

		Client._ServeTime = to_string(_ServeTime * _WaitingClient);

		_QueueLine.push(Client);

		_WaitingClient++;
	}

	void PrintInfo()
	{
		cout << "\t\t\t\t\t" << "--------------------------" << "              \n\n";
		cout << "\t\t\t\t\t" << "        Queue Info        " << "              \n\n";
		cout << "\t\t\t\t\t" << "--------------------------" << "              \n\n";
		cout << "\t\t\t\t\t" << "      Prefix      = {" << _Prefix << "}       \n\n";
		cout << "\t\t\t\t\t" << "   Total Tickets  = {" << _TotalTickets << "} \n\n";
		cout << "\t\t\t\t\t" << "   Served Client  = {" << _ServedClient << "}\n\n";
		cout << "\t\t\t\t\t" << "   Waiting Client = {" << _WaitingClient << "} \n\n";
		cout << "\t\t\t\t\t" << "--------------------------" << "              \n\n";
	}

	void PrintTicketsLineRTL()
	{
		cout << "\t\t\t\t" << "Tickets: ";

		for (short i = 1; i <= _TotalTickets; i++)
		{
			cout << _Prefix + to_string(i) + " <-- ";
		}

		cout << "\n\n";
	}

	void PrintTicketsLineLTR()
	{
		cout << "\t\t\t\t" << "Tickets: ";

		for (short i = _TotalTickets; i >= 1; i--)
		{
			cout << _Prefix + to_string(i) + " --> ";
		}

		cout << "\n\n";
	}

	void PrintAllTickets()
	{
		_TempQueue = _QueueLine;

		cout << "\t\t\t\t\t" << "       ___Tickets___       " << "             \n\n";

		while (_TempQueue.size() != 0)
		{
			cout << "\t\t\t\t\t" << "---------------------------" << "\n\n";
			cout << "\t\t\t\t\t\t   " << _TempQueue.front()._Number << "\n\n";
			cout << "\t\t\t\t\t   " << _TempQueue.front()._Date << "\n";
			cout << "\t\t\t\t\t" << "   Waiting Client ={" << _TempQueue.front()._WaitingClient << "}\n";
			cout << "\t\t\t\t\t" << "      Serve Time In " << "\n";
			cout << "\t\t\t\t\t     {" << _TempQueue.front()._ServeTime<<"} Minute(s)\n";
			cout << "\t\t\t\t\t" << "---------------------------" << "\n\n";

			_TempQueue.pop();
		}

	}

	void ServeNextClient()
	{
		_QueueLine.pop();
		_WaitingClient--;
		_ServedClient++;
	}


};

