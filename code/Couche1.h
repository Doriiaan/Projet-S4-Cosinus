/**
  Renvoit le nombre de blocs nécessaire au stockage de n octet
  input : n octets (int)
  ouput : n blocs  (int)
*/
int computenblock(int nb_octet);


/**
  Initialise la variable globale de type virtual_disk_t
  input : nom du repertoire contenant le disque (char*)
*/
void init_disk_sos(char* nom_repertoire_disque);
