/*
LU Decomposition of square matrix
theory: P*A=L*U
-->Permutation is done to get most suited elements at pivot position.
-->short column 1 and swap the row with largest element in column 1 with row 1
-->short column 2 excluding row 1 and swap the row with largest element in column 2 with row 2.....
-->Do the row wise reversible operations and fill the lower triangular matrix at same time.

Author: Purnendu Kumar, MS, IIT Madras
Date: 28/01/2015
Tested ok: compiled with (minGW, Code::Blocks 13.12, windows 8.1) and found perfectly working on 04/06/2015

Property of engineeringxd.com
For any issues: write to purnenduk90@gmail.com

*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

main(){

int i,j,m,x,l;
double mat[100][100],temp[100],a[100][100],lt[100][100],maximum,per[100][100];
printf("This program is for LU decomposition of matrix according to (P*A=L*U)\n\n");
printf("Enter the size of square matrix: ");
scanf("%d", &m);

//enter the matrix
printf("\n\nEnter the matrix e.g \n\n M11 M12 M13 ... M1n \n M21 M22 M23 ... M2n \n .\n .\n .\n Mn1 Mn2 Mn3 ... Mnn \n\n");
for(i=0;i<m;i++)
  {
    for(j=0;j<m;j++){
    scanf("%lf",&mat[i][j]); //lf for double c99
    a[i][j]=mat[i][j];    }
  }
//show matrix
  printf("\n Input matrix (A)=\n");
for(i=0;i<m;i++)
{
  for(j=0;j<m;j++)
  {
      printf("%lf\t", a[i][j]);
  }
  printf("\n");
}
//create Identity matrix
for(i=0;i<m;i++){
  for(j=0;j<m;j++)
  {
      per[i][j]=0;
      if(i==j)
      {per[i][j]= per[i][j]+1;}
      lt[i][j]=per[i][j];
    }
  }
//making the pivot elements largest
for(j=0;j<m-1;j++)
{
    maximum = fabs(mat[j][j]);
    for (i=j;i<m;i++)
    {
         if (fabs(mat[i][j]) >= maximum)
       {
       maximum  = fabs(mat[i][j]);
       l = i;//finding location of biggest element in column j leaving j rows from above untouched.
       }
    }
    for (x=0;x<m;x++)//swapping operation
    {
        temp[x]=mat[l][x];
        mat[l][x]=mat[j][x];
        mat[j][x]=temp[x];
        temp[x]=per[l][x];
        per[l][x]=per[j][x];
        per[j][x]=temp[x];
    }
}
//show permutation matrix
  printf("\n Permutation matrix matrix (P)=\n");
for(i=0;i<m;i++)
{
  for(j=0;j<m;j++)
  {
      printf("%lf\t",per[i][j]);
  }
  printf("\n");
}
//decomposition
for (x=0;x<m-1;x++)
{
    for (i=x+1;i<m;i++)
    {
    for (j=0;j<m;j++){
    temp[j]=mat[i][j]-(mat[x][j]*(double)(mat[i][x]/mat[x][x]));//row operation start
        }
    lt[i][x]=(double)(mat[i][x]/mat[x][x]);//filling lower triangular matrix
    for (j=0;j<m;j++){
       mat[i][j]=temp[j];}//row operation complete
    }
}
//show lower triangular and upper triangular matrix
  printf("\n Lower Triangular matrix (L)=\n");
for(i=0;i<m;i++)
{
  for(j=0;j<m;j++)
  {
      printf("%lf\t",lt[i][j]);
  }
  printf("\n");
}
  printf("\n Upper Triangular matrix (U)=\n");
for(i=0;i<m;i++)
{
  for(j=0;j<m;j++)
  {
      printf("%lf\t",mat[i][j]);
  }
  printf("\n");
}
return 0;
}
