package ast;

import java.io.BufferedWriter;
import java.io.IOException;
import java.util.ArrayList;

public class WhileStatement extends Statement {
	private ArrayList<Statement> statements;
	private Term term;
	
	public WhileStatement(Term term, ArrayList<Statement> statements)
	{
		this.term = term;
        this.statements = new ArrayList<Statement>(statements);
	}
	
	public void translate( BufferedWriter out )
	throws IOException 
	{
        String tempVal = ASTNode.genVar();
        String startLab = ASTNode.genLab(),
        endLab = ASTNode.genLab();

        this.term.translate(out);
        this.term.genLoad("R1", out);
        out.write(startLab + ":");
        out.newLine();
        out.write("\tJumpIfZero\t\t R1, " + endLab);
        out.newLine();
        out.write("\tStore\t\t R1, " + tempVal);
        out.newLine();

        this.statements.forEach(s->{
            try {
                s.translate(out);
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        out.write("\tLoad\t\t R1, " + tempVal);
        out.newLine();
        out.write("\tLoad_Const\t\t R2, 1");
        out.newLine();
        out.write("\tSub\t\t R1, R2");
        out.newLine();
        out.write("\tJumb\t\t" + startLab);
        out.newLine();
        out.write(endLab + ":");
		out.newLine();
	}
}
