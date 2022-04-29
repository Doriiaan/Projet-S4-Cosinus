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