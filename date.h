//Mario Shontz

#ifndef DATE_H
#define DATE_H

class Date
{
	public:
                //constructors
                Date();
                Date(int month, int date, int year);
                Date(const char *strDate);	//Allows user input of date in mm/dd/yyyy format

                //sets
                void Input();		//Changes date based on input in mm/dd/yyyy format
                void Increment();	//by 1 day
                void Decrement();	//by 1 day

                bool Set(int m, int d, int y);
                
		//gets
		int DayOfWeek() const;	//returns value 0-6 for Sunday - Saturday
                int Compare(const Date &d) const; //returns -1 if calling object comes after, 0 if equal, 1 if parameter object comes after
                int GetMonth() const;	//returns value 1-12
                int GetDay() const;
                int GetYear() const;

		void ShowByDay() const;	//prints day and date in mm/dd/yyyy format
                void ShowByMonth() const;	//Prints month in calendar format
                
        private:                
		int month,day,year;

		int numDaysInMonth(int month, int year) const;
                int firstDayOfMonth(int m, int y) const;	//Returns day of week, 0-6 for Sun-Sat
                
		void parseString(std::string &date); //takes values from date in mm/dd/yyyy format and changes respective values

                static bool validDate(int m, int d, int y);	//Checks date for validity
                static bool leapYear(int &year);	//Checks if year is leap year
                
		bool validDate() const;	//Checks if object's date is valid
                bool leapYear() const;	//Checks if current year of object is a leap year{

}; 

#endif
