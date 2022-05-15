package Cos;

import java.io.*;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Arrays;


public class SOS {
	final static int NOMBREINODES = 10;
	final static int TAILLEBLOCK = 4;
	final static int BLOCKS_INODE = 27;
	static int indTableUsers;
	static String tableUsers = "passwd\0";
	static int premierByteUsers;
	static int Nombre_de_fichier;
	static int Nombre_users;
	static int Nombre_block_used;
	static int first_free_byte;
	static RandomAccessFile raf;
	static byte[] tab = new byte[TAILLEBLOCK];
	File fichier = new File("../Dossier_Disque/Disque/d0");
	
	SOS() throws FileNotFoundException{
		 raf = new RandomAccessFile(fichier, "rw");

		
	}

	
	final public int [] informationSuperBlock() throws IOException {
		int [] tabint = new int[4];
		raf.seek(0);
		raf.read(tab,0,TAILLEBLOCK);
		Nombre_de_fichier = bytesToInt(tab);
		raf.read(tab,0,TAILLEBLOCK);
		Nombre_users = bytesToInt(tab);
		raf.read(tab,0,TAILLEBLOCK);
		Nombre_block_used =  bytesToInt(tab);
		raf.read(tab,0,TAILLEBLOCK);
		first_free_byte = bytesToInt(tab);
		raf.seek(Nombre_block_used *4 + 1);
		raf.read(tab,0,TAILLEBLOCK);
		tabint[0] = Nombre_de_fichier; tabint[1] = Nombre_users; tabint[2] = Nombre_block_used; tabint[3] = first_free_byte;
		return tabint;
	}
	
	 static final public int bytesToInt(byte[] bytes) {
	        int integer = 0;
	        for(int i = 0; i < 4; i ++) {
	            integer += ((256 + bytes[i]) % 256) * (int)Math.pow(256, i);
	        }
	        return integer;
	    }
	 
	 

	    static final public byte[] intToBytes(int integer) {
	        byte[] bytes = new byte[4];
	        for(int i = 0; i < 4; i ++) {
	            bytes[i] = (byte) (integer % 256);
	            integer = integer >> 8;
	        }
	        return bytes;
	    }
	 
	  final boolean defragmentation(RandomAccessFile raf, byte[] tab, int NombreFichiers) throws IOException {
		 byte[] fichier_en_byte = Files.readAllBytes(Paths.get("d0"));
			if(PremierByte(0) != (16+TAILLEBLOCK*BLOCKS_INODE*NOMBREINODES)) {
				System.out.println("Premier Byte du premier fichier : " + PremierByte(0) + " " + (16+TAILLEBLOCK*BLOCKS_INODE*NOMBREINODES));
				raf.seek(16+TAILLEBLOCK*BLOCKS_INODE*NOMBREINODES);
				raf.write(fichier_en_byte, PremierByte(0),Taille_fichier(0)-1);
				raf.seek(121+TAILLEBLOCK*BLOCKS_INODE*0);
				raf.write(intToBytes(16+TAILLEBLOCK*BLOCKS_INODE*NOMBREINODES),0,4);	
			}
			for (int i = 1; i < NombreFichiers ; i++) {
				int position = PremierByte(i-1) + Taille_fichier(i-1);
				
				if((PremierByte(i)) != position){
					System.out.println("Premier byte = " + PremierByte(i) +" taille =  "  + Taille_fichier(i-1) +" position = " + position + " i = " + i);
					raf.seek(position);
					raf.write(fichier_en_byte,PremierByte(i),Taille_fichier(i));
					raf.seek(120+TAILLEBLOCK*BLOCKS_INODE*i);
					byte[] remplace = new byte[4];
					remplace = intToBytes(position);
					raf.write(remplace,0,4);
					raf.seek(120+TAILLEBLOCK*BLOCKS_INODE*i);
					raf.read(tab,0,4);

					
				}
			}
			int taille_disque = PremierByte(NombreFichiers-1) + Taille_fichier(NombreFichiers-1);
			System.out.println("taille du disque = " + taille_disque/4 + "Premier byte dernier fichier :" + PremierByte(NombreFichiers-1));
			if (taille_disque % 4 == 0) {
				System.out.println();
				raf.seek(8);
				raf.write(intToBytes(taille_disque/4-1),0,4);
				
			}
			else {
				raf.seek(8);
				raf.write(intToBytes(taille_disque/4),0,4);
			}
			raf.seek(12);
			raf.write(intToBytes(taille_disque+1),0,4);
			
			
			
			
			
		 return true;
	 }
	 
	 static final public String nom_Fichier(int indiceFichier) throws IOException {
			raf.seek(16+(TAILLEBLOCK*BLOCKS_INODE*indiceFichier));
			String s = ""; 
			Arrays.fill(tab, (byte) 1);
			while((char)tab[0] != '\0') {
				raf.read(tab,0,1);
				s += (char)tab[0];
				
		}
			return s;
		 
	 }
	 
	  final public int Taille_fichier(int indiceFichier) throws IOException {
		 
		 raf.seek(48+TAILLEBLOCK*BLOCKS_INODE*indiceFichier);
		 raf.read(tab,0,4);
		 int taille = bytesToInt(tab);
		 
		 return taille;
	 }
	 
	static final int PremierByte(int indiceFichier) throws IOException{
		raf.seek(120+TAILLEBLOCK*BLOCKS_INODE*indiceFichier);
		raf.read(tab,0,4);
		int premier_byte = bytesToInt(tab);
		return premier_byte;
	}
	final boolean verifierNombreFichiers() throws IOException{
		//System.out.println(Nombre_de_fichier + " fichiers trouvés ! : ");
		for (int i = 0 ; i< 10;i++) {
			String s = nom_Fichier(i);
			if (s.charAt(0) == '\0') {
				if (i < Nombre_de_fichier-1) {
					System.out.println("Erreur, Il manque des fichiers !");
					return false;
				}
				if (i == Nombre_de_fichier-1) {
					//System.out.println("Tout les fichiers sont présents !");
					return true;
				}
			}
			else {
				if (s.equals(tableUsers)) {
					indTableUsers = i;
					premierByteUsers = PremierByte(i);
					}
				if (i > Nombre_de_fichier-1) {
					System.out.println("Erreur , Il y a des fichiers en trop !");
					return false;
				}
			}
 
		}
		
		return true;
	}
	
	 final public boolean verifNombreUsers() throws IOException {
		int Nombretrouve =0;
		//System.out.println(Nombre_users + " utilisateur(s) trouvé(s) ! : ");
		raf.seek(premierByteUsers);
		Arrays.fill(tab, (byte) 1);
		//String s ="";
		while((char)tab[0] != '\3') {
			raf.read(tab,0,1);
			/*if (Nombretrouve < Nombre_users) {
				s += (char)tab[0];
			}*/
			if((char) tab[0] == '\n') {
				//System.out.println("Utilisateur " + (Nombretrouve+1) +": "+ s);
				Nombretrouve +=1;
			}
			
		}
		if (Nombre_users == Nombretrouve) {
			return true;
		}
		return false;
	}
	 final public boolean verifNombreblocks() throws IOException {
		int nombreTrouve = 4 + NOMBREINODES*BLOCKS_INODE;
		for (int i = 0 ; i < Nombre_de_fichier; i++) {
			raf.seek(116 + TAILLEBLOCK*BLOCKS_INODE*i);
			raf.read(tab,0,4);
			nombreTrouve += bytesToInt(tab);
		}
		if (nombreTrouve == Nombre_block_used) {
			return true;
		}
		System.out.println("Erreur ,Nombre de blocks utilisés différents !");
		return false;
	}
	
	 final public boolean verifFirstFreeByte() throws IOException {
		int verifbyte = PremierByte(Nombre_de_fichier-1);
		int taille = Taille_fichier(Nombre_de_fichier-1);
		verifbyte += taille+1;
		if (verifbyte == first_free_byte) {
			return true;
		}
		System.out.println("Erreur ,Premier byte disponible différent de celui du SuperBlock !");
		return false;
	}
	
	 final public boolean verifSuperBlock(int NombreFichiers,int NombreUsers, int NombreBlockUsed, int First_Free_Byte, RandomAccessFile raf,byte[] tab) throws IOException {
		if (verifierNombreFichiers()) {
			System.out.println("Nombre de Fichiers vérifiés !\n");
			PremierByte(indTableUsers);
			if (verifNombreUsers()) {
				System.out.println("Nombre d'users vérifiés !");
				if (verifNombreblocks()) {
					System.out.println("Nombre de blocks utilisés Vérifié !");
					if (verifFirstFreeByte()){
						System.out.println("Premier byte disponible de Vérifié ! \nToutes les informations du superblocks sont correctes !");
						return true;

					}
				}
				
			}
			
			
		}
		return false;
	}
	 final boolean verifTablesInodes() throws IOException {
		System.out.println("Vérification de la table des inodes en cours ...");
		for (int i = 0; i < Nombre_de_fichier ; i++) {
			int firstbyte = PremierByte(i);
			int taille = Taille_fichier(i);
			Arrays.fill(tab, (byte) 1);
			raf.seek(firstbyte+taille-1);
			raf.read(tab,0,1);
			if ((char)tab[0]!= '\3') {
				System.out.println("Il y a une erreur dans la table des inodes !");
				return false;
			}
		}
		System.out.println("La table des inodes est correcte !");
		return true;
	}
	

}
