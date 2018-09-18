#include <stdio.h>


struct Student {
    char *name;
    int age;
};

void printName(struct Student stu) {
    printf("%s\n", stu.name);
}

void changeName(struct Student stu) {
    stu.name = "winter";
}

int main() {
    struct Student stu1, stu2, stu3;
    stu1.name = "summer";
    stu1.age = 12;
    struct Student *pstu = &stu1;
    changeName(stu1);
    printName(stu1);
}

