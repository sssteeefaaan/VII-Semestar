package AST;


import java.io.*;

public abstract class ASTNode {
	
//	broj kreiranih privremenih promenljivih
	private static int varNo;
	
	//broj kreiranih labela
	private static int labNo;
	
	public static String genVar()
	{
		//trebalo bi kreiranu promenljivu upisati
		//u tabelu simbola
		return "$tmp" + varNo++;
	}
	
	public static String genLab()
	{
		return "lab" + labNo++;
	}
	
	public abstract void translate( BufferedWriter out )
	throws IOException;
}
