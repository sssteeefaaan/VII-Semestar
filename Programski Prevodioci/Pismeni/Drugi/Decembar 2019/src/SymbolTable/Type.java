package SymbolTable;

public class Type extends SymbolNode {
	public static int INTCONST = 0;
	public static int STRINGCONST = 1;
	public static int REALCONST = 2;
	public static int UNKNOWN = 3;
	public int tkind;
	
	public Type ( String name, 
			int typeKind, 
			SymbolNode next)
	{
		super( name, SymbolNode.TYPE, null, next );
		this.tkind = typeKind;
		this.type = this;
	}
}
