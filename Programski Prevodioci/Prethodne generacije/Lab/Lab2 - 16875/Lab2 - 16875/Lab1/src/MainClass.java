import java.util.Stack;
import java.io.Reader;

public class MainClass
{
    public static void main(String args[])
    {   
        Stack<Integer> stack = new Stack();
        
        stack.push(new Integer(sym.EOF)); // push # to stack
        stack.push(new Integer(sym.REDOLOOP)); // push SS (SwitchStatement) to stack
        
        boolean prepoznat = false;
        boolean greska = false;
        
        try
        {
            MPLexer lexer = new MPLexer(new java.io.FileReader(args[0]));
            SyntaxTable table = new SyntaxTable();
            
            int next;
            do
                next = lexer.next_token().m_index;
            while (next == -1);
            
            do
            {
                SyntaxTableObject sto =  table.getSyntaxTableObject(stack.peek().intValue(), next);
                
                switch(sto.type)
                {
                    case "pop":
                    {
                        stack.pop();
                        do
                            next = lexer.next_token().m_index;
                        while (next == -1);
                        break;
                    }
                    case "rule":
                    {
                        stack.pop();
                        ((SyntaxTableRuleObject)sto).pushToStack(stack);                
                        break;
                    }
                    case "acc":
                    {
                        prepoznat = true;
                        break;
                    }
                    case "err":
                        greska = true;
                        break;
                }
            }
            while(!(prepoznat || greska));
            
            if (greska)
            {
                System.out.println("Syntax error!");
            }
            
            if (prepoznat)
            {
                System.out.println("No syntax errors!");
            }
        }
        catch (Exception e)
        {
            System.out.println(e.toString());
        }
    }
}
