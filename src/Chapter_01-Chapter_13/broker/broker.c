/*
 * Calculates a broker's comission.
*/


#include <stdio.h>


int main(void)
{
    int number_of_shares;
    float price_per_share;
    float value, comission, rival_comission;

    printf("Enter number of shares: ");
    (void)scanf("%d", &number_of_shares);
    printf("Enter price per share: ");
    (void)scanf("%f", &price_per_share);
    value = price_per_share * number_of_shares;

    while (value > 0.00f) {

        if (value < 2500.00f)
            comission = 30.00f + value * .017f;
        else if (value < 6250.00f)
            comission = 56.00f + value * .0066f;
        else if (value < 20000.00f)
            comission = 76.00f + value * .0034f;
        else if (value < 50000.00f)
            comission = 100.00f + value * .0022f;
        else if (value < 500000.00f)
            comission = 155.00f + value * .0011f;
        else
            comission = 255.00f + value * .0009f;

        if (comission < 39.00f)
            comission = 39.00f;

        rival_comission = 33.00f;
        if (number_of_shares < 2000)
            rival_comission += 0.03f * number_of_shares;
        else
            rival_comission += 0.02f * number_of_shares;

        printf("Comission: $%.2f\n", comission);
        printf("Rival comission: $%.2f\n", rival_comission);

        printf("Enter number of shares: ");
        (void)scanf("%d", &number_of_shares);
        printf("Enter price per share: ");
        (void)scanf("%f", &price_per_share);
	value = price_per_share * number_of_shares;

    }

    return 0;
}
