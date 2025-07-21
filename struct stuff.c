#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Person {
    int age;
    char* name;
    void (*sayName)(struct Person*);
};

void sayName(struct Person* p_person)
{
    printf("Name from sayName is: %s \n", p_person->name);
}



void normalStructTest()
{
    struct Person person;
    person.age = 50;
    person.name = calloc(sizeof(char), 7);
    strcpy(person.name, "test123");
    person.name[0] = "T"[0];


    printf("Hello World \n");
    printf("name: %s\n", person.name);
    printf("age: %d \n", person.age);

    // functions
    person.sayName = sayName;
    person.sayName(&person);

    free(person.name);
}


void pointerStructTest()
{
    // allocate memory for a new thing
    struct Person* p_newPerson = malloc(sizeof(struct Person) + sizeof(int));
    p_newPerson->age = 15;
    p_newPerson->name = "name that is static string thing";


    int* extraSpace = (int*) (p_newPerson + 1);
    *extraSpace = 14;



    printf("name of dynamically allocated struct: %s\n", p_newPerson->name);
    printf("extra integer value: %d \n", *(int*)((char*)p_newPerson + sizeof(struct Person)));

    free(p_newPerson);



}

int main()
{


    normalStructTest();
    pointerStructTest();

    return 0;
}






