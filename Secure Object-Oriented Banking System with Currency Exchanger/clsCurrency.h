#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

#include "clsString.h"

class clsCurrency
{
private:

	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;

	string _Country, _CurrencyCode, _CurrncyName;
	float _Rate;

	static clsCurrency _ConvertLineToCurrencyObject(string Line, string Separator = "#//#")
	{
		vector <string> vCurrencyData = clsString::Split(Line, Separator);

		return clsCurrency(enMode::UpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
			stof(vCurrencyData[3]));
	}

	static  string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Separator = "#//#")
	{
		string StringCurrencyData = "";

		StringCurrencyData = StringCurrencyData + Currency.Country() + Separator;
		StringCurrencyData = StringCurrencyData + Currency.CurrencyCode() + Separator;
		StringCurrencyData = StringCurrencyData + Currency.CurrencyName() + Separator;
		StringCurrencyData = StringCurrencyData + to_string(Currency.Rate());

		return StringCurrencyData;
	}

	static vector <clsCurrency> _LoadCurrencyDataFromFile()
	{
		fstream MyFile;

		vector <clsCurrency> vCurrency;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				vCurrency.push_back(_ConvertLineToCurrencyObject(Line));
			}
		}
		return vCurrency;
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrency)
	{
		fstream MyClientsFile;

		MyClientsFile.open("Currencies.txt", ios::out);

		string DataLine;

		if (MyClientsFile.is_open())
		{
			for (clsCurrency& C : vCurrency)
			{
				DataLine = _ConvertCurrencyObjectToLine(C);
				MyClientsFile << DataLine << endl;
			}
			MyClientsFile.close();
		}
	}

	void _Update()
	{
		vector <clsCurrency> _vCurrency;
		_vCurrency = _LoadCurrencyDataFromFile();

		for (clsCurrency& C : _vCurrency)
		{
			if (C.CurrencyCode() == CurrencyCode())
			{
				C = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(_vCurrency);
	}

public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrncyName = CurrencyName;
		_Rate = Rate;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}
	float  Rate()
	{
		return _Rate;
	}
	string Country()
	{
		return _Country;
	}
	string CurrencyCode()
	{
		return _CurrencyCode;
	}
	string CurrencyName()
	{
		return _CurrncyName;
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		string Code = clsString::UpperAll(CurrencyCode);

		fstream MyFile;

		vector <clsCurrency> vCurrency;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (Currency.CurrencyCode() == Code)
				{
					MyFile.close();

					return Currency;
				}

				vCurrency.push_back(Currency);
			}
			MyFile.close();
		}
	}

	static clsCurrency FindByCountry(string CountryName)
	{
		string Country = clsString::UpperAll(CountryName);

		fstream MyFile;

		vector <clsCurrency> vCurrency;

		MyFile.open("Currencies.txt", ios::in);

		if (MyFile.is_open())
		{
			string Line;

			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

				if (clsString::UpperAll(Currency.Country()) == Country)
				{
					MyFile.close();

					return Currency;
				}

				vCurrency.push_back(Currency);
			}
			MyFile.close();
		}
	}

	static bool IsCurrencyExists(string CurrencyCode)
	{
		clsCurrency C1 = FindByCode(CurrencyCode);
		return (!C1.IsEmpty());
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencyDataFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / Rate());
	}

	float ConvertToOtherCurrency(float Amount,clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSD(Amount);

		if (Currency2.CurrencyCode() == "USD")
			return AmountInUSD;

		return (float)(AmountInUSD * Currency2.Rate());
	}

};

