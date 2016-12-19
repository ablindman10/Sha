#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

#define SHA1CircularShift(bits,word) \
                (((word) << (bits)) | ((word) >> (32-(bits))))

uint32_t rotl32 (uint32_t value, unsigned int count);


// use this to test bit logic

//must output hex as %x otherwise complier thinks its signed.... lol



int main(void) {
    uint32_t value, i;
    
    //printf("Enter a value to test: ");
    //scanf("%d", &value);
    
    value = 0x000000Af;
    printf("Value captured was %X\n", value);
    
    for (i = 1; i <= 15; i++) {
        //value = SHA1CircularShift(i, value);
        value = rotl32(value, i);
        printf("Value after %d rotl %X\n", i, value);
    }
    
    
    
    
    return 0;
}



uint32_t rotl32 (uint32_t value, unsigned int count) {
    const unsigned int mask = (CHAR_BIT*sizeof(value)-1);
    count &= mask;
    return (value<<count) | (value>>( (-count) & mask ));
}

