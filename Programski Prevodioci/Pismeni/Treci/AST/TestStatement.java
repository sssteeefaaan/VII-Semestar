package AST;

import java.io.BufferedWriter;
import java.io.IOException;

public class TestStatement extends Statement {

    private String name = "Test";

    public TestStatement(){
        super();
    }

    public TestStatement(String name){
        super();
        this.name = name;
    }
    
    @Override
    public void translate(BufferedWriter out) throws IOException {
        out.write( "\t<IMC " + this.name + " Statement>\n");
    }
    
}
