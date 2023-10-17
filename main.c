#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lpers
{
	char nom[50];
	char prenom[50] ;
	int age;
	char genre;
	char email[50];
	struct lpers* next;
}
LPERS;

LPERS* rep[26]={NULL};


LPERS* creer_personne (char* nom, char* prenom, int age, char genre, char* email);
void ajouter_personne (LPERS* pers);
void supprimer_Lpers_from_nom (char* nom);
void afficher_Lpers_from_nom (char* nom);
void afficher_Lpers_from_age (int age);
void afficher_Lpers_from_lettre (char lettre);
void afficher_Lpers_avec_rang_from_nom (char* nom);
int calculer_nombre_personnes_from_nom (char* nom);
LPERS* chercher_personne_from_nom_et_rang (char* nom, int rang);
void modifier_personne (LPERS* pers, char* nom, char* prenom, int age, char genre, char* mail);
int initialisation(char *nom_fichier) ;

//-----------------------------------------------------------------------------------------//

LPERS* ajouter_personne_dans_liste(LPERS* liste, LPERS *nouveau);
LPERS* creer_personne (char* nom, char* prenom, int age, char genre, char* email);
void supprimer_personne_simple(LPERS** liste, LPERS* p_a_suppr);
void supprimer_personne (LPERS** liste, char* nom);
int numero_case(char prem_lttre);
void afficher_personne(LPERS* p);
void afficher_noms_liste(LPERS *liste, char* nom);//fonction affichant la liste sans rang
void afficher_noms_liste2(LPERS *liste, char* nom);//fonction qui affiche le rang des personnes
void afficher_liste(LPERS *liste);
void afficher_rep();
LPERS* creer_personne2 ();


//------------------------------------------------------------------------------------------//


void debut_de_projet();
void modification_personne();
void modification_precise_personne(LPERS *p);
int afficher_et_recuperer_choix_menu_accueil();
void afficher_suivant_nom();
void afficher_suivant_age();
void afficher_suivant_lettre();
void suppression();
int qui_vient_avant(LPERS *personne1, LPERS *personne2);

int main()
{
	int choix = 10 ;

	debut_de_projet();

	while( choix != 0){

		choix = afficher_et_recuperer_choix_menu_accueil();

		switch(choix){
			case 1:
				ajouter_personne(creer_personne2 ());
				break;
			case 2:
				modification_personne();
				break;
			case 3:
				suppression();
				break;
			case 4:
				afficher_rep();
				break ;
			case 5 :
				afficher_suivant_nom();
				break;
			case 6 :
				afficher_suivant_age();
				break ;
			case 7 :
				afficher_suivant_lettre();
				break;
			default :
				break ;
		}
	}
}



void debut_de_projet(){

	int retour = 1 ;
	char nom_fic[50];
	while( retour != 0 ){
		printf("-----------------------------------------------------------------------------------------------------------------------");
		printf("\nEcrivez le nom d'un fichier existant (sans oublier l'extension .txt), pour creer le repertoire a partir de ce fichier");
		printf("\nOu bien, vous pouvez aussi ecrire \"zero\" pour commencer a partir de zero, et creer tout votre repertoire vous meme...");
		printf("\n\nEcivez ici : ");
		scanf("%s", nom_fic);

		if( strcmp("zero", nom_fic) == 0 ){
			retour = 0 ;
		}else{
			retour = initialisation(nom_fic) ;
		}

	}
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("\n                               °°°°°°°°°°°°°°°° B I E N V E N U °°°°°°°°°°°°°°°°\n");
}


int initialisation(char *nom_fichier){

	FILE* fic ;
	char ligne[250] ;

	char nom[50];
	char prenom[50];
	int age = 0 ;
	char genre ;
	char email[80] ;

	fic = fopen(nom_fichier , "r") ;

	if(!fic)
	{
		printf("\nFichier introuvable ! (Verifier le nom du fichier ou l'extention)\n") ;
		return 1 ;
	}

	while(fgets (ligne , 250 , fic ))
	{
		//insertionLigne(& racine , ligne) ;
		sscanf(ligne, "%s %s %d %c %s", nom, prenom, &age, &genre, email);
		//printf("%s %s %d %c %s\n", nom, prenom, age, genre, email);
		ajouter_personne ( creer_personne (nom, prenom, age, genre, email) );
	}

	printf("\n****************************************** Le repertoire a ete bien creer ! *******************************************\n\n");

	fclose(fic) ;
	return 0 ;

}

int afficher_et_recuperer_choix_menu_accueil(){

	char reponse[10];

	while(1){
		printf("\nMENU, Tapez une commande suivant votre besoin : \n");
		printf("a    : pour ajouter une nouvelle personne dans le repertoire\n");
		printf("m    : pour modifier une personne du repertoire\n");
		printf("s    : pour supprimer les personnes ayant un nom donne\n");
		printf("af   : pour afficher toutes personnes du repertoire\n");
		printf("af-n : pour afficher les personnes ayant un nom donne\n");
		printf("af-a : pour afficher les personnes ayant un age donne\n");
		printf("af-l : pour afficher les personnes dont le nom commence par une lettre donnee\n");
		printf("q    : pour quitter le programme\nEcrivez ici : ");
		scanf("%s", reponse);

		if( strcmp(reponse, "a") == 0 ){
			return 1;
		}
		else if(strcmp(reponse, "m") == 0){
			return 2;
		}
		else if(strcmp(reponse, "s") == 0){
			return 3;
		}
		else if(strcmp(reponse, "af") == 0){
			return 4;
		}
		else if(strcmp(reponse, "af-n") == 0){
			return 5;
		}
		else if(strcmp(reponse, "af-a") == 0){
			return 6;
		}
		else if(strcmp(reponse, "af-l") == 0){
			return 7;
		}
		else if(strcmp(reponse, "q") == 0){
			return 0;
		}
		else ;
	}

	return 0 ;
}

void modification_personne(){

	LPERS* p_a_modifier = NULL ;
	LPERS* p_a_inserer = NULL;

	char nom[20];
	int nbre_p = 0 ;

	char n_nom[20];
	char n_prenom[20];
	int n_age = 0 ;
	char n_genre ;
	char n_email[30];

	int rang = 0 ;

	printf("################# MODIFICATION\n\nDonnez le nom de la personne a modifier : ");
	scanf("%s", nom);

	nbre_p = calculer_nombre_personnes_from_nom (nom);

	if ( nbre_p == 0){
		printf("\n*********** La personne que vous cherchez a modifier est introuvable !\n\n");
	}
	else{

        if ( nbre_p == 1){
            p_a_modifier = chercher_personne_from_nom_et_rang (nom, 1);
        }else{
            afficher_Lpers_avec_rang_from_nom (nom);
            printf("\nDonnez le rang de la personne : ");
            scanf("%d", &rang);

            p_a_modifier = chercher_personne_from_nom_et_rang (nom, rang);
        }

		//on cree une personne a partir de la personne à modifier !
        p_a_inserer = creer_personne (p_a_modifier->nom , p_a_modifier->prenom, p_a_modifier->age, p_a_modifier->genre, p_a_modifier->email) ;

        //On supprimer la personne à modifier dans la liste
        supprimer_personne_simple( &rep[ numero_case(nom[0]) ] , p_a_modifier);

        //On procede à la modification précise des champs s'il y'a lieu, suivant les choix de l'utilisateur;
        modification_precise_personne(p_a_inserer);

		//on passe par la fonction du model
		modifier_personne (p_a_inserer, p_a_inserer->nom, p_a_inserer->prenom, p_a_inserer->age, p_a_inserer->genre, p_a_inserer->email);

		//On ajoute la personne dans le liste
		ajouter_personne (p_a_inserer);

		printf("\n\n----------- Modification effectuee...\n\n");

	}
}

void modification_precise_personne(LPERS *p){

    char choix = 'z' ;
    int ok = 1 ;

    while(ok){

    	afficher_personne(p);

        printf("\nTaper n : changer nom | p : changer prenom | a : changer age | g : changer genre | e : changer email | t : j'ai termine les modifications : ");
        scanf(" %c", &choix);

        switch(choix){
            case 'n':{
                printf("\nEcrivez le nouveau nom : ");
                scanf("%s", p->nom);
                break ;
            }

            case 'p':{
                printf("\nEcrivez le nouveau prenom : ");
                scanf("%s", p->prenom);
                break ;
            }

            case 'a':{
                printf("\nEntrez le nouvel age : ");
                scanf("%d", &(p->age));
                break ;
            }

            case 'g':{
                printf("\nEntrez le nouveau genre : ");
                scanf(" %c", &(p->genre));
                break ;
            }

            case 'e':{
                printf("\nEntrez le nouvel email : ");
                scanf("%s", p->email);
                break ;
            }

            case 't':{
                ok = 0 ;
                break ;
            }

            default :{
				break;
			}
        }
    }

}

int calculer_nombre_personnes_from_nom (char* nom){
	LPERS *p = rep[ numero_case(nom[0]) ]  ;
	int cmpt = 0 ;

	for(; p != NULL ; p = p->next){
        if(strcmp( p->nom , nom) == 0){
        	cmpt ++ ;
		}
	}

	return cmpt ;
}

LPERS* chercher_personne_from_nom_et_rang (char* nom, int rang){
	LPERS *p = rep[ numero_case(nom[0]) ]  ;
	int cmpt = 0 ;

	for(; p != NULL ; p = p->next){
        if(strcmp( p->nom , nom) == 0){
        	cmpt ++ ;
        	if(cmpt == rang){
        		return p ;
			}
		}
	}

	return p ;
}

void modifier_personne (LPERS* pers, char* nom, char* prenom, int age, char genre, char* mail){
	strcpy(pers->nom , nom);
	strcpy(pers->prenom, prenom);
	pers->age = age ;
	pers->genre = genre ;
	strcpy(pers->email, mail);
}

void afficher_suivant_nom(){
	char nom[20];
	printf("\nDonnez le nom : ");
	scanf("%s", nom) ;
	afficher_Lpers_from_nom (nom);
}

void afficher_suivant_age(){
	int age ;
	printf("\nDonnez l'age : ");
	scanf("%d", &age) ;
	afficher_Lpers_from_age (age);
}

void afficher_suivant_lettre(){
	char lettre;
	printf("\nDonnez la lettre : ");
	scanf(" %c", &lettre) ;
	afficher_Lpers_from_lettre (lettre);
}

void afficher_rep(){
	int i = 0 ;
	printf("\n################# Affichage du repertoire\n\n");

	for(; i<26 ; i++){
		if(rep[i] != NULL){
			printf("------------------------------------------------- %c\n", 'A'+i);
			afficher_liste(rep[i]);
		}
	}

	printf("\n---------------------------------------------------\n");
}

void afficher_Lpers_from_age (int age){
	int i = 0 ;
	LPERS* p ;

	printf("-------------------------------------------------\n");

	for(; i<26 ; i++){
		if(rep[i] != NULL){

			for(p = rep[i] ; p != NULL ; p = p->next){
        		if(p->age == age){
        			afficher_personne(p);
				}
			}

		}
	}
}

void afficher_Lpers_from_nom (char* nom){
	afficher_noms_liste( rep[ numero_case(nom[0]) ] , nom) ;
}

void afficher_Lpers_avec_rang_from_nom (char* nom){
	afficher_noms_liste2( rep[ numero_case(nom[0]) ] , nom) ;
}

void afficher_noms_liste(LPERS *liste, char* nom){
	LPERS *p = liste ;
	printf("-------------------------------------------------\n");
	for(p = liste ; p != NULL ; p = p->next){
        if(strcmp( p->nom , nom) == 0){
        	afficher_personne(p);
		}
	}
}

void afficher_noms_liste2(LPERS *liste, char* nom){
	LPERS *p = liste ;
	int cmpt = 1 ;
	printf("-------------------------------------------------\n");
	for(p = liste ; p != NULL ; p = p->next){
        if(strcmp( p->nom , nom) == 0){
        	printf("************** %d\n", cmpt);
        	afficher_personne(p);
        	cmpt ++ ;
		}
	}
}

void afficher_Lpers_from_lettre (char lettre){
	printf("-------------------------------------------------\n");
	afficher_liste( rep[ numero_case(lettre) ] );
}

void afficher_liste(LPERS *liste){
	LPERS *p = liste ;
	for(p = liste ; p != NULL ; p = p->next){
        afficher_personne(p);
	}
}

void ajouter_personne (LPERS* pers){
	LPERS* nouveau = pers;
	rep[ numero_case( (nouveau->nom)[0]) ] = ajouter_personne_dans_liste( rep[ numero_case( (nouveau->nom)[0]) ] , nouveau ) ;
}

int numero_case(char prem_lttre){
	int val = prem_lttre ;
	if(val<='z' && val>='a'){
		return val-'a' ;
	}else if (val<='Z' && val>='A'){
		return val-'A' ;
	}
}

void suppression(){
	char nom_pers_a_suppr[20];
	printf("\nEcrivez le nom de la personne a supprimer : ");
	scanf("%s", nom_pers_a_suppr);

	if(calculer_nombre_personnes_from_nom (nom_pers_a_suppr) == 0){
		printf("\n\nIl n'existe personne de ce nom dans le repertoire !\n\n");
	}
	else{
		supprimer_Lpers_from_nom (nom_pers_a_suppr);
		printf("\n\nOperation effectuee !!\n\n");
	}
}

void supprimer_Lpers_from_nom (char* nom){
	supprimer_personne ( &rep[ numero_case(nom[0]) ]  , nom);
}

void supprimer_personne (LPERS** liste, char* nom){

    LPERS* p = NULL ;
    LPERS* suppr = NULL ;

    if((*liste) != NULL){
        if(strcmp((*liste)->nom, nom) == 0){
            suppr = (*liste) ;
            *liste = (*liste)->next ;
            free(suppr);
            supprimer_personne (&(*liste), nom) ;
        }else{
        	supprimer_personne (&((*liste)->next), nom) ;
		}
    }

}

void supprimer_personne_simple(LPERS** liste, LPERS* p_a_suppr){

    int ok = 1 ;
    LPERS* suppr = NULL ;
    LPERS* p ;

    if(  (strcmp((*liste)->nom, p_a_suppr->nom) == 0) && (strcmp((*liste)->prenom , p_a_suppr->prenom) == 0)  && (strcmp((*liste)->email, p_a_suppr->email) == 0) && ( ((*liste)->age) == (p_a_suppr->age) ) && (((*liste)->genre) == (p_a_suppr->genre))  ){
        suppr = (*liste) ;
        *liste = (*liste)->next ;
        free(suppr);
    }

    else{

        p = *liste;

        while(ok && ((p->next) != NULL)){

            if(  (strcmp((p->next)->nom, p_a_suppr->nom) == 0) && (strcmp((p->next)->prenom , p_a_suppr->prenom) == 0)  && (strcmp((p->next)->email, p_a_suppr->email) == 0) && ( ((p->next)->age) == (p_a_suppr->age) ) && (((p->next)->genre) == (p_a_suppr->genre))  ){
                suppr = (p->next) ;
                p->next = (p->next)->next ;
                free(suppr);
                ok = 0 ;
            }

            p = p->next ;
        }
    }
}

int qui_vient_avant(LPERS *personne1, LPERS *personne2){

    int retour1 = strcmp(personne1->nom, personne2->nom) ;
    int retour2 = strcmp(personne1->prenom, personne2->prenom);

    if( retour1 < 0){
        return -1 ;
    }else if(retour1 == 0){
        if( retour2 <= 0){
            return -1 ;
        }else{
            return 1 ;
        }
    }else{
        return 1 ;
    }
}


LPERS* ajouter_personne_dans_liste(LPERS* liste, LPERS* nouveau){

    LPERS *p ;

	if(liste == NULL){
		return nouveau ;
	}else{
        if ( qui_vient_avant(nouveau, liste) <= 0 ){
            nouveau->next = liste ;
            return nouveau ;
        }else{

            for(p = liste ; (p->next) != NULL ; p = p->next){
                if (  qui_vient_avant(nouveau, (p->next)) <= 0  ){
                    nouveau->next = p->next ;
                    p->next = nouveau ;
                    return liste ;
                }
            }

            p->next = nouveau ;
            return liste ;
        }

	}
}

LPERS* creer_personne (char* nom, char* prenom, int age, char genre, char* email){
    LPERS* nouveau = (LPERS*)malloc(sizeof(LPERS));
    strcpy(nouveau->nom, nom);
    strcpy(nouveau->prenom, prenom);
    nouveau->age = age;
    nouveau->genre = genre ;
    strcpy(nouveau->email, email);
    nouveau->next = NULL ;

    return nouveau ;
}

LPERS* creer_personne2 (){

	char nom[50];
	char prenom[50];
	int age;
	char genre;
	char email[50];
	struct lpers* next;


	printf("\nEntrez le nom : ");
	scanf("%s", nom);

	printf("Entrez le prenom : ");
	scanf("%s", prenom);

	printf("Entrez l'age : ");
	scanf("%d", &age);

	printf("Entrez le genre : ");
	scanf(" %c", &genre);

	printf("Entrez l'email : ");
	scanf("%s", email);

	printf("\n");

    return creer_personne (nom, prenom, age, genre, email) ;

}

void afficher_personne(LPERS* p){
    printf("\nNom : %s\nPrenom : %s\nAge : %d\nGenre : %c\nEmail : %s\n\n", p->nom, p->prenom, p->age, p->genre, p->email);
}


