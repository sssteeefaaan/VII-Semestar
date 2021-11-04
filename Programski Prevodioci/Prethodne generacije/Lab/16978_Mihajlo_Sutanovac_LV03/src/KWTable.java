import java.util.Hashtable;

public class KWTable {
	private Hashtable<String, Integer> mTable;
	public KWTable()
	{
		// Inicijalizcaija hash tabele koja pamti kljucne reci
		mTable = new Hashtable<String, Integer>();
		mTable.put("program", new Integer(sym.PROGRAM));
		mTable.put("real", new Integer(sym.REAL));
		mTable.put("boolean", new Integer(sym.BOOLEAN));
		mTable.put("integer", new Integer(sym.INTEGER));
		mTable.put("char", new Integer(sym.CHAR));
		mTable.put("begin", new Integer(sym.BEGIN));
		mTable.put("end", new Integer(sym.END));
		mTable.put("select", new Integer(sym.SELECT));
		mTable.put("case", new Integer(sym.CASE));
		mTable.put("or", new Integer(sym.OR));
		mTable.put("and", new Integer(sym.AND));
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
