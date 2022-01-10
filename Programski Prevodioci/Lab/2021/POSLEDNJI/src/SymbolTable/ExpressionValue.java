package SymbolTable;

public class ExpressionValue {
	
	public Type type;
	public Object value;
	
	public ExpressionValue(Type type, Object value)
	{
		this.type = type;
		this.value = value;
	}
}
