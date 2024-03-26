#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

//EXAMPLE OF CLASS
class Person{
private:
	std::string roomID;
	std::string Name;
	std::string DoB;
	std::string CCCD;
public:
	Person(std::string x, std::string y, std::string z, std::string t);
	friend void writeInfo(std::ofstream &f, Person &p);
	friend void writeCSV(std::ofstream &f, std::vector<Person> &pl);
	friend void out(std::vector<Person> &pl);
};

Person::Person(std::string x, std::string y, std::string z, std::string t){
	roomID = x;
	Name = y;
	DoB = z;
	CCCD = t;
}

//USE FOR WRITE A SINGLE LINE IN .CSV FILE
void writeInfo(std::ofstream &fout, Person &person){
	fout << person.roomID << ", "
		 << person.Name << ", "
		 << person.DoB << ", "
		 << person.CCCD <<"\n";
}

//USE FOR CREATE/OVERWRITE .CSV FILE
void writeCSV(std::ofstream &fout, std::vector<Person> &personList){
	//Them ten cot cho file .CSV
	fout << "ID Phong,Ten,Ngay sinh,CCCD\n";
	for(int i=0; i<int(personList.size()); i++){
		writeInfo(fout, personList[i]);
	}
}


//PRINT OUT THE LIST
void out(std::vector<Person> &personList){
	std::cout << std::setw(10) <<"Ma phong"
			  << std::setw(25) <<"Ten"
			  << std::setw(15) << "Ngay sinh"
			  << std::setw(25) << "Ma CCCD"
			  << std::endl;
	for(int i=0; i<int(personList.size()); i++){
		std::cout << std::setw(10) << personList[i].roomID
				  << std::setw(25) << personList[i].Name
				  << std::setw(15) << personList[i].DoB
				  << std::setw(25) << personList[i].CCCD
				  << std::endl;
	}
}


int main(){
	std::vector<Person> List;
	std::string fname = "test_out.csv";
	std::ofstream fileout(fname);

	//Khoi tao 3 thong tin de test xuat file
	Person a("102", "Le Van Nhu", "03/03/2001", "079022111222");
	List.push_back(a);
	Person b("204", "Hi Hi", "13/09/1999", "079022333444");
	List.push_back(b);
	Person c("204", "Hu Hu", "03/04/1995", "079022444555");
	List.push_back(c);
	
	//Xem thu thong tin vua tao
	out(List);

	//Xuat file
	writeCSV(fileout, List);
	
	
	/*
	CAC DOAN CODE KHAC
	*/

	return 0;
}