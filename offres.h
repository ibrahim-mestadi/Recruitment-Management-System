#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

#define  MAX_ENTP_NAME 30
#define FILE_OFFRE "offres.bin"
#define  FILE_indexes_offres "offresindex.bin"

typedef struct
{
    int  offres_index;
    char entrep_name[MAX_ENTP_NAME];
    int specialite_requise[2];
    int disponible;
}offres;

int reccord(candidatInfo cd,offres ofr)
{
    int record=0;
    int birth_year=cd.birthday.yyyy;
    time_t t = time(0);
    struct tm *st = localtime(&t);
    int Year_Now=st->tm_year+1900;
    int age=Year_Now-birth_year;
    if(age<=26)
        record=25;
    if(cd.sp1==ofr.specialite_requise[0] || cd.sp1==ofr.specialite_requise[1])
    {
        record+=50;
    }
    if(cd.sp1!=cd.spe2) {
        if (cd.sp1 == ofr.specialite_requise[0] || cd.sp1 == ofr.specialite_requise[1]) {
            record += 20;
        }
    }
    return record;
}

void addOffreInDB()
{
    int etat=1;
    offres offre={0};
    FILE *fp=fopen(FILE_OFFRE,"ab+");
    FILE *index=fopen(FILE_indexes_offres,"ab+");
    if (fp==NULL)
    {
        printf("Erreur lors de l'ouverture de %s \n",FILE_OFFRE);
        exit(1);
    }
    if (index==NULL)
    {
        printf("Erreur lors de l'ouverture de %s \n",FILE_OFFRE);
        exit(1);
    }
    headMsg("Ajouter new offre");
    printf("\n\n\t\t entrer les donnes de l'offre:");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    fflush(stdin);
    do
    {
        printf("\n\t\t\t nom de l'entreprise : ");
        fflush(stdin);
        scanf("%s",offre.entrep_name);
        etat=NomValid(offre.entrep_name);
        if(etat==0)
        {
            printf("\n\t\t\t nom invalid svp ressayer a nouveau");
        }
    }while(!etat);

    do {
        fflush(stdin);

        printf("\n\t\t\t deux Specialite requises ");
        printf("\n\t\t\t la principale  :");
        scanf("%d",&offre.specialite_requise[0]);
        fflush(stdin);

        printf("\n\t\t\t la secondaire  :");
        scanf("%d",&offre.specialite_requise[1]);
    }while(offre.specialite_requise[0]==0);

    offre.disponible=0;

    fread(&offre.offres_index,sizeof(int),1,index);
    fwrite(&offre,sizeof(offre),1,fp);
    fclose(fp);

    FILE *newInndexes=fopen("intermidiare.bin","wb");
    int ind;
    while(fread(&ind,sizeof(int),1,index))
        fwrite(&ind,sizeof(int),1,newInndexes);
    fclose(newInndexes);
    fclose(index);
    remove(FILE_indexes_offres);
    rename("intermidiare.bin",FILE_indexes_offres);
}




TreeCandidats *addtoTreeMerite(candidatInfo cd,TreeCandidats *rac,offres ofrs)
{
    printf("vbnjk");
    if(rac!=NULL)
    {
        if(reccord(rac->candidat,ofrs)<reccord(cd,ofrs))
        {
            rac->d=addtoTreeMerite(cd,rac->d,ofrs);
        }
        else
        {
            rac->g=addtoTreeMerite(cd,rac->g,ofrs);
        }
    }
    else
    {
        rac=(TreeCandidats*)malloc(sizeof(TreeCandidats));
        rac->candidat=cd;
        rac->g=rac->d=NULL;
    }
    return rac;
} // prend les candidat l'insere dans un ABR*/

void exploreParRecoord(TreeCandidats *r,offres ofr)
{
    if(r!=NULL)
    {
        explore(r->g);
        printf(" \n\t\t\t %s  %s  %s  %d ",r->candidat.nom,r->candidat.prenom,ofr.entrep_name,reccord(r->candidat,ofr));
        explore(r->d);
    }
}

void afficherParOffre(offres ofr)
{
    FILE *fp=fopen(FILE_BASE_CANDIDAT,"rb");
    candidatInfo cd;
    TreeCandidats *rac=NULL;
    while(fread(&cd, sizeof(candidatInfo),1,fp))
    {
        rac=addtoTreeMerite(cd,rac,ofr);
    }
    exploreParRecoord(rac,ofr);
    fclose(fp);
}