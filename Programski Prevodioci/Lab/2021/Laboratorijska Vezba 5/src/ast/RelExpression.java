package ast;

import java.io.*;


public class RelExpression 
extends Term {
	protected Term right;
	protected Term left;

	public RelExpression(Term right){
		this.right=right;
	}
	
	protected String relOp(){
		return "";
	}
	
	public void translate(BufferedWriter out)
	throws IOException
	{
		right.translate(out);
		right.genLoad( "R2", out );
		this.result = ASTNode.genVar();

		if(left != null){
			left.translate(out);
			left.genLoad( "R1", out );
			out.write( "\t" + relOp() + "\t\tR1, R2" );
			out.newLine();
			out.write( "\tStore\t\tR1, " + this.result );
		}else{
			out.write( "\tStore\t\tR2, " + this.result );
		}
		
		out.newLine();
	}	
}



