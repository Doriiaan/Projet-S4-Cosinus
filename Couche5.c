#include "header.h"
#include "Couche1.h"
#include "Couche2.h"
#include "Couche3.h"
#include "Couche4.h"
#include "Couche5.h"
#include "term_canon.h"
#include "affichage_logo.h"
extern virtual_disk_t *virtual_disk_sos;

#define FIRST_TIME 0
#define TEST_ADD_INODE 1
#define TEST_DELETE_INODE 0
#define TEST_ADD_USER 1
#define TEST_DELETE_USER 0
#define TEST_SESSION 0


int interprete = 1;

/**
* @brief retire le caractere \n lors d'une saisie de login avec fgets
* @param char*  chaine de caractere
* @return void
**/
void enlever_retour_ligne(char *chaine){

    int taille = strlen(chaine);
    if(chaine[taille-1] == '\n')
    chaine[taille-1] = '\0';
}

/**
* @brief retire les 2 caracteres @@ pour l'edition d'un fichier
* @param char*  chaine de caractere
* @return void
**/

void enlever_caractere_fin(char *chaine){

    int taille = strlen(chaine);
    if(chaine[taille-3] == '@' && chaine[taille-2]=='@'){
        chaine[taille-3] = '\0';
    }
}

/**
* @brief Affiche la liste des utilisateurs du systeme
* @param NULL
* @return void
**/
void listusers(){

    printf("Nombre d'utilisateurs : %d\n" , virtual_disk_sos->super_block.number_of_users );
    for(uint i = 0 ; i<virtual_disk_sos->super_block.number_of_users ; i++){
        if(virtual_disk_sos->users_table[i].login==NULL){
            i++;
        }
        printf("%s\n"  ,virtual_disk_sos->users_table[i].login);
    }
}


/**
* @brief Affiche la liste des fichiers et leurs descriptions
* @note affichage de toutes les donnes de l'inode
* @param NULL
* @return void
**/
void ls_l(){
    for (uint i = 0; i < virtual_disk_sos->super_block.number_of_files ; i++){
        printf("%s | %d | %d | %d | %d | %s | %s | %d | %d\n " , virtual_disk_sos->inodes[i].filename , virtual_disk_sos->inodes[i].size , virtual_disk_sos->inodes[i].uid ,
        virtual_disk_sos->inodes[i].uright , virtual_disk_sos->inodes[i].oright , virtual_disk_sos->inodes[i].ctimestamp , virtual_disk_sos->inodes[i].mtimestamp ,
        virtual_disk_sos->inodes[i].nblock , virtual_disk_sos->inodes[i].first_byte );
        printf("\n");

    }
} // je referais l'affichage plus tard


/**
* @brief Affiche le contenu d'un fichier du systeme
* @param char* filename : Nom du fichier à ecire sur stdout
* @note utilise la fonction read_file de la couche 4 pour afficher le contenu du fichier filename
* @return int : 1 si le fichier a été trouvé et affiché, 0 en cas d'erreur
**/
int cat(char* nom_fichier){
    if(search_file_inode(nom_fichier)==-1){
        printf("Fichier inexistant");
        return 0;
    }
    uint user = get_session();
    if(strcmp(nom_fichier , "passwd")==0 && user != 0){
        printf("Impossible d'afficher ce fichier\n");
        return 0;
    }
    file_t *file = malloc(sizeof(file_t));
    read_file(nom_fichier , file);
    printf("%s\n" , file->data);
    return 1;
}

/**
* @brief vide le terminal
* @param aucun
* @note utilise un printf specifique pour effacer le terminal
* @return : void
**/
void clear(){
    printf ("\033[H\033[J");
    disp_design_os(false);

}

/**
* @brief ajoute un utilisateur au systeme
* @param NULL
* @note demande un login a l'utilisateur root et si ce login n'est pas dans la table , l'user est ajouté
* @note  seul root a acces a cette commande
* @return int
**/

int adduser(char* login){
    if(get_session()!=0){
        printf("Commande réservé a l'utilisateur root\n");
        return 0;
    }
    int verif = 0;
    int confirmer = 0;
    int pos;
    pos = get_unused_user();

    if(pos==-1){
        printf("Nombre d'utilisateurs max atteint\n");
        return 0;
    }
    char existe[FILENAME_MAX_SIZE];
    char confirm[FILENAME_MAX_SIZE];
    char password[FILENAME_MAX_SIZE];
    int num = 0;
    int login_existe = 0;
     if(search_login(login)==-1)
          verif=1;
   
     if(search_login(login)!=-1){

          while(!login_existe){
               printf("Ce pseudo est déja utilisé veuillez en selectionner un autre\n");
            	printf("Saisissez un login : ");
            	fgets(existe , FILENAME_MAX_SIZE , stdin);
                if(search_login(existe)!=-1){
                	printf("Ce pseudo est déja utilisé veuillez en selectionner un autre\n");
            		printf("Saisissez un login : ");
            
        }

        else{
            login_existe=1;
        }
    }
        }

    printf("Saisissez un mot de passe : " );
    fgets(password , FILENAME_MAX_SIZE , stdin);
    printf("Veuillez confirmer le mot de passe: ");
    fgets(confirm , FILENAME_MAX_SIZE , stdin);
    enlever_retour_ligne(password);
    enlever_retour_ligne(confirm);

    while(!confirmer){

        if(strcmp(confirm , password)!=0){
            num++;
            printf("Les mot de passes ne correspondent pas , veuillez retaper le mot de passe :\n");
            fgets(confirm , FILENAME_MAX_SIZE , stdin);
            enlever_retour_ligne(confirm);
            printf("Tentative numero %d de validation\n" , num);
            if(num==3){
            	printf("Erreur creation user veuiller retaper la commande\n");
            	return 0;
            }
        }

        if(strcmp(confirm , password)==0){
        	if(verif)
            	add_user(login , password);
            	if(!verif)
            	add_user(existe , password);
            printf("Creation de l utilisateur %s reussi \n" , virtual_disk_sos->users_table[pos].login);
            confirmer = 1;
            return 1;

        }
    }
    return 0;
}

/**
* @brief affiche le proprietaire et les droits du fichier en parametre
* @note  fonction inutile mais pratique pour avoir un apercu
* @param char* : nom de fichier
* @return int 1 si tout se passe bien (si le fichier existe)
**/
int getdroit(char* nom_fichier){
    int pos = search_file_inode(nom_fichier);
    int prop = virtual_disk_sos->inodes[pos].uid;

    if(pos==-1){
        printf("Fichier inexistant , info indisponible\n");
        return 0;
    }

    printf("Proprietaire du fichier = %s\n" , virtual_disk_sos->users_table[prop].login);
    printf("\n");
    printf("Droit des utilisateurs = %d\n" , virtual_disk_sos->inodes[pos].oright);
    printf("\n");
    printf("Droit du proprietaire = %d\n" , virtual_disk_sos->inodes[pos].uright);
    printf("\n");
    return 1;
}

/**
* @brief cree le fichier nom_fichier , s'il depasse la taille max on renvoie une erreur
* @param char* : nom de fichier
* @note ajouter de la valeur 3 au debut pour simplifier la verification java
* @return int 1 si tout se passe bien , 0 si le fichier ne peut pas etre crée
**/
int cr(char* nom_fichier){

    if(strlen(nom_fichier)>FILENAME_MAX_SIZE){
        printf("Un fichier ne peut contenir que %d caractere maximum\n" , FILENAME_MAX_SIZE);
        return 0;
    }

    file_t file;
    file.size = 1;
    file.data[0]=3;
    write_file(nom_fichier , file);
    getdroit(nom_fichier);
    return 1;

}

/**
* @brief modifie le fichier s'il existe , ou le crée et ecrit dedans il existe pas
* @note  2048 caracteres max a ecrire , saisir @@ pour quitter
* @param char* : nom de fichier
* @return int 1 si tout se passe bien (si le fichier existe)
**/

int edit_file(char* filename){
    file_t* ecrase = malloc(sizeof(file_t));
        file_t* file = malloc(sizeof(file_t));
    int pos = search_file_inode(filename);
    read_file(filename,ecrase);
    printf("%s " , ecrase->data) ;
   
    if(pos==-1){
        cr(filename);
    }
    if(!Term_non_canonique())
    return 1;

    char c;
    int fin = 0;

    do {
        printf ("\033[H\033[J");
        printf("*****EDIT*****\n\n");
        printf("Tapez @@ à tout moment pour arreter la saisie\n\n");

        for (int i = 0; i < (int)file->size; i++) {
            if((int)file->data[i]+(int)file->data[i+1]==128){
                fin = 1;
            }
            printf("%c", file->data[i]);
        }

        c=fgetc(stdin);

        switch (c) {

            /*case '@':
            fin = 1;
            break;*/
            case '\b':
              if(file->size > 0)
                file->size--;
              printf ("\033[H\033[J");
              break;
            default:
              file->data[file->size] = c;
              file->size++;
        }

    } while(!fin && file->size < MAX_FILE_SIZE);
    printf("\n");
    enlever_caractere_fin((char*)file->data);
    write_file(filename , *file);
    if(!Term_canonique())
    return 1;

    return 1;
}
/**
* @brief supprimer un user du systeme
* @note  utilisable que par root et si le login existe
* @param char* nom de login
* @return int 1 si tout se passe bien (si l'user connecte est le root et si le login existe) , 0 sinon
**/

int rmuser(char * nom_login){
    int pos;
    pos = search_login(nom_login);
    if(get_session()!=0){
        printf("Commande réservé a l'utilisateur root .\n");
        return 0;
    }

    if(pos==-1){
        printf("Login inexistant\n");
        return 0;
    }

    if(pos==0){
        printf("Impossible de supprimer l'utilisateur root\n");
        return 0;
    }

    delete_user(nom_login);
    return 1;

}

/**
* @brief deconnecte l'user
* @note : l'user se deconnecte et met son id a -1
* @param NULL
* @return int 1 si tout se passe bien
**/

int deconnexion(){
    del_session();
    return 1;
}

/**
* @brief Affiche la liste des fichiers et leurs descriptions
* @note n'affiche que le nom du fichier et sa taille
* @param void
* @return void
**/

void ls(){
    for (int i = 0; i < (int)virtual_disk_sos->super_block.number_of_files ; i++){
        printf("%s \t  %d \n  " , virtual_disk_sos->inodes[i].filename , virtual_disk_sos->inodes[i].size );
    }
}

/**
* @brief ferme l'interprete et sauvegarde le systeme sur le disque
* @param NULL
* @return void
**/

void quit(){
    interprete = 0;
    save_disk_sos();
}

/**
* @brief efface un fichier du systeme si l'user connecte a les droits (root ou proprietaire du fichier)
* @note impossible d'effacer le fichier de quelqu'un d'autre
* @param char* nom_fichier
* @return int 1 si l'user a les droits et le fichier existe , 0 sinon
**/

int rm(char* nom_fichier){
    int pos = search_file_inode(nom_fichier);
    uint user = get_session();

    if(pos==-1){
        printf("Nom de fichier inexistant\n");
        return 0;
    }

    if(virtual_disk_sos->inodes[pos].uid==user){
        if(delete_file(nom_fichier)==-1){
            printf("Erreur suppression\n");
            return 0;
        }
        return 1;
    }

    if(virtual_disk_sos->inodes[pos].uid!=user && virtual_disk_sos->inodes[pos].oright==3){
        if(delete_file(nom_fichier)==-1){
            printf("Erreur suppression\n");
            return 0;
        }

        return 1;
    }
    else{
        printf("Vous n'avez pas les droits pour supprimer le fichier %s\n" , nom_fichier);
        return 0;
    }
    return 0;
}

/**
* @brief change les droits pour les autres utilisateurs si l'user connecte a les droits (root ou proprietaire)
* @note: impossible de changer les droits si le fichier ne nous appartient pas .
* @param char* nom du fichier , int droit (0 , 1 , 2 , 3)
* @return int 1 si l'user connecte a les droits et que le fichier existe , 0 sinon
**/

int chmod(char* nom_fichier , int droit){
    int pos = search_file_inode(nom_fichier);
    uint user = get_session();

    if(pos==-1){
        printf("Fichier inexistant\n");
        return 0;
    }

    if(droit>3){
        printf("Le droit maximum est 3 pour lecture et ecriture\n");
        return 0;
    }

    if(virtual_disk_sos->inodes[pos].uid==user && virtual_disk_sos->inodes[pos].uright==3){
        virtual_disk_sos->inodes[pos].oright=droit;
        getdroit(nom_fichier);
        return 1;
    }

    if(user==0){
        virtual_disk_sos->inodes[pos].oright=droit;
        getdroit(nom_fichier);
        return 1;
    }

    else{
        printf("Vous ne pouvez pas changez les droits du fichier %s\n" , nom_fichier);
        return 0;
    }

    return 0;
}

/**
* @brief change le proprietaire d'un fichier si l'user connecte a les droits (root ou proprietaire)
* @note impossible de changer le proprietaire si l'user connecte ne l'est pas ou si l'user connecte n'est pas root
* @param char * nom du fichier , char* login du nouveau proprietaire
* @return int si l'user est le root ou le proprietaire du fichier , si le fichier existe et si le login existe , 0 sinon
**/

int chown(char* nom_fichier , char* login){
    int pos = search_file_inode(nom_fichier);
    uint user = get_session();
    uint log = search_login(login);
    int logi = search_login(login);

    if(pos==-1){
        printf("Fichier inexistant\n");
        return 0;
    }

    if(virtual_disk_sos->inodes[pos].uid==log){
        printf("%s est déja le proprietaire du fichier\n" , login);
        return 0;
    }

    if(logi==-1){
        printf("Login inexistant\n");
        return 0;
    }

    if(virtual_disk_sos->inodes[pos].uid==user || user==0){
        virtual_disk_sos->inodes[pos].uid=log;
        getdroit(nom_fichier);
        return 1;
    }

    return 0;
}

/**
* @brief Affiche la liste des commandes executables
* @note: a taper a tout moment pour obtenir la liste
* @param void
* @return void
**/

void help(){
    printf("\n");
    printf("cat <nom de fichier> : affiche a  l ecran le contenu d un fichier si l utilisateur a les droits\n");
    printf("\n");
    printf("rm <nom de fichier> : supprime un fichier du systeme si l utilisateur a les droits\n");
    printf("\n");
    printf("cr <nom de fichier> : cree un nouveau fichier sur le systeme, le proprietaire est l utilisateur.\n");
    printf("\n");
    printf("edit <nom de fichier> : edite un fichier pour modifier son contenu si l utilisateur a les droits\n") ;
    printf("\n");
    printf("load <nom de fichier> : copie le contenu d un fichier du systeme hote sur le systeme avec le meme nom\n ");
    printf("\n");
    printf("store <nom de fichier> : copie le contenu d un fichier du systeme sur hote avec le meme nom\n");
    printf("\n");
    printf("chown <nom de fichier> <login autre utilisateur> change le proprietaire d un fichier\n");
    printf("\n");
    printf("chmod <nom de fichier> <droit> change les droits d’un fichier pour tous les autres utilisateurs\n");
    printf("\n");
    printf("listusers : affiche la liste des utilisateurs du systeme\n");
    printf("\n");
    printf("adduser : Ajouter un utilisateur\n");
    printf("\n");
    printf("rmuser : Supprimer un utilisateur\n");
    printf("\n");
    printf("quit : Quitter le sytème\n");
    printf("\n");
    printf("exit : Quitter la session en cours\n");
    printf("\n");
    printf("clear : efface le contenu du terminal\n");
    printf("\n");
}

/**
* @brief charge un fichier du systeme sur l'ordinateur de l'host_file
* @note: le fichier aura le meme nom que le fichier du systeme
* @param char* nom_du_fichier a transferer
* @return int si le fichier existe et que le transfert s'est bien passé , 0 sinon
**/

int store(char* filename){
    int pos = search_file_inode(filename);

    if(pos==-1){
        printf("Fichier inexistant\n");
        return 0;
    }

    store_file_to_host(filename);
    return 1;
}

/**
* @brief charge un fichier de l'ordinateur hote sur le systeme
* @note: le fichier aura le meme nom que le fichier transfere
* @param char* nom_du_fichier a transferer
* @return int si le fichier existe et que le transfert s'est bien passé , 0 sinon
**/

int load(char* filename){
    if(load_file_from_host(filename)==0){
        printf("Probleme ouverture fichier\n");
        return 0;
    }
    return 1;
}

/**
* @brief demande a l'user un login et un mdp , cherche une correspondance dans le fichier passwd , et si une correspondance existe , l'user se connecte
* @note: l'user aura acces a chaque commande du systeme
* @param void
* @return int : 1 si l'user a pu se connecter , 0 sinon
**/

int connexion(){
    char password[FILENAME_MAX_SIZE];
    char login[FILENAME_MAX_SIZE];
    int erreur = 0;
    char hash[SHA256_BLOCK_SIZE*2 + 1];
    int utilisateur = 1;
    int mot_de_passe = 1;
    int connexion = 1;
    int id;

    while(connexion){
        while(utilisateur){
            printf("Veuillez saisir un nom d'utilisateur : ");
            fgets(login , FILENAME_MAX_SIZE , stdin);
            enlever_retour_ligne(login);
            id = search_login(login);

            if(id==-1){
                printf("Nom d'utilisateur incorrect\n");
            }

            else{
                utilisateur = 0;
            }
        }

        if(!utilisateur){

            while(mot_de_passe && erreur!=3){
                printf("Saisissez le mot de passe : ");
                fgets(password , FILENAME_MAX_SIZE , stdin);
                enlever_retour_ligne(password);
                sha256ofString((BYTE *) password, hash);

                if(strcmp(virtual_disk_sos->users_table[id].passwd , hash) ==0){
                    mot_de_passe = 0;
                }

                else{
                    printf("Mot de passe incorrect\n ");
                    erreur++;

                    if(erreur==3){
                        printf("Nombre d'essai max atteint , fermeture système\n");
                        save_disk_sos();
                        return 0;
                    }
                }
            }
        }

        if(!utilisateur && !mot_de_passe){
            printf("\nTapez -help a tout moment pour connaitre les commandes utilisables\n");
            new_session(login);
            connexion=0;
            return 1;

        }
    }
    return 0;
}

/**
* @brief interprete de commande qui va executer les cpommandes saisies par l'user connecte
* @note contient un tableau de chaine de caractere commande qui contient les arguments de la commande
* @param void
* @return void
**/

void interprete_commande(){
    char str[100];
    cmd_t tab;
    char *commande[10] = {" " }; // tableau de chaine de caractere qui va contenir les commandes
    tab.nbArgs = 0;//nombre d'arguments de la commande
    const char * separators = " \n \t " " "; // separateur d'argument
    int somme = 0;

    /* On cherche à récupérer, un à un, tous les mots (token) de la phrase
    et on commence par le premier.
    exemple: l'user rentre la chaine "listusers 3" , le tableau commande va prendre ces 2 valeurs
    commande[0] = listusers , commande[1] = 3 , la fonction strtoken coupe la chaine de caractere avec le separateur espace
    et affecte les valeurs entre les espaces dans le tableau commande ,  dans ce cas la , la fonction listusers ne marcherait pas car on
    aurait 2 arguments . */

    if(connexion()==1){//si l'user a pu se connecter

        while(interprete){
            int user = get_session();
            char* pseudo = virtual_disk_sos->users_table[user].login;
            //tant que l'interprete est en marche
            printf("\n[%s] Saisissez une commande $ " , pseudo );
            fgets(str , 32 , stdin); // on rentre la commande
            printf("\n");
            int j = 0;
            char * strToken = strtok ( str, separators );

            while ( strToken != NULL ) {
                commande[j] = strToken;
                j++;
                tab.nbArgs++;
                strToken = strtok ( NULL, separators );// parcour la chaine str avec le separateur " " pour remplir le tableau de commande
            }// on prend chaque argument et on les compte

            if(strcmp(commande[0] , "ls")==0 && commande[1]==NULL){
                ls();
            }
            // si le premier argument est ls et qu'il n'ya un seul argument on appel ls

            else if(strcmp(commande[0] , "ls")==0 && strcmp(commande[1] , "-l")==0 && tab.nbArgs>2){
                printf("Trop d'argument pour la commande %s " , commande[0]);
            }

            // si le premier argument est ls et qu'il y a + que 2 arguments on affiche un message d'erreur

            else if(strcmp(commande[0] , "ls")==0 && strcmp(commande[1] , "-l")!=0 && tab.nbArgs==2){
                printf("Argument inconnu pour la commande ls voulez-vous dire -l?\n " );
            }
            // si le premier argument est ls et qu'il n'ya 2 arguments mais que le 2 eme n'est pas -l , message d'erreur

            else if(strcmp(commande[0] , "ls")==0 && strcmp(commande[1] , "-l")==0 && tab.nbArgs==2){
                ls_l();
            }
            // si le premier argument est ls et qu'il n'ya 2 arguments et que le 2 eme est  -l , appel de ls -l


            if(strcmp(commande[0] , "listusers")==0 && tab.nbArgs == 1){
                listusers();
            }
            // appel de listusers si la fonction contient exactement un argument et que son argument = listusers

            if(strcmp(commande[0] , "listusers")==0 && tab.nbArgs > 1){
                printf("Trop d'argument pour la commande listusers\n");
            }

            if(strcmp(commande[0] , "quit")==0){
                quit();
            }
            //appel quit si l'argument est unique et contient la chaine de caractere quit

            somme = get_unused_inode();
            if(strcmp(commande[0] , "cr")==0 && tab.nbArgs>1 && commande[1]!=NULL && somme==-1){
                printf("Nombre de fichier max atteint\n");
            }
            //message d'erreur car la fonction get_unused_inode a renvoyé -1 , le nombre de fichiers max est donc atteint

            if(strcmp(commande[0] , "cr")==0 && tab.nbArgs>1 && commande[1]!=NULL && somme!=-1)
            {
                printf("Creation fichier %s\n" , commande[1]);
                cr(commande[1]);
            }
            //appel de cr

            if(strcmp(commande[0] , "cr")==0 && tab.nbArgs==1 )
            {
                printf("La commande cr prend au moin un argument\n");
            }

            if(strcmp(commande[0] , "-help")==0 && tab.nbArgs==1){
                help();
            }

            if(strcmp(commande[0] , "rm")==0 && tab.nbArgs>1 && commande[1]!=NULL && search_file_inode(commande[1])!=-1){
                rm(commande[1]);
            }

            if(strcmp(commande[0] , "edit")==0 && tab.nbArgs>1 && commande[1]!=NULL){
                edit_file(commande[1]);
            }

            if(strcmp(commande[0] , "cat")==0 && tab.nbArgs>1 && commande[1]!=NULL){
                cat(commande[1]);
            }
            if(strcmp(commande[0] , "adduser")==0 && tab.nbArgs==2 ){
                adduser(commande[1]);
            }

            if(strcmp(commande[0] , "rmuser")==0 && tab.nbArgs>1 && commande[1]!=NULL){
                rmuser(commande[1]);
            }

            if(strcmp(commande[0] , "exit")==0 && tab.nbArgs==1 ){
                deconnexion();
                connexion();
            }

            if(strcmp(commande[0] , "chmod")==0 && tab.nbArgs==3 ){
                chmod(commande[1] , atoi(commande[2]));
            }

            if(strcmp(commande[0] , "chown")==0 && tab.nbArgs==3 ){
                chown(commande[1] , commande[2]);
            }

            if(strcmp(commande[0] , "clear")==0 && tab.nbArgs==1 ){
                clear();
            }

            if(strcmp(commande[0] , "store")==0 && tab.nbArgs==2 ){
                store(commande[1]);
            }

            if(strcmp(commande[0] , "store")==0 && tab.nbArgs>2){
                printf("Trop d'argument pour la commande store\n");
            }

            if(strcmp(commande[0] , "load")==0 && tab.nbArgs==2){
                load(commande[1]);
            }

            tab.nbArgs = 0;

        }
    }
}
int main(void) {
    if(init_disk_sos("../Dossier_Disque/Disque"))
      return 1;

    disp_design_os(true);
    interprete_commande();



    return 0;
}
