
public class SyntaxTableLR {
	private STObject[][] table;
	   
    
    public SyntaxTableLR(){
        table = new STObject[20][15];
        
        
        for(int i = 0; i <19; i++){
            for(int j = 0; j<14; j++){
                table[i][j] = new STObject("err", -1);
            }
        }
        
        //shifts
        table[0][sym2.LOOP] = new STObject("s", 2);
        table[2][sym2.LEFTBRACKET] = new STObject("s", 3);
        table[3][sym2.ID] = new STObject("s", 16);
        table[3][sym2.CONST] = new STObject("s", 17);
        table[4][sym2.RIGHTBRACKET] = new STObject("s", 5);
        table[4][sym2.LOGICOR] = new STObject("s", 12);
        table[5][sym2.LOOP] = new STObject("s", 2);
        table[5][sym2.ID] = new STObject("s", 8);
        table[8][sym2.ASSIGN] = new STObject("s", 9);
        table[9][sym2.ID] = new STObject("s", 16);
        table[9][sym2.CONST] = new STObject("s", 17);
        table[10][sym2.SEMICOLON] = new STObject("s", 11);
        table[12][sym2.ID] = new STObject("s", 16);
        table[12][sym2.CONST] = new STObject("s", 17);
        table[13][sym2.LOGICAND] = new STObject("s", 14);
        table[14][sym2.ID] = new STObject("s", 16);
        table[14][sym2.CONST] = new STObject("s", 17);
      
        
        //accept 
        table[1][sym2.EOF] = new STObject("acc", -1);
        
        //reductions
        table[6][sym2.EOF] = new STObject("r",1);
        table[7][sym2.EOF] = new STObject("r", 8);
        table[11][sym2.EOF] = new STObject("r", 9);
        table[13][sym2.RIGHTBRACKET] = new STObject("r", 2);
        table[13][sym2.LOGICOR] = new STObject("r", 2);
        table[13][sym2.SEMICOLON] = new STObject("r", 2);
        table[15][sym2.RIGHTBRACKET] = new STObject("r", 4);
        table[15][sym2.LOGICOR] = new STObject("r", 4);
        table[15][sym2.LOGICAND] = new STObject("r", 4);
        table[15][sym2.SEMICOLON] = new STObject("r", 4);
        table[16][sym2.RIGHTBRACKET] = new STObject("r", 6);
        table[16][sym2.LOGICOR] = new STObject("r", 6);
        table[16][sym2.LOGICAND] = new STObject("r", 6);
        table[16][sym2.SEMICOLON] = new STObject("r", 6);
        table[17][sym2.RIGHTBRACKET] = new STObject("r", 7);
        table[17][sym2.LOGICOR] = new STObject("r", 7);
        table[17][sym2.LOGICAND] = new STObject("r", 7);
        table[17][sym2.SEMICOLON] = new STObject("r", 7);
        table[18][sym2.RIGHTBRACKET] = new STObject("r", 5);
        table[18][sym2.LOGICOR] = new STObject("r", 5);
        table[18][sym2.LOGICAND] = new STObject("r", 5);
        table[18][sym2.SEMICOLON] = new STObject("r", 5);
        table[19][sym2.RIGHTBRACKET] = new STObject("r", 3);
        table[19][sym2.LOGICOR] = new STObject("r", 3);
        table[19][sym2.SEMICOLON] = new STObject("r", 3);
        
        
        //goto
        table[0][sym2.RedoLoop] = new STObject("goto", 1);
        table[3][sym2.Expression] = new STObject("goto", 4);
        table[3][sym2.AndExpression] = new STObject("goto", 19);
        table[3][sym2.Term] = new STObject("goto", 18);
        table[5][sym2.RedoLoop] = new STObject("goto", 7);
        table[5][sym2.Statement] = new STObject("goto", 6);
        table[9][sym2.AndExpression] = new STObject("goto", 19);
        table[9][sym2.Term] = new STObject("goto",18);
        table[12][sym2.AndExpression] = new STObject("goto",13);
        table[12][sym2.Term] = new STObject("goto",18);
        table[14][sym2.Term] = new STObject("goto",15);
}
    STObject getSTObject(int i, int j){
        return table[i][j];
    }
}
