#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>

//EXAMPLE OF CLASS
class Person{
	//Cac thong tin nam trong private nen hau het cac ham duoc khai bao la friend
private:
	std::string roomID;
	std::string Name;
	std::string DoB;
	std::string CCCD;
public:
	friend void readInfo(std::ifstream &f, Person &p);
	friend void readCSV(std::ifstream &f, std::vector<Person> &pl);
	friend void out(std::vector<Person> &pl);
};


//USING FOR READ LINE BY LINE OF .CSV FILE
void readInfo(std::ifstream &filein, Person &person){
	getline(filein, person.roomID, ',');
	getline(filein, person.Name, ',');
	getline(filein, person.DoB, ',');
	getline(filein, person.CCCD);
}

//USING FOR READ ENTIRE .CSV FILE
void readCSV(std::ifstream &filein, std::vector<Person> &personList){
	//Loai bo di ten cot cua file CSV
	std::string line;
	getline(filein, line);
	//Thong tin cua moi person (a) duoc dua vao vector personList
	while(filein.eof() == false){
		Person a;
		readInfo(filein, a);
		personList.push_back(a);
	}
}

//USING FOR WRITE .CSV (CREATE THE FIRST TIME/ UPDATE ON AVAILABLED DATA )
void writeCSV(){

}

//PRINT OUT THE LIST
void out(std::vector<Person> &personList){
	//Su dung data doc duoc
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

//DEFINE THE ERROR: FILE NOT FOUND
int fileNotExist(std::string file_name){
	int opt;
	std::cout << "<<ERROR!>>: Could not find '"<< file_name <<"', please choose the following options:" <<std::endl;
	std::cout << "0. Quit" << std::endl;
	std::cout << "1. Create a new '"<< file_name <<"' file " << std::endl;
	std::cout << "2. Update the location of the file (if you alread have the '" << file_name << "')" << std::endl;
	std::cout << "\n--> Enter the option: ";
	std::cin >> opt;
	switch(opt){
		case 0:
			return -1;
			break;
		case 1:
			system("cls");
			std::cout << "\t\t-> Create a new '" << file_name << "'<-" << std::endl;
			return 1;
			break;
		case 2:
			system("cls");
			std::cout << "\t\t-> Updating the location of the file <-" << std::endl;
			std::cout << "Instruction: Close the application then move/copy .csv file. Attention:"<< std::endl <<
						 "- Please be sure the location of .csv file is the same folder with source.cpp" <<std::endl<<
						 "- The file was named '" << file_name << "'" <<std::endl;
		 	return -1;
			break;
	}
	if(opt!=1 && opt!=2){
		system("cls");
		fileNotExist(file_name);
	}
	return 0;
}

int main(){
	std::vector<Person> List;
	std::string fname = "test_in.csv";
	std::ifstream filein(fname);
	int er;													//er is the ERROR_CODE, use for decide what to do next
//CASE: COULD NOT FIND .CSV FILE
	if(!filein.is_open()){
		er = fileNotExist(fname);							
	}
	std::cout << "er = " << er << "\n";
	if(er == -1) return 0;									//Quit the program (opt = 0 or opt = 2 is entered)
	else if(er == 1) writeCSV();							//Create new file(for the first time)
	
//CASE: FOUND .CSV FILE
	std::cout << "Thong tin tu file " << fname << ":" << std::endl;
	readCSV(filein, List);
	out(List);

	/*
	CAC DOAN CODE KHAC
	*/

	
	return 0;
}

//CURRENTLY PROGRESS: writeCSV()