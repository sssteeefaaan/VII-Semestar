package ast;
import java.io.*;

import SymbolTable.Variable;

public class VariableTerm 
extends Term {
	private Variable targetVar;
	
	public VariableTerm( Variable var )
	{
		targetVar = var;
	}
	
	public void translate( BufferedWriter out )
	throws IOException
	{
		this.result = targetVar.name;
	}
}
