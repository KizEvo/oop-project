#include <cstdint>
#include <string>
#include "person.h"
#include "date.h"

Person::Person() : cccd{"UnknownCCCD"}, birthday{}, name{"UnknownName"}, age{0} {}

Person::Person(std::string cccdStr, Date birthdayObj, std::string nameStr, uint8_t ageVal)
		: cccd{cccdStr}, birthday{birthdayObj}, name{nameStr}, age{ageVal} {}
