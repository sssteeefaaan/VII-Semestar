package SymbolTable;

public class Constant {
	public Type type;
	public Object value;
	public Constant( Type constType, Object constValue )
	{
		type = constType;
		value = constValue;
	}
}
