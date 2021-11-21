import java.util.Hashtable;
public class KWTable {
    
    private Hashtable<String, Integer> m_Table;

    public KWTable()
    {
        this.m_Table = new Hashtable<>();

        this.m_Table.put("strategy", sym.STRATEGY_BEGIN);
        this.m_Table.put("~strategy", sym.STRATEGY_END);
        this.m_Table.put("declaration", sym.DECLARATION_BEGIN);
        this.m_Table.put("~declaration", sym.DECLARATION_END);
        this.m_Table.put("int", sym.INT);
        this.m_Table.put("double", sym.DOUBLE);
        this.m_Table.put("string", sym.STRING);
        this.m_Table.put("bool", sym.BOOL);
        this.m_Table.put("char", sym.CHAR);
        this.m_Table.put("repeat", sym.REPEAT);
        this.m_Table.put("less", sym.LESS);
        this.m_Table.put("equal", sym.EQUAL);
        this.m_Table.put("greater", sym.GREATER);
        this.m_Table.put("numInstances", sym.NUM_INSTANCES);
        this.m_Table.put("service", sym.SERVICE_BEGIN);
        this.m_Table.put("~service", sym.SERVICE_END);
        this.m_Table.put("serviceName", sym.SERVICE_NAME);
        this.m_Table.put("executedBy", sym.EXECUTED_BY);
        this.m_Table.put("if", sym.IF);
        this.m_Table.put("then", sym.THEN);
        this.m_Table.put("scale", sym.SCALE);
        this.m_Table.put("redeployOn", sym.REDEPLOY_ON);
        this.m_Table.put("optimize", sym.OPTIMIZE);
    }

    public int find(String keyword)
    {
        Object symbol = this.m_Table.get(keyword);

        if(symbol != null)
            return ((Integer)symbol).intValue();

        return sym.ID;
    }
}
