#include <stdio.h>
#include <stdlib.h>

// This constant can be avoided by explicitly
// calculating height of Huffman Tree
#define MAX_TREE_HT 100

//Structure de l'arbre pour les noeuds
struct noeuds
{
    char uneDonnee;                                     //Caractére entrer par l'utilisateur
    unsigned frequence;             	                //Occurence des caractere stocké dans cette variable
    struct noeuds *gauche, *droite;                     // gauche and droite child of this node
};

//Pour regrouper les arbres miniatures
struct regroupement
{
    unsigned taille;                                    // Taille pour les noeuds petits
    unsigned capacite;                                  // Capacité des noeuds petits
    struct noeuds** tableau;                            // Pointeur de types noeud
};

//fonction permettant l'allocation dynamique d'un nouveau noeud
struct noeuds* nouveauNoeuds(char uneDonnee, unsigned frequence)///
{
    struct noeuds* x = (struct noeuds*)malloc(sizeof(struct noeuds));

    x->gauche = x->droite = NULL;
    x->uneDonnee = uneDonnee;
    x->frequence = frequence;

    return x;
}

// fonction permettant d'obtenir la capacirté minimal
struct regroupement* creation(unsigned capacite)///
{
    struct regroupement* reg = (struct regroupement*)malloc(sizeof(struct regroupement));

    // la taille est de  0
    reg->taille = 0;

    reg->capacite = capacite;

    reg->tableau = (struct noeuds**)malloc(reg->capacite * sizeof(struct noeuds*));
    return reg;
}

//creation d'un nouveu noeud dans laquelle on va insérer tout les caractere
//contenue dans le tableau d'entree, la taille est initialisé avec le noeud minimum egal à la capacité
struct regroupement* creationContruction(char uneDonnee[],int frequence[], int taille)///
{
    struct regroupement* reg = creation(taille);

    for (int i = 0; i < taille; ++i)
    {
        reg->tableau[i] = nouveauNoeuds(uneDonnee[i], frequence[i]);
    }
    reg->taille = taille;
    contructeur(reg);

    return reg;
}

// Extraction de la valeur minimum d'un noeud
struct noeuds* extractionNoeudMini(struct regroupement* reg)
{
    struct noeuds* x = reg->tableau[0];
    reg->tableau[0] = reg->tableau[reg->taille - 1];

    --reg->taille;
    tasMinimum(reg, 0);

    return x;
}

//fonction principal qui va permettre de construire l'arbre huffman
struct noeuds* contructionArbre(char uneDonnee[],int frequence[], int taille)///
{
    struct noeuds *gauche, *droite, *haut;

    //Dans un premier temps on va creer un tas minimum dont la capacité sera égal à la taille
    struct regroupement* reg = creationContruction(uneDonnee, frequence, taille);

    //iteration tant que cela n'est pas égal à un
    while (!laTaille(reg))
    {

        //on va extraire deux membre avec le plus petit occurence
        gauche = extractionNoeudMini(reg);
        droite = extractionNoeudMini(reg);

        //Creer un nouveau noeud qui aura pour occurence la somme des occurence les plus faible
        //# correspond aux caractere dont l'occurence est la somme de tout les occurence
        haut = nouveauNoeuds('#', gauche->frequence + droite->frequence);
        haut->gauche = gauche;
        haut->droite = droite;
        insertMinHeap(reg, haut);
    }

    //Le noeud restant va correspondre à la racine
    return extractionNoeudMini(reg);
}

// Voir si les fonction corresspondent à une somme des occurences
int branche(struct noeuds* fin)///
{
    return !(fin->gauche) && !(fin->droite);
}

//On continue le programme tant que la valeur n'est pas égale 1
int laTaille(struct regroupement* reg)///
{
    return (reg->taille == 1);
}

// Echanger deux valeurs selon leurs occurence
void echangerValeurs(struct noeuds** a,struct noeuds** b)///
{
    struct noeuds* x = *a;
    *a = *b;
    *b = x;
}

//pour savoir si les valeurs vont à droite ou à gauche
void tasMinimum(struct regroupement* reg, int unIndex)///
{
    int lpp = unIndex;
    int gauche = 2 * unIndex + 1;
    int droite = 2 * unIndex + 2;

    if (gauche < reg->taille && reg->tableau[gauche]->frequence < reg->tableau[lpp]->frequence)
    {
        lpp = gauche;
    }

    if (droite < reg->taille && reg->tableau[droite]->frequence < reg->tableau[lpp]->frequence)
    {
        lpp = droite;
    }

    if (lpp != unIndex)
    {
        echangerValeurs(&reg->tableau[lpp],&reg->tableau[unIndex]);
        tasMinimum(reg, lpp);
    }
}

//inserer un nouveau par ordre croissant
void insertMinHeap(struct regroupement* reg,struct noeuds* minHeapNode)
{
    ++reg->taille;
    int i = reg->taille - 1;

    while (i && minHeapNode->frequence < reg->tableau[(i - 1) / 2]->frequence)
    {
        reg->tableau[i] = reg->tableau[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    reg->tableau[i] = minHeapNode;
}

//construire un noeud
void contructeur(struct regroupement* reg)///
{
    int n = reg->taille - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
    {
        tasMinimum(reg, i);
    }
}

// affichage des caractre à partir d'une taille donne par la variable n
void affichageCaractere(int arr[], int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        printf("%d", arr[i]);
    }
    printf("\n");
}

// affichage du code à partir du tableau
void afficherCode(struct noeuds* fin, int arr[],int haut)///
{
    // on attribut la valeur 0
    if (fin->gauche)
    {
        arr[haut] = 0;
        afficherCode(fin->gauche, arr, haut + 1);
    }
    // on atribut la valeur de 1
    if (fin->droite)
    {
        arr[haut] = 1;
        afficherCode(fin->droite, arr, haut + 1);
    }

    // si c'est une branche et elle contient des valeurs
    // on affiche le caractere et ça valeur
    if (branche(fin))
    {
        printf("%c: ", fin->uneDonnee);
        affichageCaractere(arr, haut);
    }
}

// cette fonction est utiliser pour construire l'arbre et afficher l'arbre
void fonctionHuffman(char uneDonnee[], int frequence[], int taille)
{
    struct noeuds* fin = contructionArbre(uneDonnee, frequence, taille);            //appel de la fonction pour construction Arbre
    int arr[taille], haut = 0;
    afficherCode(fin, arr, haut);
}

int main()
{
    char tableau[200];
    char alphabet[27] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' '};
    //char alphabet[27] = {97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,32};
    char *arr, *tableau2, caractere;
    int *frequence,nombre, compt=0, l, compt2=0;

    printf("saisir une phrase :\n");
    fgets(tableau, 200, stdin);

    l = strlen(tableau);

    frequence = (int*)malloc((l-1)*sizeof(int));
    tableau2 = (char*)malloc((l-1)*sizeof(char));

    for (int i=0; tableau[i]!='\0'; i++)                    //conversion des caractère en minuscule
    {
        if(tableau[i] >= 'A' && tableau[i] <= 'Z')
        {
            tableau[i] = tableau[i] +32;
        }
    }
                                                            //remplir le tableau final et de fréquence
                                                            //on fait parcourir le tableau de caractere
    for(int j=0; j<28; j++)
    {
        caractere = alphabet[j];                            //la valeur parcourut à l'instant est stockée dans ma variable
        for(int i=0; i<l; i++)
        {
            if(tableau[i] == caractere)                     //si la chaine de caractère correspond à la variable
            {
                nombre++;
            }
        }

        if(nombre>0)                                     //on affiche le nombre d'occurence et on attribut les valeur au nouveau tableau
        {
            if(caractere>='a' && caractere<='z' || caractere == ' ')
            {
                tableau2[compt]=caractere;
                frequence[compt]=nombre;
                compt++;
                compt2++;
            }
        }
        nombre=0;
    }

    arr = (char*)malloc(compt2*sizeof(char));            //création d'un nouveau tableau sans les caractere bizarret
    l=compt2;

    for(int i=0; i<l; i++)
    {
        arr[i] = tableau2[i];
    }
    fonctionHuffman(arr,frequence,l);

    return 0;
}
