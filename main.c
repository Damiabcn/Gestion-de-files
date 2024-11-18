#include <stdio.h>
#include<stdlib.h>
#include <string.h>
    /*---------------------PARTIE DECLARATIVE--------------------------------------------------*/
    /* I) les types utilsés */
    struct client {    /* LE NOYEAU (client) */
        char nom[25];
        int ticket;
        struct client* adr;
    };

    struct gichet {   /* le guichet/agent */

    struct client *T,*Q;
    };
    /*----------------------les-modules-utilise------------------- */
    /*(1) allouer un client*/

    void allouer(struct client **p){
     *p=malloc(sizeof(struct client));
    };
    /*(2) tester si le gichet est vide  */

    int vide_gich(struct gichet p){
        return (p.T==NULL);
    };
    /*(3) enfiler un client */

  int enfiler_client(struct gichet *g, const char *name, int ticket){
    struct client *u,*prec,*curr;

    allouer(&u);
    strcpy(u->nom, name);
    u->ticket = ticket;
    u->adr = NULL;
    if (g->T == NULL){
        g->T = u;
        g->Q = u;
    } else { prec=g->T;
        curr=g->T->adr;
        if(curr == NULL && u->ticket<g->T->ticket){
            u->adr=g->Q;
            g->T=u;
    }
    else{

        while(curr!=NULL && u->ticket > curr->ticket){
            prec=curr;
            curr=curr->adr;
        }
        if(curr == NULL){
            g->Q->adr= u;
            g->Q= u;
        } else {
            u->adr=curr;
            prec->adr=u;
        }
    }
    }
    return 1;
}

    /* defiler un client */
    int defiler_client(struct gichet *g, char *name, int *ticket){
    struct client *u;
    if (g->T == NULL){
        return 0;
    } else {
        strcpy(name, g->T->nom);
        *ticket = g->T->ticket;
        u = g->T;
        g->T = g->T->adr;
        free(u);
        return 1;
    }
}
 /* AFFICHER UN GUICHET */
    void afficher_gichet(struct gichet *g){
    struct client *p;

    if (g->T==NULL){
        printf("Le gichet est vide\n");
    } else {
        p=g->T;
        printf("+-----------------------+\n");
        printf("|    NOM     |   TICKET |\n");
        printf("+-----------------------+\n");
        while (p!=NULL){
            printf("|  %-12s |   %-3d   |\n",p->nom, p->ticket);
            p=p->adr;
        }
        printf("+-----------------------+\n");
    }
}
/*AFFICHER GLOBALE*/
    void afficher_accueille(struct gichet p[]) {
    int i;
    char alphabet = 'A';
    for (i = 0; i < 4; i++) {

        printf("+-----------------------+\n");
        printf("|    GUICHET-%c            |\n", alphabet);

        afficher_gichet(&p[i]);
        alphabet++;
    }
}
/*reinitialisation_tickets*/
int resinstallation_tickets(struct gichet p[4],int nbrclm){
int cpt=1,verif=0,min,recent=0,i;
struct client *c,*u;
for (i=0; i<4; i++){
    if(p[i].T!=NULL){
        verif=1;
    }
}
    if(verif==1){
            while(cpt != nbrclm+1) {
                    min=1000000;
for (i = 0; i < 4; i++){
        c=p[i].T;
  while (c!=NULL){
    if(c->ticket<min && c->ticket>recent){
        min=c->ticket;
        u=c;
    }
    c=c->adr;
  }

}
recent=min;
u->ticket=cpt;
 cpt++;
}
return 1;
}else {
return 0;
}
}
/*transfert d'un guichet vers l'autre*/

int transfer_gichet(struct gichet *g,struct gichet *f){
/*declaration*/
int tmp;
char chartmp[25];
if (g->T==NULL){
   return 0;
}else{ while(g->T!=NULL){
    defiler_client(g,chartmp,&tmp);
    enfiler_client(f,chartmp,tmp);
}
return 1;
}
}
/*-----REEIQUILIBRE GICHETS---*/
int reequilibre(struct gichet p[4]){
/*declaration*/
int tmp,i;
char chartmp[25];
struct gichet *h;
h = malloc(sizeof(struct gichet));
h->T=NULL;
h->Q=NULL;
for (i=0;i<4;i++){
    transfer_gichet(&p[i],h);
}
i=0;
while(h->T!=NULL){
        if(i==4){i=0;}
      defiler_client(h, chartmp, &tmp);
      enfiler_client(&p[i], chartmp, tmp);
      i++;
}


 free(h->T);
    free(h);
return 0;
}
/*redirection module*/
int split_gichet(struct gichet p[4],struct gichet *g, int tab[], int nmbrgich){
    int i=0,tmp,j;
    char chartmp[25];
    while(g->T!=NULL){
            if(i==nmbrgich){i=0;}
        defiler_client(g,chartmp,&tmp);
            j=tab[i];
        enfiler_client(&p[j],chartmp,tmp);
        i++;
    }
    return 1;
}


    /*---------------------PARTIE IMPLEMENTATION (PROGRAMME PRINCIPAL)--------------------------------------------------*/
    int main (){
            /* II) les variables utilisées */

    struct gichet accueille[4];
    struct gichet *temp,*temp2;
    int i,quit=0,tickets=0,choice3,choiceb,choiceb2,quitb=0,quitd=0,choice2,tmp,nbrcl=0,quitd3=0,nbrgich,quitd1;
    int tab[4];
    char nemo[25],choice,tmpname[25];
    /* III) initialisation des variables */
    for (i=0;i<4;i++){
        accueille[i].T=NULL;
        accueille[i].Q=NULL;
    };
    temp = malloc(sizeof(struct gichet));
    temp->T=NULL;
    temp->Q=NULL;
    temp2 = malloc(sizeof(struct gichet));
    temp2->T=NULL;
    temp2->Q=NULL;


      while (quit == 0){
            quitb=0;
            quitd=0;
            quitd3=0;
        printf("--------MENU--------\n");
        printf("1.Ajouter un client\n");
        printf("2.Afficher la file d'un guichet\n");
        printf("3.Afficher la file d'accueil globale\n");
        printf("4.Opération en vrac sur les files des gichets\n");
        printf("5.Quitter\n");
        printf("Choix ?:");
        scanf("%d", &choice3);

        if(choice3 == 1){
                nbrcl++;
                tickets++;
            printf("Entrez le nom du client: ");
            scanf("%s", nemo);

            printf("Choisissez le guichet A,B,C ou D: ");
            scanf(" %c", &choice);
            while (choice < 'A' || choice > 'D'){
                printf("Choix invalide !\n");
                printf("Choisissez le guichet A,B,C ou D: ");
                scanf(" %c", &choice);
            }
                enfiler_client(&accueille[choice - 'A'],nemo,tickets);
                printf("Client ajouté avec succés\n");

        }
        else if(choice3 == 5){
            quit = 1;
        }
        else{ if(choice3==2) {
             printf("choisissez le guichet A,B,C ou D: ");
             scanf(" %c", &choice);
            while (choice < 'A' || choice > 'D'){
                printf("choix invalide !\n");
                printf("choisissez le guichet A,B,C ou D: ");
                scanf(" %c", &choice);
            }
        afficher_gichet(&accueille[choice - 'A']);
        if(accueille[choice - 'A'].T == NULL){
                 printf("Vous ne pouvez pas recevoir un client !\n");
        } else{
        while (quitb == 0){
            printf("--GUICHET--MENU---\n");
            printf("1.recevoir un client\n");
            printf("2.retour\n");
            printf("choix :");
            scanf("%d",&choiceb);
            if (choiceb==1){
                printf("========================\n");
                printf("NOM:%s\tTICKET:%d\n",accueille[choice - 'A'].T->nom,accueille[choice - 'A'].T->ticket);
                printf("========================\n");
                defiler_client(&accueille[choice - 'A'],tmpname,&tmp);

                printf("1.Traiter la requette du client\n");
                printf("2.Rediriger le client vers un autre gichet\n");
                printf("choix:");
                scanf("%d",&choiceb2);
                if(choiceb2==1){
                        nbrcl--;

                    printf("Requette traitée !\n");
                    quitb=1;
                } else{
                    if (choiceb2==2){
                            printf("choisissez le guichet A,B,C ou D: ");
                            scanf(" %c", &choice);
                            while (choice < 'A' || choice > 'D'){
                            printf("choix invalide !\n");
                            printf("choisissez le guichet A,B,C ou D: ");
                            scanf(" %c", &choice);
                             }
                              enfiler_client(&accueille[choice - 'A'],tmpname,tmp);
                              printf("Redirection avec succeés\n");
                              quitb=1;


                        }else{
                            printf("choix invalide\n");

                        }

                      }


            } else {
            if (choiceb==2){
                quitb=1;

            } else{

            printf("choix invalide\n");

            }
                  }
                        }
        }

                           }else{ if (choice3==3){
                               afficher_accueille(accueille);
                               printf("================\n");
                               printf("TOTAL CLIENTS: %d\n",nbrcl);
                               printf("================\n");

                           }else{ if(choice3 == 4){
                                printf("------Opérations en vrac-MENU-------\n");
                                printf("1.REDIRIGER UNE FILE D'UN GuICHET VERS d'AUTRES GUICHETS\n");
                                printf("2.REDIRIGER DEUX FILES OU PLUS VERS UNE FILE\n");
                                printf("3.REEQUILIBRER LES FILES\n");
                                printf("4.REINITIALISATION DES TICKETS\n");
                                printf("5.Retour\n");
                                printf("choix: ");
                                scanf(" %d", &choice2);
                                while(quitd==0){
                                        if(choice2==1){
                                                nbrgich=0;
                                                i=0;
                                                quitd1=0;
                                                printf("choisissez le guichet à rediriger A,B,C ou D: ");
                                                scanf(" %c", &choice);
                                                while (choice < 'A' || choice > 'D' || accueille[choice- 'A'].T==NULL){
                                                printf("choix invalid ou gichet vide !\n");
                                                printf("choisissez le guichet à rediriger A,B,C ou D: ");
                                                scanf(" %c", &choice);
                                                            }

                                                       transfer_gichet(&accueille[choice - 'A'],temp2);
                                                 while(quitd1==0 && nbrgich!=4){
                                                printf("Choisissez les guichets à recevoir A,B,C ou D: ");
                                                scanf(" %c", &choice);
                                                nbrgich++;
                                                while (choice < 'A' || choice > 'D' || accueille[choice- 'A'].T!=NULL ){
                                                printf("Choix invalide ou guichet non vide !\n");
                                                printf("Choisissez les guichets à recevoir A,B,C ou D: ");
                                                scanf(" %c", &choice);
                                                            }
                                                    tab[i]=choice - 'A';
                                                    i++;

                                                    printf("Pour rediriger entrez 1, pour ajouter un guichet à recevoir entrez 0:");
                                                    scanf("%d",&quitd1);
                                                    if(nbrgich==4){
                                                            printf("Vous avez choisi tous les guichets !\n");
                                                            quitd1=1;

                                                    }

                                                 }
                                                 split_gichet(accueille,temp2,tab,nbrgich);
                                                 printf("Redirection avec succés \n");
                                            quitd=1;
                                        }else {if(choice2==2){

                                            while(quitd3==0){
                                               printf("Choisissez les guichets à rediriger A,B,C ou D: ");
                                                scanf(" %c", &choice);
                                                while (choice < 'A' || choice > 'D'){
                                                printf("Choix invalide !\n");
                                                printf("Choisissez les guichets à rediriger A,B,C ou D: ");
                                                scanf(" %c", &choice);
                                                    }
                                                transfer_gichet(&accueille[choice - 'A'],temp);
                                                printf("Pour rediriger entrez 1, pour ajouter un guichet à rediriger entrez 0");
                                                scanf("%d",&quitd3);
                                            }
                                                printf("Choisissez le guichet déstinataire A,B,C ou D: ");
                                                scanf(" %c", &choice);
                                                while (choice < 'A' || choice > 'D'){
                                                printf("Choix invalid !\n");
                                                printf("Choisissez le guichet déstinataire A,B,C ou D: ");
                                                scanf(" %c", &choice);
                                                }
                                                transfer_gichet(temp,&accueille[choice - 'A']);
                                                printf("Redirection avec succés\n");
                                                quitd=1;
                                        }else {if(choice2==3){
                                            reequilibre(accueille);
                                        printf("Rééquilibre avec succés\n");
                                        quitd=1;
                                        }else {if(choice2==4){
                                            resinstallation_tickets(accueille,nbrcl);
                                            tickets=nbrcl;
                                        printf("Reinitialisation avec succés\n");
                                        quitd=1;



                                        }else if(choice2==5){
                                            quitd=1;
                                        }else{
                                        printf("choix invalide\n");
                                        }
                                        }
                                        }
                                        }
                                }
                           }else{
                           printf("Erreur de choix !\n");


                           }
                           }
             }
        }

      }
    return 0;
}
