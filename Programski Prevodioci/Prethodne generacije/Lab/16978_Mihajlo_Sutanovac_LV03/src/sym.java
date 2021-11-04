
public class sym {
	public final static int EOF = 0;
	public final static int PROGRAM = 1;
	public final static int BEGIN = 2;
	public final static int END = 3;
	public final static int ID = 4;
	public final static int INTEGER = 5;
	public final static int CHAR = 6;
	public final static int REAL = 7;
	public final static int BOOLEAN = 8;
	public final static int SELECT = 9;
	public final static int CASE = 10;
	public final static int OR = 11;
	public final static int AND = 12;
	public final static int LESS = 13;
	public final static int LESSEQUAL = 14;
	public final static int EQUAL = 15;
	public final static int NOTEQUAL = 16;
	public final static int GREATER = 17;
	public final static int GREATEREQUAL = 18;
	public final static int CONST = 19;
	public final static int LEFTPAR = 20;
	public final static int RIGHTPAR = 21;
	public final static int ASSIGN = 22;
	public final static int SEMICOLON = 23;
	public final static int COMMA = 24;
	public final static int DOT = 25;
	public final static int COLON = 26;
	public final static int ARROW = 27;
	
	
	//non-terminal symobls
	public final static int SelectStatement=28;
	public final static int CaseList=29;
	public final static int CaseListP=30;
	public final static int Case=31;
	public final static int Statement=32;
	public final static int StatementP=33;
	
	//counters
	public final static int TerminalCount=28;
	public final static int Count=34;
}
