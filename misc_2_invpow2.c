/*
Problem statement:
------------------------------------------------------------------------------
Create a text file, "data.txt"  containing inverse powers of 2 starting from 0 to 31, up-to 12th decimal place.
-------------------------------------------------------------------------------
Author: Purnendu Kumar
Date:June 14th 2014
Series: Learn C by examples
Compiled and tested: Code Block 13.12,(GNU-GCC).
www.engineeringxd.com
-------------------------------------------------------------------------------
*/
#include<stdio.h>
#include<math.h>
main()
{
    double a[32];
    int i;
    FILE *fout;
    char fname[100]="data.txt";         //User can change the data file name every time if want to save each data in seprate file.
    fout = fopen(fname, "w");
    for (i=0;i<32;i++){
        a[i]=(double) pow(2,-i);
        fprintf(fout, "%01.12f\n", a[i]);
    }
    fclose(fout);
}
