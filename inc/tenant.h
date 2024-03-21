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
		const uint16_t &getApartmentId();
};

#endif
