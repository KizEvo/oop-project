#include <ctime>
#include <iomanip>
#include <fstream>
#include "manager.h"
#include "person.h"
#include "apartment.h"


bool checkValidRoom(uint16_t idRoom);
bool checkValidDay(Date date);
int16_t Sub2Date(Date Date1, Date Date2);
bool Compare2Date(Date Date1, Date Date2);


std::string Manager::Password = "12345678";

bool Compare2Date(Date Date1, Date Date2) { 
    if (Date2.year > Date1.year) return true;
    else if (Date2.year == Date1.year && Date2.month > Date1.month) return true;
    else if (Date2.year == Date1.year && Date2.month == Date1.month && Date2.day > Date1.day) return true;
    else return false;
}


int16_t Sub2Date(Date Date1, Date Date2) {
    Date SmallerDate, BiggerDate;
    int8_t symbolSign; 
    bool compareValue = Compare2Date(Date1,Date2);
    if (compareValue) {
        SmallerDate = Date1;
        BiggerDate = Date2;
        symbolSign = 1;
    } else {
        SmallerDate = Date2;
        BiggerDate = Date1;
        symbolSign = -1;
    }
    int day_count_smaller_year = 0;
    int day_count_bigger_year = 0; 
    int dayofmonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; 
    for (int i = 1; i <= SmallerDate.month; i++) {
        if (i == SmallerDate.month) day_count_smaller_year += SmallerDate.day;
        else if((i == 2) && ((SmallerDate.year % 400 == 0) || ((SmallerDate.year % 4 == 0)&&(SmallerDate.year%100!=0))))
            day_count_smaller_year += 29;
        else day_count_smaller_year += dayofmonth[i-1];
    }

    for (int i = SmallerDate.year; i <= BiggerDate.year; i ++) {
        if (i < BiggerDate.year) {
            if ((i % 400 == 0) || ((i % 4 == 0) && (i % 100 != 0))) day_count_bigger_year += 366;
            else day_count_bigger_year += 365;
        } else {
            for (int j = 1; j <= BiggerDate.month; j++) {
                if (j == BiggerDate.month) day_count_bigger_year += BiggerDate.day;
                else if((j == 2) && ((i % 400 == 0) || ((i % 4 == 0) && (i % 100 != 0))))
                    day_count_bigger_year += 29;
                else day_count_bigger_year += dayofmonth[j-1];
            }
        }
    }
    return (day_count_bigger_year - day_count_smaller_year) * symbolSign;
}

//function will check and return true if idRoom is valid
bool checkValidRoom(uint16_t idRoom) {
    if ( idRoom < 100 || idRoom > 999) return false;       //idRoom is a 3-digit number
    if ( idRoom % 100 > 10 || idRoom % 100 == 0) return false;                   //on each floor only have 10 rooms 
    return true;
}

//function to validate date and return true if date is valid
bool checkValidDay(Date date) {
    uint8_t  d = date.day;
    uint8_t  m = date.month;
    uint16_t y = date.year;

    //check year
    if (y < 1900 || y > 2100) return false;

    //check month 
    if (m < 1 || m > 12) return false;

    //check date
    //months have 31 days
    if ( (d > 31 || d < 1) && ( (m == 1) || (m == 3) || (m==5) || (m==7) || (m==8) || (m==10) || (m==12) ))
        return false;
    //months have 30 days
    if ( (d > 30 || d < 1) && ( (m == 4) || (m == 6) || (m==9) || (m==11)) )
        return false;
    //February && no leap year
    if ( (d > 28 || d < 1) && ((y%400!=0) && ((y%4 != 0)||(y%100==0))) && (m == 2)) return false;
    //February && leep year
    if ( (d > 29 || d < 1) && ((y%400==0) || ((y%4 == 0)&&(y%100!=0))) && (m == 2)) return false;
    return true;
}



Tenant Manager::writeTenantWhenApartmentIsEmpty(uint16_t &IdRoom) {
    Apartment temp;
    temp.id = IdRoom;
    std::string nameTemp, cccdTemp;
    std::cout << "Enter Name: ";
    std::getline(std::cin,nameTemp);
    Date tempbirthday;
    int day, month, year;
    do{ std::cout << "\nEnter Date Of Birth \n";
        std::cout << "Enter Day: ";     std::cin >> day   ; std::cin.ignore();
        std::cout << "Enter Month: ";   std::cin >> month ; std::cin.ignore();
        std::cout << "Enter Year: ";    std::cin >> year  ; std::cin.ignore();
        tempbirthday.day = day;
        tempbirthday.month = month;
        tempbirthday.year = year;
        if(!checkValidDay(tempbirthday)) std::cout << "\nDate is not valid. Try again!\n";
    } while(!checkValidDay(tempbirthday));
    std::cout << "Enter CCCD: ";
    std::getline(std::cin,cccdTemp);
    time_t now_time = time(0);
    struct tm *today = localtime(&now_time);
    uint8_t ageTemp = today->tm_year + 1900 - tempbirthday.year;

    temp.ownerName = nameTemp;
    temp.isRented = true;
    temp.maxPerson = 4;
    int dayRent, monthRent, yearRent;
    do{ std::cout << "\nEnter Date To Rent \n";
        std::cout << "Enter Day: ";     std::cin >> dayRent   ; std::cin.ignore();
        std::cout << "Enter Month: ";   std::cin >> monthRent ; std::cin.ignore();
        std::cout << "Enter Year: ";    std::cin >> yearRent  ; std::cin.ignore();
        temp.startRent.day = dayRent;
        temp.startRent.month = monthRent;
        temp.startRent.year = yearRent; 
        if(!checkValidDay(temp.startRent)) std::cout << "\nDate is not valid. Try again!\n";
    } while(!checkValidDay(temp.startRent));
    int monthDeposit = 0;
    std::cout << "Enter the number of months deposited: ";
    std::cin >> monthDeposit; std::cin.ignore();

    temp.endRent.day   = temp.startRent.day ;
    temp.endRent.month = (temp.startRent.month + monthDeposit )  % 12;
    temp.endRent.year  = temp.startRent.year + (temp.startRent.month + monthDeposit )  / 12;  

    std::string payment_mt;
    do{ std::cout << "\nEnter Payment Method (CASH, DEBIT_CARD, CREDIT_CARD): ";
        std::cin >> payment_mt; std::cin.ignore();
        if  (payment_mt == "0" || payment_mt == "CASH" || payment_mt == "Cash") {
            temp.paymentMethod = CASH;
            break;
        } else if  (payment_mt == "1" || payment_mt == "DEBIT_CARD" || payment_mt == "Debit_Card") {
            temp.paymentMethod = DEBIT_CARD;
            break;
        } else if  (payment_mt == "2" || payment_mt == "CREDIT_CARD" || payment_mt == "Credit_Card") {
            temp.paymentMethod = CREDIT_CARD;
            break;
        }
        printf("\n Invalid Input\n");
    } while(1);

    Date CurrentDate;
    CurrentDate.day = today->tm_mday;
    CurrentDate.month = today->tm_mon + 1;
    CurrentDate.year = today->tm_year + 1900;
    temp.maxDayPastDue = Sub2Date(CurrentDate,temp.endRent);
    Tenant var(temp, nameTemp, cccdTemp, tempbirthday, ageTemp);
    std::cout << "Input Information\n";
    std::cout << "Name: " << nameTemp << std::endl ;
    std::cout << "Date Of Birth: " << (int)tempbirthday.day << " / " << (int)tempbirthday.month << " / " << (int)tempbirthday.year;
    std::cout << "\nCCCD: " << cccdTemp;
    std::cout << "\nAge: " << (int)ageTemp;
    std::cout << "\nID Room: " << temp.id;
    std::cout << "\nMax Person " << (int)temp.maxPerson;
    std::cout << "\nOwner Name " << temp.ownerName;
    std::cout << "\nStart Rent " << (int)temp.startRent.day << " / " << (int)temp.startRent.month << " / "  << (int)temp.startRent.year;
    std::cout << "\nEnd Rent " << (int)temp.endRent.day << " / " << (int)temp.endRent.month << " / "  << (int)temp.endRent.year;
    std::cout << "\nIs rented " << temp.isRented;
    std::cout << "\nMax Day Past Due " << temp.maxDayPastDue;
    std::cout << "\nPayment Method " << temp.paymentMethod << std::endl;
    return var;
}


void Manager::displayApartmentInfo(Apartment var) {
    std::cout << "\n\t------------        Apartment ID: " << var.id << "        ------------\n\n"
    		  << "- Max Person: " << (int)var.maxPerson << std::setw(18) <<"- Owner Name: " << var.ownerName << "\n"
    		  << "- Start Rent: " << (var.startRent.day<10 ? "0" : "") << (int)var.startRent.day << "/" << (var.startRent.month<10 ? "0" : "") << (int)var.startRent.month << "/"  << (int)var.startRent.year << std::setw(36)
 			  << "- End Rent: " << (var.endRent.day<10 ? "0" : "") << (int)var.endRent.day << "/" << (var.endRent.month<10 ? "0" : "") << (int)var.endRent.month << "/"  << (int)var.endRent.year << "\n"
    		  << "- Is rented: " << var.isRented << std::setw(25) << "- Max Day Past Due: " << var.maxDayPastDue << std::setw(25) << "- Payment Method: " << var.paymentMethod << std::endl;
    std::cout << "\n\t----------   Apartment "<< var.id <<"'s List of Tenants   ----------\n\n"
    		  << std::setw(20) << "Name" << std::setw(10) << "Age" << std::setw(18) << "Birthday" << std::setw(20) << "CCCD" << "\n";

}

Tenant Manager::extendApartmentEndRent(Tenant& var, uint16_t extendedRentMonth) {
    int dayofmonth[12] = {31,28,31,30,31,30,31,31,30,31,30,31}; 
    Apartment Apart = var.getApartmentInfo();
    Apart.endRent.year  =  Apart.endRent.year + ( ((Apart.endRent.month + extendedRentMonth) > 12) ? (Apart.endRent.month + extendedRentMonth) / 12 : 0);
    Apart.endRent.month = ((Apart.endRent.month + extendedRentMonth) > 12) ? (((Apart.endRent.month + extendedRentMonth) % 12) + (((Apart.endRent.month + extendedRentMonth) % 12 == 0) ? 12 : 0) )  : (Apart.endRent.month + extendedRentMonth) ; 
    Apart.endRent.day =  Apart.endRent.day > dayofmonth[Apart.endRent.month-1] ? dayofmonth[Apart.endRent.month-1] : Apart.endRent.day;
    time_t now_time = time(0);
    struct tm *today = localtime(&now_time);
    Date CurrentDate;
    CurrentDate.day = today->tm_mday;
    CurrentDate.month = today->tm_mon + 1;
    CurrentDate.year = today->tm_year + 1900;
    Apart.maxDayPastDue = Sub2Date(CurrentDate,Apart.endRent);
    Tenant var_new(Apart,var.getTenantName(), var.getTenantCCCD(), var.getTenantDateOfBirth(), var.getTenantAge());
    return var_new;
}
void Manager::requestPassword() {
	std::string Password_Input;
	do {
		std::cout << "Enter Password: ";
		std::cin >> Password_Input; std::cin.ignore();
		if (!Password_Input.compare(Password)) {
			std::cout << "\nWelcome Manager\n";
		}
		else {
			std::cout << "\nPassword is wrong. Please try again! \n";
		}
	} while(Password_Input.compare(Password));
}

void Manager::displayTenantInfo(Tenant var) {
    Date DoB = var.getTenantDateOfBirth();
    std::cout << std::setw(20) << var.getTenantName()
    		  << std::setw(10) << (int)var.getTenantAge()
    		  << std::setw(10) << (DoB.day<10 ? "0" : "") << (int)DoB.day << "/" << (DoB.month<10 ? "0" : "") << (int)DoB.month << "/" << (DoB.year==0 ? "000" : "") << (int)DoB.year
    		  << std::setw(20) << var.getTenantCCCD() << "\n";
    
}
Tenant Manager::writeTenantWhenApartmentIsOccupied(Apartment& Apart) {
    std::string nameTemp, cccdTemp;
    std::cout << "Enter Name: ";
    std::getline(std::cin,nameTemp);
    Date tempbirthday;
    int day, month, year;
    do{ std::cout << "\nEnter Date Of Birth \n";
        std::cout << "Enter Day: ";     std::cin >> day   ; std::cin.ignore();
        std::cout << "Enter Month: ";   std::cin >> month ; std::cin.ignore();
        std::cout << "Enter Year: ";    std::cin >> year  ; std::cin.ignore();
        tempbirthday.day = day;
        tempbirthday.month = month;
        tempbirthday.year = year;
        if(!checkValidDay(tempbirthday)) std::cout << "\nDate is not valid. Try again!\n";
    } while(!checkValidDay(tempbirthday));
    std::cout << "Enter CCCD: ";
    std::getline(std::cin,cccdTemp);
    time_t now_time = time(0);
    struct tm *today = localtime(&now_time);
    uint8_t ageTemp = today->tm_year + 1900 - tempbirthday.year;
    Tenant Tent(Apart,nameTemp, cccdTemp, tempbirthday, ageTemp);
    std::cout << "Input Information\n";
    std::cout << "Name: " << nameTemp << std::endl ;
    std::cout << "Date Of Birth: " << (int)tempbirthday.day << " / " << (int)tempbirthday.month << " / " << (int)tempbirthday.year;
    std::cout << "\nCCCD: " << cccdTemp;
    std::cout << "\nAge: " << (int)ageTemp;    
    return Tent;
}
void Manager::writeInfo(std::fstream &fout, Manager admin, Tenant p){
	Date tempDate;
	Apartment a = p.getApartmentInfo();
	fout << admin.getApartmentID(a) << ","
		 << (int)admin.getMaxPerson(a) << ","
		 << admin.getOwnerName(a) << ","
		 << p.getTenantName() << ","
		 << p.getTenantCCCD() << ",";
	tempDate = p.getTenantDateOfBirth();
	fout << (int)tempDate.day << "/" << (int)tempDate.month << "/" << (int)tempDate.year << ","
		 << (int)p.age << ","
		 << 1 << ",";
	tempDate = admin.getStartRent(a);
	fout << (int)tempDate.day << "/" << (int)tempDate.month << "/" << (int)tempDate.year << ",";
	tempDate = admin.getEndRent(a);
	fout << (int)tempDate.day << "/" << (int)tempDate.month << "/" << (int)tempDate.year << ","
		 << (int)admin.getPastDayAsDue(a) << ","
		 << admin.getPaymentMethod(a)
		 << "\n";
}

std::string Manager::getOwnerName(Apartment& var) {
    return var.ownerName;    
}
uint8_t Manager::getMaxPerson(Apartment& var){
    return var.maxPerson;
}
Date Manager::getStartRent(Apartment& var) {
    return var.startRent;
}
Date Manager::getEndRent(Apartment& var) {
    return var.endRent;
}
PAYMENT_METHOD Manager::getPaymentMethod(Apartment& var) {
    return var.paymentMethod;
}
uint16_t Manager::getApartmentID(Apartment& var) {
    return var.id;
}

int16_t Manager::getPastDayAsDue(Apartment& var)  {
    return var.maxDayPastDue;
}

