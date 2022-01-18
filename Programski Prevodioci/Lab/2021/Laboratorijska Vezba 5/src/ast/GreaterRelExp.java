package ast;

public class GreaterRelExp extends RelExpression {
	
    public GreaterRelExp(Term left, Term right){
        super(right);
        this.right = right;
    }

	protected String relOp(){
        return "Compare_greater";
    }	
}