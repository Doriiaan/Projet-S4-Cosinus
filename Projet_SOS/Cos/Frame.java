package Cos;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.Arrays;

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
	JButton quitter;
	JButton retour1;
	JButton retour2;
	JButton retour3;
	JButton retour4;
	JButton retour5;
	JButton infoFichiers;
	JButton infoUsers;
	
	JPanel panel1;
	JPanel panel2;
	JPanel panel3;
	JPanel panel4;
	JPanel panel5;
	JPanel panel6;
	JPanel information_fichiers;
	JPanel information_user;
	
	
	
	JLabel label3;
	JLabel label4;
	JLabel label5;
	JLabel label6;
	JLabel label7;
	JLabel label8;
	JLabel label9;
	JLabel label10;
	JLabel label11;
	JLabel label12;
	JLabel label13;
	JLabel label14;
	JLabel label15;
	JLabel label16;
	
	JLabel fich1;
	JLabel fich2;
	JLabel fich3;
	JLabel fich4;
	JLabel fich5;
	JLabel fich6;
	JLabel fich7;
	JLabel fich8;
	JLabel fich9;
	JLabel fich10;

	JTextArea textareaUser;

	

	
	boolean acceuil = true;
	boolean testnf;
	boolean testnu;
	boolean testnb;
	boolean testfb;
	
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
		
		/* QUATRIEME JPANEL */
		panel4 = new JPanel();
		panel4.setBackground(Color.black);
		panel4.setBounds(0, 0, 750, 500);
		panel4.setVisible(false);
		panel4.setLayout(null);
		add(panel4);
		
		/* CINQUIEME JPANEL */
		panel5 = new JPanel();
		panel5.setBackground(Color.black);
		panel5.setBounds(0, 0, 750, 500);
		panel5.setVisible(false);
		panel5.setLayout(null);
		add(panel5);
		
		/*  JPANEL INFORMATIONS FICHIERS */
		information_fichiers = new JPanel();
		information_fichiers.setBackground(Color.black);
		information_fichiers.setBounds(0, 0, 750, 500);
		information_fichiers.setVisible(false);
		information_fichiers.setLayout(null);
		add(information_fichiers);
		
		/*  JPANEL INFORMATIONS USERS */
		
		information_user = new JPanel();
		information_user.setBackground(Color.black);
		information_user.setBounds(0, 0, 750, 500);
		information_user.setVisible(false);
		information_user.setLayout(null);
		add(information_user);

		
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
		
		/* NEUVIEME JLABEL */

		label9 = new JLabel();
		label9.setFont(new Font("Comic sans MS", Font.BOLD,35));
		label9.setForeground(Color.green);
		label9.setBounds(125, 0, 800, 100);
		label9.setVisible(true);
		panel4.add(label9);
		
		/* DIXIEME JLABEL */

		label10 = new JLabel();
		label10.setFont(new Font("Comic sans MS", Font.BOLD,20));
		label10.setForeground(Color.green);
		label10.setBounds(0, 150, 600, 30);
		label10.setVisible(true);
		panel4.add(label10);
		
		/* ONZIEME JLABEL */

		label11 = new JLabel();
		label11.setFont(new Font("Comic sans MS", Font.BOLD,20));
		label11.setForeground(Color.green);
		label11.setBounds(0, 200, 600, 30);
		label11.setVisible(true);
		panel4.add(label11);
		

		/* DOUZIEME JLABEL */

		label12 = new JLabel();
		label12.setFont(new Font("Comic sans MS", Font.BOLD,20));
		label12.setForeground(Color.green);
		label12.setBounds(0, 250, 600, 30);
		label12.setVisible(true);
		panel4.add(label12);
		
		/* TREIZIEME JLABEL */

		label13 = new JLabel();
		label13.setFont(new Font("Comic sans MS", Font.BOLD,20));
		label13.setForeground(Color.green);
		label13.setBounds(0, 300, 600, 30);
		label13.setVisible(true);
		panel4.add(label13);
		
		/* QUATORZIEME JLABEL */

		label14 = new JLabel();
		label14.setFont(new Font("Comic sans MS", Font.BOLD,20));
		label14.setForeground(Color.green);
		label14.setBounds(75, 400, 600, 30);
		label14.setVisible(true);
		panel4.add(label14);
		
		/* QUINZIEME JLABEL */

		label15 = new JLabel();
		label15.setFont(new Font("Comic sans MS", Font.BOLD,35));
		label15.setForeground(Color.green);
		label15.setBounds(125, 0, 800, 100);
		label15.setVisible(true);
		panel5.add(label15);	
		
		/* SEIZIEME JLABEL */

		label16 = new JLabel();
		label16.setFont(new Font("Comic sans MS", Font.BOLD,20));
		label16.setForeground(Color.green);
		label16.setBounds(0, 150,600, 30);
		label16.setVisible(true);
		panel5.add(label16);
		
		/* LABELS DES FICHIERS */
		
		fich1 = new JLabel();
		fich1.setFont(new Font("Comic sans MS", Font.BOLD,15));
		fich1.setForeground(Color.green);
		fich1.setBounds(0,75,600,30);
		fich1.setVisible(false);
		information_fichiers.add(fich1);
		
		fich2 = new JLabel();
		fich2.setFont(new Font("Comic sans MS", Font.BOLD,15));
		fich2.setForeground(Color.green);
		fich2.setBounds(0,100,600,30);
		fich2.setVisible(false);
		information_fichiers.add(fich2);
		
		fich3= new JLabel();
		fich3.setFont(new Font("Comic sans MS", Font.BOLD,15));
		fich3.setForeground(Color.green);
		fich3.setBounds(0,125,600,30);
		fich3.setVisible(false);
		information_fichiers.add(fich3);

		
		fich4 = new JLabel();
		fich4.setFont(new Font("Comic sans MS", Font.BOLD,15));
		fich4.setForeground(Color.green);
		fich4.setBounds(0,150,600,30);
		fich4.setVisible(false);
		information_fichiers.add(fich4);

		
		fich5 = new JLabel();
		fich5.setFont(new Font("Comic sans MS", Font.BOLD,15));
		fich5.setForeground(Color.green);
		fich5.setBounds(0,175,600,30);
		fich5.setVisible(false);
		information_fichiers.add(fich5);
		
		fich6 = new JLabel();
		fich6.setFont(new Font("Comic sans MS", Font.BOLD,15));
		fich6.setForeground(Color.green);
		fich6.setBounds(0,200,600,30);
		fich6.setVisible(false);
		information_fichiers.add(fich6);
		
		fich7 = new JLabel();
		fich7.setFont(new Font("Comic sans MS", Font.BOLD,15));
		fich7.setForeground(Color.green);
		fich7.setBounds(0,225,600,30);
		fich7.setVisible(false);
		information_fichiers.add(fich7);
		
		fich8 = new JLabel();
		fich8.setFont(new Font("Comic sans MS", Font.BOLD,15));
		fich8.setForeground(Color.green);
		fich8.setBounds(0,250,600,30);
		fich8.setVisible(false);
		information_fichiers.add(fich8);
		
		fich9 = new JLabel();
		fich9.setFont(new Font("Comic sans MS", Font.BOLD,15));
		fich9.setForeground(Color.green);
		fich9.setBounds(0,275,600,30);
		fich9.setVisible(false);
		information_fichiers.add(fich9);
		
		fich10 = new JLabel();
		fich10.setFont(new Font("Comic sans MS", Font.BOLD,15));
		fich10.setForeground(Color.green);
		fich10.setBounds(0,300,600,30);
		fich10.setVisible(false);
		information_fichiers.add(fich10);


			/* TEXTAREA DES USERS */
		textareaUser = new JTextArea();
		textareaUser.setFont(new Font("Comic sans MS", Font.BOLD,15));
		textareaUser.setForeground(Color.green);
		textareaUser.setBackground(Color.black);
		textareaUser.setBounds(0, 100, 600, 400);
		textareaUser.setEditable(false);
		textareaUser.setVisible(true);
		information_user.add(textareaUser);
				
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
		
			/* JBUTTON QUITTER */
		
		quitter = new JButton("Quitter");
		quitter.setFont(new Font("Comic sans MS", Font.BOLD, 25));
		quitter.setForeground(Color.black);
		quitter.setBackground(Color.green);
		quitter.setBounds(575, 400, 150, 50);
		quitter.setVisible(false);
		quitter.addActionListener(click);
		panel2.add(quitter);
		
		
			/* JBUTTON infos fichiers */
		infoFichiers = new JButton("Infos Fichiers");
		infoFichiers.setFont(new Font("Comic sans MS", Font.BOLD, 15));
		infoFichiers.setForeground(Color.black);
		infoFichiers.setBackground(Color.green);
		infoFichiers.setBounds(500, 152, 140, 25);
		infoFichiers.setVisible(false);
		infoFichiers.addActionListener(click);
		panel4.add(infoFichiers);
		
			/* JBUTTON infos users */
		infoUsers = new JButton("Infos Utilisateurs");
		infoUsers.setFont(new Font("Comic sans MS", Font.BOLD, 15));
		infoUsers.setForeground(Color.black);
		infoUsers.setBackground(Color.green);
		infoUsers.setBounds(525, 202, 170, 25);
		infoUsers.setVisible(false);
		infoUsers.addActionListener(click);
		panel4.add(infoUsers);
		
			/* JBUTTON RETOUR1 */
		
		retour1 = new JButton("Retour");
		retour1.setFont(new Font("Comic sans MS", Font.BOLD, 25));
		retour1.setForeground(Color.black);
		retour1.setBackground(Color.green);
		retour1.setBounds(600, 400, 120, 50);
		retour1.setVisible(false);
		retour1.addActionListener(click);
		panel3.add(retour1);
		
			/* JBUTTON RETOUR2 */
		
		retour2 = new JButton("Retour");
		retour2.setFont(new Font("Comic sans MS", Font.BOLD, 25));
		retour2.setForeground(Color.black);
		retour2.setBackground(Color.green);
		retour2.setBounds(600, 400, 120, 50);
		retour2.setVisible(false);
		retour2.addActionListener(click);
		panel4.add(retour2);
		
			/* JBUTTON RETOUR3 */
		
		retour3 = new JButton("Retour");
		retour3.setFont(new Font("Comic sans MS", Font.BOLD, 25));
		retour3.setForeground(Color.black);
		retour3.setBackground(Color.green);
		retour3.setBounds(600, 400, 120, 50);
		retour3.setVisible(false);
		retour3.addActionListener(click);
		information_fichiers.add(retour3);
		
		
			/* JBUTTON RETOUR4 */
		
		retour4 = new JButton("Retour");
		retour4.setFont(new Font("Comic sans MS", Font.BOLD, 25));
		retour4.setForeground(Color.black);
		retour4.setBackground(Color.green);
		retour4.setBounds(600, 400, 120, 50);
		retour4.setVisible(false);
		retour4.addActionListener(click);
		information_user.add(retour4);
			
			/* JBUTTON RETOUR5 */
		
		retour5 = new JButton("Retour");
		retour5.setFont(new Font("Comic sans MS", Font.BOLD, 25));
		retour5.setForeground(Color.black);
		retour5.setBackground(Color.green);
		retour5.setBounds(600, 400, 120, 50);
		retour5.setVisible(false);
		retour5.addActionListener(click);
		panel5.add(retour5);
	}	
							
											/* ANIMATION 1 */
							
	 void  animation1(JLabel label1, String s1, JLabel label2, String s2,JButton start) {
		Timer timer = new Timer(50, new ActionListener() {
			boolean test = true;
			String texte;

			public void actionPerformed(ActionEvent e) {
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
	
	 									/* ANIMATION 2 */
	 
	 
	 void  animation2(JLabel label, String s1, JButton infos_superblock,String s2, JButton verif_superblock,String s3, JButton verif_tableinodes, String s4 , JButton defrag , String s5) {
		Timer timer = new Timer(15, new ActionListener() {
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
						quitter.setVisible(true);
						((Timer) e.getSource()).stop();

					}
				}
			}


		});
		timer.start();

	}
	
	 															/* ANIMATION 3*/
	 
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
	 
	 													/* ANIMATION 4 */
	
	 void  animation4(JLabel Titre, String s1, JLabel NbFichiers,String s2, JLabel NbUsers,String s3, JLabel NbBlocks, String s4 , JLabel FirstByte , String s5,JLabel Conclusionsp) {
			Timer timer = new Timer(25, new ActionListener() {
				boolean test1 = true;
				boolean test2 = true;
				boolean test3 = true;
				boolean test4 = true;
				boolean test5 = true;
				String texte;
				String s6 = "";
			

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
					else if (i < s5.length() && test5) {
						texte = FirstByte.getText();
						texte += s5.charAt(i);
						FirstByte.setText(texte);
						i++;
						if (i >= s5.length()) {
							i =0;
							test5 = false;
							if (testnf && testnu && testnb && testfb) {
								s6 = "Les informations du SuperBlock sont correctes !";
							}
							else {
								s6 = "Les informations du SuperBlock sont éronnées !";
							}

						}
					}
					else {
						texte=Conclusionsp.getText();
						texte += s6.charAt(i);
						Conclusionsp.setText(texte);
						i++;
						if (i >= s6.length()) {
							i = 0;
							retour2.setVisible(true);
							infoFichiers.setVisible(true);
							infoUsers.setVisible(true);
							((Timer) e.getSource()).stop();
						}
					}
				}


			});
			timer.start();

		}
	
	 	 
	 
	 
	
	private class Clicklistener implements ActionListener{

		@SuppressWarnings("static-access")
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
					tab = prog.informationSuperBlock();
				} catch (IOException e1) {
				}
				String NombresFichiers = "Il y a " + tab[0] + " fichiers"; 
				String NombresUsers = "Il y a " + tab[1] + " Utilisateurs";
				String NombreBlock = "Il y a " + tab[2] + " Blocks Utilisés";
				String FirstByte = "Le premier Byte de Libre est à la position " + tab[3];
				animation3(label4," Informations SuperBlock",label5,NombresFichiers,label6,NombresUsers,label7,NombreBlock,label8 , FirstByte);
			}
			
			else if (e.getSource() == retour1 || e.getSource() == retour2 || e.getSource() == retour5) {
				setContentPane(panel2);
				retour1.setVisible(false);retour2.setVisible(false);infoFichiers.setVisible(false);information_user.setVisible(false);retour5.setVisible(false);
				label4.setText("");label5.setText("");label6.setText("");label7.setText("");label8.setText("");
				label9.setText("");label10.setText("");label11.setText("");label12.setText("");label13.setText("");label14.setText("");
				label15.setText("");label16.setText("");

			}
			
			else if (e.getSource() == retour3 || e.getSource() == retour4) {
				setContentPane(panel4);
			}
			
			
			else if (e.getSource() == verif_superblock ) {
			    testnf = false;
				testnu = false;
				testnb = false;
				testfb = false;
				String verifsp =" Vérifications du Superblock";
				String verifnf = "Vérification du nombre de fichiers ...";
				String verifnd = "Vérification du nombre d'utilisateurs ...";
				String verifnb = "Vérification du nombre de blocks ...";
				String veriffb = "Vérification du premier byte disponible ...";
				try {prog.informationSuperBlock();} catch (IOException e1) {}
				try {if (prog.verifierNombreFichiers()) {verifnf += "   Vérifié !"; testnf = true;}else {verifnf += "    ERREUR ";}}catch (IOException e1) {}
				try {if (prog.verifNombreUsers())  {verifnd += "   Vérifié !";testnu = true;}else {verifnd += "    ERREUR ";}}catch (IOException e1) {}
				try {if (prog.verifNombreblocks())  {verifnb += "   Vérifié !";testnb = true;}else {verifnb += "    ERREUR ";}}catch (IOException e1) {}
				try {if (prog.verifFirstFreeByte()) {veriffb += "   Vérifié !";testfb = true;}else {veriffb += "    ERREUR ";}}catch (IOException e1) {}

				setContentPane(panel4);
				panel4.setVisible(true);

				animation4(label9,verifsp, label10,verifnf,label11,verifnd,label12,verifnb, label13,veriffb,label14);
			}
			
			
			else if (e.getSource() == infoFichiers) {
				setContentPane(information_fichiers);
				for (i = 0; i < prog.Nombre_de_fichier; i++) {
					switch(i) {
					case 0:
						try {fich1.setText("fichier numéro " + (i+1) +" :" + prog.nom_Fichier(i));fich1.setVisible(true);} catch (IOException e1) {} break;
					case 1:
						try {fich2.setText("fichier numéro " + (i+1) +" :" + prog.nom_Fichier(i));fich2.setVisible(true);} catch (IOException e1) {}break;
					case 2:
						try {fich3.setText("fichier numéro " + (i+1) +" :" + prog.nom_Fichier(i));fich3.setVisible(true);} catch (IOException e1) {}break;
					case 3:
						try {fich4.setText("fichier numéro " + (i+1) +" :" + prog.nom_Fichier(i));fich4.setVisible(true);} catch (IOException e1) {}break;
					case 4:
						try {fich5.setText("fichier numéro " + (i+1) +" :" + prog.nom_Fichier(i));fich5.setVisible(true);} catch (IOException e1) {}break;
					case 5:
						try {fich6.setText("fichier numéro " + (i+1) +" :" + prog.nom_Fichier(i));fich6.setVisible(true);} catch (IOException e1) {}break;
					case 6:
						try {fich7.setText("fichier numéro " + (i+1) +" :" + prog.nom_Fichier(i));fich7.setVisible(true);} catch (IOException e1) {}break;
					case 7:
						try {fich8.setText("fichier numéro " + (i+1) +" :" + prog.nom_Fichier(i));fich8.setVisible(true);} catch (IOException e1) {}break;
					case 8:
						try {fich9.setText("fichier numéro " + (i+1) +" :" + prog.nom_Fichier(i));fich9.setVisible(true);} catch (IOException e1) {}break;
					case 9:
						try {fich10.setText("fichier numéro " + (i+1) +" :" + prog.nom_Fichier(i));fich10.setVisible(true);} catch (IOException e1) {}break;
					
					}
				}
				i=0;
				information_fichiers.setVisible(true);
				retour3.setVisible(true);
			}
			
			else if (e.getSource() == infoUsers) {
				setContentPane(information_user);
				information_user.setVisible(true);
				try {
					prog.raf.seek(prog.premierByteUsers);
				} catch (IOException e2) {}
				Arrays.fill(prog.tab, (byte) 1);
				String textuser = "Utilisateur 1 : ";
				boolean attendrefinligne;
				int compteur_user = 1;
					attendrefinligne = false;
					while((char)prog.tab[0] != '\3') {
						try {
							prog.raf.read(prog.tab,0,1);
						} catch (IOException e1) {}
						if ((char)prog.tab[0] == ':') {
							textuser += '\n';
							attendrefinligne = true; 
						}
						else if((char) prog.tab[0] == '\n') {
							compteur_user++;
							try {
								prog.raf.read(prog.tab,0,1);
							} catch (IOException e1) {}
							if ((char) prog.tab[0] !='\3') {
								textuser += ("Utilisateur " + compteur_user +" : " );
							}
							attendrefinligne = false;
						}
						else if (!attendrefinligne && (char) prog.tab[0] != '\3') {
							textuser += (char)prog.tab[0];
						
					}
				}
				textareaUser.setText(textuser);
				retour4.setVisible(true);
			}
			
			else if (e.getSource() == verif_tableinodes) {
				setContentPane(panel5);
				String veriftb = "Verification de la table des inodes en cours ... ";
				try {
					if (prog.verifTablesInodes()) {veriftb += "CORRECTE !";}else{veriftb += "ERREUR !";}} catch (IOException e1) {}
				panel5.setVisible(true);
				animation1(label15, "Vérification de la Table d'Inodes", label16, veriftb, retour5);
			}
			
			else if (e.getSource() == quitter) {
				System.exit(0);
			}
			
				
				
				
			
		}
		
	}

}
