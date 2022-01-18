import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;

import ast.ASTNode;

public class Main {

	public static void main(String[] args) {
		try
		  {
			FileReader file = new FileReader( args[0] );
			MPLexer scanner = new MPLexer( file );
			MPParser parser = new MPParser( scanner );
			ASTNode ast = (ASTNode) parser.parse().value;
			String outFileName = args[0].substring(0, args[0].indexOf(".") + 1);
			outFileName += "ic";
			BufferedWriter writer = new BufferedWriter(new FileWriter( outFileName ));
			ast.translate( writer );
			writer.close();
			System.out.println("Prevodjenje zavrseno, kod se nalazi u fajlu '" + outFileName + "'");
		  }
		  catch( Exception e )
		  {
			 e.printStackTrace();
		  }
	}

}
