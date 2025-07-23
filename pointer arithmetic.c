#include <stdio.h>

struct Person
{
    int age;
};

int main()
{

    struct Person people[100];
    struct Person *p_Person = people;

    // populate ages
    for (int i = 0; i < 100; i++)
    {
        people[i].age = i + 1;
    }

    // mess around with pointers
    // because the location of our pointer - the starting location(start of array) gives us our offset, it can replace i
    for (; p_Person - people < 100; p_Person++)
    {
        printf("");
        printf("\n Person %d age: %d \n", p_Person - people, p_Person->age);
        printf("");
    }

    // kinda cool !!
    return 0;
}