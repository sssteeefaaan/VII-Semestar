package ast;
import java.io.*;


public abstract class Term extends ASTNode{
	
	protected String result;
	
	protected void genLoad( String reg,
			BufferedWriter out ) throws IOException
	{
		out.write( "\tLoad_Mem\t\t" + 
			reg + ", " + result );
		out.newLine();
	}
}

