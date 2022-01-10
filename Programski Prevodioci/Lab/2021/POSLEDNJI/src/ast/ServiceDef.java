package ast;

import java.io.BufferedWriter;
import java.io.IOException;

public class ServiceDef extends ASTNode{

    protected AdaptationRule adaptationRule;

    public ServiceDef(AdaptationRule a){
        this.adaptationRule=a;
    }

    @Override
    public void translate(BufferedWriter out) throws IOException {
        this.adaptationRule.translate(out);
    }
}
