# OOP Project
**Capstone project in OOP coursework - Apartment Building Management**
<br>
* Nhóm thực hiện : Nhóm 11
* Phần mềm lập trình : Makefile và phần mềm soạn thảo văn bản Visual Studio Code.
* Phiên bản : Makefile phiên bản 4.4.1 và C++ phiên bản 14 (Visual Studio Code chỉ để viết chương trình nên không lệ thuộc phiên bản sử dụng).

## Cách chạy chương trình
* Trước tiên hãy bật terminal và có đường dẫn tới danh mục bên trong oop-project như sau :
	* D:\AHocTap\HK2Nam3\OOP\oop-project>
	* Đường dẫn có thể khác trên máy thầy nhưng terminal phải ở trong danh mục oop-project.

- Nếu trên máy có Makefile (4.4.1) -> trên terminal chạy `make` để compile chương trình, sau đó chạy `make run`
- Nếu trên máy không có Makefile, chạy các dòng sau trên terminal :
	- `mkdir build`
	- `g++ -Wall -Wextra -std=c++14 -g -O0 -Iinc/ -I. -o build/out.exe src/apartment.cpp src/main.cpp src/manager.cpp src/person.cpp src/tenant.cpp`
	- `./build/out.exe` - Chạy chương trình đã compile
