package Cos;

import java.io.IOException;

import javax.swing.SwingUtilities;

public class Main {

	public static void main(String[] args) throws IOException {
		
		
		SOS prog = new SOS();
		
		SwingUtilities.invokeLater(new Runnable() {		
			public void run() {
				new Frame("SOS",prog);
				try {
					prog.informationSuperBlock(prog.raf, prog.tab);
				} catch (IOException e) {
				}
			}
		});
		
		
	}
	



}
