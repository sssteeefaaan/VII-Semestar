package SymbolTable;

public class Variable extends SymbolNode {
	
	public int last_def;
	public int last_use;
	public Object value;
	
	public Variable( String name, 
			Type type, 
			SymbolNode next )
	{
		super( name, SymbolNode.VARIABLE, type, next );
		last_def = -1;
		last_use = -1;
		value = null;
	}
	
}
