
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
        table[0][sym2.SELECT] = new STObject("s", 2);
        table[2][sym2.BEGIN] = new STObject("s", 3);
        table[3][sym2.CASE] = new STObject("s", 8);
        table[4][sym2.END] = new STObject("s", 5);
        table[4][sym2.CASE] = new STObject("s", 8);
        table[8][sym2.ID] = new STObject("s", 9);
        table[9][sym2.ARROW] = new STObject("s", 10);
        table[10][sym2.ID] = new STObject("s", 13);
        table[10][sym2.SELECT] = new STObject("s", 2);
        table[13][sym2.ASSIGN] = new STObject("s", 14);
        table[14][sym2.CASE] = new STObject("s", 8);
        table[14][sym2.ID] = new STObject("s", 15);
        table[14][sym2.CONST] = new STObject("s", 17);
        table[15][sym2.SEMICOLON] = new STObject("s", 16);
        table[17][sym2.SEMICOLON] = new STObject("s", 18);
        
        
        //accept 
        table[1][sym2.EOF] = new STObject("acc", -1);
        
        //reductions
        table[5][sym2.END] = new STObject("r",1);
        table[5][sym2.CASE] = new STObject("r", 1);
        table[5][sym2.EOF] = new STObject("r", 1);
        table[6][sym2.END] = new STObject("r", 2);
        table[6][sym2.CASE] = new STObject("r", 2);
        table[7][sym2.END] = new STObject("r", 3);
        table[7][sym2.CASE] = new STObject("r", 3);
        table[11][sym2.END] = new STObject("r", 4);
        table[11][sym2.CASE] = new STObject("r", 4);
        table[12][sym2.END] = new STObject("r", 5);
        table[12][sym2.CASE] = new STObject("r", 5);
        table[16][sym2.END] = new STObject("r", 6);
        table[16][sym2.CASE] = new STObject("r", 6);
        table[18][sym2.END] = new STObject("r", 7);
        table[18][sym2.CASE] = new STObject("r", 7);
        
        //goto
        table[0][sym2.SelectStatement] = new STObject("goto", 1);
        table[3][sym2.CaseList] = new STObject("goto", 4);
        table[3][sym2.Case] = new STObject("goto", 7);
        table[4][sym2.Case] = new STObject("goto", 6);
        table[10][sym2.SelectStatement] = new STObject("goto", 12);
        table[10][sym2.Statement] = new STObject("goto", 11);
}
    STObject getSTObject(int i, int j){
        return table[i][j];
    }
}
