package ast;

public class Sum extends Expression {
	
	public Sum( Expression left, Term right )
	{
		super(right);
		this.left = left;
	}
	
	protected String opCode()
	{
		return "Add";
	}
}
