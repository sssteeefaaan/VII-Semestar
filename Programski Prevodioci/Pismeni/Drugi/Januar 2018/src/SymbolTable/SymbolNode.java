package SymbolTable;

import java.util.ArrayList;

public class SymbolNode {
	public static int TYPE = 0;
	public static int VARIABLE = 1;
	
	public String name;
	public int kind;
	public Type type;
	public SymbolNode next;
	
	public SymbolNode( String symbolName, 
			int symbolKind, 
			Type symbolType, 
			SymbolNode nextSymbol)
	{
		name = symbolName;
		kind = symbolKind;
		type = symbolType;
		next = nextSymbol;
	}
	
}
