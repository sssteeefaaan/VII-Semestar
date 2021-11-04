
public class SyntaxTable {
	 public int[][] matrix;
     public static final int ERROR = -3;
     public static final int ACCEPT = -1;
     public final static int POP = -2;
       
     public SyntaxTable()
     {
        matrix = new int[sym.Count][sym.TerminalCount];
           
            //initialize with ERROR
            for(int i = 0; i< sym.Count; i++)
            {
                for(int j= 0; j<sym.TerminalCount; j++)
                {
                    matrix[i][j] = ERROR;
                }
            }
           
            //ACTION: POP
            matrix[sym.SELECT][sym.SELECT] = POP;
            matrix[sym.BEGIN][sym.BEGIN] = POP;
            matrix[sym.END][sym.END] = POP;
            matrix[sym.ID][sym.ID] = POP;
            matrix[sym.CONST][sym.CONST] = POP;
            matrix[sym.ASSIGN][sym.ASSIGN] = POP;
            matrix[sym.SEMICOLON][sym.SEMICOLON] = POP;
            matrix[sym.CASE][sym.CASE] = POP;
            matrix[sym.ARROW][sym.ARROW] = POP;
            
            //ACTION: ACCEPT
            matrix[sym.EOF][sym.EOF] = ACCEPT;
           
            //ACTION: RULES
            matrix[sym.SelectStatement][sym.SELECT] = 0;
            matrix[sym.CaseList][sym.CASE] = 1;
            matrix[sym.CaseListP][sym.CASE] = 1;
            matrix[sym.CaseListP][sym.END] = 2;
            matrix[sym.Case][sym.CASE] = 3;
            matrix[sym.Statement][sym.SELECT] = 4;
            matrix[sym.Statement][sym.ID] = 5;
            matrix[sym.StatementP][sym.ID] = 6;
            matrix[sym.StatementP][sym.CONST] = 7;
            
        }
}
