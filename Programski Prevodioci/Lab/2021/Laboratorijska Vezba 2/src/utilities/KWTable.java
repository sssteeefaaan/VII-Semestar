package utilities;

import java.util.Hashtable;
public class KWTable {
    
    private Hashtable<String, Integer> m_Table;

    public KWTable()
    {
        this.m_Table = new Hashtable<>();

        this.m_Table.put("int", sym.INT);
        this.m_Table.put("double", sym.DOUBLE);
        this.m_Table.put("string", sym.STRING);
        this.m_Table.put("bool", sym.BOOL);
        this.m_Table.put("char", sym.CHAR);
        this.m_Table.put("repeat", sym.REPEAT);

        this.m_Table.put("true", sym.CONST);
        this.m_Table.put("false", sym.CONST);
    }

    public int find(String keyword)
    {
        Object symbol = this.m_Table.get(keyword);

        if(symbol != null)
            return ((Integer)symbol).intValue();

        return sym.ID;
    }
}
