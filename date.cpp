//Mario Shontz

#include <string>
#include <iomanip>
#include <iostream>
#include "date.h"

//PUBLIC

//constructors
Date::Date(): month(1), day(1), year(2020) {}

Date::Date(int m, int d, int y): month(m), day(d), year(y)
{
	if(!validDate())  //calls private validDate() function which returns a boolean value
		month = 1; day=1; year =2020;
}

Date::Date(const char* strDate)
{
	//copying inputted c-string into a c++ string type
	std::string dateCpy = strDate;
	//assigns proper values from string to member data as integers
	parseString(dateCpy);	
	//testing values for validity, defaulting to 1/1/2020 if not
	if(!validDate())
		month=1; day=1; year = 2020;
}

//sets
void Date::Input()
{
	do
	{
		std::string date;
		
		std::cout<<"Input date in month/day/year format: "<<std::endl;
		std::cin>>date;
		
		parseString(date);
		if(!validDate())
			std::cout<<"Invalid date. Try again: "<<std::endl;
	}
	while(!validDate());
}
void Date::Increment()
{
	//if next day is in the same month
	if(validDate(month,day+1,year))
		day++;
	else
	{
		//if next month is in the same year
		if(validDate(month+1,1,year))
		{
			month++;
			day=1;
		}
		else
		{
			month=1;
			day=1;
			year++;
		}
	}
}
void Date::Decrement()
{
	if(validDate(month,day-1,year))
                day--;
        else
        {
                if(month>1)
                {
			day=numDaysInMonth(month-1,year);
			month--;
                }
                else
                {
			month = 12;
			day = 31;
			year--;	
                }
        }

}
bool Date::Set(int m, int d, int y)
{
	if (!validDate(m,d,y))
		return false;
	month = m;
	day = d;
	year = y;
	return true;
}

//gets
int Date::DayOfWeek() const
{
	//need copy of year b/c year is changed within const function
	int yearCpy = year;
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	yearCpy -= month < 3;
	return (yearCpy + yearCpy/4 - yearCpy/100 + yearCpy/400 + t[month-1] + day) % 7;
}
int Date::Compare(const Date &d) const
{
	if(year > d.year || year == d.year && month > d.month || year == d.year && month == d.month && day > d.day) 
		return -1;
	else if(year == d.year && month == d.month && day == d.day)
		return 0;
	else
		return 1;
}
int Date::GetMonth() const
{
	return month;
}
int Date::GetDay() const
{
	return day;
}
int Date::GetYear() const 
{
	return year;
}

void Date::ShowByDay() const
{
	switch(DayOfWeek())
	{
		case 0:
                        std::cout<<"Sunday ";
			break;
		case 1:
                        std::cout<<"Monday ";
			break;
		case 2:
                        std::cout<<"Tuesday ";
			break;
		case 3:
                        std::cout<<"Wednesday ";
			break;
		case 4:
                        std::cout<<"Thursday ";
			break;
		case 5:
                        std::cout<<"Friday ";
			break;
		case 6:
                        std::cout<<"Saturday ";
			break;
	}
	std::cout<<GetMonth()<<"/"<<GetDay()<<"/"<<GetYear()<<std::endl;
}
void Date::ShowByMonth() const
{
	static std::string months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", \
"September", "October", "November", "December"};
	std::cout<<months[month-1]<<"    "<<year<<std::endl;
	
	//dayCount counts how many days of week have been printed
	int dayCount=0, numDays = numDaysInMonth(month, year);
	
	std::cout<<"Su    Mo    Tu    We    Th    Fr    Sa"<<std::endl;	
	for(int i = 0; i<firstDayOfMonth(month,year); i++)
	{
		for(int j = 0; j<6; j++)
		{
			std::cout<<" ";
		}
		++dayCount;
	}
	for(int k = 1; k<=numDays; k++)
	{	
		if(k<10)
		{
			std::cout<<'0'<<k;
		}
		else
		{
			std::cout<<k;
		}
		if(dayCount<6 && k != numDays)
		{
			std::cout<<"    ";
			++dayCount;
		}
		else if (dayCount==6)
		{
			std::cout<<std::endl;
			dayCount=0; 
		}
		else
			std::cout<<std::endl;
	}
}

//PRIVATE
int Date::numDaysInMonth(int month, int year) const
{
	if(((month < 8) && (month%2==0)) || ((month >= 8) && (month%2 !=0))) //if not a month with 31 days
        {
                if (month == 2)
                {
                        if(leapYear(year))
                                return 29;
                        else
                                return 28;
                }
                else
                        return 30;
        }
	return 31;	
}
int Date::firstDayOfMonth(int m, int y) const
{
	int d=1;
	static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
	y -= m < 3;
	return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

void Date::parseString(std::string& date) //Takes string as input and assigns values to month,day, and year
{

        //sz is index of character that stoi stopped on last(where it found a non-integer value aka '/')
        std::string::size_type sz;

        month = std::stoi(date,&sz);
        //delete beginning of line up until next number (deletes numbers for month and the slash)
        date.erase(0,sz+1);
        day = std::stoi(date,&sz);

        //delete beginning of line up to next number (deletes numbers for day and slash)
        date.erase(0,sz+1);
        year =  std::stoi(date,&sz);
}

bool Date::validDate(int m, int d, int y)
{
	if(m<1 || m>12 || y<1900 || d<1 || d>31) //finds obviously invalid dates immediately
                return false;
        else if(((m < 8) && (m%2==0)) || ((m >= 8) && (m%2 !=0))) //if not a month with 31 days
        {
                if (m ==2)
                {
                        if(leapYear(y)) //calls boolean leapYear() function
                        {
                                if(d > 29)
                                        return false;
                        }
                        else
                        {
                                if (d>28)
                                        return false;
                        }
                }
                else
                {
                        if(d>30)
                                return false;
		}
        }
        //don't need an else for if month is 31 days because we test if days >31 already
        return true;
}
bool Date::leapYear(int &year)
{
	if( ((year % 100==0) && (year % 400 == 0)) || ((year % 100 !=0) && (year % 4 == 0)) )
                return true;
        return false;
}

bool Date::validDate() const
{
	if(month<1 || month>12 || year<1900 || day<1 || day>31) //finds obviously invalid dates immediately
                return false;
	else if(((month < 8) && (month%2==0)) || ((month >= 8) && (month%2 !=0))) //if not a month with 31 days
        {
		if (month ==2)
		{
			if(leapYear())
			{
				if(day > 29)
					return false;
			}
			else
			{
				if (day>28)
					return false;
			}
		}
		else
		{
			if(day>30)
				return false;
		}
	}
	//don't need an else for if month is 31 days because we test if days >31 already
	return true;
}
bool Date::leapYear() const
{
	if( ((year % 100==0) && (year % 400 == 0)) || ((year % 100 !=0) && (year % 4 == 0)) )
		return true;
	return false;
}
