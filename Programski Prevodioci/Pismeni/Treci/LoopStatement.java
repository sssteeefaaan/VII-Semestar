import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;

import AST.ASTNode;
import AST.Statement;
import AST.TestExpression;
import AST.TestStatement;

public class LoopStatement extends Statement{
    private ArrayList<Statement> statementList;

    public LoopStatement(ArrayList<Statement> statementList){
        this.statementList = new ArrayList<>(statementList);
    }
    @Override
    public void translate(BufferedWriter out) throws IOException {
        String  startLab = ASTNode.genLab(),
                endLab = ASTNode.genLab();

        out.write( startLab + ":\n" );
        
        for(Statement s : statementList ){
            if( s instanceof ExitStatement )
                ((ExitStatement)s).exitLabel = endLab;
            s.translate(out);
        }

        out.write( "\tJump " + startLab + "\n" );
        out.write( endLab + ":\n" );
    }
    
    public static void main( String[] args ) throws Exception
    {
        LoopStatement ls = new LoopStatement(new ArrayList<>(){{
            add(new TestStatement("Test 1"));
            add(new TestStatement("Test 2"));
            add(new TestStatement("Test 3"));
            add(new TestStatement("Test 4"));
            add(new ExitStatement(new TestExpression("Exit")));
            add(new TestStatement("Test 6"));
        }});

        BufferedWriter bw = new BufferedWriter( new OutputStreamWriter( System.out ));
        ls.translate( bw );
        bw.flush();
    }
}
