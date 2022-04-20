/**
* @file Couche4.c
* @author Groupe Cosinus
* @brief Implémentation de la couche 1
* @date Avril 2022
*
*/

#include "Couche4.h"


/*
* @brief Cherche un fichier dans la table d'unodes
* @param char* filename : Nom du fichier à écrire
* @return int[] : un tableau contenant des informations sur le fichier
* @note infos[0] = 1 si le fichier 'filename' existe, et 0 sinon.
*		infos[1] = l'indice du fichier trouvé dans la table d'inodes, -1 par défaut
*/
int[] find_file(char* filename){
	int infos[2];
	infos[0] = 0;
	infos[1] = -1;
	
	/* cherche dans inodes[] si le fichier existe déjà */
	for(int i = 0; i < taille; i++){
		if(!strcmp(filename, inodes[i].filename)){
			infos[0]; = 1;
			infos[1]; = i;
			return infos;
	}
	
	return infos;
}


/*
* @brief Créé ou modifie un fichier en utilisant la table d'inodes
* @param char* filename : Nom du fichier à écrire
* @param file_t file : Fichier à écrire sur le système
* @return int : 1 en cas d'erreur, 0 sinon
*/
/// il faut penser à faire la date et les droits du fichier mais en vrai, faut aussi modifier la couche 2, 
///ça va ensemble donc je verrais ça plus tard, pour l'instant c'est nickel
int write_file(char* filename, file_t file){
	///si tu modifie le int[2] en int, tu pourras faire if((pos=find_file(filename)) != -1){...}else{...} 
	///mais après tu gère ça comme tu préfère
	int infos[2] = find_file(filename); 
	int existe = infos[0];
	int i_index = infos[1];
	
	int rd = read_super_block(); ///traitre directement l'erreur dans un if, sinon tu n'auras pas la bonne valeur de free_bytes
	
	int free_byte = virtual_disque_sos->super_block.first_free_byte;
	int nb_blocks = computenblock(file.size);
	block_t block = malloc(sizeof(block_t)); ///je ne pense pas qu'il y ai besoin de malloc, une variable normale suffit, write_bloc prend en param une variable normale
	int i = 0; int j;
	
	/* cas: le fichier n'existe pas
		on créé un nouvel inode */
	if(!existe){
		if(rd){ ///pas besoin si tu as fait le if avant
			printf("Erreur lecture du super block\n");
			return 1;
		}
		
		/* ecriture du fichier sur le disque */
		while(i < nb_blocks){ 
			for(j = 0; j < 4; j++){
				block.data[j + (i*4)] = file.data[j + (i*4)]; ///block.data[j] = file.data[j+i] si tu fais i=i*4 plus bas (pas de i dans data[j])
			}
			write_block(free_byte + (i*4), block);
			i++; ///i = i*4 te permet d'être plus clair
		}
		
		/* initialise l'inode correspondant au fichier */
		init_inode(filename, file.size, free_byte);
		
		return 0;
	}
	
	/* cas: le fichier existe déjà */
	else{
		
		/* si le fichier existant est plus grand que file,
			on modifie ses informations */
		///remplace inodes par virtual_disque_sos->inodes et regarde avec les nb_block plutôt que size 
		///parce que si file prend 3 octets et l'autre que 2, ça fait 1 bloc chacun donc ça passe, parce qu'on écrit des blocs
		if(file.size <= inodes[i_index].size){      
			inodes[i_index].filename = filename;
			inodes[i_index].size = file.size;
			return 0;
		}
		
		/* si fichier existant est plus petit que file,
			on le supprime et on créé un nouvel inode */
		else{
			if(rd){ ///pas besoin si tu met un if en haut
				printf("Erreur lecture du super block\n");
				return 1;
			}
			
			delete_inode[i_index];
			
			/* ecriture du fichier sur le disque */
			while(i < nb_blocks){
				for(j = 0; j < 4; j++){
					block.data[j + (i*4)] = file.data[j + (i*4)];
				}
				write_block(free_byte + (i*4), block);
				i++;
			}
		
			/* initialise l'inode correspondant au fichier */
			init_inode(filename, file.size, free_byte);
			return 0;
		}
	}
}


/*
* @brief Lit un fichier et enregistre son contenu
* @param char* filename : Nom du fichier à lire
* @param file_t file : Fichier qui enregistre les données du fichier lu
* @return int : 1 si le fichier a été lu, 0 s'il n'existe pas
*/
int read_file(char* filename, file_t file){
	int infos[2] = find_file(filename);
	int existe = infos[0];
	int i_index = infos[1];
	
	/* cas: le fichier n'existe pas */
	if(!existe){
		return 0;
	}
	/* cas: le fichier existe */
	else{
		file.data = inodes[i_index].data;
		return 1;
	}
}


/*
* @brief Supprime l'inode correspondant au fichier "filename"
* @param char* filename : Nom du fichier à supprimer
* @return int : 1 si le fichier a été supprimé, 0 s'il n'existe pas, et -1 en cas d'erreur
*/
int delete_file(char* filename){
	int infos[2] = find_file(filename);
	int existe = infos[0];
	int i_index = infos[1];
	
	/* cas: le fichier n'existe pas */
	if(!existe){
		return 0;
	}
	/* cas: le fichier existe */
	else{
		/* delete_inode(i) retourne 0 si tout s'est bien passé, 1 s'il y a eu une erreur, et 2 si l'inode est déjà libre */
		switch(delete_inode(i_index)){
			case 0:
				return 1;
				
			case 1:
				return -1;
				
			default:
				return 0;
		}
	}
}


/*
* @brief Ecrit un fichier du host sur le système
* @param char* filename : Nom du fichier à transférer
* @return void
*/
void load_file_from_host(char* filename){



}


/*
* @brief Ecrit un fichier du système sur l'ordinateur host
* @param char* filename : Nom du fichier à transférer
* @return void
*/
void store_file_to_host(char* filename){



}
