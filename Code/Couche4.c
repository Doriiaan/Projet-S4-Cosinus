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
				data_block.data[i_data_block] = (uchar)'\0';
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
			virtual_disk_sos->inodes[index].size = file.size;
			virtual_disk_sos->inodes[index].nblock = nb_blocks;
			strcpy(virtual_disk_sos->inodes[index].mtimestamp, time);
			
			if(write_file_on_disk(file, virtual_disk_sos->inodes[index].first_byte)){
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
	int first_byte = virtual_disk_sos->inodes[index].first_byte;
	int nb_blocks = virtual_disk_sos->inodes[index].nblock;
	block_t* block = malloc(sizeof(block_t));
	int i = 0; int j; int k;

	/* si le fichier n'existe pas */
	if(index == -1){
		return 0;
	}
	
	/* si le fichier 'filename' est vide */
	if(virtual_disk_sos->inodes[index].size == 0){
		/* on s'arrête car il n'y a rien à recopier */
		return 1;
	}

	/* on recopie les données écrits sur le système dans file */
	while(i < nb_blocks){
		k = i*BLOCK_SIZE;
		read_block(first_byte + k, block);

		for(j = 0; j < BLOCK_SIZE; j++){
			file->data[j+k] = block->data[j];
		}

		i++;
	}

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
	/* variables nécessaires */
	FILE* host_file = fopen(filename, "r");
	int size = ftell(host_file);
	char ch = fgetc(host_file);
	file_t new_file;
	int i = 0;

	/* vérification de l'ouverture du fichier */
    if(host_file == NULL){
		return 0;
    }
	
	/* si le fichier est vide */
	if(size == 0){
		/* on peut l'écrire directement car il est vide */
		return write_file(filename, new_file);
	}
	
	/* si la taille du fichier dépasse la limite */
	if(size > MAX_FILE_SIZE){
		/* on s'arrête car l'écriture du fichier sera impossible */
		return 0;
	}

	/* sauvegarde du fichier host dans le variable 'new_file' caractère par caractère */
	while(ch != EOF){
		new_file.data[i] = ch;
		i++;

		ch = fgetc(host_file);
	}

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
	file_t* system_file = malloc(sizeof(file_t));
	FILE* new_file = fopen(filename, "w");
	read_file("filename", system_file);
	char data[MAX_FILE_SIZE];

	/* vérification de la création du fichier */
	if(new_file == NULL){
		return 0;
	}
	
	/* si le fichier est vide */
	if(system_file->size == 0){
		/* on s'arrête car il n'y a rien à recopier */
		return 1;
	}

	/* on sauvegarde les données du fichier dans un variable */
	for(uint i = 0; i < system_file->size; i++){
		data[i] = system_file->data[i];
	}

	/* stockage des données sur le host */
	fprintf(new_file, data);
	return 1;
}
