#include <stdio.h>
#include <string.h>

// similar to #define INT 0

/* Enums are good for:
Representing states in a state machine.
Defining error codes.
Handling menu options or user input.
*Working with flags (especially when enumerator values are powers of two, allowing bitwise operations).
Improving the clarity of switch-case statements.

*really good to fix magic numbers
*/
typedef enum DataType
{
    INT,   // 0
    FLOAT, // 1
    STRING // 2
} DataType;

typedef struct GenericData
{
    DataType type;
    union value // this works yay
    {
        int int_val;
        float float_val;
        char string_val[50];
    } value;
} GenericData;

int main()
{
    GenericData data_array[6];

    data_array[0].type = INT;
    data_array[0].value.int_val = 100;

    data_array[1].type = FLOAT;
    data_array[1].value.float_val = 9.99;

    data_array[2].type = STRING;
    strcpy(data_array[2].value.string_val, "C Programming");

    for (int i = 0; i < 3; i++)
    {
        switch (data_array[i].type)
        {
        case INT:
            printf("Element %d: Integer = %d\n", i, data_array[i].value.int_val);
            break;
        case FLOAT:
            printf("Element %d: Float = %.2f\n", i, data_array[i].value.float_val);
            break;
        case STRING:
            printf("Element %d: String = %s\n", i, data_array[i].value.string_val);
            break;
        }
    }

    return 0;
}