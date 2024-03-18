#ifndef MANAGER_H
#define MANAGER_H

#include "tenant.h"

enum KIND_OF_TENANT {OWNER, CO_RENTER};
class Manager: private Tenant
{
    private:
        uint16_t idRoom; 
        KIND_OF_TENANT KOT;
    public:
        /* Constructor */
        Manager();
        void getTenantInformation();        //get tenant information from console
        void getMoneyTenant();              //get money from tenant
        void delTenantInformation();        //delete tenant information from console
        void searchTenantInformation();     //search tenant information by idRoom or cccd or name
};

#endif