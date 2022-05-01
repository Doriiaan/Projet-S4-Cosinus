void listusers(){
  if(virtual_disk_sos->super_block.number_of_users == 0){
    printf("0 utilisateurs");
  }
  printf("Nombre d'utilisateurs : %d" , virtual_disk_sos->super_block.number_of_users );
  for(int i = 0 ; i<virtual_disk_sos->super_block.number_of_users ; i++){
    printf("%s\n"  ,virtual_disk_sos->users_table[i].login);
  }

int cat(char* nom_fichier){
  if(find_file(nom_fichier)==-1){
    return 0;
  }
  block_t *t;
  int indice = find_file(nom_fichier);
  int bit = virtual_disk_sos->inodes[indice].first_byte;
  int taille = virtual_disk_sos->inodes[indice].size;
  int nb_bloc = computenblock(taille);
  for(int i = 0 ; i<nb_bloc ; i++){
    read_block(bit , t);
    printf("%s" , t->data);
    bit+=BLOCK_SIZE;
  }
  return 1;
}

int rm(char* nom_fichier){
  if(find_file(nom_fichier)==-1){
    return 0;
  }
  delete_file(nom_fichier);
  return 1;
}  
  
void ls_l(){
  for (int i = 0; i < virtual_disk_sos->super_block.number_of_files ; i++){
    printf("%s | %d | %d | %d | %d | %s | %s | %d | %d\n " , virtual_disk_sos->inodes[i].filename , virtual_disk_sos->inodes[i].size , virtual_disk_sos->inodes[i].uid , 
      virtual_disk_sos->inodes[i].uright , virtual_disk_sos->inodes[i].oright , virtual_disk_sos->inodes[i].ctimestamp , virtual_disk_sos->inodes[i].mtimestamp , 
      virtual_disk_sos->inodes[i].nblock , virtual_disk_sos->inodes[i].first_byte );
    fflush(stdout);
    
  }
} // je referais l'affichage plus tard


void ls(){
  for (int i = 0; i < virtual_disk_sos->super_block.number_of_files ; i++){
    printf("%s | %d\n " , virtual_disk_sos->inodes[i].filename , virtual_disk_sos->inodes[i].size);
    fflush(stdout);
    
  }
}

  int main(void){
  char str[100];
  cmd_t tab;
  char *commande[10]; // tableau de pointeur qui va contenir les commandes
  tab.nbArgs = 0;
  const char * separators = " \n \t " " ";

    // On cherche à récupérer, un à un, tous les mots (token) de la phrase
    // et on commence par le premier.
  
  printf("Saisissez une commande : ");
  gets(str);
  int j = 0;
  char * strToken = strtok ( str, separators );
    while ( strToken != NULL ) {
        printf ( "%s\n", strToken );
        commande[j] = strToken;
        j++;
        tab.nbArgs++;
        strToken = strtok ( NULL, separators );
    }// on prend chaque argument et on les compte

    if(strcmp(commande[0] , "ls")==0 && tab.nbArgs==1){
      ls();
    }

    if(strcmp(commande[0] , "ls")==0 && strcmp(commande[1] , "-l")==0 && tab.nbArgs==2){
      ls_l();
    }
    else{
      printf("Erreur commande");
    }
    printf("Le nombre total de mots dans cette chaine est = %d\n", tab.nbArgs);



  return 0;

}
