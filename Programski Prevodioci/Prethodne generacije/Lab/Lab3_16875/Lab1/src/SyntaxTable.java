/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


public class SyntaxTable
{
    private SyntaxTableObject[][] table;
    
    public SyntaxTable()
    {
        table = new SyntaxTableObject[20][13];
        
        for (int i = 0; i < 20; i++)
        {
            for(int j = 0; j < 13; j++)
            {
                if (i == j)
                {
                    if (i != 12)
                    {
                        table[i][j] = new SyntaxTableObject("pop");
                    }
                    else
                    {
                        table[i][j] = new SyntaxTableObject("acc");
                    }
                }
                else
                {
                    table[i][j] = new SyntaxTableObject("err");
                }
            }
        }
        
        int[] rightSide0 = { sym.LOOP, sym.LEFTBRACKET, sym.EXPRESSION, sym.RIGHTTBRACKET, sym.LEFTCURLY, sym.STATEMENT, sym.REDO, sym.LEFTBRACKET, sym.EXPRESSION, sym.RIGHTTBRACKET, sym.SEMICOLON, sym.STATEMENT, sym.RIGHTCURLY };
        this.table[sym.REDOLOOP][sym.LOOP] = new SyntaxTableRuleObject(0, rightSide0);
        
        int[] rightSide1 = { sym.ANDEXPRESSION, sym.EXPRESSION1 };
        this.table[sym.EXPRESSION][sym.CONST] = new SyntaxTableRuleObject(1, rightSide1);
        this.table[sym.EXPRESSION][sym.ID] = new SyntaxTableRuleObject(1, rightSide1);

        int[] rightSide2 = { sym.LOGICOR, sym.ANDEXPRESSION,sym.EXPRESSION1};
        this.table[sym.EXPRESSION1][sym.LOGICOR] = new SyntaxTableRuleObject(2 ,rightSide2);
        
        int[] rightSide3 = { sym.EPS };
        this.table[sym.EXPRESSION1][sym.RIGHTTBRACKET] = new SyntaxTableRuleObject(3, rightSide3);
		
	    int[] rightSide4 = { sym.TERM, sym.ANDEXPRESSION1 };
        this.table[sym.ANDEXPRESSION][sym.ID] = new SyntaxTableRuleObject(4, rightSide4);
		this.table[sym.ANDEXPRESSION][sym.CONST] = new SyntaxTableRuleObject(4, rightSide4);
        
        int[] rightSide5 = { sym.ANDEXPRESSION1, sym.LOGICAND,sym.TERM,sym.ANDEXPRESSION1};
        this.table[sym.ANDEXPRESSION1][sym.LOGICAND] = new SyntaxTableRuleObject(5, rightSide5);

        
        int[] rightSide6 = { sym.EPS};
        this.table[sym.ANDEXPRESSION1][sym.LOGICOR] = new SyntaxTableRuleObject(6, rightSide6);
        this.table[sym.ANDEXPRESSION1][sym.RIGHTTBRACKET] = new SyntaxTableRuleObject(6, rightSide6);

        
        int[] rightSide7 = { sym.ID};
        this.table[sym.TERM][sym.ID] = new SyntaxTableRuleObject(7, rightSide7);

        int[] rightSide8 = { sym.CONST};
        this.table[sym.TERM][sym.CONST] = new SyntaxTableRuleObject(8, rightSide8);

        int[] rightSide9 = { sym.REDOLOOP};
        this.table[sym.STATEMENT][sym.LOOP] = new SyntaxTableRuleObject(9, rightSide9);

        int[] rightSide10 = { sym.ID, sym.EQUAL,sym.EXPRESSION};
        this.table[sym.STATEMENT][sym.EQUAL] = new SyntaxTableRuleObject(10, rightSide10);
        this.table[sym.STATEMENT][sym.ID] = new SyntaxTableRuleObject(10, rightSide10);
    }
    
    SyntaxTableObject getSyntaxTableObject(int m, int n)
    {
            return table[m][n];
    }
}
