#include "header.h"
#include "Couche1.h"
#include "Couche2.h"
#include "Couche3.h"
#include "Couche4.h"
#include "Couche5.h"
#include "term_canon.h"
extern virtual_disk_t *virtual_disk_sos;

#define FIRST_TIME 1
#define TEST_ADD_INODE 1
#define TEST_DELETE_INODE 0
#define TEST_ADD_USER 1
#define TEST_DELETE_USER 0
#define TEST_SESSION 0


int interprete = 1;

void enlever_retour_ligne(char *chaine){

    int taille = strlen(chaine);
    if(chaine[taille-1] == '\n')
    chaine[taille-1] = '\0';
}

void listusers(){
    if(virtual_disk_sos->super_block.number_of_users == 0){
        printf("0 utilisateurs");
    }
    printf("Nombre d'utilisateurs : %d\n" , virtual_disk_sos->super_block.number_of_users );
    for(uint i = 0 ; i<virtual_disk_sos->super_block.number_of_users ; i++){
        if(virtual_disk_sos->users_table[i].login==NULL){
            i++;
        }
        printf("%s\n"  ,virtual_disk_sos->users_table[i].login);
    }
}

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
    file_t *file = malloc(sizeof(file_t));
    read_file(nom_fichier , file);
    printf("%s\n" , file->data);
    return 1;
}

/**
* @brief vide le terminal
* @param aucun
* @note utilise un printf specifique pour effacer le terminal
**/
void clear(){
    printf ("\033[H\033[J");

}

int adduser(){
    if(get_session()!=0){
        printf("Commande réservé a l'utilisateur root .\n");
        return 0;
    }

    int confirmer = 0;
    int pos;
    pos = get_unused_user();
    printf("%d\n", pos);

    if(pos==-1){
        printf("Nombre d'utilisateurs max atteint\n");
        return 0;
    }

    char confirm[FILENAME_MAX_SIZE];
    char login[FILENAME_MAX_SIZE];
    char password[FILENAME_MAX_SIZE];
    int num = 0;
    int login_existe = 0;
    printf ("\033[H\033[J");
    printf("Saisissez un login\n");
    fgets(login , FILENAME_MAX_SIZE , stdin);
    enlever_retour_ligne(login);

    while(!login_existe){
        if(search_login(login)!=-1){
            printf("Ce pseudo est déja utilisé veuillez en selectionner un autre\n");
            printf("Saisissez un login\n");
            fgets(login , FILENAME_MAX_SIZE , stdin);
        }

        else{
            login_existe=1;
        }
    }

    printf("Saisissez un mot de passe :\n" );
    fgets(password , FILENAME_MAX_SIZE , stdin);
    printf("Veuillez confirmer le mot de passe:\n");
    fgets(confirm , FILENAME_MAX_SIZE , stdin);
    enlever_retour_ligne(password);
    enlever_retour_ligne(confirm);

    while(!confirmer){

        if(strcmp(confirm , password)!=0){
            num++;
            printf("Les mot de passes ne correspondent pas , veuillez retaper le mdp\n");
            fgets(confirm , FILENAME_MAX_SIZE , stdin);
            enlever_retour_ligne(confirm);
            printf("Tentative numero %d de validation\n" , num);
        }

        if(strcmp(confirm , password)==0){
            add_user(login , password);
            printf("Creation de l utilisateur %s reussi \n" , virtual_disk_sos->users_table[pos].login);
            confirmer = 1;
            return 1;

        }
    }
    return 0;
}

int edit_file(file_t *file){

    if(!Term_non_canonique())
    return 1;

    char c;
    int fin = 0;

    do {
        printf ("\033[H\033[J");
        printf("*****EDIT*****\n\n");

        for (int i = 0; i < (int)file->size; i++) {
            printf("%c", file->data[i]);
        }

        c=fgetc(stdin);

        switch (c) {
            case '@':
            fin = 1;
            break;
            case '\b':
            if(file->size > 0)
            file->size--;
            break;
            default:
            file->data[file->size] = c;
            file->size++;
        }

    } while(!fin && file->size < MAX_FILE_SIZE);
    printf ("\033[H\033[J");

    if(!Term_canonique())
    return 1;

    return 0;
}



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

int deconnexion(){
    del_session();
    return 1;
}

void ls(){
    for (uint i = 0; i < virtual_disk_sos->super_block.number_of_files ; i++){
        printf("%s \t  %d \n  " , virtual_disk_sos->inodes[i].filename , virtual_disk_sos->inodes[i].size );
    }
}
void quit(){
    interprete = 0;
    save_disk_sos();
    printf("\nSAVE\n");

}

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
void help(){
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
    printf("quit : sort de l interprete de commande\n");
    printf("\n");
    printf("clear : efface le contenu du terminal\n");
    printf("\n");
}

int store(char* filename){
    int pos = search_file_inode(filename);

    if(pos==-1){
        printf("Fichier inexistant\n");
        return 0;
    }

    store_file_to_host(filename);
    return 1;
}

int load(char* filename){
    if(load_file_from_host(filename)==0){
        printf("Probleme ouverture fichier\n");
        return 0;
    }
return 1;
}
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
            printf("Veuillez saisir un nom d'utilisateur : \n");
            fgets(login , FILENAME_MAX_SIZE , stdin);
            enlever_retour_ligne(login);
            id = search_login(login);
            printf("L'id est %d\n" , id);

            if(id==-1){
                printf("Nom d'utilisateur incorrect\n");
            }

            else{
                printf("Nom d'utilisateur correct\n");
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
                    printf("Mot de passe correct\n");
                    mot_de_passe = 0;
                }
                else{
                    printf("Mot de passe incorrect\n ");
                    erreur++;
                    if(erreur==3){
                        printf("Nombre d'essai max atteint , fermeture système\n");
                        return 0;
                    }
                }
            }
        }
        if(!utilisateur && !mot_de_passe){
            printf("Connexion valide : \n");
            printf("Lancement de l'interprete de commande ...\n");
            printf("Tapez -help a tout moment pour connaitre les commandes utilisables\n");
            new_session(login);
            connexion=0;
            return 1;

        }
    }
    return 0;
}

void interprete_commande(){
    char str[100];
    cmd_t tab;
    char *commande[10] = {" " }; // tableau de pointeur qui va contenir les commandes
    tab.nbArgs = 0;
    const char * separators = " \n \t " " ";
    int somme = 0;
    // On cherche à récupérer, un à un, tous les mots (token) de la phrase
    // et on commence par le premier.
    if(connexion()==1){
        while(interprete){
            printf("Saisissez une commande :\n ");
            fgets(str , 32 , stdin);
            int j = 0;
            char * strToken = strtok ( str, separators );
            while ( strToken != NULL ) {
                commande[j] = strToken;
                j++;
                tab.nbArgs++;
                strToken = strtok ( NULL, separators );
            }// on prend chaque argument et on les compte

            if(strcmp(commande[0] , "ls")==0 && commande[1]==NULL){
                ls();
            }
            else if(strcmp(commande[0] , "ls")==0 && strcmp(commande[1] , "-l")==0 && tab.nbArgs>2){
                printf("Trop d'argument pour la commande %s " , commande[0]);
            }

            else if(strcmp(commande[0] , "ls")==0 && strcmp(commande[1] , "-l")!=0 && tab.nbArgs==2){
                printf("Argument inconnu pour la commande ls voulez-vous dire -l?\n " );
            }

            else if(strcmp(commande[0] , "ls")==0 && strcmp(commande[1] , "-l")==0 && tab.nbArgs==2){
                ls_l();
            }

            if(strcmp(commande[0] , "listusers")==0 && tab.nbArgs == 1){
                listusers();
            }

            if(strcmp(commande[0] , "listusers")==0 && tab.nbArgs > 1){
                printf("Trop d'argument pour la commande listusers\n");
            }

            if(strcmp(commande[0] , "quit")==0){
                quit();
            }

            somme = get_unused_inode();
            if(strcmp(commande[0] , "cr")==0 && tab.nbArgs>1 && commande[1]!=NULL && somme==-1){
                printf("Nombre de fichier max atteint\n");
            }

            if(strcmp(commande[0] , "cr")==0 && tab.nbArgs>1 && commande[1]!=NULL && somme!=-1)
            {
                printf("Creation fichier %s\n" , commande[1]);
                cr(commande[1]);
            }

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

            /*if(strcmp(commande[0] , "edit")==0 && tab.nbArgs>1 && commande[1]!=NULL){
            edit_file(commande[1]);
        }*/

        if(strcmp(commande[0] , "cat")==0 && tab.nbArgs>1 && commande[1]!=NULL){
            cat(commande[1]);
        }
        if(strcmp(commande[0] , "adduser")==0 && tab.nbArgs==1 ){
            adduser();
        }

        if(strcmp(commande[0] , "rmuser")==0 && tab.nbArgs>1 && commande[1]!=NULL){
            rmuser(commande[1]);
        }

        if(strcmp(commande[0] , "exit")==0 && tab.nbArgs==1 ){
            deconnexion();
            printf("%d session :\n " , get_session());
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
