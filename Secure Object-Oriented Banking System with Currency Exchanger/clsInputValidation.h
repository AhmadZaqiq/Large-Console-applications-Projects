#pragma once
#include <iostream>
#include "clsDate.h"

using namespace std;

class clsInputValidation
{
public:

	static bool IsNumberBetween(short LowestNumber, short HighestNumber, short Number)
	{
		return (LowestNumber < Number&& HighestNumber > Number);
	}
	static bool IsNumberBetween(int LowestNumber, int HighestNumber, int Number)
	{
		return (LowestNumber < Number&& HighestNumber > Number);
	}
	static bool IsNumberBetween(float LowestNumber, float HighestNumber, float Number)
	{
		return (LowestNumber < Number&& HighestNumber > Number);
	}
	static bool IsNumberBetween(double LowestNumber, double HighestNumber, double Number)
	{
		return (LowestNumber < Number&& HighestNumber > Number);
	}
	static bool IsDateBetween(clsDate Date, clsDate FirstDate, clsDate SecondDate)
	{
		return (clsDate::IsDate1AfterThanDate2(Date, FirstDate) && clsDate::IsDate1BeforeThanDate2(Date, SecondDate));
	}
	static int ReadIntNumber(string Message = "Please Enter Int Number: ",string ErrorMessage = "Try Again Babe,")
	{
		int Number;
		
		cout << Message;
		cin >> Number;


		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage << "\n";
			cin >> Number;
		}

		return Number;
	}
	static string ReadString(string Message = "Plese Enter A String: ")
	{
		string String;

		cout << Message;
		getline(cin >> ws, String);

		return String;
	}
	static double ReaddoubleNumber(string Message = "Plese Enter A Number: ",string ErrorMessage = "Try Again Babe,")
	{
		double Number;

		cout << Message;
		cin >> Number;

		while (cin.fail())
		{
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ErrorMessage << "\n";
			cin >> Number;
		}

		return Number;
	}
	static int ReadIntNumberBetween(int LowestNumber, int HighestNumber,string Message = "Please Enter Int Number: ",string ErrorMessage= "Try Again Babe,")
	{
		int Number = ReadIntNumber(Message, ErrorMessage);

		while (!IsNumberBetween(LowestNumber, HighestNumber, Number))
		{
			cout << ErrorMessage << "\n";
			Number = ReadIntNumber(Message, ErrorMessage);
		};

		return Number;
	}
	static double ReaddoubleNumberBetween(double LowestNumber, double HighestNumber, string ErrorMessage)
	{
		double Number = ReaddoubleNumber();
		cin >> Number;

		while (!IsNumberBetween(LowestNumber, HighestNumber, Number))
		{
			cout << ErrorMessage << "\n";
			Number = ReaddoubleNumber();
		};

		return Number;
	}
	static bool ISValidDate(clsDate Date)
	{
		if (Date.Day > clsDate::NumberOfDaysInMonth(Date.Year, Date.Month))
			return false;

		if (Date.Month > 12)
			return false;

		return true;
	}

};
