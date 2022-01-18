package ast;

import java.io.BufferedWriter;
import java.io.IOException;
import java.util.ArrayList;

public class Body extends ASTNode{
    public ArrayList<Statement> statements;
    public ArrayList<ServiceDef> serviceList;
    
    public Body(ArrayList<Statement> statements, ArrayList<ServiceDef> serviceList) {
    	this.statements = new ArrayList(statements);
    	this.serviceList = new ArrayList(serviceList);
    }
    
    @Override
    public void translate(BufferedWriter out) throws IOException {
        statements.forEach(s->{
            try {
                s.translate(out);
            } catch (IOException e) {
                e.printStackTrace();
            }
        });

        serviceList.forEach(sl->{
            try {
                sl.translate(out);
            } catch (IOException e) {
                e.printStackTrace();
            }
        });
    }
}
