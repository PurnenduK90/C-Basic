/*
Program to calculate the width, impedance and losses of micro-strip on a PCB board for proper signal integrity.
Uses the formula as stated on page no. 148, 149 and 150 of Microwave engineering 4th Edition by David M Pozar.ISBN:978-81-265-4190-4
Assumption: Thickness of conductor is negligible with respect to thickness of PCB

Author: Purnendu Kumar, MS, IIT Madras
Date: 02/06/2015
Tested ok: compiled with (minGW, Code::Blocks 13.12, windows 8.1) and found perfectly working on 04/06/2015

Property of engineerinxd.com
For any issues: write to purnenduk90@gmail.com

*/

#include <stdio.h>
#include <math.h>

#define c 299792458//speed of light in m/sec
#define pi 3.14159265//value of pie
#define u 0.0000012566//permittivity of vaccum H/m

main(void)
{
    double W,H,Z,Er,Ee,Vp,beta,f,t,sigma,Rs,Ad,Ac;
    int condition;
    char decision;

    start:
    printf("Select Mode : \n1\tfor calculating width of micro-strip\n2\tfor calculating impedance of micro-strip\n\nMode = ");
    scanf("%d", &condition);

    switch (condition)
    {
        case 1:
            printf("Di-electric strength of PCB material = ");
            scanf("%lf", &Er);

            printf("Thickness of PCB material(mils) = ");
            scanf("%lf", &H);

            printf("Characteristic impedance(ohm) = ");
            scanf("%lf", &Z);

            double A, B, ratio;

            A= ((Z/60) * sqrt((Er+1)/2))+((Er-1)/(Er+1))*(0.23+(0.11/Er));//equation 3.197 for W/H<2

            ratio=(8*exp(A))/(exp(2*A)-2);//equation 3.197 for W/H<2

            if (ratio<2)
            {
                W=H*ratio;
            }
            else
            {
                B= (377*pi)/(2*Z*sqrt(Er));//equation 3.197 for W/H>2
                W= H*((2/pi)*(B-1-log((2*B)-1)+(((Er-1)/(2*Er))*(log(B-1)+0.39-(0.61/Er)))));//equation 3.197 for W/H>2
            }
            Ee=((Er+1)/2)+(((Er-1)/2)*(1/sqrt(1+((12*H)/W))));//equation 3.195
            printf("\nWidth of strip = %f mils\n",W);
        break;

        case 2:
            printf("Di-electric strength of PCB material = ");
            scanf("%lf", &Er);

            printf("Thickness of PCB material(mils) = ");
            scanf("%lf", &H);

            printf("Width of Micro-strip(mils) = ");
            scanf("%lf", &W);

            Ee=((Er+1)/2)+(((Er-1)/2)*(1/sqrt(1+((12*H)/W))));//equation 3.195

            if((W/H)<1)
            {
                Z=(60/sqrt(Ee))*((8*H/W)+(W/(4*H)));//equation 3.196 for W/H<1
            }
            else
            {
                Z=(120*pi)/(sqrt(Ee)*((W/H)+1.393+0.667*log((W/H)+1.444)));//equation 3.196 for W/H>1
            }

            printf("\nCharacteristic impedance of micro-strip = %f ohm\n",Z);
        break;

        default:
            printf("\nyou have entered wrong value, retry\n");
            goto start;
        break;
    }

    selection:
    printf("\nDo you want to calculate attenuation? Y/N..");
    scanf("%s",&decision);
    if (decision=='Y')
    {
        printf("\nOperating frequency (MHz) = ");
        scanf("%lf",&f);
        f=f*1000000;
        printf("\nLoss tangent of dielectric (tan delta) = ");
        scanf("%lf",&t);
        printf("\nSigma = ");
        scanf("%lf",&sigma);
        printf("\nEffective relative permittivity = %f\n", Ee);
        Vp = c/sqrt(Ee);//equation 3.193
        printf("\nPhase velocity = %f m/sec\n", Vp);
        beta=2*pi*f*sqrt(Ee)/c;//equation 3.194
        printf("\nPropagation constant = %f\n", beta);
        Rs=sqrt(pi*f*u/sigma);
        printf("\nSurface resistivity = %f\n", Rs);
        Ad=(beta*t*0.08686/2)*((Er*(Ee-1)/(Ee*(Er-1))));//equation 3.198 also it is converted to db/cm hence multiplied by 0.08686
        printf("\nAttenuation due to di-electric loss = %f dB/cm\n", Ad);//1cm = 393.7 mil
        Ac=Rs*8.686/(Z*W*0.00254);//equation 3.199 also it is converted to db/cm hence multiplied by 8.686, W is converted to cm.
        printf("\nAttenuation due to conductor loss = %f dB/cm\n", Ac);

        printf("\nPhase delay is equal to (Propagation constant * length of strip), where phase delay is in radians and length in meters.\n");

    }
    else if (decision=='N') goto end;
    else
    {
        printf("\nyou have entered wrong value, retry\n");
        goto selection;
    }
    end:
    printf("\nDo you want to run program for another input set? Y/N..");
    scanf("%s",&decision);
    if (decision=='Y') goto start;
    else if (decision!='Y' && decision!='N')
    {
        printf("\nyou have entered wrong value, retry\n");
        goto end;
    }
    else printf("\n----------------------------------------------------------------------\nthanks for using the program! computation has been completed.\n\nPlease visit 'engineeringxd.com' for more program like this.\n----------------------------------------------------------------------\nPress any key to exit.");

   getch();
   return 0;
}

