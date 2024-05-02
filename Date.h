#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <ctime>

namespace project {

int rand(int low, int high)
{
	srand((unsigned) time(0));
	return std::rand() % (high - low + 1) + low;
}

// Bu algoritma Şubat ayını yılın sonuna kaydırır.
// (153 * m - 457)/5 kaydırılan ayın önceki günlerinin sayısını hesaplar.
// Başlangıç yılında 1 Mart'tan 31 Aralık'a kadar 306 gün vardır.
int rataDieDay(int d, int m, int y) { /* Rata Die day one is 0001-01-01 */
    if (m < 3)
        y--, m += 12;
    return 365*y + y/4 - y/100 + y/400 + (153*m - 457)/5 + d - 306;
}

class Date {
public:
	static constexpr int year_base = 1970;  //1
	static constexpr int random_min_year = 2000;  //2
	static constexpr int random_max_year = 2023;  //3

	static constexpr int year_days[2][12] =
	{
		{ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 },
		{ 0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335 },
	};
	
	static constexpr int month_days[2][12] =
	{
		{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
		{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	};

	enum class Weekday { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday }; //4

	Date() //5
	{
		set();
	};

	Date(int d, int m, int y) //6
	{
		set(d, m, y);
	}

	explicit Date(const char* p)  //7
	{
		const auto day   = stoi(std::string(p, 0, 2));
		const auto month = stoi(std::string(p, 3, 2));
		const auto year  = stoi(std::string(p, 6, 4));

		set(day, month, year);
	}
	
	explicit Date(std::time_t time) //8
	{
		int day = (time + 3 * 60 * 60) / (86400); // 3 * 60 * 60 (for GMT+3) 
		set() += day;
	}

	int getMonthDay() const //9
	{
		return m_day;
	}

	int getMonth() const //10
	{
		return m_month;
	}

	int getYear() const //11
	{
		return m_year;
	}

	int getYearDay() const //12
	{
		return year_days[isLeap( getYear() ) ? 1 : 0][getMonth() - 1] + getMonthDay();
	}

	int getDaysInMonth() const
	{
		return getDaysInMonth(getMonth(), getYear());
	}

	static int getDaysInMonth(int month, int year)
	{
		return month_days[isLeap( year ) ? 1 : 0][month - 1];
	}

	//Tomohiko Sakamoto
	Weekday getWeekDay() const //13
	{
		static constexpr int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
		
		const auto d = getMonthDay();
		const auto m = getMonth();
		auto y = getYear();
		
		if (m < 3)
			y -= 1;
		
		return static_cast<Weekday>((y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7);
	}

	// set functions -> without exception handling
	Date& setMonthDay(int day) //14
	{
		m_day = day;
		return *this;
	}

	Date& setMonth(int month) //15
	{
		m_month = month;
		return *this;
	}

	Date& setYear(int year) //16
	{
		m_year = year;
		return *this;
	}

	Date& set(int day = 1, int mon = 1, int year = year_base) //17
	{
		return setMonthDay(day), setMonth(mon), setYear(year);
	}

	Date operator-(int day) const //18
	{
		Date res = *this;

		while ( day >=  res.getMonthDay() )
		{
			res.setMonth( res.getMonth() - 1 );
			day -= res.getDaysInMonth();

			if( res.getMonth() == 0 )
			{
				res.setMonth(12);
				res.setYear( res.getYear() - 1 );
			}
		}

		res.setMonthDay( res.getMonthDay() - day );
		return res;
	}

	Date& operator+=(int day) //19
	{
		setMonthDay( getMonthDay() + day );
		
		while ( getMonthDay() > getDaysInMonth() )
		{
			setMonthDay( getMonthDay() - getDaysInMonth() );
			setMonth( getMonth() + 1 );
			
			if ( getMonth() > 12 )
			{
				setMonth(1);
				setYear( getYear() + 1 );
			}
		}

		return *this;
	}

	Date& operator-=(int day) //20
	{
		*this = operator-(day);
		return *this;
	}

	Date& operator++() //21
	{
		return operator+=(1);
	}

	Date operator++(int) //22
	{
		Date res{ *this };
		operator++();
		return res;
	}

	Date& operator--() //23
	{
		return operator-=(1);
	}

	Date operator--(int) //24
	{
		Date res{ *this };
		operator--();
		return res;
	}

	friend bool operator<(const Date& d1, const Date& d2) //27
	{
		if( d1.getYear() < d2.getYear() )
			return true;

		else if( d1.getYear() == d2.getYear() )
		{
			if( d1.getMonth() < d2.getMonth() )
				return true;

			else if( d1.getMonth() == d2.getMonth() )
			{
				if( d1.getMonthDay() < d2.getMonthDay() )
					return true;
			}
		}

		return false;
	}

	friend bool operator==(const Date& d1, const Date& d2) //27
	{
		return d1.getMonthDay() == d2.getMonthDay() && d1.getMonth() == d2.getMonth() && d1.getYear() == d2.getYear();
	}

	static Date randomDate() //25
	{
		const auto year  = rand(random_min_year, random_max_year);
		const auto month = rand(1, 12);
		const auto day   = month == 2 ? rand(1, 29) : rand(1, Date::getDaysInMonth(month, year));

		return Date{day, month, year};
	}

	static constexpr bool isLeap(int y) //26
	{
		return y % 4 == 0 && (y % 100 != 0 || y % 400 == 0);
	}

	friend std::ostream& operator<<(std::ostream& os, const Date &date) //31
	{
		static constexpr const char* months[] = {"Ocak", "Şubat", "Mart", "Nisan", "Mayıs", "Haziran", "Temmuz", "Ağustos", "Eylül", "Ekim", "Kasım", "Aralık"}; 
		return os << date.m_day << " " << months[date.m_month - 1] << " " << date.m_year;
	}

	friend std::istream& operator>>(std::istream& is, Date &date) //32
	{
		char ch;
		int day, month, year;

		if (is >> day >> ch >> month >> ch >> year)
		{
			date = Date{day, month, year};
		}
		
		return is;
	}

private:
    int m_day;
    int m_month;
    int m_year;

};

bool operator>(const Date& d1, const Date& d2) //27
{
	return !( d1 == d2  || d1 < d2 );
}

bool operator<=(const Date& d1, const Date& d2) //27
{
	return !( d1 > d2 );
}

bool operator>=(const Date& d1, const Date& d2) //27
{
	return !( d1 < d2 );
}

bool operator!=(const Date& d1, const Date& d2) //27
{
	return !( d1 == d2 );
}

int operator-(const Date& d1, const Date& d2) //28
{
	return rataDieDay(d1.getMonthDay(), d1.getMonth(), d1.getYear()) - rataDieDay(d2.getMonthDay(), d2.getMonth(), d2.getYear());
}

Date operator+(const Date& date, int n) //29
{
	Date td = date;
	return td+=n;
}

Date operator+(int n, const Date& date) //29
{
	return operator+(date, n);
}

Date::Weekday& operator++(Date::Weekday& r) //30
{
	using enum Date::Weekday;
	return r = r == Saturday ? Sunday : static_cast<Date::Weekday>(static_cast<int>(r) + 1);
}

Date::Weekday operator++(Date::Weekday& r, int) //30
{
	Date::Weekday res{ std::move(r) };
	operator++(r);
	return res;
}

Date::Weekday& operator--(Date::Weekday& r) //30
{
	using enum Date::Weekday;
	return r = r == Monday ? Sunday : static_cast<Date::Weekday>(static_cast<int>(r) - 1);
}

Date::Weekday operator--(Date::Weekday& r, int) //30
{
	Date::Weekday res{ std::move(r) };
	operator--(r);
	return res;
}

}

#endif