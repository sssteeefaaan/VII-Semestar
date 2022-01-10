package ast;

public class LessRelExp extends RelExpression {
	
    public LessRelExp(Term left, Term right){
        super(right);
        this.right = right;
    }

	protected String relOp(){
        return "Compare_Less";
    }	
}