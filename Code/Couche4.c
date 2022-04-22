/**
* @file Couche4.c
* @author Groupe Cosinus
* @brief Implémentation de la couche 4
* @date Avril 2022
*
*/

#include "Couche4.h"


/*
* @brief Cherche un fichier dans la table d'unodes
* @param char* filename : Nom du fichier à écrire
* @return int : L'indice du fichier trouvé dans la table d'inodes, -1 par défaut
*/
int find_file(char* filename){
	int indice = -1;
	/* cherche dans virtual_disque_sos->inodes[] si le fichier 'filename' existe */
	for(int i = 0; i < taille; i++){
		if(!strcmp(filename, virtual_disque_sos->inodes[i].filename)){
			indice = i;
			return indice;
	}
	
	return indice;
}


/*
* @brief Créé ou modifie un fichier en utilisant la table d'inodes
* @param char* filename : Nom du fichier à écrire
* @param file_t file : Fichier à écrire sur le système
* @return int : 1 si le fichier a été écrit, 0 en cas d'erreur
*/
int write_file(char* filename, file_t file){
	
	if(read_super_block()){
			printf("Erreur lecture du super block\n");
			return 0;
		}
		
	int index = find_file(filename);
	int free_byte = virtual_disque_sos->super_block.first_free_byte;
	int nb_blocks = computenblock(file.size);
	block_t block;
	int i = 0; int j; int k;
	
	/* cas: le fichier n'existe pas
		on créé un nouvel inode */
	if(index == -1){
		/* ecriture du fichier sur le disque */
		while(i < nb_blocks){
			k = i*BLOCK_SIZE;
			
			for(j = 0; j < BLOCK_SIZE; j++){
				block.data[j+k] = file.data[j+k];
			}
			write_block(free_byte + k, block);
			i++;
		}
		
		/* initialisation l'inode correspondant au fichier */
		init_inode(filename, file.size, free_byte);
	}
	/* cas: le fichier existe déjà */
	else{
		int old_file_blocks = computenblock(virtual_disque_sos->inodes[index].size);
		int new_file_blocks = computenblock(file.size);
		
		/* si le fichier existant est plus grand que file,
			on modifie ses informations */
		if(new_file_blocks <= old_file_blocks){
			virtual_disque_sos->inodes[index].filename = filename;
			virtual_disque_sos->inodes[index].size = file.size;
		}
		/* si fichier existant est plus petit que file,
			on le supprime et on créé un nouvel inode */
		else{
			delete_inode[index];
			/* ecriture du fichier sur le disque */
			while(i < nb_blocks){
				k = i*BLOCK_SIZE;
				
				for(j = 0; j < BLOCK_SIZE; j++){
					block.data[j+k] = file.data[j+k];
				}
				write_block(free_byte + k, block);
				i++;
			}
			/* initialisation l'inode correspondant au fichier */
			init_inode(filename, file.size, free_byte);
		}
	}
	return 1;
}


/*
* @brief Lit un fichier et enregistre son contenu
* @param char* filename : Nom du fichier à lire
* @param file_t file : Fichier qui enregistre les données du fichier lu
* @return int : 1 si le fichier a été lu, 0 s'il n'existe pas
*/
int read_file(char* filename, file_t file){
	int index = find_file(filename);
	
	/* cas: le fichier n'existe pas */
	if(index == -1){
		printf("Le fichier '%s' n'existe pas\n", filename);
		return 0;
	}
	/* cas: le fichier existe */
	else{
		file.data = virtual_disque_sos->inodes[index].data;
		return 1;
	}
}


/*
* @brief Supprime l'inode correspondant au fichier "filename"
* @param char* filename : Nom du fichier à supprimer
* @return int : 1 si le fichier a été supprimé, 0 s'il n'existe pas, et -1 en cas d'erreur
*/
int delete_file(char* filename){
	int index = find_file(filename);
	
	/* cas: le fichier n'existe pas */
	if(index == -1){
		return 0;
	}
	/* cas: le fichier existe */
	else{
		/* delete_inode(i) retourne 0 si tout s'est bien passé, 1 s'il y a eu une erreur, et 2 si l'inode est déjà libre */
		switch(delete_inode(index)){
			case 0:
				return 1;
				
			case 1:
				printf("Erreur suppression du fichier\n");
				return -1;
				
			default:
				printf("Le fichier '%s' n'existe pas\n", filename);
				return 0;
		}
	}
}


/*
* @brief Ecrit un fichier du host sur le système
* @param char* filename : Nom du fichier à transférer
* @return int : 1 si le fichier a été chargé, 0 en cas d'erreur
*/
int load_file_from_host(char* filename){
	FILE* host_file = fopen(filename, "r");
    char ch;
	file_t new_file = malloc(sizeof(file_t));
 
	/* vérification de l'ouverture du fichier */
    if(host_file == NULL){
        printf("Erreur ouverture du fichier\n");
		return 0;
    }
	
	int i = 0;
	/* sauvegarde du fichier host dans le variable 'new_file' caractère par caractère */
	while(ch != EOF){
		ch = fgetc(host_file);
		new_file.data[i] = ch;
		
		i++;
		
		if(i > MAX_FILE_SIZE){
			printf("Erreur chargement du fichier. Le fichier '%s' est trop grand\n", filename);
		}
	}
		
	fclose(host_file);
	
	/* écriture le fichier sur le système */
	return write_file(filename, new_file);
}


/*
* @brief Ecrit un fichier du système sur l'ordinateur host
* @param char* filename : Nom du fichier à transférer
* @return int : 1 si le fichier a été stocké, 0 en cas d'erreur
*/
int store_file_to_host(char* filename){
	FILE* new_file = fopen(filename, "w");
	
	/* vérification de la création du fichier */
	if(new_file == NULL){
		printf("Erreur création du fichier\n");
		return 0;
	}
}
