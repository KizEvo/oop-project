#include "tenant.h"

Tenant::Tenant(Apartment& room ,std::string tenantName, std::string tenantcccd, Date tenantbirthday, uint8_t tenantage)
    :apartment(room)
    {
        this->name = tenantName;
        this->cccd = tenantcccd;
        this->age = tenantage;
        this->birthday = tenantbirthday;
    } 
std::string Tenant::getTenantName() {
    return name;
}
uint8_t Tenant::getTenantAge() {
    return age;
}
Date Tenant::getTenantDateOfBirth() {
    return birthday;
}
std::string Tenant::getTenantCCCD() {
    return cccd;
}
Apartment Tenant::getApartmentInfo() {
    return apartment;
}