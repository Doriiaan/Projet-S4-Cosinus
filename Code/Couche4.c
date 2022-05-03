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





/*
* @brief Lit un fichier et enregistre son contenu
* @param char* filename : Nom du fichier à lire
* @param file_t file : Fichier qui enregistre les données du fichier lu
* @return int : 1 si le fichier a été lu, 0 s'il n'existe pas
*/
int read_file(char* filename, file_t* file){
	int index = search_file_inode(filename);

	/* cas: le fichier n'existe pas */
	if(index == -1){
		printf("Le fichier '%s' n'existe pas\n", filename);
		return 0;
	}

	if(file->size == 0){
		return 1;
	}

	/* cas: le fichier existe */
	int first_byte = virtual_disk_sos->inodes[index].first_byte;
	int nb_blocks = virtual_disk_sos->inodes[index].nblock;
	block_t* block = malloc(sizeof(block_t));

	int i = 0; int j; int k;
	/* recopie les données écrits sur le système dans file */
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


/*
* @brief Supprime l'inode correspondant au fichier "filename"
* @param char* filename : Nom du fichier à supprimer
* @return int : 1 si le fichier a été supprimé, 0 s'il n'existe pas, et -1 en cas d'erreur
*/
int delete_file(char* filename){
	int index = search_file_inode(filename);

	/* cas: le fichier n'existe pas */
	if(index == -1){
		return 0;
	}
	/* cas: le fichier existe */
	else{
		/* delete_inode(nom_fichier) retourne 0 si tout s'est bien passé, 1 s'il y a eu une erreur, et 2 si l'inode est déjà libre */
		switch(delete_inode(filename)){
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
	file_t new_file;

	/* vérification de l'ouverture du fichier */
    if(host_file == NULL){
        printf("Erreur ouverture du fichier\n");
		return 0;
    }

	int size = ftell(host_file);
	if(size == 0){
		return write_file(filename, new_file);
	}

	int i = 0;
	/* sauvegarde du fichier host dans le variable 'new_file' caractère par caractère */
	ch = fgetc(host_file);
	while(ch != EOF){


		new_file.data[i] = ch;

		i++;

		if(i > MAX_FILE_SIZE){
			printf("Erreur chargement du fichier. Le fichier '%s' est trop grand\n", filename);
		}
		ch = fgetc(host_file);
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

	file_t* system_file = malloc(sizeof(file_t));
	read_file("filename", system_file);
	char data[MAX_FILE_SIZE];

	if(system_file->size == 0){
		return 1;
	}

	/* stockage du fichier sur le host caractère par caractère */
	for(uint i = 0; i < system_file->size; i++){
		data[i] = system_file->data[i];
	}

	fprintf(new_file, data);

	return 1;
}
