#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>


struct joueur
{
    char nom[50];
};

///Couleur du texte
void couleur(int cTexte,int cFond)
{
        HANDLE H = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,cFond*16+cTexte);
}
///mene de la partie
int menu()
{
    int choix = 0;

    couleur(15,0);
    printf("Voici le menue du jeu\n");
    printf("Vous avez le droit de :\n");
    printf("       1 -Jouer\n");
    printf("       2 -Voir les regles du jeu\n");
    printf("       3 -Voir les credits\n");
    printf("       4 -Quitter\n");
    printf("Choisir entre 1/2/3/4 : \n");

    do
    {
        scanf("%d",&choix);
        if(choix<1 || choix>4)
        {
            couleur(4,0);
            printf("!!!!!!!!!! Valeur Inconnue !!!!!!!!!!\n");
            printf("!!!!!!!!!!   Recommencez   !!!!!!!!!!\n");
        }

    }while(choix<1 || choix>4);


    return choix;
}

///remplir le nom des joueurs
void remplissage(struct joueur *cas, int num)
{
    printf("Entrer le nom du joueur %d: \n",num);
    scanf("%s",&cas->nom);
    fflush(stdin);
 }
///affichage regle
void regle()
{
    int fin=0;
    do
    {
        couleur(7,0);
        printf("Le jeu ce joue a deux, vous avez n nombre d'allumettes\n");
        printf("A tour de role, vous devez enlever entre 1 a 3 allumettes\n");
        printf("Le perdant est celui qui retire la derniere allumettes\n");
        printf("Attention il existe 3 niveaux de difficultées\n");
        printf("Si jamais vous arrivez a reussi a battre le dernier niveau\n");
        printf("Contactez moi par mail a : bermond.moselle@outlook.com\n");
        printf("\n");
        printf("                      ************************                      \n");
        printf("Appuyer sur 1 pour quitter : ");
        scanf("%d",&fin);
        printf("\n");
        system("cls");
    }while(fin == 0);

}

///affichage credit
void credit()
{
    int fin = 0;
    do
    {
        couleur(6,0);
        printf("\n");
        printf("                                ************************                          \n");
        printf("            /////////////////////////////////////////////////////////////////////   \n");
        printf("                                ************************                          \n");
        printf("                         *Developpez par Bermond Cedric Maxence*                          \n");
        printf("                                ************************                          \n");
        printf("            /////////////////////////////////////////////////////////////////////   \n");
        printf("                                ************************                          \n");
        printf("\n");
        printf("Appuyer sur 1 pour quitter : ");
        scanf("%d",&fin);
        printf("\n");
        system("cls");
    }while(fin == 0);
}

///choix du niveau
int level()
{
    int niveau;
    do
    {
        printf("Choisir le niveau de difficulte : \n");
        scanf("%d",&niveau);
    }while(niveau<1 || niveau>3 );
    fflush(stdin);

    return niveau;
}

///affichage des allumettes
void display(int valeur, char *tab)
{
    for(int i=0;i<valeur;i++)
        {
            ///afficher le nombre d'allumettes
            couleur(12,0);
            printf("%c ",tab[i]);
        }
        couleur(1,0);
        printf("\t il reste %d allumettes\n",valeur);
        printf("\n");
        fflush(stdin);
}
///enlever le nombre d'allumette
int nombre(struct joueur *tour, int qui, int allumettes)
{
    int valeur;
    do
    {
        couleur(15,0);
        printf("joueur : %s combien d'allumettes voulez vous retirer ?  ",tour[qui]); ///affichage des allumettes
        scanf("%d",&valeur);

        if(valeur<0 || valeur>3)  ///blindage du nombres d'allumettes à enlever
        {
            printf("valeur non valide\n");
        }

        if(allumettes == 1 && valeur>1)
        {
            printf("le nombre a enlever est  pas valide : \n");
            do
            {
                printf("joueur : %s combien d'allumettes voulez vous retirer ?  ",tour[qui]); ///affichage des allumettes
                scanf("%d",&valeur);

            }while(valeur>1);
        }

    }while(valeur<0 || valeur>3);

    return valeur;
}

/// Ordi
int tourOrdi(struct joueur *tour, int qui)
{
    srand(time(NULL));
    int valeur, alea = rand()%3+1;
    do
    {
        couleur(15,0);
        printf("joueur : %s combien d'allumettes voulez vous retirer ?  ",tour[qui]); ///affichage des allumettes
        valeur = alea;
        printf("%d",valeur);

        if(valeur<0 || valeur>3)  ///blindage du nombres d'allumettes à enlever
        {
            printf("valeur non valide\n");
        }

    }while(valeur<0 || valeur>3);

    return valeur;
}
///afficher le tableau des resusltats
void resultat(struct joueur *res, int taille)
{
    couleur(9,0);
    printf("le gagnant est : \n");
    printf("\n");
    printf("                                ************************                          \n");
    printf("            ///////////////////////////////////////////////////////////////////// \n");
    printf("                                ************************                          \n");
    couleur(4,0);
    printf("                                       ***%s***                        \n",res[taille].nom);
    couleur(9,0);
    printf("                                ************************                          \n");
    printf("            ///////////////////////////////////////////////////////////////////// \n");
    printf("                                ************************                          \n");
    printf("\n");
}

int main()
{
    int choix=0, niveau=0,fin=0, nombreA=30, enlever=0, jouer=0, alea = rand()/(RAND_MAX+1.0);
/// les joueurs
    struct joueur bibliotheque[2];
///Nombre d'allumette
    char allumette[30] = {'|','|','|','|','|','|','|','|','|',
                          '|','|','|','|','|','|','|','|','|','|',
                          '|','|','|','|','|','|','|','|','|','|','|','|'};
///initialisation de l'horloge
    srand(time(NULL));

    couleur(3,0);
    printf("                                    **********************                      \n");
    printf("                                    * Jeu des allumettes *                      \n");
    printf("                                    **********************                      \n");
    printf("                        Bonjour et bienvennue dans le jeu des allumettes       \n");
    printf("\n");

    do
    {
        choix = menu();
        switch(choix)
        {
            case 1:
                break;
            case 2:
                regle();///afficher les regles
                break;
            case 3:
                credit();/// afficher les credits
                break;
            case 4:
                printf("Au revoir\n"); ///quitte le programme
                return EXIT_SUCCESS;
                break;
        }
    }while(choix != 1);

    do
    {
        niveau = level();
        if(niveau == 1)
        {
            for(int i=0;i<2;i++)///remplis le nom des joueurs
            {
                remplissage(&bibliotheque[i], i);
            }

            jouer = alea; /// pour jouer à tour de role

            do ///partie de niveau 1
            {
                display(nombreA,&allumette); //affiche le nombre d'allumette

                ///pour faire tourner les joueur
                if(jouer == 1)
                {
                    jouer = 0;
                }
                else
                {
                    jouer = 1;
                }
                enlever = nombre(&bibliotheque, jouer, nombreA); //retire le nombre d'allumette
                nombreA = nombreA-enlever;//retire une valeur

            }while(nombreA>0);

            if(jouer == 1)
            {
                resultat(&bibliotheque, 0);
            }
            else
            {
                resultat(&bibliotheque, 1);
            }

            printf("voulez vous recommencer?(1 = oui, 0 = non)\n");
            scanf("%d",&fin);
            nombreA = 30;
        }
        else if(niveau == 2)
        {
            remplissage(&bibliotheque[1], 1);
            strcpy(bibliotheque[2].nom,"*Ordi*");

            do ///partie de niveau 2
            {
                display(nombreA,&allumette); //affiche le nombre d'allumette

                ///pour faire tourner les joueur
                if(jouer == 1)
                {
                    enlever = nombre(&bibliotheque, jouer, nombreA); //retire le nombre d'allumette
                    jouer = 0;
                }
                else
                {
                    enlever = tourOrdi(&bibliotheque,jouer);
                    jouer = 1;
                }

                nombreA = nombreA-enlever;//retire une valeur
                printf("\n");

            }while(nombreA>0);

            if(jouer == 1)
            {
                resultat(&bibliotheque, 1);
            }
            else
            {
                resultat(&bibliotheque, 0);
            }

            printf("voulez vous recommencer?(1 = oui, 0 = non)\n");
            scanf("%d",&fin);
            nombreA = 30;
        }
    }while(fin == 1);
    return 0;
}
