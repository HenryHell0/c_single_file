#include <stdio.h>
#include <string.h>

union data // this works yay
{
    int int_val;
    char string_val[4];
} data;

int main(int argc, char *argv[])
{

    /*
    *Notes about overlap of array and pointer and int or whatever
    If you use char *string_val; in your union, then string_val is a pointer (not an array).
    The union will only store the pointer value (the address), not the actual string data.
    This means int_val and string_val will overlap in memory, so writing to one will overwrite the other.
    But currrently, string_val is an array, not a char*, so the elements in the array share memory.

    char(size 1)  |    |                - treated as one char
    int (size 4)  |    |    |    |    | - treated as one big number, with different signifances
    */

    // messing around with INT printed as STRING
    /*
    - Setting string_val[0] = 6; only sets the first byte (sizeof(char) = 1)
    - Printing int_val interprets all bytes as an int, not just the first. (sizeof(int) = 4)
    */

    data.int_val = 100; // only needs one byte, so D is printed
    printf("Element 3: Integer = %d\n", data.int_val);
    printf("Element 3: Integer (as string) = %s - ASCII d = 100.\n\n", data.string_val);

    // little itty bitty endian
    data.int_val = (100 << 8) | 100; //* now, this needs multiple bytes, so it overflows to multiple bytes
    printf("Element 3: Integer = %d\n", data.int_val);
    printf("Element 3: Integer (as string) = %s\n\n", data.string_val);

    // !?!?!?!?!?!?! endianness aaah
    /*


    okay so its little itty bitty endian

    okay so what had me confused was I was thinking about for each byte. each byte itself is big endian.
    however, in the memory it is little endian, which makes sense

    | 115 | 117 | 112 |  0  |
    | 's' | 'u' | 'p' | \0  |
    */
    data.int_val = (115) | (117 << 8 * 1) | (112 << 8 * 2) | (0 << 8 * 3); //* now it overflows to say "sup"
    printf("Element 3: Integer = %d\n", data.int_val);
    printf("Element 3: Integer (as string) = %s\n\n", data.string_val);

    // ! now messing around with setting the char value and then going to int

    data.string_val[0] = 'E';
    data.string_val[1] = '\0';
    data.string_val[2] = '\0';
    data.string_val[3] = '\0';
    //data.int_val = 69696969;

    printf("Element 3: String = %s\n", data.string_val);
    printf("Element 3: String as Int = %d\n", data.int_val);


    /*
        used to find the ASCII character that is the hidden last one
    data.int_val = 69696969;
    data.int_val = data.int_val >> (8*3);
    printf("Element 3: String as Int = %d\n", data.int_val);\
    */
}

/*
also for pico8 you could use enums like this

typedef enum {
    FLAG_SOLID   = 1 << 0, // 00000001
    FLAG_WATER   = 1 << 1, // 00000010
    FLAG_LAVA    = 1 << 2, // 00000100
    FLAG_COLLECT = 1 << 3, // 00001000
    // ... add more flags as needed
} SpriteFlag;

*/