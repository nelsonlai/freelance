#include <iostream>
#include <string>
#include <stdexcept>

// Date class demonstrating constructor overloading and validation
class Date {
private:
    int year;
    int month;
    int day;
    
    // Helper function to check if a year is a leap year
    bool is_leap_year(int year) const {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }
    
    // Helper function to get days in a month
    int days_in_month(int month, int year) const {
        const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (month == 2 && is_leap_year(year)) {
            return 29;
        }
        return days[month - 1];
    }
    
    // Helper function to validate date
    bool is_valid_date(int year, int month, int day) const {
        if (year < 1 || month < 1 || month > 12 || day < 1) {
            return false;
        }
        return day <= days_in_month(month, year);
    }
    
public:
    // Default constructor - creates current date (simplified)
    Date() : year(2024), month(1), day(1) {
        std::cout << "Default date created: ";
        display();
    }
    
    // Constructor with year only
    Date(int year) : year(year), month(1), day(1) {
        if (year < 1) {
            throw std::invalid_argument("Year must be positive");
        }
        std::cout << "Date with year " << year << " created: ";
        display();
    }
    
    // Constructor with year and month
    Date(int year, int month) : year(year), month(month), day(1) {
        if (!is_valid_date(year, month, 1)) {
            throw std::invalid_argument("Invalid year or month");
        }
        std::cout << "Date with year " << year << " and month " << month << " created: ";
        display();
    }
    
    // Constructor with year, month, and day
    Date(int year, int month, int day) : year(year), month(month), day(day) {
        if (!is_valid_date(year, month, day)) {
            throw std::invalid_argument("Invalid date");
        }
        std::cout << "Date with full date " << year << "-" << month << "-" << day << " created: ";
        display();
    }
    
    // Copy constructor
    Date(const Date& other) : year(other.year), month(other.month), day(other.day) {
        std::cout << "Date copied: ";
        display();
    }
    
    // Destructor
    ~Date() {
        std::cout << "Date " << to_string() << " destroyed" << std::endl;
    }
    
    // Getters
    int get_year() const { return year; }
    int get_month() const { return month; }
    int get_day() const { return day; }
    
    // Setters with validation
    void set_year(int new_year) {
        if (new_year < 1) {
            throw std::invalid_argument("Year must be positive");
        }
        if (!is_valid_date(new_year, month, day)) {
            throw std::invalid_argument("Invalid date with new year");
        }
        year = new_year;
    }
    
    void set_month(int new_month) {
        if (!is_valid_date(year, new_month, day)) {
            throw std::invalid_argument("Invalid month");
        }
        month = new_month;
    }
    
    void set_day(int new_day) {
        if (!is_valid_date(year, month, new_day)) {
            throw std::invalid_argument("Invalid day");
        }
        day = new_day;
    }
    
    // Member functions
    void display() const {
        std::cout << year << "-" << month << "-" << day << std::endl;
    }
    
    std::string to_string() const {
        return std::to_string(year) + "-" + std::to_string(month) + "-" + std::to_string(day);
    }
    
    // Check if date is a leap year
    bool is_leap_year() const {
        return is_leap_year(year);
    }
    
    // Get days in current month
    int days_in_current_month() const {
        return days_in_month(month, year);
    }
    
    // Add days to date (simplified implementation)
    void add_days(int days) {
        day += days;
        while (day > days_in_current_month()) {
            day -= days_in_current_month();
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
    }
    
    // Static member function
    static Date today() {
        // Simplified - returns a fixed date for demonstration
        return Date(2024, 1, 15);
    }
    
    // Operator overloading
    bool operator==(const Date& other) const {
        return year == other.year && month == other.month && day == other.day;
    }
    
    bool operator!=(const Date& other) const {
        return !(*this == other);
    }
    
    bool operator<(const Date& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
    
    // Friend function for stream output
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};

// Friend function implementation
std::ostream& operator<<(std::ostream& os, const Date& date) {
    os << date.to_string();
    return os;
}

int main() {
    std::cout << "Date Class Demonstration" << std::endl;
    std::cout << "========================" << std::endl;
    
    // 1. Default constructor
    std::cout << "\n1. DEFAULT CONSTRUCTOR:" << std::endl;
    Date date1;
    
    // 2. Constructor with year only
    std::cout << "\n2. CONSTRUCTOR WITH YEAR:" << std::endl;
    Date date2(2023);
    
    // 3. Constructor with year and month
    std::cout << "\n3. CONSTRUCTOR WITH YEAR AND MONTH:" << std::endl;
    Date date3(2023, 6);
    
    // 4. Constructor with full date
    std::cout << "\n4. CONSTRUCTOR WITH FULL DATE:" << std::endl;
    Date date4(2023, 6, 15);
    
    // 5. Copy constructor
    std::cout << "\n5. COPY CONSTRUCTOR:" << std::endl;
    Date date5 = date4;
    
    // 6. Static member function
    std::cout << "\n6. STATIC MEMBER FUNCTION:" << std::endl;
    Date today = Date::today();
    std::cout << "Today is: " << today << std::endl;
    
    // 7. Member functions
    std::cout << "\n7. MEMBER FUNCTIONS:" << std::endl;
    std::cout << "Date 4: " << date4 << std::endl;
    std::cout << "Is leap year: " << std::boolalpha << date4.is_leap_year() << std::endl;
    std::cout << "Days in current month: " << date4.days_in_current_month() << std::endl;
    
    // 8. Operator overloading
    std::cout << "\n8. OPERATOR OVERLOADING:" << std::endl;
    std::cout << "date4 == date5: " << std::boolalpha << (date4 == date5) << std::endl;
    std::cout << "date4 < date2: " << std::boolalpha << (date4 < date2) << std::endl;
    
    // 9. Modifying dates
    std::cout << "\n9. MODIFYING DATES:" << std::endl;
    Date date6(2024, 2, 28);
    std::cout << "Original date: " << date6 << std::endl;
    date6.add_days(1);
    std::cout << "After adding 1 day: " << date6 << std::endl;
    
    // 10. Error handling
    std::cout << "\n10. ERROR HANDLING:" << std::endl;
    try {
        Date invalid_date(2023, 2, 30);  // Invalid date
    } catch (const std::invalid_argument& e) {
        std::cout << "Error caught: " << e.what() << std::endl;
    }
    
    try {
        Date date7(2023, 6, 15);
        date7.set_month(13);  // Invalid month
    } catch (const std::invalid_argument& e) {
        std::cout << "Error caught: " << e.what() << std::endl;
    }
    
    std::cout << "\nProgram ending - destructors will be called..." << std::endl;
    return 0;
}
