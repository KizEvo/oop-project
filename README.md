# OOP Project
Capstone project in OOP coursework - Apartment Building Management

<br>

* Phần mềm lập trình : Makefile và phần mềm soạn thảo văn bản Visual Studio Code.
* Phiên bản : Makefile phiên bản 4.4.6 và C++ phiên bản 14 (Visual Studio Code chỉ để viết chương trình nên không lệ thuộc phiên bản sử dụng).

* Cách chạy chương trình : 
	- Nếu trên máy có Makefile (4.4.6) -> bật terminal chạy 'make' để compile chương trình, sau đó chạy 'make run'
	- Nếu trên máy không có Makefile, chạy các dòng sau trên terminal :
		- `g++ -Wall -Wextra -std=c++14 -g -O0 -Iinc/ -I. -o build/out.exe src/apartment.cpp src/main.cpp src/manager.cpp src/person.cpp src/tenant.cpp`
		- `./build/out.exe` - Chạy chương trình đã compile
