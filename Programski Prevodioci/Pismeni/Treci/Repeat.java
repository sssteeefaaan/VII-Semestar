/*
	LoadMem R1, TIMES_COUNT
	JumpIfZero R1, default
	Store R1, X
	IMC<Condition>
	LoadMem R1, Res<Condition>
	JumpIfZero R1, default
start:
	<IMC Body>
	
	LoadMem R1, X
	Sub R1, 1
	JumpIfZero R1, end
	Store R1, X
	
	<IMC Condition>
	LoadMem R1, Res<Condition>
	JumpIfZero end
	
	Jump start
default:
	<IMC DefaultStatement>
end:
*/

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.ArrayList;

import AST.*;

public class Repeat extends Statement
{
	private Expression condition;
	private ArrayList<Statement> body;
	private Statement defaultStatement;
	private int TIMES_COUNT;
	
	public Repeat( Expression c, ArrayList<Statement> body, Statement defaultStatement, int TIMES_COUNT ){
		super();
		this.condition = c;
		this.body = new ArrayList<>(body);
		this.defaultStatement = defaultStatement;
		this.TIMES_COUNT = TIMES_COUNT;
	}

	@Override
	public void translate(BufferedWriter out) throws IOException {
		String tempX = ASTNode.genVar();
		String startLab = ASTNode.genLab(),
			defaultLab = ASTNode.genLab(),
			endLab = ASTNode.genLab();
			
		out.write( "\tLoad_Const R1, " + TIMES_COUNT );
		out.write( "\n\tJumpIfZero R1, " + defaultLab );
		out.write( "\n\tStore R1, " + tempX  + "\n");
		
		condition.translate( out );
		condition.genLoad( "R1", out );
		out.write( "\tJumpIfZero R1, " + defaultLab );
		
		out.write( "\n" + startLab + ":\n");
		
		for( Statement s : body )
			s.translate( out );
		
		out.write( "\n\tLoad_Mem R1, " + tempX );
		out.write( "\n\tSub R1, 1" );
		out.write( "\n\tJumpIfZero R1, " + endLab );
		out.write( "\n\tStore R1, " + tempX + "\n" );
		
		condition.translate( out );
		condition.genLoad( "R1", out );
		out.write( "\tJumpIfZero R1, " + endLab );
		
		out.write( "\n\tJump " + startLab );
		
		out.write( "\n" + defaultLab + ":\n");
		
		defaultStatement.translate( out );
		
		out.write( endLab + ":\n" );
	}

	public static void main( String[] args ){
		Repeat test = new Repeat( new TestExpression("Condition"), new ArrayList<Statement>(){{
			add(new TestStatement("Test 1"));
			add(new TestStatement("Test 2"));
			add(new TestStatement("Test 3"));
		}}, new TestStatement("Default"), 5 );
		try {
			BufferedWriter bw =  new BufferedWriter ( new OutputStreamWriter( System.out ) ) ;
			test.translate( bw );
			bw.flush();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}