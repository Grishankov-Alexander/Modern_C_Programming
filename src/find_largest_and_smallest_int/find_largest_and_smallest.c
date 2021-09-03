/*
 * Program that finds largest and smallest ints
*/


#include <stdio.h>


int main(void)
{
    int i1, i2, i3, i4, largest, smallest;

    printf("Enter four integers: ");
    (void)scanf("%d%d%d%d", &i1, &i2, &i3, &i4);

    if (i1 > i2) {
        largest = i1;
        smallest = i2;
    } else {
        largest = i2;
        smallest = i1;
    }
    if (i3 > i4) {
        largest = i3 > largest ? i3 : largest;
        smallest = i4 < smallest ? i4 : smallest;
    } else {
        largest = i4 > largest ? i4 : largest;
        smallest = i3 < smallest ? i3 : smallest;
    }

    printf("Largest: %d\nSmallest: %d\n", largest, smallest);

    return 0;
}
