#pragma once
#include<iostream>
#include<string>
#include <vector>

using namespace std;

class clsString
{
private:

	string _StringValue;

	static char InvertCharacter(char C1)
	{
		return (isupper(C1) ? tolower(C1) : toupper(C1));
	}
	static bool IsVowel(char C1)
	{
		C1 = tolower(C1);

		return (C1 == 'a' || C1 == 'e' || C1 == 'o' || C1 == 'i' || C1 == 'u');
	}

public:

	clsString()
	{

	}

	clsString(string Value)
	{
		_StringValue = Value;
	}

	void SetStringValue(string StringValue)
	{
		_StringValue = StringValue;
	}

	string GetStringValue()
	{
		return _StringValue;
	}


	static void PrintFirstLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;

		for (short i = 0;i < S1.length();i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
			{
				cout << S1[i] << endl;
			}
			IsFirstLetter = (S1[i] == ' ' ? true : false);
		}
	}
	static string UpperFirstLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;

		for (short i = 0;i < S1.length();i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
			{
				S1[i] = toupper(S1[i]);
			}
			IsFirstLetter = (S1[i] == ' ' ? true : false);
		}
		return S1;
	}
	static string LowerFirstLetterOfEachWord(string S1)
	{
		bool IsFirstLetter = true;

		for (short i = 0;i < S1.length();i++)
		{
			if (S1[i] != ' ' && IsFirstLetter)
			{
				S1[i] = tolower(S1[i]);
			}
			IsFirstLetter = (S1[i] == ' ' ? true : false);
		}
		return S1;
	}
	static string UpperAll(string S1)
	{
		for (short i = 0;i < S1.length();i++)
			S1[i] = toupper(S1[i]);

		return S1;
	}
	static string LowerAll(string S1)
	{
		for (short i = 0;i < S1.length();i++)
			S1[i] = tolower(S1[i]);

		return S1;
	}
	static string Invert(string S1)
	{
		for (short i = 0; i < S1.length();i++)
		{
			S1[i] = InvertCharacter(S1[i]);
		}
		return S1;
	}
	static short CapitalLettersCount(string S1)
	{
		short CapitalCount = 0;

		for (short i = 0;i < S1.length();i++)
		{
			if (isupper(S1[i]))
				CapitalCount++;
		}
		return CapitalCount;
	}
	static short SmallLettersCount(string S1)
	{
		short SmallCount = 0;

		for (short i = 0;i < S1.length();i++)
		{
			if (islower(S1[i]))
				SmallCount++;
		}
		return SmallCount;
	}
	static short CountVowel(string S1)
	{
		short Counter = 0;

		for (short i = 0;i < S1.length();i++)
		{
			if (IsVowel(S1[i]))
				Counter++;
		}
		return Counter;
	}
	static void PrintVowels(string S1)
	{
		for (short i = 0;i < S1.length();i++)
		{
			if (IsVowel(S1[i]))
				cout << S1[i] << "  ";
		}
	}
	static void PrintEachWord(string S1)
	{
		string delim = " ";
		short pos = 0;
		string Sword;

		while ((pos = S1.find(delim)) != std::string::npos)
		{
			Sword = S1.substr(0, pos);
			if (Sword != "")
			{
				cout << Sword << endl;
			}
			S1.erase(0, pos + delim.length());
		}

		if (S1 != "")
		{
			cout << S1 << endl;
		}
	}
	static short NumberOfWords(string S1)
	{
		string delim = " ";
		string Sword;
		short pos = 0, Counter = 0;

		while ((pos = S1.find(delim)) != std::string::npos)
		{
			Sword = S1.substr(0, pos);

			if (Sword != "")
			{
				Counter++;
			}
			S1.erase(0, pos + delim.length());
		}

		if (S1 != "")
		{
			Counter++;
		}
		return Counter;
	}
	static vector <string> Split(string S1, string delim)
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
	static string TrimLeft(string S1)
	{
		for (short i = 0;i < S1.length();i++)
		{
			if (S1[i] != ' ')
				return S1.substr(i, S1.length() - i);
		}
		return "";
	}
	static string TrimRight(string S1)
	{
		for (short i = S1.length();i > 0;i--)
		{
			if (S1[i] != ' ')
				return S1.substr(0, i + 1);
		}
		return "";
	}
	static string Trim(string S1)
	{
		return	TrimLeft(TrimRight(S1));
	}
	static string JoinString(vector <string> vString, string Delim)
	{
		string S1 = "";

		for (string& Word : vString)
		{
			S1 = S1 + Word + Delim;
		}
		return S1.substr(0, S1.length() - Delim.length());
	}
	static string ReverseWord(string S1)
	{
		vector <string> vString = Split(S1, " ");
		string S2 = "";
		vector <string>::iterator iter = vString.end();

		while (iter != vString.begin())
		{
			--iter;

			S2 += *iter + " ";
		}
		return S2.substr(0, S2.length() - 1);
	}
	static string ReplaceWord(string S1, string Replacementword, string  WordToBeReplaced)
	{
		short pos = S1.find(Replacementword);

		while (pos != string::npos)
		{
			S1 = S1.replace(pos, Replacementword.length(), WordToBeReplaced);
			pos = S1.find(Replacementword);
		}
		return S1;
	}
	static string RemovePauncuations(string S1)
	{
		string S2 = "";

		for (short i = 0;i < S1.length();i++)
		{
			if (!ispunct(S1[i]))
				S2 += S1[i];
		}
		return S2;
	}


	void PrintFirstLetterOfEachWord()
	{
		PrintFirstLetterOfEachWord(_StringValue);
	}
	void UpperFirstLetterOfEachWord()
	{
		_StringValue = UpperFirstLetterOfEachWord(_StringValue);
	}
	void LowerFirstLetterOfEachWord()
	{
		_StringValue = LowerFirstLetterOfEachWord(_StringValue);
	}
	void UpperAll()
	{
		_StringValue = UpperAll(_StringValue);
	}
	void LowerAll()
	{
		_StringValue = LowerAll(_StringValue);
	}
	void Invert()
	{
		_StringValue = Invert(_StringValue);
	}
	short CapitalLettersCount()
	{
		return CapitalLettersCount(_StringValue);
	}
	short SmallLettersCount()
	{
		return SmallLettersCount(_StringValue);
	}
	short CountVowel()
	{
		return CountVowel(_StringValue);
	}
	void PrintVowels()
	{
		PrintVowels(_StringValue);
	}
	void PrintEachWord()
	{
		return PrintEachWord(_StringValue);
	}
	short NumberOfWords()
	{
		return NumberOfWords(_StringValue);
	}
	void TrimLeft()
	{
		_StringValue = TrimLeft(_StringValue);
	}
	void TrimRight()
	{
		_StringValue = TrimRight(_StringValue);
	}
	void Trim()
	{
		_StringValue = Trim(_StringValue);
	}
	void ReverseWord()
	{
		_StringValue = ReverseWord(_StringValue);
	}
	void RemovePauncuations()
	{
		_StringValue = RemovePauncuations(_StringValue);
	}

	__declspec(property(get = GetStringValue, put = SetStringValue)) string Value;
};
