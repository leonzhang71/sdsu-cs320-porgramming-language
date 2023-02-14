#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
Name: Chonglin Zhang
class: CS320
instructor: Shawn Healey
Date: 3-6-2021
Problem 1 and Problem 4:
Problem 1: Write a program which returns the number of capital letters in an
input string of characters.
Problem 4: Write a function which determines if the two input characters differ
by a single bit.

The purpose of problem 1 and 4: When you start to debug the program. It would ask you
to type 1 and 4. When you type 1, it will run the question 1 and ask you to type the 
input string. For example, you type 'AAAAAbbbCCC', and it would show up the number of 
upper case character: 8. After executing the question 1, you have to run the program 
again. Next time, you might type 4, and this is the problem for question 4. It will 
ask you to type the first single character, and then it will ask you to type the
second single character. And then, they will compare these two single characters to 
determines them if the two input characters differ by a single bit. For example, you can type
the first character 'A', and the second character 'B'. The result shows that these two characters
are different by one bit. If the first character 'A', and the second character 'C'. The result shows that two 
characters don't differ by one single bit. 

CAUTION: for question 4, don't input the same character.

CAUTION: Need to modifiy propreties for this homework. Click the "Project",
and then click the "cs320hw2 propreties". In C/C++, click the "Preprocessor". 
In the "Preprocessor Definions" part, you might have to copy and paste "CRT_SECURE_NO_WARNINGS".
 This part is for "scanf" in order to use safely. 
*/


void question1() {
    char str[100];
    int count = 0;
    int i;

    printf("Enter a string: ");
    gets(str);

    for (i = 0; str[i] != '\0'; i++)
    {

        if (str[i] >= 'A' && str[i] <= 'Z')
        {
            count++;
        }
    }

    printf("Number of Upper case characters: %d ", count);

}

int bitDiff(char a, char b)
{
    int x = a ^ b;
    for (int i = 0; i < 8; i++)
    {
        if (pow(2, i) == x)return 1;
    }
    return 0;
}


void question4() {
    char fc;
    char sc;

    printf("Please input your first character: ");
    scanf(" %c", &fc);
    printf("Please input your second character: ");
    scanf(" %c", &sc);

    if (bitDiff(fc, sc) == 1)
    {
        printf("The two characters don't differ by a single bit");
    }
    else {
        printf("The two characters differ by a single bit");
    }
    return 0;
}


int main() {
    int question;
    printf("There are question 1 and question 4, enter the number to solve the problem: ");
    scanf("%d", &question);
    getchar();

    if (question == 1) {
        question1();
    }
    else if (question == 4) {
        question4();
    }
    else {
        printf("Please choose 1 or 4");
    }
    return 0;
}





