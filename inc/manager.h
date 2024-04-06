#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <cstdint>
#include <string.h>
#include "tenant.h"

class Manager: public Person
{
    private:
        std::string Password = "12345678";
    public:
        uint16_t getApartmentID(Apartment&);
        int16_t getPastDayAsDue(Apartment&);
        Tenant writeTenantWhenApartmentIsEmpty(uint16_t&);              
        Tenant writeTenantWhenApartmentIsOccupied(Apartment&);                  
        Tenant extendApartmentEndRent(Tenant&,uint16_t);                  
        void displayTenantInfo(Tenant);
        void displayApartmentInfo(Apartment);            
};

#endif