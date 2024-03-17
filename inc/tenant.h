#ifndef TENANT_H
#define TENANT_H

#include "person.h"

enum PAYMENT_METHOD {CASH, DEBIT_CARD, CREDIT_CARD};

class Tenant: public Person
{
        private:
                PAYMENT_METHOD paymentMethod;
                Date startRent;
                Date endRent;

        public:
                /*Constructor*/
                Tenant();
                Tenant(PAYMENT_METHOD, Date, Date);
};

#endif
