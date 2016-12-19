#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

/*
 * CURRENT CHAR LIMIT IS 55 CHARS INCLUDING SPACES ETC.....
 * frist 55 chars are legal, 56th char is reserved for the 1 pad, and last 16 are reserved
 * total of 64 chars, for a bit size of 512 bits
 * 
 */





/*****************************************************************************
 * NEED A FUNCTION CALLED binaryToHex
 * function should take the bitarray input located on line 58, 
 * and convert it to hex and store it in a new 2D array
 * binaryToHex(int *input, int [what ever you can get to work])
 * 
 * in the end the binary array should be converted to hex, in such a way that
 * 448 bits will become [14][8] hex array, see the following link page 5
 * https://tools.ietf.org/html/rfc3174
 * ***************************************************************************/

#define MAX 100000 * sizeof(char)
uint32_t rotl32 (uint32_t value, unsigned int count);
void toBinary (char input, int *output);
//binaryToHex(int *input,int [what ever you can get to work]);

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
    
    printf("The input was: %s", password);
    
    
    
    //calucate messege legth
    for(i = 0; password[i] != '\n'; i++)
        ml++;
    
    //array of bits for each char value given, 512 bits
    int bitarray[64][8];
    
    
    //take the password and turn it into an array of bits
    for(i = 0; i < ml; i++) {
        toBinary(password[i], bitarray[i]);
    }
    
    
    
    printf("The number of Chars inputed was: %ld\n", ml);
    
    //start the padding process
    ml = ml * 8;
    
    
    
    //pad rest of the 448 bits to 0
    for(i = ml / 8; i < 56; i++) {
        for(j = 0; j < 8; j++)
            bitarray[i][j] = 0;
    }
    
    //pad the 1 on the ml + 1 location, example if input is abcde, ml = 40, pad 41 location to be 1 
    bitarray[ml / 8][0] = 1;
    
    
    //pad the last 64 bits
    
    //reprint large array
    printf("After padding the frist 448 bits the array looks like:");
    for(i = 0; i < 56; i++) {
        if(i % 4 == 0)
            printf("\n");
        for(j = 0; j < 8; j++)
            printf("%d", bitarray[i][j]);
        printf(" ");
    }
    
    //array to hold hex, all only 448 bits will be used last 64 are reserved
    //can move this to the top later, leave for now
    int hexArray[16][8];
    
    
}

/*
void binaryToHex(int *input, int [what ever you can get to work]) {
    
    
    
    
}
*/

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
        
        else
            output[i] = 1;
        value /= 2;
    }
}
