package SymbolTable;

public class Type extends SymbolNode {
	public static int UNKNOWN = 0;
	public static int INT = 1;
	public static int DOUBLE = 3;
	public static int BOOL = 4;
	public static int CHAR = 5;
	public static int STRING = 6;
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
