#include "date.h"
#include "tenant.h"

Tenant::Tenant() : paymentMethod{CASH}, startRent{}, endRent{} {}

Tenant::Tenant(PAYMENT_METHOD method, Date startRentDate, Date endRentDate)
		: paymentMethod{method}, startRent{startRentDate}, endRent{endRentDate} {}
