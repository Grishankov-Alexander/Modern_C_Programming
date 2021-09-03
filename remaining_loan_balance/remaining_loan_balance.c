/*
 * Program that calculates the remaining balance
 * on a loan after first, second and third payments.
*/

#include <stdio.h>

int main(void)
{
    float loan_amount, interest_rate, monthly_payment;
    float balance, increase;
    int number_of_payments;

    printf("Enter loan amount: ");
    (void)scanf("%f", &loan_amount);
    balance = loan_amount;
    printf("Enter interest_rate (percents): ");
    (void)scanf("%f", &interest_rate);
    printf("Enter montly_payment: ");
    (void)scanf("%f", &monthly_payment);
    printf("Enter number of payments: ");
    (void)scanf("%d", &number_of_payments);

    for (int i = 0; i < number_of_payments; ++i) {
        increase = balance * (interest_rate / 100) / 12;
        balance = balance + increase - monthly_payment;
    }
    
    printf("Balance, remaining after %d payments: %.2f\n",
            number_of_payments, balance);

    return 0;
}
