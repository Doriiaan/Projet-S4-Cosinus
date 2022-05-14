package Cos;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

import javax.swing.*;
import javax.swing.border.MatteBorder;

public class Frame extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	int i = 0;
	SOS prog;

	JButton start;
	JButton infos_superblock;
	JButton verif_superblock;
	JButton verif_tableinodes;
	JButton defrag;
	JButton retour1;
	
	JPanel panel1;
	JPanel panel2;
	JPanel panel3;
	JPanel panel4;
	JPanel panel5;
	JPanel panel6;
	
	
	
	JLabel label3;
	JLabel label4;
	JLabel label5;
	JLabel label6;
	JLabel label7;
	JLabel label8;

	
	boolean acceuil = true;
	boolean animation_pannel3 = true;
	
	public Frame(String title ,SOS prog) {
		/*  VARIABLES TEXTE  */
		String cosinus = "COSINUS";
		String sos = "Programme SOS";
		
		/* VARIABLE PROG */ 
		
		this.prog = prog;
		
		
		/* SET JFRAME */
		setTitle(title);
		setSize(750,500);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setResizable(false);
		setLocationRelativeTo(null);
		setVisible(true);
		setLayout(null);
		
		/* PREMIER JPANEL */
		panel1 = new JPanel();
		panel1.setBackground(Color.lightGray);
		panel1.setBounds(0, 0, 750, 500);
		panel1.setVisible(true);
		panel1.setLayout(null);
		add(panel1);
		
		/* DEUXIEME JPANEL */
		panel2 = new JPanel();
		panel2.setBackground(Color.black);
		panel2.setBounds(0, 0, 750, 500);
		panel2.setVisible(false);
		panel2.setLayout(null);
		add(panel2);
		
		/* TROISIEME JPANEL */
		panel3 = new JPanel();
		panel3.setBackground(Color.black);
		panel3.setBounds(0, 0, 750, 500);
		panel3.setVisible(false);
		panel3.setLayout(null);
		add(panel3);
		
		/* PREMIER JLABEL */
		JLabel label1 = new JLabel();
		label1.setFont(new Font("Comic sans MS", Font.BOLD,50));
		label1.setForeground(Color.RED);
		label1.setBounds(250,100,300,100);
		label1.setVisible(true);
		panel1.add(label1);

		/* DEUXIEME JLABEL */

		JLabel label2 = new JLabel();
		label2.setFont(new Font("Comic sans MS", Font.BOLD,50));
		label2.setForeground(Color.GREEN);
		label2.setBounds(175,200,400,100);
		label2.setVisible(true);
		panel1.add(label2);
	
		/* TROISIEME JLABEL */

		label3 = new JLabel();
		label3.setFont(new Font("Comic sans MS", Font.BOLD,30));
		label3.setForeground(Color.green);
		label3.setBounds(125,0,700,100);
		label3.setVisible(true);
		panel2.add(label3);
		
		/* QUATRIEME JLABEL */

		label4 = new JLabel();
		label4.setFont(new Font("Comic sans MS", Font.BOLD,35));
		label4.setForeground(Color.green);
		label4.setBounds(175,0,800,100);
		label4.setVisible(true);
		panel3.add(label4);
		
		/* CINQUIEME JLABEL */

		label5 = new JLabel();
		label5.setFont(new Font("Comic sans MS", Font.BOLD,20));
		label5.setForeground(Color.green);
		label5.setBounds(0, 150, 430, 30);
		label5.setVisible(true);
		panel3.add(label5);
		
		/* SIXIEME JLABEL */

		label6 = new JLabel();
		label6.setFont(new Font("Comic sans MS", Font.BOLD,20));
		label6.setForeground(Color.green);
		label6.setBounds(0, 225, 430, 30);
		label6.setVisible(true);
		panel3.add(label6);
		

		/* SEPTIEME JLABEL */

		label7 = new JLabel();
		label7.setFont(new Font("Comic sans MS", Font.BOLD,20));
		label7.setForeground(Color.green);
		label7.setBounds(0, 300, 430, 30);
		label7.setVisible(true);
		panel3.add(label7);
		
		/* HUITIEME JLABEL */

		label8 = new JLabel();
		label8.setFont(new Font("Comic sans MS", Font.BOLD,20));
		label8.setForeground(Color.green);
		label8.setBounds(0, 375, 500, 30);
		label8.setVisible(true);
		panel3.add(label8);
		
		/* JBUTTON START */
		
		Clicklistener click = new Clicklistener();
		start = new JButton("Start");
		start.setFont(new Font("Comic sans MS", Font.BOLD, 25));
		start.setForeground(Color.GRAY);
		start.setBounds(300, 350, 150, 50);
		start.setVisible(false);
		start.addActionListener(click);
		panel1.add(start);
		animation1(label1,cosinus,label2,sos,start);
		
		
		/* JBUTTON infos_superblock */
		
		infos_superblock = new JButton();
		infos_superblock.setFont(new Font("Comic sans MS", Font.BOLD, 20));
		infos_superblock.setForeground(Color.GREEN);
		infos_superblock.setBounds(0, 150, 430, 30);
		infos_superblock.setBackground(Color.black);
		infos_superblock.setBorder(new MatteBorder(0, 0, 0, 0, Color.black));
		infos_superblock.setVisible(true);
		infos_superblock.setEnabled(false);
		infos_superblock.addActionListener(click);
		panel2.add(infos_superblock);
		
		/* JBUTTON verif_superblock */
		
		verif_superblock = new JButton();
		verif_superblock.setFont(new Font("Comic sans MS", Font.BOLD, 20));
		verif_superblock.setForeground(Color.GREEN);
		verif_superblock.setBounds(0, 225, 420, 30);
		verif_superblock.setBackground(Color.black);
		verif_superblock.setBorder(new MatteBorder(0, 0, 0, 0, Color.black));
		verif_superblock.setVisible(true);
		verif_superblock.setEnabled(false);
		verif_superblock.addActionListener(click);
		panel2.add(verif_superblock);
		
		/* JBUTTON verif_tableinodes */
		
		verif_tableinodes = new JButton();
		verif_tableinodes.setFont(new Font("Comic sans MS", Font.BOLD, 20));
		verif_tableinodes.setForeground(Color.GREEN);
		verif_tableinodes.setBounds(0, 300, 482, 30);
		verif_tableinodes.setBackground(Color.black);
		verif_tableinodes.setBorder(new MatteBorder(0, 0, 0, 0, Color.black));
		verif_tableinodes.setVisible(true);
		verif_tableinodes.addActionListener(click);
		verif_tableinodes.setEnabled(false);
		panel2.add(verif_tableinodes);
		
		/* JBUTTON defrag */
		
		defrag = new JButton();
		defrag.setFont(new Font("Comic sans MS", Font.BOLD, 20));
		defrag.setForeground(Color.GREEN);
		defrag.setBounds(0, 375, 260, 30);
		defrag.setBackground(Color.black);
		defrag.setBorder(new MatteBorder(0, 0, 0, 0, Color.black));
		defrag.setVisible(true);
		defrag.setEnabled(false);
		panel2.add(defrag);
		
		/* JBUTTON RETOUR1 */
		
		retour1 = new JButton("Retour");
		retour1.setFont(new Font("Comic sans MS", Font.BOLD, 25));
		retour1.setForeground(Color.black);
		retour1.setBackground(Color.green);
		retour1.setBounds(600, 400, 120, 50);
		retour1.setVisible(false);
		retour1.addActionListener(click);
		panel3.add(retour1);
		
		
		
	}

	 void  animation1(JLabel label1, String s1, JLabel label2, String s2,JButton start) {
		Timer timer = new Timer(100, new ActionListener() {
			boolean test = true;
			String texte;

			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				if (i < s1.length() && test) {
					texte = label1.getText();
					texte += s1.charAt(i);
					label1.setText(texte);
					i++;
					if (i >= s1.length()) {
						test = false;
						i = 0;
					}
				} else {
					texte = label2.getText();
					texte += s2.charAt(i);
					label2.setText(texte);
					i++;
					if (i >= s2.length()) {
						start.setVisible(true);
						i=0;
						((Timer) e.getSource()).stop();
					}

				}

			}


		});
		timer.start();

	}
	
	 void  animation2(JLabel label, String s1, JButton infos_superblock,String s2, JButton verif_superblock,String s3, JButton verif_tableinodes, String s4 , JButton defrag , String s5) {
		Timer timer = new Timer(25, new ActionListener() {
			boolean test1 = true;
			boolean test2 = true;
			boolean test3 = true;
			boolean test4 = true;
			String texte;

			public void actionPerformed(ActionEvent e) {
				// TODO Auto-generated method stub
				if (i < s1.length() && test1) {
					texte = label.getText();
					texte += s1.charAt(i);
					label.setText(texte);
					i++;
					if (i >= s1.length()) {
						test1 = false;
						i = 0;
					}
				} 
				else if (i < s2.length() && test2) {
					texte = infos_superblock.getText();
					texte += s2.charAt(i);
					infos_superblock.setText(texte);
					i++;
					if (i >= s2.length()) {
						test2 = false;
						i = 0;
					}
				}
				else if (i < s3.length() && test3) {
					texte = verif_superblock.getText();
					texte += s3.charAt(i);
					verif_superblock.setText(texte);
					i++;
					if (i >= s3.length()) {
						test3 = false;
						i = 0;	
					}
				}
				else if (i < s4.length() && test4) {
					texte = verif_tableinodes.getText();
					texte += s4.charAt(i);
					verif_tableinodes.setText(texte);
					i++;
					if ( i >= s4.length()) {
						test4 = false;
						i = 0;
					}
				}
				else {
					texte = defrag.getText();
					texte += s5.charAt(i);
					defrag.setText(texte);
					i++;
					if (i >= s5.length()) {
						i =0;
						infos_superblock.setEnabled(true);
						verif_superblock.setEnabled(true);
						verif_tableinodes.setEnabled(true);
						defrag.setEnabled(true);
						((Timer) e.getSource()).stop();

					}
				}
			}


		});
		timer.start();

	}
	
	 
	 void  animation3(JLabel Titre, String s1, JLabel NbFichiers,String s2, JLabel NbUsers,String s3, JLabel NbBlocks, String s4 , JLabel FirstByte , String s5) {
			Timer timer = new Timer(25, new ActionListener() {
				boolean test1 = true;
				boolean test2 = true;
				boolean test3 = true;
				boolean test4 = true;
				String texte;

				public void actionPerformed(ActionEvent e) {
					// TODO Auto-generated method stub
					if (i < s1.length() && test1) {
						texte = Titre.getText();
						texte += s1.charAt(i);
						Titre.setText(texte);
						i++;
						if (i >= s1.length()) {
							test1 = false;
							i = 0;
						}
					} 
					else if (i < s2.length() && test2) {
						texte = NbFichiers.getText();
						texte += s2.charAt(i);
						NbFichiers.setText(texte);
						i++;
						if (i >= s2.length()) {
							test2 = false;
							i = 0;
						}
					}
					else if (i < s3.length() && test3) {
						texte = NbUsers.getText();
						texte += s3.charAt(i);
						NbUsers.setText(texte);
						i++;
						if (i >= s3.length()) {
							test3 = false;
							i = 0;	
						}
					}
					else if (i < s4.length() && test4) {
						texte = NbBlocks.getText();
						texte += s4.charAt(i);
						NbBlocks.setText(texte);
						i++;
						if ( i >= s4.length()) {
							test4 = false;
							i = 0;
						}
					}
					else {
						texte = FirstByte.getText();
						texte += s5.charAt(i);
						FirstByte.setText(texte);
						i++;
						if (i >= s5.length()) {
							i =0;
							retour1.setVisible(true);
							((Timer) e.getSource()).stop();

						}
					}
				}


			});
			timer.start();

		}
	 
	 
	 
	
	private class Clicklistener implements ActionListener{

		public void actionPerformed(ActionEvent e) {
			if( e.getSource() == start) {
				setContentPane(panel2);
				panel2.setVisible(true);
				animation2(label3,"QUE SOUHAITEZ VOUS FAIRE ?",infos_superblock,"Afficher les informations du SuperBlock",verif_superblock,"Vérifier les informations du Superblock",verif_tableinodes,"Vérifier les informations de la table d'inodes",defrag,"Defragmenter le disque");
			}
			else if (e.getSource() == infos_superblock) {
				setContentPane(panel3);
				panel3.setVisible(true);
				int [] tab = new int[4];
				try {
					tab = prog.informationSuperBlock(prog.raf,prog.tab);
				} catch (IOException e1) {
				}
				String NombresFichiers = "Il y a " + tab[0] + " fichiers"; 
				String NombresUsers = "Il y a " + tab[1] + " Utilisateurs";
				String NombreBlock = "Il y a " + tab[2] + " Blocks Utilisés";
				String FirstByte = "Le premier Byte de Libre est à la position " + tab[3];
				if (animation_pannel3) {
					i= 0;
					animation3(label4,"Informations SuperBlock",label5,NombresFichiers,label6,NombresUsers,label7,NombreBlock,label8 , FirstByte);
					animation_pannel3 = false;
				}
			}
			
			else if (e.getSource() == retour1) {
				setContentPane(panel2);
			}
			
			
				
				
				
			
		}
		
	}

}
