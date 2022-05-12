package Cos;

import java.io.*;

import java.lang.reflect.Array;
import java.nio.ByteBuffer;
import java.nio.CharBuffer;
import java.nio.charset.Charset;
import java.nio.charset.CharsetDecoder;
import java.util.Arrays;


public class SOS {
	final static int NOMBREINODES = 10;
	final static int TAILLEBLOCK = 4;
	final static int BLOCKS_INODE = 27;
	static int indTableUsers;
	static String tableUsers = "passwd\0";
	static int premierByteUsers;
	public static void main(String[] args) throws IOException {
		
		
		// TODO Auto-generated method stub
		String nomFichier = "d0";
		File fichier = new File(nomFichier);
		RandomAccessFile raf = new RandomAccessFile(fichier, "r");
		CharsetDecoder cd = Charset.forName("UTF-8").newDecoder();
	    ByteBuffer in ;
	    CharBuffer out = CharBuffer.allocate(1);
	    int p = 0;
		byte[] tab = new byte[TAILLEBLOCK];
		raf.read(tab,0,TAILLEBLOCK);
		int Nombre_de_fichier = bytesToInt(tab);
		raf.read(tab,0,TAILLEBLOCK);
		int Nombre_users = bytesToInt(tab);
		raf.read(tab,0,TAILLEBLOCK);
		int Nombre_block_used =  bytesToInt(tab);
		raf.read(tab,0,TAILLEBLOCK);
		int first_free_byte = bytesToInt(tab);
		String s = nom_Fichier(raf, 0,tab);
		raf.seek(Nombre_block_used *4 + 1);
		raf.read(tab,0,TAILLEBLOCK);
		System.out.println(tab);		
		System.out.println("Nb fichier = " + Nombre_de_fichier + "\nNb users = " + Nombre_users + "\nNb block used = " + Nombre_block_used + " \nFirst free byte = " + first_free_byte );
		verifSuperBlock(Nombre_de_fichier, Nombre_users, Nombre_block_used, first_free_byte, raf, tab);
		

	}
	
	 static final public int bytesToInt(byte[] bytes) {
	        int integer = 0;
	        for(int i = 0; i < 4; i ++) {
	            integer += ((256 + bytes[i]) % 256) * (int)Math.pow(256, i);
	        }
	        return integer;
	    }
	 static final public String nom_Fichier(RandomAccessFile raf, int indiceFichier,byte[] tab) throws IOException {
			raf.seek(17+(TAILLEBLOCK*BLOCKS_INODE*indiceFichier));
			String s = "";
			Arrays.fill(tab, (byte) 1);
			while((char)tab[0] != '\0') {
				raf.read(tab,0,1);
				s += (char)tab[0];
				
		}
			return s;
		 
	 }
	 
	 static final public int Taille_fichier(RandomAccessFile raf, int indiceFichier,byte[] tab) throws IOException {
		 
		 raf.seek(49+TAILLEBLOCK*BLOCKS_INODE*indiceFichier);
		 raf.read(tab,0,4);
		 int taille = bytesToInt(tab);
		 
		 return taille;
	 }
	 
	static final int PremierByte(int indiceFichier,RandomAccessFile raf , byte[] tab) throws IOException{
		raf.seek(121+TAILLEBLOCK*BLOCKS_INODE*indiceFichier);
		raf.read(tab,0,4);
		int premier_byte = bytesToInt(tab);
		return premier_byte;
	}
	static final boolean verifierNombreFichiers(int NombreFichiers,RandomAccessFile raf,byte[] tab) throws IOException{
		System.out.println(NombreFichiers + " fichiers trouvés ! : ");
		for (int i = 0 ; i< 10;i++) {
			String s = nom_Fichier(raf, i, tab);
			System.out.println( "	fichier numéro " + (i+1) +" :" + s );
			if (s.charAt(0) == '\0') {
				if (i < NombreFichiers-1) {
					System.out.println("Erreur, Il manque des fichiers !");
					return false;
				}
				if (i == NombreFichiers -1) {
					System.out.println("Tout les fichiers sont présents !");
					return true;
				}
			}
			else {
				if (s.equals(tableUsers)) {
					indTableUsers = i;
					premierByteUsers = PremierByte(i,raf,tab);
					}
				if (i > NombreFichiers-1) {
					System.out.println("Erreur , Il y a des fichiers en trop !");
					return false;
				}
			}
 
		}
		
		return true;
	}
	
	static final public boolean verifNombreUsers(int NombreUser,int premierByte,RandomAccessFile raf, byte[] tab) throws IOException {
		int NombresUsers =0;
		System.out.println(NombreUser + " utilisateur(s) trouvé(s) ! : ");
		raf.seek(premierByte);
		Arrays.fill(tab, (byte) 1);
		String s ="";
		while((char)tab[0] != '\3') {
			raf.read(tab,0,1);
			if (NombresUsers < NombreUser) {
				s += (char)tab[0];
			}
			if((char) tab[0] == '\n') {
				System.out.println("Utilisateur " + (NombresUsers+1) +": "+ s);
				NombresUsers +=1;
			}
			
		}
		if (NombreUser == NombresUsers) {
			return true;
		}
		return false;
	}
	static final public boolean verifNombreblocks(int NombreBlockUsed, RandomAccessFile raf , byte[] tab, int NombreFichiers) throws IOException {
		int nombreTrouvé = 4 + NOMBREINODES*BLOCKS_INODE;
		for (int i = 0 ; i < NombreFichiers; i++) {
			raf.seek(117 + TAILLEBLOCK*BLOCKS_INODE*i);
			raf.read(tab,0,4);
			nombreTrouvé += bytesToInt(tab);
		}
		if (nombreTrouvé == NombreBlockUsed) {
			return true;
		}
		System.out.println("Erreur ,Nombre de blocks utilisés différents !");
		return false;
	}
	
	static final public boolean verifFirstFreeByte(int First_Free_Byte,RandomAccessFile raf, byte[] tab, int NombreFichiers) throws IOException {
		int verifbyte = PremierByte(NombreFichiers-1, raf, tab);
		int taille = Taille_fichier(raf, NombreFichiers-1, tab);
		verifbyte += taille;
		verifbyte += (verifbyte%4);
		if (verifbyte == First_Free_Byte) {
			return true;
		}
		System.out.println("Erreur ,Premier byte disponible différent de celui du SuperBlock !");
		return false;
	}
	
	static final public boolean verifSuperBlock(int NombreFichiers,int NombreUsers, int NombreBlockUsed, int First_Free_Byte, RandomAccessFile raf,byte[] tab) throws IOException {
		if (verifierNombreFichiers(NombreFichiers, raf, tab)) {
			System.out.println("Nombre de Fichiers vérifiés !\n");
			PremierByte(indTableUsers, raf, tab);
			if (verifNombreUsers(NombreUsers,premierByteUsers,raf,tab)) {
				System.out.println("Nombre d'users vérifiés !");
				if (verifNombreblocks(NombreBlockUsed, raf, tab, NombreFichiers)) {
					System.out.println("Nombre de blocks utilisés Vérifié !");
					if (verifFirstFreeByte(First_Free_Byte, raf, tab, NombreFichiers)){
						System.out.println("Premier byte disponible de Vérifié ! \nToutes les informations du superblocks sont correctes !");
						return true;

					}
				}
				
			}
			
			
		}
		return false;
	}
	

}
