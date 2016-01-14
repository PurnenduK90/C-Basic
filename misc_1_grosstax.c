/*
Problem statement:
------------------------------------------------------------------------------
Assume Govt. of India follow the following rules for income tax calculation:
first 5000 of income is tax free(slot D);
next 10000 of income has 10% tax on it(slot C);
next 20000 of income has 15% tax on it(slot B);
amount above 35000 has 20% tax on it(slot A);
Write a program to calculate tax while salary is entered by user.
-------------------------------------------------------------------------------
Author: Purnendu Kumar
Date:October 2nd 2015
Series: Learn C by examples
Emphasis: "Switch case", "while loop", "if condition"
Compiled and tested: Code Block 13.12,(GNU-GCC).
www.engineeringxd.com
-------------------------------------------------------------------------------
*/
#include<stdio.h>

int main()
{
    //make it a standard practice to name variables such that it can be easily related. This makes program more readable.
    int salary;//We have assumed that salary is int, it can also be float or double.
    char grade, slot;//grade is defined for employee
    float tax=0.0;//initial tax

    printf("Please enter the salary (Rs): ");
    scanf("%d", &salary);//getting salary amount from user

    //define grade/slot
    if (salary > 35000)     grade='A';
    if ((salary > 15000) && (salary<=35000))     grade='B';
    if ((salary > 5000) && (salary<=15000))     grade='C';
    if (salary<=5000) grade='D';
    slot=grade;

    //calculation of tax
    while(slot!='D')//no tax for D slot
    {
        switch(slot)
        {
        case 'A'://tax of 20% above amount 35000
            tax=tax+(salary-35000)*0.2;
            slot='B';
            salary=35000;
            break;//loop again goes back to while condition followed by a switch based on slot
        case 'B'://tax of 15% above amount 15000 and less than 35000
            tax=tax+(salary-15000)*0.15;
            slot='C';
            salary=15000;
            break;//loop again goes back to while condition followed by a switch based on slot
        case 'C'://tax of 10% above amount 5000 and less than 15000
            tax=tax+(salary-5000)*0.1;
            slot='D';
            salary=5000;
            break;//loop again goes back to while condition followed by a switch based on slot
        default://this case is not required in this program but it is written here only to follow a standard practice.
            printf("Invalid tax slot");
            break;
        }
    }

    printf("Employee fall in '%c' grade and calculated tax is Rs.%f", grade,tax);//output
    return 0;
}
