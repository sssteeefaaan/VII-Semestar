package AST;
import java.io.BufferedWriter;
import java.io.IOException;

public class TestExpression extends Expression {

    private String name = "Test";
    public TestExpression(){
        super();
        this.result = "Res<" + this.name + " Expression>";
    }

    public TestExpression(String name){
        super();
        this.name = name;
        this.result = "Res<" + this.name + " Expression>";
    }

    @Override
    public void translate(BufferedWriter out) throws IOException {
        out.write( "\t<IMC " + this.name +" Expression>\n");
    }
    
}
