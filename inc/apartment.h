#ifndef APARTMENT_H
#define APARTMENT_H

#include <cstdint>
#include "date.h"

enum PAYMENT_METHOD {CASH, DEBIT_CARD, CREDIT_CARD};

class Apartment
{
	private:
		std::string id;				/*The apartment ID*/
		std::string ownerName;			/*The tenant who rent the apartment*/
		uint8_t maxPerson;			/*Maximum number of person in an apartment*/
		uint8_t maxDayPastDue;			/*Maximum number of days before requires immediate rent payment*/
		bool isRented;				/*Checks if the apartment with ID is rented or not*/
		Date startRent;				/*The date the apartment was rented*/
		Date endRent;				/*The date the apartment rent ends*/
		PAYMENT_METHOD paymentMethod;		/*The tenant monthly payment method*/
	public:
		friend class Landlord;
};

#endif
