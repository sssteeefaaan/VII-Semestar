import java.util.Stack;

public class LRParser {
	 public static void main(String args[])
	    {   
		
	        int[] lookup = new int[sym.Count];
	        int[] indices = {sym.LOOP, sym.LEFTBRACKET, sym.RIGHTTBRACKET, sym.LOGICOR, sym.LOGICAND, sym.ID, sym.ASSIGN, sym.CONST, sym.SEMICOLON, sym.EOF};
	        
	        for(int i = 0; i < sym.Count; i++)
	        {
	            lookup[i] = -1;
	        }
	        
	        for (int i = 0; i < 10; i++)  
	        {                            
	            lookup[indices[i]] = i;
	        }
	        
	        Stack<Integer> stack = new Stack();
	        
	        stack.push(new Integer(0));
	        
	        boolean prepoznat = false;
	        boolean greska = false;
	        
	        
	        try
	        {
	            MPLexer lexer = new MPLexer(new java.io.FileReader(args[0]));
	            SyntaxTableLR table = new SyntaxTableLR();
	            Rules rules = new Rules();
	            
	            int next;
	            do
	                next = lookup[lexer.next_token().m_index];
	            while (next == -1);
	            
	            do
	            {
	                STObject sto =  table.getSTObject(stack.peek().intValue(), next);
	                
	                switch(sto.type)
	                {   
	                    case "s":{
	                        System.out.println(sto.type + " " + sto.state);
	                        
	                       stack.push(next);
	                       stack.push(sto.state);
	                       do
	                            next = lookup[lexer.next_token().m_index];
	                        while (next == -1);
	                        break;
	                    }
	                    
	                     case "r":{
	                         
	                         System.out.println(sto.type + " " + sto.state);
	                          
	                         rules.getRule(sto.state).popFromStack(stack);
	                         int top_state = stack.peek();
	                         rules.getRule(sto.state).pushOnStack(stack);
	                         stack.push(table.getSTObject(top_state, rules.getRule(sto.state).getLeft()).state);
	             
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
	                System.out.println("Sintax error!");
	            }
	            
	            if (prepoznat)
	            {
	                System.out.println("No sintax errors!");
	            }
	        }
	        catch (Exception e)
	        {
	            System.out.println(e.toString());
	        }
	    }

}
