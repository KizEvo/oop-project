#ifndef TENANT_H
#define TENANT_H

#include "person.h"
#include "apartment.h"

class Tenant: public Person
{
        private:
        	Apartment apartment;
	public:
		const std::string &getApartmentId();
};

#endif
