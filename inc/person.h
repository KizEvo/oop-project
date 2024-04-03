#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <cstdint>
#include "date.h"

class Person
{
	protected:
		std::string cccd;
		Date birthday;
	public:
		std::string name;
		uint8_t age;
		/*Constructor*/
		Person();
		Person(std::string, Date, std::string, uint8_t);
};

#endif
