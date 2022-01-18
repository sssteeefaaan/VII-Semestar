import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;

import AST.ASTNode;
import AST.Expression;
import AST.TestExpression;

public class SelectExpression extends Expression{

    private ArrayList<Expression> expressionList;
    private Expression expression;

    public SelectExpression( ArrayList<Expression> expressionList, Expression expression )
    {
        this.expressionList = new ArrayList<>( expressionList );
        this.expression = expression;
    }


    @Override
    public void translate(BufferedWriter out) throws IOException {

        String tempLab = ASTNode.genLab( ),
                endLab = ASTNode.genLab( );

        this.expression.translate( out );
        this.expression.genLoad( "R2", out );

        for(int i = 0; i < this.expressionList.size( ); i++)
        {
            out.write( tempLab + ":\n" );
            out.write( "\tLoad_Const R1, " + i );
            out.write( "\n\tCompare_Equal R1, R2\n" );

            tempLab = ASTNode.genLab( );

            if( i < this.expressionList.size() - 1)
            {
                out.write( "\tJumpIfNotZero R1, " + tempLab + "\n" );
                this.expressionList.get( i ).translate( out );
                this.expressionList.get( i ).genLoad( "R1", out );
                out.write( "\tJump " + endLab + "\n" );
            }
            else{
                out.write( "\tJumpIfNotZero R1, " + endLab + "\n" );
                this.expressionList.get( i ).translate( out );
                this.expressionList.get( i ).genLoad( "R1", out );
            }
        }

        out.write( endLab + ":\n" );
        this.result = ASTNode.genVar();
        out.write("\tStore R1, " + this.result + "\n" );
    }

    public static void main(String[] args) throws IOException{
        SelectExpression se = new SelectExpression( new ArrayList<Expression>(){{
            add( new TestExpression( "Temp 1" ) );
            add( new TestExpression( "Temp 2" ) );
            add( new TestExpression( "Temp 3" ) );
            add( new TestExpression( "Temp 4" ) );
            add( new TestExpression( "Temp 5" ) );
        }}, new TestExpression( "Select" ) );

        BufferedWriter bw = new BufferedWriter( new OutputStreamWriter( System.out ) );
        se.translate( bw );
        bw.flush();
    }

}