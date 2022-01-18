package ast;

import java.io.*;


public class AdaptationRule extends ASTNode{
	private RelExpression condition;
	
	public AdaptationRule(RelExpression re)
	{
		this.condition = re;
	}
	
	public void translate( BufferedWriter out )
	throws IOException
	{
		condition.translate( out );
		condition.genLoad( "R1", out );
		String notThen = ASTNode.genLab();
		out.write( "\tJumpIfNotZero\tR1, " + notThen );
		out.newLine();
		out.write("\tIMC<Response>");
		out.newLine();
		out.write(notThen + ":");
		out.newLine();
	}
}


