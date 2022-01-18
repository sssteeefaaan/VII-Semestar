import java.io.BufferedWriter;
import java.io.IOException;

import AST.Expression;
import AST.Statement;

public class ExitStatement extends Statement{
    private Expression exitExpression;
    public String exitLabel;

    public ExitStatement(Expression exitExpression){
        this.exitExpression = exitExpression;
    }
    
    @Override
    public void translate(BufferedWriter out) throws IOException {
        exitExpression.translate(out);
        exitExpression.genLoad( "R1", out );
        out.write( "\tJumpIfNotZero R1, " + this.exitLabel + "\n" );
    }
}
