#include<stdlib.h>
#include<stdio.h>

#define SHIFT_AMOUNT 16 // 2^16 = 65536
#define SHIFT_MASK ((1 << SHIFT_AMOUNT) - 1) // 65535 (all LSB set, all MSB clear)

int main(){

    int price = 500 << SHIFT_AMOUNT;
    price += 10 << SHIFT_AMOUNT;
    price *= 3;
    price /= 4; // now our price is ((500 + 10) * 3) / 4 = 382.5
    printf ("price integer is %d\n", price >> SHIFT_AMOUNT);
    printf ("price fraction is %d\n", price & SHIFT_MASK);
    printf("price fraction in decimal is %f\n", ((double)(price & SHIFT_MASK) / (1 << SHIFT_AMOUNT)));
    printf("price is roughly %d.%lld\n", price >> SHIFT_AMOUNT, (long long)(price & SHIFT_MASK) * 100000 / (1 << SHIFT_AMOUNT));


    //printf ("%d\n", 1 << SHIFT_AMOUNT);

    
    return 0;
}
