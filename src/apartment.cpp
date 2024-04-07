#include "apartment.h"

Apartment::Apartment() {}

Apartment::	Apartment(uint16_t Id, std::string NameStr, uint8_t MaxPerson, \
    int16_t MaxDay, bool IsRented, Date StartDate, Date EndDate, PAYMENT_METHOD PM)
    : id{Id} , ownerName{NameStr}, maxPerson{MaxPerson}, maxDayPastDue{MaxDay}, isRented{IsRented}, \
    startRent{StartDate}, endRent{EndDate}, paymentMethod{PM} {}

