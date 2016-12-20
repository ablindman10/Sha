#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>

/*
 * CURRENT CHAR LIMIT IS 55 CHARS INCLUDING SPACES ETC.....
 * frist 55 chars are legal, 56th char is reserved for the 1 pad, and last 16 are reserved
 * total of 64 chars, for a bit size of 512 bits
 * NEED TO CLEAN ARRAYS AS WE MOVE
 * fix array data types
 * 
 */





/*****************************************************************************
 * NEED A FUNCTION CALLED binaryToHex
 * function should be called on line 107
 * function should take the bitarray input located on line 58, 
 * and convert it to hex and store it in a new array
 * binaryToHex(int *input, int [what ever you can get to work])
 * 
 * in the end the binary array should be converted to hex, in such a way that
 * 448 bits will become [14] hex array, see the following link page 5
 * https://tools.ietf.org/html/rfc3174
 * 
 * for example abcde in hex array form should look like this
 * 
 * 
 * index  [1]      [2]      [3]      [3]    ...
 *      61626364 65800000 00000000 00000000 ...
 * 
 * 
 * 61626364 is one hex number, with that value so we can easily shift and xor it
 * 
 * ***************************************************************************/

#define MAX 100000 * sizeof(char)
uint32_t rotl32 (uint32_t value, unsigned int count);
void toBinary (char input, int *output);
void messageLengthPad(uint32_t length, uint32_t *array);
//binaryToHex(int *input,int [what ever you can get to work]);

int main(void) {
    //Initialize variables
    int i, j;
    uint32_t h0, h1, h2, h3, h4;
    uint32_t ml = 0;
    
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
    
    
    
    printf("The number of Chars inputed was: %d\n", ml);
    
    //start the padding process
    ml = ml * 8;
    
    
    
    //pad rest of the 512 bits to 0
    for(i = ml / 8; i < 64; i++) {
        for(j = 0; j < 8; j++)
            bitarray[i][j] = 0;
    }
    
    //pad the 1 on the ml + 1 location, example if input is abcde, ml = 40, pad 41 location to be 1 
    bitarray[ml / 8][0] = 1;
    
    
    //pad the last 64 bits big endian, so that it contains the message length
    messageLengthPad(ml, *bitarray);
    
    
    //reprint large array
    printf("After padding the 512 bits the array looks like:");
    for(i = 0; i <= 63; i++) {
        if(i % 4 == 0)
            printf("\n");
        for(j = 0; j < 8; j++)
            printf("%d", bitarray[i][j]);
        printf(" ");
    }
    
    //array to hold hex, all only 448 bits will be used last 64 are reserved
    //can move this to the top later, leave for now
    uint32_t hexArray[16];
    
    //insert call the binaryToHex function here
    
    
    
    //last step of the padding process, store message length (ml) as a big endian
    
    
    
    
    //create large hex array for extention, should be extened to hold 80 total "numbers"
    uint32_t largeHexArray[80];
    
    //copy old values into new one
    for(i = 0; i < 16; i++)
        largeHexArray[i] = hexArray[i];
    
    //extend 16 hex words into 80
    for(i = 16; i < 80; i++) {
        largeHexArray[i] = rotl32((largeHexArray[i - 3] ^ largeHexArray[i - 8] ^ largeHexArray[i - 14] ^ largeHexArray[i - 16]), 1);
    }
    
    
    //needed for main loop
    uint32_t a, b, c, d, e, f, k, temp;
    a = h0;
    b = h1;
    c = h2;
    d = h3;
    e = h4;
    
    
    
    //main loop
    for(i = 0; i < 80; i++) {
        if(i >= 0 && i <= 19) {
            f = (b & c) | ((~b) & d);
            k = 0x5A827999;
        }
        
        else if (i >= 20 && i <= 39) {
            f = b ^ c ^ d;
            k = 0x6ED9EBA1;
        }
        
        else if (i >= 40 && i <= 59) {
            f = (b & c) | (b & d) | (c & d);
            k = 0x8F1BBCDC;
        }
        
        else if (i >= 60 && i <= 79) {
            f = b ^ c ^ d;
            k = 0xCA62C1D6;
        }
        
        temp = (rotl32(a, 5)) + f + e + k + largeHexArray[i];
        e = d;
        d = c;
        c = rotl32(b, 30);
        b = a;
        a = temp;
    }
    
    /****************************************
    * Here down is is a mess, ignore please
    ****************************************/
    
    //as it turns out we have to use an array of unsigned 8 bit ints to hold 160 bits for hash
    
    uint8_t hash[20];
    //now has is 160 bits little endian
    
    //how the hell do we compare bits with a array?
    //looks like NSA has some method for this on top of page 13
    //NSA seems to be doing some very complex math for this
    //all of our data types match, so thats a good sign
    
    
    //hash = rotl32(h0, 128) | rotl32(h1, 96) | rotl32(h2, 64) | rotl32(h3, 32) | h4;
    
    //printf("\nhash output in little endian is: %d\n", hash);
    // hash has to be 160 bits and has to be big endian
        
}

/*
void binaryToHex(int *input, int [what ever you can get to work]) {
    
    
    
    
}
*/


void messageLengthPad(uint32_t length, uint32_t *array) {
    
    int i, j;
    j = 1;
    for(i = 511; i >= 417; i--) {
        if(length % 2 == 0) {
        *(array + i) = 0;
        }
        
        else
            *(array + i) = 1;
        length /= 2;
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
        
        else
            output[i] = 1;
        value /= 2;
    }
}
