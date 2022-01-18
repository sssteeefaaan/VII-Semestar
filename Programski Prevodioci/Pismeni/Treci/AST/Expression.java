package AST;
import java.io.*;


public abstract class Expression extends ASTNode{
	
	protected String result;
	
	public void genLoad( String reg, BufferedWriter out ) throws IOException
	{
		out.write( "\tLoad_Mem\t" + 
			reg + ", " + result );
		out.newLine();
	}
}

