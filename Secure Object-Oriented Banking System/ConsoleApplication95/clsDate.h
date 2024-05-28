#pragma once
#include<iostream>
#include <ctime>
#include <vector>
#include <string>

using namespace std;

class clsDate
{
private:

	short _Day;
	short _Month;
	short _Year;




public:

	clsDate()
	{
		time_t t = time(0);
		tm now;
		if (localtime_s(&now, &t) == 0)
		{
			_Day = now.tm_mday;
			_Month = now.tm_mon + 1;
			_Year = now.tm_year + 1900;
		}
	}
	clsDate(string S1)
	{
		vector <string> vString;

		short pos = 0;
		string Sword;
		string delim = "/";

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

		_Day = stoi(vString.at(0));
		_Month = stoi(vString.at(1));
		_Year = stoi(vString.at(2));

	}
	clsDate(short Day, short Month, short Year)
	{
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(short TotalDays, short Year)
	{

		short RemainingDays = TotalDays;
		short MonthsDays = 0;

		_Year = Year;
		_Month = 1;

		while (true)
		{
			MonthsDays = NumberOfDaysInMonth(Year, _Month);

			if (RemainingDays > MonthsDays)
			{
				RemainingDays -= MonthsDays;
				_Month++;
			}

			else
			{
				_Day = RemainingDays;
				break;
			}

		}
	}

	void SetDay(short Day)
	{
		_Day = Day;
	}
	void SetMonth(short Month)
	{
		_Month = Month;
	}
	void SetYear(short Year)
	{
		_Year = Year;
	}

	short GetDay()
	{
		return _Day;
	}
	short GetMonth()
	{
		return _Month;
	}
	short GetYear()
	{
		return _Year;
	}

	__declspec(property(get = GetDay, put = SetDay)) short Day;
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;
	__declspec(property(get = GetYear, put = SetYear)) short Year;

	void Print()
	{
		cout << _Day << "/" << _Month << "/" << _Year;
	}
	static bool IsLeapYear(short Year)
	{
		return((Year % 400 == 0) || (Year % 4 == 0 && Year % 100 != 0));
	}
	static short NumberOfDaysInMonth(short Year, short Month)
	{
		if (Month < 1 || Month >12)
			return 0;

		short ArrOfMonthDays[12] = { 31,28 + IsLeapYear(Year) ,31,30,31,30,31,31,30,31,30,31 };

		return ArrOfMonthDays[Month - 1];
	}
	static short NumberOfDaysInAYear(short Year)
	{
		return IsLeapYear(Year) ? 366 : 365;
	}
	static short NumberOfHoursInAYear(short Year)
	{
		return NumberOfDaysInAYear(Year) * 24;
	}
	static int NumberOfMinutesInAYear(short Year)
	{
		return NumberOfHoursInAYear(Year) * 60;
	}
	static int NumberOfSecondsInAYear(short Year)
	{
		return NumberOfMinutesInAYear(Year) * 60;
	}
	static short NumberOfHoursInMonth(short Year, short Month)
	{
		return NumberOfDaysInMonth(Year, Month) * 24;
	}
	static int NumberOfMinutesInMonth(short Year, short Month)
	{
		return	NumberOfHoursInMonth(Year, Month) * 60;
	}
	static int NumberOfSecondssInMonth(short Year, short Month)
	{
		return NumberOfMinutesInMonth(Year, Month) * 60;
	}
	static short DayOfWeekOrder(short Year, short Month, short Day)
	{
		short a = floor((14 - Month) / 12);
		short y = Year - a;
		short m = Month + (12 * a) - 2;
		return  (Day + y + (short)floor(y / 4) - (short)floor(y / 100) +
			(short)floor(y / 400) + (short)floor((31 * m) / 12)) % 7;
	}
	static string DayOfWeekShortName(short Year, short Month, short Day)
	{
		short DayOrder = DayOfWeekOrder(Year, Month, Day);
		string ArrDayName[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };

		return ArrDayName[DayOrder];
	}
	static string MonthShortName(short Month)
	{
		string ArrMonthName[12] =
		{
			"Jan", "Feb", "Mar", "Apr",
			"May", "Jun", "Jul", "Aug",
			"Sep", "Oct", "Nov", "Dec"
		};

		return ArrMonthName[Month - 1];
	}
	static void PrintMonthsCalendar(short Year, short Month)
	{
		string MonthName = MonthShortName(Month);

		cout << "  _______________" << MonthName << "_______________\n\n";
		cout << "  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n\n";

		short NumberOfDays = NumberOfDaysInMonth(Year, Month);
		short Current = DayOfWeekOrder(Year, Month, 1);

		short i;

		for (i = 0; i < Current; i++)
			cout << "     ";

		for (short j = 1; j <= NumberOfDays; j++)
		{
			printf("%5d", j);

			if (++i == 7)
			{
				i = 0;
				cout << "\n";
			}
		}
		cout << "\n\n  _________________________________\n\n";
	}
	static void PrintYearCalendar(short Year)
	{
		cout << "\n\n  _________________________________\n\n";

		cout << "           Calendar - " << Year;

		cout << "\n  _________________________________\n\n";

		for (short i = 1; i <= 12; i++)
			PrintMonthsCalendar(Year, i);
	}
	static short NumberOfDaysFromTheBeginingOfTheYear(clsDate Date)
	{
		short TotalDays = 0;

		for (short i = 0; i <= Date.Month - 1; i++)
		{
			TotalDays += NumberOfDaysInMonth(Date.Year, i);
		}
		TotalDays += Date.Day;

		return TotalDays;
	}
	static clsDate GetDateFromDayOrderInYear(clsDate Date)
	{



		short RemainingDays = NumberOfDaysFromTheBeginingOfTheYear(Date);
		short MonthsDays = 0;


		Date.Month = 1;

		while (true)
		{
			MonthsDays = NumberOfDaysInMonth(Date.Year, Date.Month);

			if (RemainingDays > MonthsDays)
			{
				RemainingDays -= MonthsDays;
				Date.Month++;
			}

			else
			{
				Date.Day = RemainingDays;
				break;
			}

		}

		return Date;
	}
	static clsDate AddDaysToDate(short DaysToAdd, clsDate Date)
	{

		short RemainingDays = DaysToAdd + NumberOfDaysFromTheBeginingOfTheYear(Date);
		short MonthDays = 0;

		Date.Month = 1;


		while (true)
		{
			MonthDays = NumberOfDaysInMonth(Date.Year, Date.Month);

			if (RemainingDays > MonthDays)
			{
				RemainingDays -= MonthDays;

				Date.Month++;

				if (Date.Month > 12)
				{
					Date.Month = 1;
					Date.Year++;
				}
			}
			else
			{
				Date.Day = RemainingDays;
				break;
			}
		}

		return Date;
	}
	static bool IsDate1BeforeThanDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
	}
	static bool IsDateBeforeThanDate2(clsDate Date1, clsDate Date2)
	{
		return (Date1.Year < Date2.Year) ? true : ((Date1.Year == Date2.Year) ? (Date1.Month < Date2.Month ? true : (Date1.Month == Date2.Month ? Date1.Day < Date2.Day : false)) : false);
	}
	static bool IsDate1EqualToDate2(clsDate Date1, clsDate Date2)
	{
		return(Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day == Date2.Day);
	}
	static bool IsDateEqualToDate2(clsDate Date1, clsDate Date2)
	{
		return(Date1.Year == Date2.Year && Date1.Month == Date2.Month && Date1.Day == Date2.Day);
	}
	static bool IsDate1AfterThanDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeThanDate2(Date1, Date2) && !IsDate1EqualToDate2(Date1, Date2));
	}
	static bool IsDateAfterThanDate2(clsDate Date1, clsDate Date2)
	{
		return (!IsDate1BeforeThanDate2(Date1, Date2) && !IsDate1EqualToDate2(Date1, Date2));
	}
	static bool IsLastDayInMonth(clsDate Date)
	{
		return(Date.Day == NumberOfDaysInMonth(Date.Year, Date.Month));
	}
	static bool IsLastMonthInYear(short Month)
	{
		return(Month == 12);
	}
	static bool ISValidDate(clsDate Date)
	{
		if (Date.Day > NumberOfDaysInMonth(Date.Year, Date.Month))
			return false;

		if (Date.Month > 12)
			return false;

		return true;
	}
	static clsDate IncreaseDateByOneDay(clsDate Date)
	{
		if (IsLastDayInMonth(Date))
		{
			if (IsLastMonthInYear(Date.Month))
			{
				Date.Month = 1;
				Date.Day = 1;
				Date.Year++;
			}
			else
			{
				Date.Month++;
				Date.Day = 1;
			}
		}

		else
		{
			Date.Day++;
		}

		return Date;
	}
	static int GetDifferenceInDays(clsDate Date1, clsDate Date2, bool IncludeEndDay = false)
	{
		int Days = 0;

		while (IsDate1BeforeThanDate2(Date1, Date2))
		{
			Days++;
			Date1 = IncreaseDateByOneDay(Date1);
		}

		return IncludeEndDay ? ++Days : Days;
	}
	static int CalculateYourAgeInDays(clsDate Date1)
	{
		return	GetDifferenceInDays(Date1, clsDate());
	}
	static void SwapDates(clsDate& Date1, clsDate& Date2)
	{
		clsDate Temp;

		Temp.Year = Date1.Year;
		Temp.Month = Date1.Month;
		Temp.Day = Date1.Day;

		Date1.Year = Date2.Year;
		Date1.Month = Date2.Month;
		Date1.Day = Date2.Day;

		Date2.Year = Temp.Year;
		Date2.Month = Temp.Month;
		Date2.Day = Temp.Day;
	}
	static clsDate IncreaseDateByXDays(clsDate& Date, short NumberOfDays)
	{
		for (short i = 0; i < NumberOfDays; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;
	}
	static clsDate IncreaseDateByOneWeek(clsDate& Date)
	{
		for (short i = 0; i < 7; i++)
		{
			Date = IncreaseDateByOneDay(Date);
		}

		return Date;
	}
	static clsDate IncreaseDateByXWeeks(clsDate& Date, short NumberOfWeeks)
	{
		for (short i = 0; i < NumberOfWeeks; i++)
		{
			Date = IncreaseDateByOneWeek(Date);
		}

		return Date;
	}
	static clsDate IncreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month == 12)
		{
			Date.Month = 1;
			Date.Year++;
		}

		else
		{
			Date.Month++;
		}

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year, Date.Month);

		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}
	static clsDate IncreaseDateByXMonths(clsDate& Date, short NumberOfWeeks)
	{
		for (short i = 0; i < NumberOfWeeks; i++)
		{
			Date = IncreaseDateByOneMonth(Date);
		}

		return Date;
	}
	static clsDate IncreaseDateByOneYear(clsDate& Date)
	{
		Date.Year++;

		return Date;
	}
	static clsDate IncreaseDateByXYears(clsDate& Date, short NumberOfYears)
	{
		for (short i = 0; i < NumberOfYears; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}
	static clsDate IncreaseDateByXYears_Faster(clsDate& Date, short NumberOfYears)
	{
		Date.Year += NumberOfYears;

		return Date;
	}
	static clsDate IncreaseDateByOneDecade(clsDate& Date)
	{
		for (short i = 0; i < 10; i++)
		{
			Date = IncreaseDateByOneYear(Date);
		}

		return Date;
	}
	static clsDate IncreaseDateByXDecades(clsDate& Date, short NumberOdDecades)
	{
		for (short i = 0; i < NumberOdDecades; i++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}

		return Date;
	}
	static clsDate IncreaseDateByXDecades_Faster(clsDate& Date, short NumberOdDecades)
	{
		Date.Year = Date.Year + (NumberOdDecades * 10);

		return Date;
	}
	static clsDate IncreaseDateByOneCentury(clsDate& Date)
	{
		for (short i = 0; i < 10; i++)
		{
			Date = IncreaseDateByOneDecade(Date);
		}

		return Date;
	}
	static clsDate IncreaseDateByOneMillennium(clsDate& Date)
	{
		for (short i = 0; i < 10; i++)
		{
			Date = IncreaseDateByOneCentury(Date);
		}

		return Date;
	}
	static bool IsFirstDayInMonth(clsDate Date)
	{
		return(Date.Day == 1);
	}
	static bool IsFirstMonthInYear(short Month)
	{
		return(Month == 1);
	}
	static clsDate DecreaseDateByOneDay(clsDate& Date)
	{
		if (IsFirstDayInMonth(Date))
		{
			if (IsFirstMonthInYear(Date.Month))
			{
				Date.Month = 12;
				Date.Day = NumberOfDaysInMonth(Date.Year, Date.Month);
				Date.Year--;
			}
			else
			{
				Date.Month--;
				Date.Day = NumberOfDaysInMonth(Date.Year, Date.Month);
			}
		}

		else
		{
			Date.Day--;
		}

		return Date;
	}
	static clsDate DecreaseDateByXDays(clsDate& Date, short NumberOfDays)
	{
		for (short i = 0; i < NumberOfDays; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}
	static clsDate DecreaseDateByOneWeek(clsDate& Date)
	{
		for (short i = 0; i < 7; i++)
		{
			Date = DecreaseDateByOneDay(Date);
		}

		return Date;
	}
	static clsDate DecreaseDateByXWeeks(clsDate& Date, short NumberOfWeeks)
	{
		for (short i = 0; i < NumberOfWeeks; i++)
		{
			Date = DecreaseDateByOneWeek(Date);
		}

		return Date;
	}
	static clsDate DecreaseDateByOneMonth(clsDate& Date)
	{
		if (Date.Month == 1)
		{
			Date.Month = 12;
			Date.Year--;
		}

		else
		{
			Date.Month--;
		}

		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date.Year, Date.Month);

		if (Date.Day > NumberOfDaysInCurrentMonth)
		{
			Date.Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}
	static clsDate DecreaseDateByXMonths(clsDate& Date, short NumberOfWeeks)
	{
		for (short i = 0; i < NumberOfWeeks; i++)
		{
			Date = DecreaseDateByOneMonth(Date);
		}

		return Date;
	}
	static clsDate DecreaseDateByOneYear(clsDate& Date)
	{
		Date.Year--;

		return Date;
	}
	static clsDate DecreaseDateByXYears(clsDate& Date, short NumberOfYears)
	{
		for (short i = 0; i < NumberOfYears; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}
	static clsDate DecreaseDateByXYears_Faster(clsDate& Date, short NumberOfYears)
	{
		Date.Year -= NumberOfYears;

		return Date;
	}
	static clsDate DecreaseDateByOneDecade(clsDate& Date)
	{
		for (short i = 0; i < 10; i++)
		{
			Date = DecreaseDateByOneYear(Date);
		}

		return Date;
	}
	static clsDate DecreaseDateByXDecades(clsDate& Date, short NumberOdDecades)
	{
		for (short i = 0; i < NumberOdDecades; i++)
		{
			Date = DecreaseDateByOneDecade(Date);
		}

		return Date;
	}
	static clsDate DecreaseDateByXDecades_Faster(clsDate& Date, short NumberOdDecades)
	{
		Date.Year = Date.Year - (NumberOdDecades * 10);

		return Date;
	}
	static clsDate DecreaseDateByOneCentury(clsDate& Date)
	{
		for (short i = 0; i < 10; i++)
		{
			Date = DecreaseDateByOneDecade(Date);
		}

		return Date;
	}
	static clsDate DecreaseDateByOneMillennium(clsDate& Date)
	{
		for (short i = 0; i < 10; i++)
		{
			Date = DecreaseDateByOneCentury(Date);
		}

		return Date;
	}
	static string DateToString(clsDate Date)
	{
		return	to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}
	static string GetCurrentTime()
	{
		time_t t = time(0);
		tm now;
		if (localtime_s(&now, &t) == 0)
		{
			return DateToString(clsDate()) + " - " + to_string(now.tm_hour) + ":" + to_string(now.tm_min) + ":" + to_string(now.tm_sec);
		}
	}



	bool IsLeapYear()
	{
		return IsLeapYear(_Year);
	}
	short NumberOfDaysInMonth()
	{
		return NumberOfDaysInMonth(_Year, _Month);
	}
	short NumberOfDaysInAYear()
	{
		return NumberOfDaysInAYear(_Year);
	}
	short NumberOfHoursInAYear()
	{
		return NumberOfHoursInAYear(_Year);
	}
	int NumberOfMinutesInAYear()
	{
		return NumberOfMinutesInAYear(_Year);
	}
	int NumberOfSecondsInAYear()
	{
		return NumberOfSecondsInAYear(_Year);
	}
	short NumberOfHoursInMonth()
	{
		return NumberOfHoursInMonth(_Year, _Month);
	}
	int NumberOfMinutesInMonth()
	{
		return NumberOfMinutesInMonth(_Year, _Month);
	}
	int NumberOfSecondssInMonth()
	{
		return NumberOfSecondssInMonth(_Year, _Month);
	}
	short DayOfWeekOrder()
	{
		return DayOfWeekOrder(_Year, _Month, _Day);
	}
	string DayOfWeekShortName()
	{
		return DayOfWeekShortName(_Year, _Month, _Day);
	}
	void PrintMonthsCalendar()
	{
		PrintMonthsCalendar(_Year, _Month);
	}
	void PrintYearCalendar()
	{
		PrintYearCalendar(_Year);
	}
	short NumberOfDaysFromTheBeginingOfTheYear()
	{
		return NumberOfDaysFromTheBeginingOfTheYear(*this);
	}
	void GetDateFromDayOrderInYear()
	{
		*this = GetDateFromDayOrderInYear(*this);
	}
	void AddDaysToDate(short DaysToAdd)
	{
		*this = AddDaysToDate(DaysToAdd, *this);
	}
	bool IsDateBeforeThanDate2(clsDate Date2)
	{
		return IsDateBeforeThanDate2(*this, Date2);
	}
	bool IsDateEqualToDate2(clsDate Date2)
	{
		return IsDateEqualToDate2(*this, Date2);
	}
	bool IsDateAfterThanDate2(clsDate Date2)
	{
		return IsDateAfterThanDate2(*this, Date2);

	}
	bool IsLastDayInMonth()
	{
		return IsLastDayInMonth(*this);
	}
	bool IsLastMonthInYear()
	{
		return IsLastMonthInYear(_Month);
	}
	void IncreaseDateByOneDay()
	{
		*this = IncreaseDateByOneDay(*this);
	}
	int GetDifferenceInDays(clsDate Date1)
	{
		return GetDifferenceInDays(Date1, *this);
	}
	int CalculateYourAgeInDays()
	{
		return CalculateYourAgeInDays(*this);
	}
	void SwapDates(clsDate Date1)
	{
		SwapDates(Date1, *this);
	}
	bool ISValidDate()
	{
		return ISValidDate(*this);
	}
	void IncreaseDateByXDays(short NumberOfDays)
	{
		*this = IncreaseDateByXDays(*this, NumberOfDays);
	}
	void IncreaseDateByOneWeek()
	{
		*this = IncreaseDateByOneWeek(*this);
	}
	void IncreaseDateByXWeeks(short NumberOfWeeks)
	{
		*this = IncreaseDateByXWeeks(*this, NumberOfWeeks);
	}
	void IncreaseDateByOneMonth()
	{
		*this = IncreaseDateByOneMonth(*this);
	}
	void IncreaseDateByXMonths(short NumberOfWeeks)
	{
		*this = IncreaseDateByXMonths(*this, NumberOfWeeks);
	}
	void IncreaseDateByOneYear()
	{
		*this = IncreaseDateByOneYear(*this);
	}
	void IncreaseDateByXYears(short NumberOfYears)
	{
		*this = IncreaseDateByXYears(*this, NumberOfYears);
	}
	void IncreaseDateByXYears_Faster(short NumberOfYears)
	{
		*this = IncreaseDateByXYears_Faster(*this, NumberOfYears);
	}
	void IncreaseDateByOneDecade()
	{
		*this = IncreaseDateByOneDecade(*this);
	}
	void IncreaseDateByXDecades(short NumberOdDecades)
	{
		*this = IncreaseDateByXDecades(*this, NumberOdDecades);
	}
	void IncreaseDateByXDecades_Faster(short NumberOdDecades)
	{
		*this = IncreaseDateByXDecades_Faster(*this, NumberOdDecades);
	}
	void IncreaseDateByOneCentury()
	{
		*this = IncreaseDateByOneCentury(*this);
	}
	void IncreaseDateByOneMillennium()
	{
		*this = IncreaseDateByOneMillennium(*this);
	}
	bool IsFirstDayInMonth()
	{
		return  IsFirstDayInMonth(*this);
	}
	bool IsFirstMonthInYear()
	{
		return IsFirstDayInMonth(*this);
	}
	void DecreaseDateByOneDay()
	{
		*this = DecreaseDateByOneDay(*this);
	}
	void DecreaseDateByXDays(short NumberOfDays)
	{
		*this = DecreaseDateByXDays(*this, NumberOfDays);
	}
	void DecreaseDateByOneWeek()
	{
		*this = DecreaseDateByOneWeek(*this);
	}
	void DecreaseDateByXWeeks(short NumberOfWeeks)
	{
		*this = DecreaseDateByXWeeks(*this, NumberOfWeeks);
	}
	void DecreaseDateByOneMonth()
	{
		*this = DecreaseDateByOneMonth(*this);
	}
	void DecreaseDateByXMonths(short NumberOfWeeks)
	{
		*this = DecreaseDateByXMonths(*this, NumberOfWeeks);
	}
	void DecreaseDateByOneYear()
	{
		*this = DecreaseDateByOneYear(*this);
	}
	void DecreaseDateByXYears(short NumberOfYears)
	{
		*this = DecreaseDateByXYears(*this, NumberOfYears);
	}
	void DecreaseDateByXYears_Faster(short NumberOfYears)
	{
		*this = DecreaseDateByXYears_Faster(*this, NumberOfYears);
	}
	void DecreaseDateByOneDecade()
	{
		*this = DecreaseDateByOneDecade(*this);
	}
	void DecreaseDateByXDecades(short NumberOdDecades)
	{
		*this = DecreaseDateByXDecades(*this, NumberOdDecades);
	}
	void DecreaseDateByXDecades_Faster(short NumberOdDecades)
	{
		*this = DecreaseDateByXDecades_Faster(*this, NumberOdDecades);
	}
	void DecreaseDateByOneCentury()
	{
		*this = DecreaseDateByOneCentury(*this);
	}
	void DecreaseDateByOneMillennium()
	{
		*this = DecreaseDateByOneMillennium(*this);
	}


};
