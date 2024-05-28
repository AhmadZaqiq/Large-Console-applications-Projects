#pragma once
#include <iostream>
#include <string>

using namespace std;

class clsUtil
{
public:

	enum enRandom { SmallLetter = 0, CapitalLetter = 1, SpecialCharacter = 2, Digit = 3 };

	static void Srand()
	{
		srand((unsigned)time(NULL));
	}

	static int RandomNumber(int From, int To)
	{
		int randNum = rand() % (To - From + 1) + From;
		return randNum;
	}
	static void PrintReverseDigits(int Number)
	{
		int Reminder = 0;

		cout << "Number In Reverse {";
		while (Number > 0)
		{
			Reminder = Number % 10;
			Number /= 10;

			cout << Reminder;
		}
		cout << "}\n";
	}
	static int CalculateDigitsSum(int Number)
	{
		int Reminder = 0, Sum = 0;
		while (Number > 0)
		{
			Reminder = Number % 10;
			Number /= 10;

			Sum += Reminder;
		}

		return Sum;
	}
	static int RrverseNumber(int Number)
	{
		int Reminder = 0, NumInRev = 0;
		while (Number > 0)
		{
			Reminder = Number % 10;
			Number /= 10;

			NumInRev = NumInRev * 10 + Reminder;
		}

		return NumInRev;
	}
	static bool CheckIfNumberIsPalindrome(int Number)
	{
		return (Number == RrverseNumber(Number));
	}
	static string EncryptText(string Name, const short Key)
	{

		for (int i = 0; i < Name.length(); i++)
		{
			Name[i] = char(int(Name[i]) + Key);
		}
		return Name;
	}
	static string DecryptText(string Encrypt, const short Key)
	{

		for (int i = 0; i < Encrypt.length(); i++)
		{
			Encrypt[i] = char(int(Encrypt[i]) - Key);
		}
		return Encrypt;
	}
	static char RandomInfo(enRandom Random)
	{
		switch (Random)
		{
		case enRandom::SpecialCharacter:
			return char(RandomNumber(33, 47));
			break;

		case enRandom::Digit:
			return char(RandomNumber(48, 57));
			break;

		case enRandom::CapitalLetter:
			return char(RandomNumber(65, 90));
			break;

		case enRandom::SmallLetter:
			return char(RandomNumber(97, 122));
			break;

		}

	};
	static string GenerateWord(enRandom Random, short Length)
	{
		string Word = "";

		for (int i = 0; i < Length; i++)
		{
			Word = Word + RandomInfo(Random);
		}
		return Word;
	}
	static string GenerateKey()
	{
		string Key = "";

		Key = GenerateWord(enRandom::CapitalLetter, 4) + "-";
		Key = Key + GenerateWord(enRandom::CapitalLetter, 4) + "-";
		Key = Key + GenerateWord(enRandom::CapitalLetter, 4) + "-";
		Key = Key + GenerateWord(enRandom::CapitalLetter, 4);

		return Key;
	}
	static void GenerateKeys(short Keys)
	{
		for (int i = 1; i <= Keys; i++)
		{
			cout << "Key [" << i << "] : " << GenerateKey() << endl;
		}
	}
	static void Swap(int& Num1, int& Num2)
	{
		int Temp;

		Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}
	static void Swap(double& Num1, double& Num2)
	{
		double Temp;

		Temp = Num1;
		Num1 = Num2;
		Num2 = Temp;
	}
	static void Swap(string& String1, string& String2)
	{
		string Temp;

		Temp = String1;
		String1 = String2;
		String2 = Temp;
	}
	static void FillArrayNumbers(int Arr[100], int ArrLength)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			Arr[i] = i + 1;
		}
	}
	static void ArrayShuffule(int Arr[100], int ArrLength)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			Swap(Arr[RandomNumber(1, ArrLength) - 1], Arr[RandomNumber(1, ArrLength) - 1]);
		}
	}
	static void PrintArray(int Arr[100], int ArrLength)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			cout << Arr[i] << " ";
		}
	}
	static void FillArrayWithRandomNumbers(int Arr[100], short ArrLength, short From, short To)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			Arr[i] = RandomNumber(From, To);
		}
	}
	static void FillArrayWithRandomWords(string Arr[100], short ArrLength, enRandom Random, short WordLength)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			Arr[i] = GenerateWord(Random, WordLength);
		}
	}
	static void PrintArray(string Arr[100], int ArrLength)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			cout << Arr[i] << " ";
		}
	}
	static void FillArrayWithRandomKeys(string Arr[100], short ArrLength)
	{
		for (int i = 0; i < ArrLength; i++)
		{
			Arr[i] = GenerateKey();
		}
	}
	static string Tabs(short NumberOfTabs)
	{
		string t = "";

		for (int i = 1; i < NumberOfTabs; i++)
		{
			t = t + "\t";
			cout << t;
		}
		return t;
	}
	static string NumberToText(int Number)
	{
		if (Number >= 1 && Number <= 19)
		{
			string Arr[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
							 "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
							 "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
			return Arr[Number];
		}

		if (Number >= 20 && Number <= 99)
		{
			string Arr[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty",
							 "Sixty", "Seventy", "Eighty", "Ninety" };

			return Arr[Number / 10] + (Number % 10 != 0 ? " " + NumberToText(Number % 10) : "");
		}

		if (Number >= 100 && Number <= 999)
		{
			return NumberToText(Number / 100) + " Hundred" + (Number % 100 != 0 ? " " + NumberToText(Number % 100) : "");
		}

		if (Number >= 1000 && Number <= 999999)
		{
			return NumberToText(Number / 1000) + " Thousand" + (Number % 1000 != 0 ? " " + NumberToText(Number % 1000) : "");
		}

		if (Number >= 1000000 && Number <= 999999999)
		{
			return NumberToText(Number / 1000000) + " Million" + (Number % 1000000 != 0 ? " " + NumberToText(Number % 1000000) : "");
		}

		if (Number >= 1000000000 && Number <= 999999999999)
		{
			return NumberToText(Number / 1000000000) + " Billion" + (Number % 1000000000 != 0 ? " " + NumberToText(Number % 1000000000) : "");
		}

		return "Number out of range";
	}


};
