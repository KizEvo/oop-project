#include <iostream>
#include <utility>
#include <iomanip>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include "manager.h"
#include "tenant.h"

using RoomId = uint16_t;

const std::string Password = "12345678";

typedef std::vector<Tenant> 	tenantVector;
typedef std::unordered_map<RoomId,tenantVector> 	ApartmentMap; 

bool checkApartment(uint16_t);
void resetApartment(ApartmentMap&);
void tenantRegistation(ApartmentMap&,Manager);
void selectDeletion(ApartmentMap&,Manager);
void tenantDeletionManual(ApartmentMap&);
void tenantDeletionAutomatic(ApartmentMap&,Manager);
void printAllRentedApartmentInfo(ApartmentMap,Manager);
void printSingleApartmentInfo(tenantVector,Manager);
void extendEndRentedDate(ApartmentMap&,Manager);
void findIDRoom(ApartmentMap,Manager);
void requestPassword();


void extendEndRentedDate(ApartmentMap& tenant, Manager admin) {
	uint16_t id;
	do {std::cout << "\nEnter Apartment ID you need to extend end rented date: " ;
        std::cin >> id;
        std::cin.ignore();
        if(!checkApartment(id)) std::cout << "\nApartment ID is not valid\n";
    } while(!checkApartment(id));
	if (tenant[id].empty()) {
		std::cout << "Apartment is not rented\n";
	}
	else {
		uint16_t monthExtendRent;
		std::cout << "\nEnter number of months you need to extend: ";
		std::cin >> monthExtendRent;
		for (int i = 0; i < (int)tenant[id].size(); i++) {
		tenant[id].at(i) = admin.extendApartmentEndRent(tenant[id].at(i),monthExtendRent);
		}
		std::cout << "\nExtend Succesful " << std::endl;	
	}	
}

void findIDRoom(ApartmentMap tenant, Manager admin) {
	uint16_t id;
	do {std::cout << "\nEnter Apartment ID you need to extend end rented: " ;
        std::cin >> id;
        std::cin.ignore();
        if(!checkApartment(id)) std::cout << "\nApartment ID is not valid\n";
    } while(!checkApartment(id));
	if (tenant[id].empty()) {
		std::cout << "Apatment is not rented\n";
	}
	else {
		printSingleApartmentInfo(tenant[id],admin);
	}
}

//function will check and return true if Apartment ID is valid
bool checkApartment(uint16_t idRoom) {
    if ( idRoom < 100 || idRoom > 999) return false;       						//idRoom is a 3-digit number
    if ( idRoom % 100 > 10 || idRoom % 100 == 0) return false;                  //on each floor only have 10 rooms 
    return true;
}


void requestPassword() {
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


//print single room info
void printSingleApartmentInfo(tenantVector idRoom, Manager admin) {
	std::cout << "\n\n-------------------------\n" ;	
	admin.displayApartmentInfo(idRoom.begin()->getApartmentInfo());
	for (auto i = idRoom.begin() ; i != idRoom.end() ; i++ ) {
		admin.displayTenantInfo(*i);
	}
}


//print Apartment Is Rented Infomation
void printAllRentedApartmentInfo(ApartmentMap tenant, Manager admin) {
	std::cout << "\n-----Print Rented Room Information-----\n";
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j <= 10; j++) {
			if (!tenant[i*100+j].empty()) {
				printSingleApartmentInfo(tenant[i*100+j],admin);
			}
		}
	}
	std::cout << "\n\n--------------" <<std::endl;
} 

//create a map with key is id room and value is null vector
void resetApartment(ApartmentMap& tenant) {
	for (int i = 1; i < 10; i++) {
	for (int j = 1; j <= 10; j++) {
			tenant[i*100+j] = tenantVector();
		}
	}
}

void selectDeletion(ApartmentMap& tenant,Manager admin) {
		int SelectOption;
		std::cout << "\nChoose 1 kind of deletion\n";
        std::cout << "1.Delete manually (Choose 1 room and Delete) \n";
        std::cout << "2.Delete automatically (Delete room which did not pay for 1 month)\n";
		std::cout << "Your Option is: ";
		std::cin >> SelectOption;  std::cin.ignore();
        switch (SelectOption)
        {
        case 1:
			tenantDeletionManual(tenant);
            break;
        case 2:
			tenantDeletionAutomatic(tenant,admin);
            break;
        }
}
void tenantDeletionManual(ApartmentMap& tenant) {
	uint16_t id;
	do {std::cout << "\nEnter IDRomm: " ;
        std::cin >> id;
        std::cin.ignore();
        if(!checkApartment(id)) std::cout << "\nidRoom is not valid\n";
    } while(!checkApartment(id));
	tenant[id].clear();
	std::cout << "\nDelete Succesfully \n";
}
void tenantDeletionAutomatic(ApartmentMap& tenant, Manager admin) {
	std::cout << "\n The apartments did not pay for 1 month \n";
	int SelectOption;
	std::vector<uint16_t> id;
	for ( std::pair<RoomId,tenantVector> pair: tenant) {
		Apartment ApartmentInfo = pair.second.at(0).getApartmentInfo();
		if (admin.getPastDayAsDue(ApartmentInfo) < -15)  {
			admin.displayApartmentInfo(pair.second.begin()->getApartmentInfo());
			id.push_back(pair.first);	
		}
	}
	std::cout << "\nDo you want to delete them? ";
	std::cout << "\n1. Yes";
	std::cout << "\n2. No";
	std::cin  >> SelectOption; std::cin.ignore();
	if (SelectOption == 1) {
		for (auto i = id.begin() ; i != id.end() ; i++ ) {
			tenant[*i].clear();
		}
	}
}
//assign idroom into a key and tenant information into value
void tenantRegistation(ApartmentMap& tenant, Manager admin) {
	uint16_t idCheck;
	do {std::cout << "\nEnter IDRomm: " ;
        std::cin >> idCheck;
        std::cin.ignore();
        if(!checkApartment(idCheck)) std::cout << "\nidRoom is not valid\n";
    } while(!checkApartment(idCheck));
	if (tenant[idCheck].empty()) {
		Tenant tenantINFO = admin.writeTenantWhenApartmentIsEmpty(idCheck) ;
		Apartment tenantApartmentInfo = tenantINFO.getApartmentInfo();
		uint16_t idRoom = admin.getApartmentID(tenantApartmentInfo);
		tenant[idRoom].push_back(tenantINFO);
	}
	else {
		std::cout << "Apartment already has tenant \n";
		Apartment Apart = tenant[idCheck].at(0).getApartmentInfo();
		Tenant tenantINFO = admin.writeTenantWhenApartmentIsOccupied(Apart);
		Apartment tenantApartmentInfo = tenantINFO.getApartmentInfo();
		uint16_t idRoom = admin.getApartmentID(tenantApartmentInfo);
		tenant[idRoom].push_back(tenantINFO);		
	}
}

int main(void)
{
	std::cout << "*****************************\n";
	std::cout << "*" << std::setw(10) << " " << "Welcome"	<< std::setw(10) << " " << "*\n";
	std::cout << "*****************************\n";
	requestPassword();
	ApartmentMap member; 
	Manager administrator;
	std::cout << "\n\n===== Welcome ======\n";
	int SelectOption;
    do { 
		std::cout << "\nAll the options: \n";
        std::cout <<"1.Reset Apartment\n";
        std::cout <<"2.Register The Tenant\n";
		std::cout <<"3.Extended Apartment End Rented Date \n";
        std::cout <<"4.Delete The Room\n";
        std::cout <<"5.Search The Room\n";
        std::cout <<"6.Print All Rented Apartment\n";
        std::cout <<"Choose 1 option ( 0 to exit ): ";
        std::cin >> SelectOption;  std::cin.ignore();
        switch (SelectOption)
        {
        case 1:
			resetApartment(member);
            break;
        case 2:
			tenantRegistation(member,administrator);
            break;
		case 3:
			extendEndRentedDate(member, administrator);
			break;
        case 4:
			selectDeletion(member, administrator);
            break;
        case 5:
			findIDRoom(member,administrator);
            break;
        case 6:
            printAllRentedApartmentInfo(member,administrator);
            break;
        }
		std::cout << "\n";
    }while(SelectOption != 0);
	// std::cout << "Hello world" << std::endl;
	return 0;
}
