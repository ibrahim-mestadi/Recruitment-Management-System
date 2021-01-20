#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "affichage.h"
#define  MAX_SPE 20
#define  MAX_NOM_PRENOM 30
#define  MAX_ADRESS 50
#define  MAX_CODE
#define  MAX_YEAR 2001
#define  MIN_YEAR 1985
#define  MAX_MOUNTH 13
#define  MAX_DAY 32
#define MAX_SPECIALITE 10
#define MAX_CIN 7
#define  Malloc(type) (*type)malloc(type)
#define  FILE_BASE_CANDIDAT "candidat.bin"

typedef struct date
{
    int jj;int mm;int yyyy;
}date;


typedef struct {
    int num;
    char nom[MAX_SPE];
}specialite;

typedef struct
{
    char nom[MAX_NOM_PRENOM];
    char prenom[MAX_NOM_PRENOM];
    char adress[MAX_ADRESS];
    char code[MAX_CODE+1];
    date birthday;
    char CIN[MAX_CIN]; //primary key
    int sp1;
    int spe2; // it will be downloded from a file
}candidatInfo;

int NomValid(char *nom)
{
    int validName = 1;
    int len = 0;
    int index = 0;
    len = strlen(nom);
    for(index =0; index <len ; ++index)
    {
        if(!(isalpha(nom[index])) && (nom[index] != '\n') && (nom[index] != ' '))
        {
            validName = 0;
            break;
        }
    }
    return validName;
}


int validAdress(char *adress)
{
    int i=0;
    while(adress[i]!='/0')
    {
        if (adress[i]=='@')
        {
            return 1;
        }
        else
            i++;
    }
    return 0;
}
int validDate(date dt)
{
    if (MIN_YEAR<=dt.yyyy<=MAX_YEAR)
        if(dt.mm<MAX_MOUNTH)
            if(dt.jj<MAX_DAY)
                return 1;
    return 0;
}
void addCandidatInDB()
{
    candidatInfo  candidat={0};
    FILE *fp=fp=fopen(FILE_BASE_CANDIDAT,"ab+");;
    int etat=0;
    if (fp==NULL)
    {
        printf("Erreur lors de l'ouverture de %s \n",FILE_BASE_CANDIDAT);
        exit(1);
    }
    headMsg("Ajouter new Candidat");
    printf("\n\n\t\t entrer les donnes du candidat:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    fflush(stdin);
    do
        {
        printf("\n\t\t\t nom : ");
        fflush(stdin);
        //fgets(candidat.nom,MAX_NOM_PRENOM,stdin);
        scanf("%s",candidat.nom);
        etat=NomValid(candidat.nom);
        if (etat==0)
            printf("\n\t\t\t nom invalid svp ressayer a nouveau");

       } while (!etat);

    do
        {
    printf("\n\t\t\t prenom : ");
    fflush(stdin);
    //fgets(candidat.nom,MAX_NOM_PRENOM,stdin);
    scanf("%s",candidat.prenom);
    etat=NomValid(candidat.prenom);
    if (etat==0)
        printf("\n\t\t\t prenom invalid svp ressayer a nouveau");

    } while (!etat);

    do{
        printf("\n\t\t\t adress : ");
        fflush(stdin);
        scanf("%s",candidat.adress);
        etat=validAdress(candidat.adress);
        if (etat==0)
            printf("\n\t\t\t adress invalid svp ressayer a nouveau");

    } while (!etat);
    do{
        printf("\n\t\t\t Specialite principale entre 0 et %d :",MAX_SPECIALITE);
        fflush(stdin);
        scanf("%d",&candidat.sp1);

        if (0<candidat.sp1<MAX_SPECIALITE+1)
            etat=1;
        else {
            etat = 0;
            printf("\n\t\t\t choix invalid svp ressayer a nouveau");
        }

    } while (!etat);

    do{
        printf("\n\t\t\t Specialite secondaire entre 1 et %d :",MAX_SPECIALITE);fflush(stdin);
        scanf("%d",&candidat.spe2);

        if (-1<candidat.spe2<MAX_SPECIALITE+1)
            etat=1;
        else {
            etat = 0;
            printf("\n\t\t\t choix invalid svp ressayer a nouveau");
        }

    } while (!etat);

    do {
        printf("\n\t\t\t Entrer la date de naissence jj-mm-yyyy :");
        fflush(stdin);
        scanf("%d-%d-%d", &(candidat.birthday.jj), &(candidat.birthday.mm), &(candidat.birthday.yyyy));
        etat=validDate(candidat.birthday);
        if(etat==0)
            printf("\n\t\t\t veuillez entrer un date valide ");
    }while(!etat);
    printf("\n\t\t\t Entrer  CIN :");
    fflush(stdin);
    scanf("%s",candidat.CIN);
    strcpy(candidat.code,"ka5450");
    fwrite(&candidat, sizeof(candidatInfo),1,fp);
    fclose(fp);
}

void SupprimeCandidat()
{
    int trouve=0;
    FILE *fp=fopen(FILE_BASE_CANDIDAT,"rb");
    if(fp==NULL)
    {
        printf("erreur lors de l'ouverture du fichier candidat \n");
        exit(1);
    }
    FILE *p=fopen("p.bin","wb");
    if(fp==NULL) {
        printf("erreur lors de l'ouverture du fichier  \n");
        exit(1);
    }
    candidatInfo candidat;
    printf("\n\t\t\t entrer le CIN du candidat a supprime");
    char CIN[MAX_CIN+1];
    scanf("%s",CIN);
    while(fread(&candidat,sizeof(candidatInfo),1,fp))
    {
        if (strcmp(candidat.CIN, CIN) != 0)
        {

            fwrite(&candidat, sizeof(candidat), 1, p);
        }
        else  {
            trouve = 1;
            printf("%s\n",candidat.nom);
        }
    }
    (trouve)? printf("\n\t\t\t candidat est supprime ....") :printf("\n\t\t\t Candidat non trouve");
    fclose(fp);
    fclose(p);
    remove(FILE_BASE_CANDIDAT);
    rename("p.bin",FILE_BASE_CANDIDAT);
}

void modifyCandidat() {
    int tv=0;
    printf("\n\t\t\t entrer le CIN du candidat du a Modifier");
    char cin[MAX_CIN + 1];
    scanf("%s", cin);
    FILE *fp = fopen(FILE_BASE_CANDIDAT, "ab+");
    candidatInfo candidat;
    FILE *p = fopen("p.bin", "wb");
    while (fread(&candidat, sizeof(candidatInfo), 1, fp)) {
        if (strcmp(candidat.CIN, cin) != 0) {
            fwrite(&candidat, sizeof(candidat), 1, p);
        } else {
            tv=1;
            printf("\n\t\t\t pour modifier le nom choisissez 1 ");
            printf("\n\t\t\t pour modifier le prenom choisissez 2 ");
            printf("\n\t\t\t pour modifier le birthday choisissez 3 ");
            printf("\n\t\t\t pour modifier l' adress  choisissez  4 ");
            printf("\n\t\t\t pour modifier l' spetielite principale   choisissez  5* ");
            printf("\n\t\t\t pour modifier l' spetielite secondaire   choisissez  6 *");

            int choix;int e=0;
            scanf("%d",&choix);
            switch (choix) {
                case 1:
                    printf("\n\t\t\t entrer le nom modifie");
                    char nom[MAX_NOM_PRENOM];
                    scanf("%s", nom);
                    strcpy(candidat.nom, nom);
                    printf("nom est bien Modifie");
                    break;
                case 2:
                    printf("\n\t\t\t entrer le prenom modifie");
                    char prenom[MAX_NOM_PRENOM];
                    scanf("%s", prenom);
                    strcpy(candidat.prenom, prenom);
                    printf("prenom est bien Modifie");
                    break;
                case 3:

                    do {

                        printf("\n\t\t\t Entrer la date de naissence jj-mm-yyyy :");
                        fflush(stdin);
                        scanf("%d-%d-%d", &(candidat.birthday.jj), &(candidat.birthday.mm), &(candidat.birthday.yyyy));
                        e = validDate(candidat.birthday);
                        if (e == 0)
                            printf("\n\t\t\t veuillez entrer un date valide ");
                    } while (!e);
                    printf(" \n\t\t\t la date de naissance  est bien Modifie");
                    break;
                case 4:
                    printf("\n\t\t\t Entrer la nouvelle adress : ");
                    char adress[MAX_ADRESS];
                    scanf("%s",adress);
                    strcpy(candidat.adress,adress);
                    printf("\n\t\t\t  adress modifie ");
                    break;

            }
        }
        if(tv!=0)
        {
            printf("candidat makaynch");
        }



    }
}


typedef struct _liste
{
    candidatInfo *candidat;
    struct _liste *next;
}listeCandidat;


listeCandidat* insert(candidatInfo *cd,listeCandidat *head)
{
    listeCandidat *newCandidat=(listeCandidat*)malloc(sizeof(listeCandidat));
    newCandidat->candidat=cd;
    listeCandidat *p=head;
    if(!p ,stricmp(cd->nom,p->candidat->nom))
    {
        newCandidat->next=p;
        head=newCandidat;
    }
    else
    {
        while(p->next && (stricmp(newCandidat->candidat->nom,p->next->candidat->nom))>0)
        {
            p=p->next;
        }
        p->next=newCandidat;
    }
    return head;
}

void afficherParOrdre()
{
    listeCandidat *head=NULL;
    candidatInfo *cdi;
    FILE *fp=fopen(FILE_BASE_CANDIDAT,"ab+");
    while(fread(cdi,sizeof(candidatInfo),1,fp))
    {
        head=insert(cdi,head);
    }
    fclose(fp);
    listeCandidat *p=head;
    if(head==NULL)
    {printf("zbiiiiii"); }

    while(head!=NULL)
    {
        printf(head->candidat->nom);
    }
}






