/**
* @file Couche4.c
* @author Groupe Cosinus
* @brief Implémentation de la couche 4
* @date Avril 2022
*
*/

#include "Couche4.h"
#include "time_stamp.h"

extern virtual_disk_t *virtual_disk_sos;


/**
* @brief Fonction interne, non visible par l'utilisateur, écrit un fichier sur le disque
* @param file_t file : fichier à écrire
* @param uint first_byte : emplacement de fichier sur le disque
* @return int : 0 si tout c'est bien passé, 1 sinon
**/
int write_file_on_disk(file_t file, uint first_byte){

	/* variables nécessaires */
	int size = (int) file.size;
	block_t data_block;
	int nb_block = 0;
	int i_data = 0;

	while(i_data < size){
		for (int i_data_block = 0; i_data_block < 4; i_data_block++){
			/* on recopie les données de file dans le data_block */

			if(i_data < size){
				data_block.data[i_data_block] = file.data[i_data];
			}
			/* si on a pas dépassé la taille de file */
			else{
				data_block.data[i_data_block] = '\0';
			}

			i_data++;
		}

		if(write_block(first_byte+nb_block*BLOCK_SIZE, data_block)){
			return 1;
		}

		nb_block++;
	}

	return 0;
}


/**
* @brief Créer ou modifier un fichier
* @param char* filename : Nom du fichier à écrire
* @param file_t file : Fichier à écrire sur le système
* @return int : 1 si le fichier a été écrit, 0 en cas d'erreur
* @pre variable systeme et session initialisé
* @note ne pas créer de fichier si aucune session n'est ouverte
**/
int write_file(char* filename, file_t file){
	/* variables nécessaires */

	int index;
	int nb_blocks;
	char time[TIMESTAMP_SIZE];
	index = search_file_inode(filename); /* indice de l'inode ou -1 s'il existe pas */
	nb_blocks = computenblock(file.size);
	strcpy(time, timestamp());

	/* si le fichier existe déjà */
	if(index != -1){
		/* si le nouveau fichier à une taille supérieure à l'ancien */
		if(file.size > virtual_disk_sos->inodes[index].size){
			delete_inode(filename);
		}
		/* si le nouveau fichier à une taille inférieure ou égale à l'ancien */
		else{
			uint first_byte = virtual_disk_sos->inodes[index].first_byte;
			virtual_disk_sos->inodes[index].size = file.size;
			virtual_disk_sos->inodes[index].nblock = nb_blocks;
			strcpy(virtual_disk_sos->inodes[index].mtimestamp, time);
			if(index == (int)virtual_disk_sos->super_block.number_of_files-1)
				update_first_free_byte_super_block(first_byte + file.size); //positionne au debut du prochain bloc

			if(write_file_on_disk(file, first_byte)){
				return 0;
			}

			return 1; /* on s'arrête là pour ne pas créer un nouveaux fichier */
		}
	}

	/* création du nouveaux fichier */

	if((index=init_inode(filename, file.size, virtual_disk_sos->super_block.first_free_byte)) == -1){

		return 0;
	}
	virtual_disk_sos->inodes[index].uid = (uint)get_session();
	virtual_disk_sos->inodes[index].uright = RW;
	virtual_disk_sos->inodes[index].oright = rw;
	strcpy(virtual_disk_sos->inodes[index].ctimestamp, time);
	strcpy(virtual_disk_sos->inodes[index].mtimestamp, time);


	if(write_file_on_disk(file, virtual_disk_sos->inodes[index].first_byte)){
		return 0;
	}

	return 1;
}


/**
* @brief Lit un fichier et enregistre son contenu
* @param char* filename : Nom du fichier à lire
* @param file_t file : Fichier qui enregistre les données du fichier lu
* @return int : 1 si le fichier a été lu, 0 s'il n'existe pas
**/
int read_file(char* filename, file_t* file){
	/* variables nécessaires */
	int index = search_file_inode(filename);
	/* si le fichier n'existe pas */
	if(index == -1){
		return 0;
	}
	int first_byte = virtual_disk_sos->inodes[index].first_byte;
	int nb_blocks = virtual_disk_sos->inodes[index].nblock;
	block_t block;
	int i = 0; int j; int k;


	/* on recopie les données écrits sur le système dans file */
	while(i < nb_blocks){
		k = i*BLOCK_SIZE;
		read_block(first_byte + k, &block);

		for(j = 0; j < BLOCK_SIZE; j++){
			file->data[j+k] = block.data[j];
		}

		i++;
	}
	file->size = virtual_disk_sos->inodes[index].size;
	return 1;
}


/**
* @brief Supprime l'inode correspondant au fichier "filename"
* @param char* filename : Nom du fichier à supprimer
* @return int : 1 si le fichier a été supprimé, 0 s'il n'existe pas, et -1 en cas d'erreur
**/
int delete_file(char* filename){
	/* variable nécessaire */
	int index = search_file_inode(filename);

	/* si le fichier n'existe pas */
	if(index == -1){
		return 0;
	}
	/* si le fichier existe */
	else{
		/* delete_inode(nom_fichier) retourne 0 si tout s'est bien passé, 1 s'il y a eu une erreur, et 2 si l'inode est déjà libre */
		switch(delete_inode(filename)){
			case 0:
				return 1;

			case 1:
				return -1;

			default:
				return 0;
		}
	}
}


/**
* @brief Ecrit un fichier du host sur le système
* @param char* filename : Nom du fichier à transférer
* @return int : 1 si le fichier a été chargé, 0 en cas d'erreur
**/
int load_file_from_host(char* filename){

	FILE* host_file = fopen(filename, "r");
	if(host_file == NULL)
		return 0;

	file_t new_file;
	int i = 0;
	char ch;


	ch = fgetc(host_file);
	while(ch != EOF && i < MAX_FILE_SIZE-1){
		new_file.data[i] = ch;
		ch = fgetc(host_file);
		i++;
	}

	//si c'était le dernier caractère du fichier mais que c'était pas un EOF
	//il faut s'arrêter au MAX_FILE_SIZE-1 pour ajouter le dernier caractère
	if(i == MAX_FILE_SIZE-1 && ch != EOF)
		return 0;


	new_file.data[i] = 3;
	i++;
	new_file.size = i;

	/* écriture le fichier sur le système */
	fclose(host_file);
	return write_file(filename, new_file);
}



/**
* @brief Ecrit un fichier du système sur l'ordinateur host
* @param char* filename : Nom du fichier à transférer
* @return int : 1 si le fichier a été stocké, 0 en cas d'erreur
**/
int store_file_to_host(char* filename){
	/* variables nécessaires */
	if(search_file_inode(filename)==-1){
		printf("Fichier inexistant");
		return 0;
	}
	file_t *file = malloc(sizeof(file_t));
    read_file(filename , file);
	char test[]={"../Stockage_file/"};
	strcat(test , filename);
	FILE* new_file = fopen(test , "a+");
	fprintf(new_file , "%s" , (char*)file->data);
	fclose(new_file);
	return 1;
}
