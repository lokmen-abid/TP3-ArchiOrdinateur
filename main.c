//SISSAOUI HAITHEM CODE PERMANENT UQTR :SISH2735****
//ABID LOKMEN CODE PERMANENT UQTR :ABIL1933****
//DEROUICHE AHMED CODE PERMANENT UQTR : DERA6431****

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//declaration des variables et structure
typedef unsigned char  UCHAR;
struct IMAGERAW
{
    int hauteur;
    int largeur;
    UCHAR * image;
};
typedef struct IMAGERAW IMAGE;


// la fonction qui permet la lecture de l'image � crypt�e
IMAGE *lire_image()
{
    IMAGE *im;
    FILE *fpI;
    //ouvrir le fichier en lecture
    fpI = fopen("benji.raw","rb");
    if (fpI == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
    }
    //Reserver un espace memoire pour  im
    im = (IMAGE *)malloc(sizeof(IMAGE));
    im->largeur = 1690;
    im->hauteur = 1409;
    im->image = (UCHAR *) malloc(im->hauteur*im->largeur);
    //Lire l�image sur le disque
    fread(im->image,sizeof(UCHAR),im->hauteur*im->largeur,fpI);
    //fermer le fichier
    fclose(fpI);
    //RETOURNER LE POINTEUR SUR IMAGE
    return(im);

}

// La fonction qui permet le cryptage et le d�cryptage d'image  avec un fonction de codage XOR.
IMAGE *crypter_decrypter(IMAGE*im)
{
    int L,H,m,n;
    // Demander et valider la valeur de la cl� entre 0 et 255
    printf("Entrez le cle de cryptage/decryptage (entre 0-255) : ");
    unsigned int cle;
    scanf("%u",&cle);
    while (cle < 0 || cle > 255)
    {
        printf("Entrez le cle de cryptage/decryptage (entre 0-255) : ");
        scanf("%u", &cle);
    }
    //Demander l�ordre de parcours de la matrice (rang�e ou colonne)
    printf("Tapez 1 si vous voulez faire un parcours par colonne et tapez 0 si par rangee : ");
    unsigned int parcours;
    scanf("%u",&parcours);

    // Acces avec positionnement spatial dans une image
    L = im->largeur; // largeur de l�image
    H = im->hauteur; // hauteur de l�image
    if(parcours)
    {
        for(m=0; m<H; m++) // Acces avec positionnement
            for(n=0; n<L; n++) // Parcours par rangee
                im->image[m*L+n] = im->image[m*L+n]^cle; /*XOR*/
    }
    else if(!parcours)
    {
        for(n=0; n<L; n++) // Acces avec positionnement spatial
            for(m=0; m<H; m++) // Parcours par colonne
                im->image[m*L+n] = im->image[m*L+n]^cle; /*XOR*/
    }
}

// La fonction qui permet la sauvegarde de l'image crypt�e ou d�crypt�e
void ecrire_image(IMAGE *imageD)
{

    FILE *fpD;
    // Ouverture de fichier
    fpD = fopen("Decript.raw","wb");
    //Ecriture de fichier
    fwrite(imageD->image,sizeof(UCHAR),imageD->hauteur*imageD->largeur,fpD); // voir si fwrite() retourne une valeur valide
    //Fermeture de fichier
    fclose(fpD);


}

int main()
{
// declaration de pointeur Pour la structure image
    IMAGE *Im;
// Fonction pour mesurer le temps d'execution
    clock_t debut = clock();

// lecture de l'image cryptee
    Im = lire_image() ;

// Cryptage de l'image
    crypter_decrypter(Im);

// Sauvgarde de l'image cryptee L�IMAGE CRYPTEE
    ecrire_image(Im);

    clock_t fin = clock();
// calcule et affichage de temps
    double tempsExecution = (double)(fin - debut) / CLOCKS_PER_SEC;
    printf("Temps d'execution : %f secondes\n", tempsExecution);



//  Liberer la memoire
    free(Im->image);
    free(Im);

    printf("\n* L'image a ete bien crypte * \n");
    return 0;
}


