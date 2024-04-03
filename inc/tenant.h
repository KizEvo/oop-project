#ifndef TENANT_H
#define TENANT_H

#include <cstdint>
#include "person.h"
#include "apartment.h"

class Tenant: public Person
{
    private:
       	Apartment apartment;
	public:
		Tenant(Apartment&,std::string, std::string, Date, uint8_t);
		std::string getTenantName();
		uint8_t getTenantAge();
		Date getTenantDateOfBirth();
		std::string getTenantCCCD();
		Apartment getApartmentInfo();
};

#endif
