#ifndef APARTMENT_H
#define APARTMENT_H

#include <cstdint>
#include <string>
#include "date.h"

enum PAYMENT_METHOD {CASH, DEBIT_CARD, CREDIT_CARD};

class Apartment
{
	private:
		uint16_t id;				/*The apartment ID, use this format XYZ (X is apartment floor, YZ is the apartment number)*/
		std::string ownerName;			/*The tenant who rent the apartment*/
		uint8_t maxPerson;			/*Maximum number of person in an apartment*/
		uint8_t maxDayPastDue;			/*Maximum number of days before requires immediate rent payment*/
		bool isRented;				/*Checks if the apartment with ID is rented or not*/
		Date startRent;				/*The date the apartment was rented*/
		Date endRent;				/*The date the apartment rent ends*/
		PAYMENT_METHOD paymentMethod;		/*The tenant monthly payment method*/
	public:
		friend class Manager;
};

#endif
