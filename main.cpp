#include "Date.h"

int main(int argc, char const *argv[])
{
    using namespace project;

    std::cout << std::boolalpha;

    Date d1{}; //5
    std::cout << "d1 == 1 Ocak 1970 \t\t\t"   << (d1 == Date{1, 1, 1970})   << "\n";

    Date d2{25, 04, 2024}; //6
    std::cout << "d2 == 25 Nisan 2024 \t\t\t" << (d2 == Date{25, 04, 2024}) << "\n";

    Date d3{"15/03/2022"}; //7
    std::cout << "d3 == 15 Mart 2022 \t\t\t"  << (d3 == Date{15, 03, 2022}) << "\n";

    Date d4{std::time({})}; //8
    std::cout << "d4 == Date{std::time({})} \t\t" << (d4 == Date{std::time({})}) << "\n";

    std::cout << "d2.getMonthDay() == 25 \t\t\t"  << (d2.getMonthDay() == 25)    << "\n"; //9
    std::cout << "d2.getYear() == 2024 \t\t\t"    << (d2.getYear() == 2024)      << "\n"; //10
    std::cout << "d2.getYearDay() == 116 \t\t\t"  << (d2.getYearDay() == 116)    << "\n"; //11
    std::cout << "d2.getDaysInMonth() == 30 \t\t" << (d2.getDaysInMonth() == 30) << "\n"; //12
    std::cout << "d2.getWeekDay() == 4 \t\t\t"    << (static_cast<int>(d2.getWeekDay()) == 4) << "\n"; //13

    std::cout << "d2.setMonthDay(12) == 12 Nisan 2024 \t"  << (d2.setMonthDay(12)  == Date{12, 04, 2024}) << "\n"; //14
    std::cout << "d2.setMonth(10) == 12 Ekim 2024 \t"      << (d2.setMonth(10)     == Date{12, 10, 2024}) << "\n"; //15
    std::cout << "d2.setYear(2015) == 12 Ekim 2015 \t"     << (d2.setYear(2015)    == Date{12, 10, 2015}) << "\n"; //16
    std::cout << "d2.set(18, 5, 2017) == 18 Mayıs 2017 \t" << (d2.set(18, 5, 2017) == Date{18, 5, 2017})  << "\n"; //17

    std::cout << "d2-12 == 6 Mayıs 2017 \t\t\t"  << (d2 - 12 == Date{6, 5, 2017})  << "\n"; //18
    std::cout << "d2+=5 == 23 Mayıs 2017 \t\t\t" << ((d2+=5) == Date{23, 5, 2017}) << "\n"; //19
    std::cout << "d2-=3 == 20 Mayıs 2017 \t\t\t" << ((d2-=3) == Date{20, 5, 2017}) << "\n"; //20

    std::cout << "d2++(prefix first)  == 21 Mayıs 2017 \t"  << ((++d2) == Date{21, 5, 2017}) << "\n"; //21
    std::cout << "d2++(prefix last)   == 21 Mayıs 2017 \t"  << ((d2)   == Date{21, 5, 2017}) << "\n"; //21
    std::cout << "d2++(postfix first) == 21 Mayıs 2017 \t"  << ((d2++) == Date{21, 5, 2017}) << "\n"; //22
    std::cout << "d2++(postfix last)  == 22 Mayıs 2017 \t"  << ((d2)   == Date{22, 5, 2017}) << "\n"; //22
    
    std::cout << "d2--(prefix first)  == 21 Mayıs 2017 \t" << ((--d2) == Date{21, 5, 2017}) << "\n"; //23
    std::cout << "d2--(prefix last)   == 21 Mayıs 2017 \t" << ((d2)   == Date{21, 5, 2017}) << "\n"; //23
    std::cout << "d2--(postfix first) == 21 Mayıs 2017 \t" << ((d2--) == Date{21, 5, 2017}) << "\n"; //24
    std::cout << "d2--(postfix last)  == 20 Mayıs 2017 \t" << ((d2)   == Date{20, 5, 2017}) << "\n"; //24
   
    std::cout << "Date::isLeap(d2.getYear()) == false \t" << (Date::isLeap(d2.getYear()) == false) << "\n"; //26

    std::cout << "operator>(d2, d3)  == false \t\t" << (operator>(d2, d3)  == false) << "\n"; //27
    std::cout << "operator<=(d2, d3) == true \t\t"  << (operator<=(d2, d3) == true)  << "\n"; //27
    std::cout << "operator>=(d2, d3) == false \t\t" << (operator>=(d2, d3) == false) << "\n"; //27
    std::cout << "operator!=(d2, d3) == true \t\t"  << (operator!=(d2, d3) == true)  << "\n"; //27
    std::cout << "operator-(d3, d2)  == 1760 \t\t"  << (operator-(d3, d2) == 1760)   << "\n"; //28
    std::cout << "operator+(d2, 5)   == 25 Mayıs 2017 \t"  << (operator+(d2, 5) == Date{25, 5, 2017}) << "\n"; //29
    std::cout << "operator+(5, d2)   == 25 Mayıs 2017 \t"  << (operator+(5, d2) == Date{25, 5, 2017}) << "\n"; //29

    auto d2_wd = d2.getWeekDay();
    std::cout << "operator++(prefix first)  == Saturday \t"  << (++d2_wd == Date::Weekday::Sunday) << "\n"; //30
    std::cout << "operator++(prefix last)   == Sunday \t"    << (d2_wd   == Date::Weekday::Sunday) << "\n"; //30
    std::cout << "operator++(postfix first) == Saturday \t"  << (d2_wd++ == Date::Weekday::Sunday) << "\n"; //30
    std::cout << "operator++(postfix last)  == Sunday \t"    << (d2_wd   == Date::Weekday::Monday) << "\n"; //30
    
    std::cout << "operator<<(d2) == 20 Mayıs 2017 \t"; (operator<<(std::cout, d2)) << "\n"; //31
    
    std::cout << "Date::randomDate()  =  " << Date::randomDate() << "\n"; //25

    Date dd{};
    std::cout << "Bir tarih giriniz(gg/aa/yyyy): ";
    std::cin  >> dd; //32
    std::cout << "Girdiğiniz Tarih: " << dd << "\n";
}