/*
 * Program that compares two dates
 * Shows which comes earlier
*/


#include <stdio.h>


int main(void)
{
    int d, m, y;
    int s_d, s_m, s_y;

    printf("Enter a date (mm/dd/yy): ");
    scanf("%d /%d /%d", &m, &d, &y);
    s_d = d, s_m = m, s_y = y;

    while (d != 0 || m != 0 || y !=0) {
        if ((y < s_y) || (y == s_y && m < s_m) || (y == s_y && m == s_m &&  d < s_d))
            s_d = d, s_m = m, s_y = y;
        printf("Enter a date (mm/dd/yy): ");
        scanf("%d /%d /%d", &m, &d, &y);
    }

    printf("Smallest date: %d/%d/%.2d\n", s_m, s_d, s_y);

    return 0;
}
