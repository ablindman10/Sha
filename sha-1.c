#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

/*
 * CURRENT CHAR LIMIT IS 56 CHARS INCLUDING SPACES ETC.....
 * MISSING THE 1 PADDING
 * 
 */
#define MAX 100000 * sizeof(char)
uint32_t rotl32 (uint32_t value, unsigned int count);
void toBinary (char input, int *output);

int main(void) {
    //Initialize variables
    int i, j;
    unsigned int h0, h1, h2, h3, h4;
    unsigned long ml = 0;
    
    //password can be size of 100,000 chars
    char password[MAX];

    
    h0 = 0x67452301;
    h1 = 0xEFCDAB89;
    h2 = 0x98BADCFE;
    h3 = 0x10325476;
    h4 = 0xC3D2E1F0;

    //grab the password
    printf("Enter the password you wish to encrypt using sha-1: ");
    fgets(password, MAX, stdin);
    
    printf("\n%s", password);
    
    
    
    //calucate messege legth
    for(i = 0; password[i] != '\n'; i++)
        ml++;
    
    //array of bits for each char value given, 512 bits
    int bitarry[64][8];
    
    //assign them all the be 0, might not be needed
    /*
    for(i = 0; i < 64; i++) {
        for(j = 0; j < 8; j++)
            bitarry[i][j] = 0;
    }
    */
    
    //take the password and turn it into an array of bits
    for(i = 0; i < ml; i++) {
        toBinary(password[i], bitarry[i]);
    }
    
    
    
    printf("%ld", ml);
    

    printf("\nHere is the bit array of the the chars:\n");
    for(i = 0; i < ml; i++) {
        for(j = 0; j < 8; j++) {
            printf("%d", bitarry[i][j]);
        }
        printf("\n");
    }
    
    //start the padding process
    ml = ml * 8;
    
    //must pad to 448 bits
    for(i = ml / 8; i < 56; i++) {
        for(j = 0; j < 8; j++)
            bitarry[i][j] = 0;
    }
    
    //pad the last 64 bits
    
    //reprint large array
    printf("After padding the bit array looks like:\n");
    for(i = 0; i < 56; i++) {
        if(i % 4 == 0)
            printf("\n");
        for(j = 0; j < 8; j++)
            printf("%d", bitarry[i][j]);
        printf(" ");
    }
    
    
    
    
}


//left shift rotate
uint32_t rotl32 (uint32_t value, unsigned int count) {
    const unsigned int mask = (CHAR_BIT*sizeof(value)-1);
    count &= mask;
    return (value<<count) | (value>>( (-count) & mask ));
}

//converts the array of bits to bit value of char password
void toBinary(char input, int *output) {
        
    int i, j, value;
    value = input;
        for(i = 7; i >= 0; i--) {
        if(value % 2 == 0) {
            output[i] = 0;  
        } 
        
        else {
            output[i] = 1;
        }
        value /= 2;
        }
}
