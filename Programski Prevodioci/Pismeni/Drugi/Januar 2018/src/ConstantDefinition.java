import SymbolTable.Constant;

public class ConstantDefinition{
    public String id;
    public Constant constant;

    public ConstantDefinition(String id, Constant constant){
        this.id = id;
        this.constant = constant;
    }
}