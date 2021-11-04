
import java.util.Hashtable;
public class KWTable {

	private Hashtable mTable;
	public KWTable()
	{
		// Inicijalizcaija hash tabele koja pamti kljucne reci
		mTable = new Hashtable();
		mTable.put("main", new Integer(sym.MAIN));
		mTable.put("float", new Integer(sym.FLOAT));
		mTable.put("int", new Integer(sym.INT));
		mTable.put("char", new Integer(sym.CHAR));
		mTable.put("bool", new Integer(sym.BOOL));
		mTable.put("loop", new Integer(sym.LOOP));
		mTable.put("redo", new Integer(sym.REDO));
		
	}
	
	/**
	 * Vraca ID kljucne reci 
	 */
	public int find(String keyword)
	{
		Object symbol = mTable.get(keyword);
		if (symbol != null)
			return ((Integer)symbol).intValue();
		
		// Ako rec nije pronadjena u tabeli kljucnih reci radi se o identifikatoru
		return sym.ID;
	}
	

}
