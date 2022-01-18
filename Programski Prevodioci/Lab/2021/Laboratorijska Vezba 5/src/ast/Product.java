package ast;

public class Product extends Expression {
	
	public Product( Expression left, Term right )
	{
		super(right);
		this.left = left;
	}
	
	protected String opCode()
	{
		return "Mul";
	}
}
