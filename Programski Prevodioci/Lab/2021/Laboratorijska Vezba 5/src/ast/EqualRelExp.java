package ast;

public class EqualRelExp extends RelExpression {
	
    public EqualRelExp(Term left, Term right){
        super(right);
        this.right = right;
    }

	protected String relOp(){
        return "Compare_equal";
    }	
}