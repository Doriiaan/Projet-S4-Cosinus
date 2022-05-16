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
	 
	  final boolean defragmentation() throws IOException {
		 byte[] fichier_en_byte = new byte[1024*2];
		 int newfirstbyte = (16+TAILLEBLOCK*NOMBREINODES*BLOCKS_INODE)+taillefichiertotale();
		 int oldfirstbyte = PremierByte(0);
		 raf.seek(0);
		 raf.read(fichier_en_byte,0,12);
		 raf.seek(0);
		 raf.write(fichier_en_byte, 0, 12);
		 raf.write(intToBytes(newfirstbyte));
		 raf.seek(120);
		 raf.write(intToBytes(16+TAILLEBLOCK*NOMBREINODES*BLOCKS_INODE));
		 raf.seek(oldfirstbyte);
		 raf.read(fichier_en_byte,0,Taille_fichier(0)+1);
		 raf.seek(newfirstbyte);
		 raf.write(fichier_en_byte,0,Taille_fichier(0)+1);
		 for (int i = 1 ; i < Nombre_de_fichier ; i++) {
			 oldfirstbyte = PremierByte(i);
			 newfirstbyte = PremierByte(i-1) + Taille_fichier(i-1);
			 if (newfirstbyte % 4 != 0) {
				 newfirstbyte +=  4 -( newfirstbyte %4 );
			 }
			 raf.seek(120+TAILLEBLOCK*BLOCKS_INODE*i );
			 raf.write(intToBytes(newfirstbyte));
			 raf.seek(oldfirstbyte);
			 raf.read(fichier_en_byte,0,Taille_fichier(i));
			 raf.seek(newfirstbyte);
			 raf.write(fichier_en_byte,0,Taille_fichier(i));
			 
		 }
			
			
			
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
	  
	  public final int taillefichiertotale() throws IOException{
		  int total = 0;
		  int taille_aux = 0;
		  for (int indice = 0; indice < Nombre_de_fichier;indice++ ) {
			  taille_aux = Taille_fichier(indice);
				 if (taille_aux % 4 != 0) {
					 taille_aux +=  4 -( taille_aux %4 );
				 }
				 total += taille_aux;
		  }
		  return total;
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
		String s ="";
		while((char)tab[0] != '\3') {
			raf.read(tab,0,1);
			if (Nombretrouve < Nombre_users) {
				s += (char)tab[0];
			}
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
		//System.out.println("i dernier fichier = " +( Nombre_de_fichier-1) + " premier byte = " + verifbyte);
		int taille = Taille_fichier(Nombre_de_fichier-1);
		verifbyte += taille;
		if (verifbyte %4 !=0) {
			verifbyte +=( 4- (verifbyte %4));

		}
		//System.out.println("byte trouvé " + verifbyte + " byte cherché " + first_free_byte + "taille = " + taille );
		if (verifbyte == first_free_byte) {
			return true;
		}
		System.out.println("Erreur ,Premier byte disponible différent de celui du SuperBlock !");
		return false;
	}
	
	 final public boolean verifSuperBlock() throws IOException {
		if (verifierNombreFichiers()) {
			System.out.println("Nombre de Fichiers vérifiés !\n");
			PremierByte(indTableUsers);
			//System.out.println(PremierByte(indTableUsers));
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
		//System.out.println("Vérification de la table des inodes en cours ...");
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
		//System.out.println("La table des inodes est correcte !");
		return true;
	}
	

}
