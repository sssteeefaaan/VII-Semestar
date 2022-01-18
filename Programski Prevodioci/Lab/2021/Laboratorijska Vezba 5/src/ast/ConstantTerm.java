package ast;



import java.io.*;

import SymbolTable.Constant;

public class ConstantTerm 
extends Term{
	private Constant targetConst;
	
	public ConstantTerm( Constant c )
	{
		targetConst = c;
	}
	
	public void translate( BufferedWriter out )
	throws IOException
	{
		this.result = targetConst.value.toString();
	}
	
	protected void genLoad( String reg, BufferedWriter out )
	throws IOException
	{
		out.write( "\tLoad_Const\t" + 
				reg + ", " + result );
		out.newLine();
	}
}
