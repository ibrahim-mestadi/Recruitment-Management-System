#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>





void afficherMessageAuCentre(char *message)
{
    int len=0;
    int position=0;
    len=(78-strlen(message))/2;
    printf("\t\t\t");
    for(position=0;position<len;position++)
    {
        printf(" "); // espace
    }
    printf("%s",message);
}

void headMsg(char *msg)
{
    system("cls");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    afficherMessageAuCentre(msg);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}

void BonjoureMsg()
{
    headMsg("www.manpower.com");
    printf("\n\n\n\n\n");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t        =                  Bonjour                  =");
    printf("\n\t\t\t        =                   dans                    =");
    printf("\n\t\t\t        =         Gestion Offres-Candidats          =");
    printf("\n\t\t\t        =                   Systeme                 =");
    printf("\n\t\t\t        =                   MANPOWER                =");
    printf("\n\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Enter any key to continue.....");
    getch();
}
