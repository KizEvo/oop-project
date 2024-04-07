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
        std::string getOwnerName(Apartment&);
        uint8_t getMaxPerson(Apartment&);
        Date getStartRent(Apartment&);
        Date getEndRent(Apartment&);
        PAYMENT_METHOD getPaymentMethod(Apartment&);

        void writeInfo(std::fstream &fout, Manager admin, Tenant p);
        Tenant writeTenantWhenApartmentIsEmpty(uint16_t&);              
        Tenant writeTenantWhenApartmentIsOccupied(Apartment&);                  
        Tenant extendApartmentEndRent(Tenant&,uint16_t);                  
        void displayTenantInfo(Tenant);
        void displayApartmentInfo(Apartment);            
};

#endif