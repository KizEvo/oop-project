#include <iostream>
#include <utility>
#include <fstream>
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

void writeCSV(std::fstream&, std::string, Manager, ApartmentMap );
int CountLine(std::fstream &fin, std::string fname);
Date string2Date(std::string s);
void readInfo(std::fstream &fin, uint16_t &key, Tenant &p);
void readCSV(std::fstream &fin, std::string finName, ApartmentMap &m);
void requestPassword();


void writeCSV(std::fstream &fout, std::string foutName, Manager admin, ApartmentMap m){
	fout.open(foutName, std::ios::out);
	fout << "RoomID,MaxPerson,OwnerName,TenantName,CCCD,Birthday,Age,Rented,StartRent,EndRent,MaxDayPastDue,PaymentMETHOD\n";
	tenantVector idRoom;
	for(auto x : m){
		idRoom = x.second;
		for(int i=0; i<int(idRoom.size()); i++){
			Tenant p = idRoom[i];
			admin.writeInfo(fout, admin, p);
		}
	}
	fout.close();
	std::cout << "-> Saved in " << foutName << "!\n"; 
}
int CountLine(std::fstream &fin, std::string fname){
	std::string line;
	int count=0;
	fin.open(fname, std::ios::in);
	if(fin.is_open()) 
	{
		while(fin.peek()!=EOF)
		{
			getline(fin, line);
			count++;
		}
		fin.close();
		return count;
	}
	else{
		std::cout << "<<<NOTIFICATION!>>>: Couldn't open the "<< fname <<" file!\n";
		return 0;
	}
}


Date string2Date(std::string s){
	std::string d;
	std::vector<std::string> date;
	Date tempDay;
	for(int i=0, j=0; i<int(s.size()); i++){
		if(s.at(i) == '/'){
			d = s.substr(j, i-j);
			date.push_back(d);
			j = i+1;					//Bo qua 1 ky tu '/'
		}
		if(i == int(s.size() - 1)){
			d = s.substr(j, s.size() - j);
			date.push_back(d);
		}
	}
	tempDay.day = std::stoul(date[0]);	tempDay.month = std::stoul(date[1]); tempDay.year = std::stoul(date[2]);
	return tempDay;
}

void readInfo(std::fstream &fin, uint16_t &key, Tenant &p){
	std::string line, s;
	getline(fin, line);
//TACH DU LIEU
	std::vector<std::string> data, date;
	for(int i=0, j=0; i<int(line.size()); i++){
		//Lay cac chuoi truoc dau phay, them vao vector data
		if(line.at(i) == ','){
			s = line.substr(j, i-j);	//line.substr(start, n) : bat dau tu [start] cua line, lay n ky tu
			data.push_back(s);			//Dua vao data
			j = i+1;					//Bo qua ky tu ','
		}
		//Lan lap cuoi cung -> lay chuoi sau dau phay cuoi cung
		if(i == int(line.size() - 1)){
			s = line.substr(j, line.size() - j);
			data.push_back(s);
		}
	}
//CHUYEN DOI KIEU DU LIEU
	//data[0] -> ApartmentID (key of map)
	key = std::stoul(data[0]);
	//data[1] -> maxPerson (Apartment)
	uint8_t tempMaxPerson = std::stoul(data[1]);
	//data[2] -> ownerName (Apartment)
	std::string tempOwnerName = data[2];
	//data[3] -> name (Tenant)
	std::string tempName = data[3];
	//data[4] -> cccd (Tenant)
	std::string tempCCCD = data[4];
	//data[5] -> birthday (Tenant)
	Date tempBirthday = string2Date(data[5]);
	//data[6] -> age (Tenant)
	uint8_t tempAge = std::stoul(data[6]);
	//data[7] -> isRented (Apartment)
	bool tempIsRented = true;
	//data[8] -> startRent (Apartment)
	Date tempStartRent = string2Date(data[8]);
	//data[9] -> endRent (Apartment)
	Date tempEndRent = string2Date(data[9]);
	//data[10] -> MaxDayPastDue (Apartment)
	int16_t tempMaxDayPastDue = std::stoi(data[10]);
	//data[11] -> paymentMethod (Apartment)
	PAYMENT_METHOD tempPMT;
	unsigned int temp = stoul(data[11]);
	switch(temp){
		case 0: tempPMT = CASH; break;
		case 1: tempPMT = DEBIT_CARD; break;
		case 2: tempPMT = CREDIT_CARD; break;
	}
//GAN DU LIEU BANG CONSTRUCTOR
	Apartment a(key, tempOwnerName, tempMaxPerson, tempMaxDayPastDue, tempIsRented, tempStartRent, tempEndRent, tempPMT);
	Tenant tempTenant(a, tempName, tempCCCD, tempBirthday, tempAge);
	p = tempTenant;
}

void readCSV(std::fstream &fin, std::string finName, ApartmentMap &m){
	int n = CountLine(fin, finName);		//Tim so hang cua file .csv
	if(n != 0){
		std::cout << "<<<NOTIFICATION!>>>: Read " << finName << " successfully! (" << n-1 <<" lines of data detected)\n";
		fin.open(finName, std::ios::in);
		std::string line;
		uint16_t key;
		getline(fin, line);					//Loai bo di ten cot cua file CSV
		Date emptyDate; emptyDate.day = 0; emptyDate.month = 0; emptyDate.year = 0;
		for(int i=0; i<n-1; i++){
			Apartment a;
			Tenant p(a, "-", "-", emptyDate, 0);
			readInfo(fin, key, p);
			m[key].push_back(p);
		}
		fin.close();
		return;
	}
	std::cout <<  "\t\t Please check if the file is exist or create a new one!\n";
}

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
	do {std::cout << "\nEnter Apartment ID you need to find: " ;
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
	std::cout << "\n\n\t\t         -----------------------\n" ;	
	admin.displayApartmentInfo(idRoom.begin()->getApartmentInfo());
	for (auto i = idRoom.begin() ; i != idRoom.end() ; i++ ) {
		admin.displayTenantInfo(*i);
	}
}


//print Apartment Is Rented Infomation
void printAllRentedApartmentInfo(ApartmentMap tenant, Manager admin) {
	std::cout << "\n---------------      Print Rented Room Information     ---------------\n";
	for (int i = 1; i < 10; i++) {
		for (int j = 1; j <= 10; j++) {
			if (!tenant[i*100+j].empty()) {
				printSingleApartmentInfo(tenant[i*100+j],admin);
			}
		}
	}
	std::cout << "\n\n-------------------------    End Of List!    -------------------------" <<std::endl;

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
	std::cout << "\n\n1. Yes";
	std::cout << "\n2. No";
	std::cout << "\nDo you want to delete them? ";
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

	std::fstream fileout, filein;
	std::string fname = "test.csv";				//Doi ten file tuy y
	
	requestPassword();
	ApartmentMap member; 
	Manager administrator;

	
	//DOC .CSV KHI VUA CHAY CHUONG TRINH
	readCSV(filein, fname, member);

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
        std::cout <<"Choose 1 option ( 0 to save and exit ): ";
        std::cin >> SelectOption;  std::cin.ignore();
        switch (SelectOption)
        {
		case 0:
			writeCSV(fileout, fname, administrator, member);
			break;
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
	return 0;
}
