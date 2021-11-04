import java.io.IOException;
import java.util.Stack;

public class SyntaxAnalizer {
	private MPLexer lexer;
    private java.util.Stack<Integer> workingStack;
    private SyntaxTable syntaxTable;
    private Rule[] rules;
    private String resault;
    
    private SyntaxAnalizer()
    {
        workingStack = new Stack<Integer>();
        InitializeStack();
        syntaxTable = new SyntaxTable();
        InitializeRules();
        
    }
    
    public SyntaxAnalizer(java.io.Reader in)
    {
        this();
        lexer = new MPLexer(in);
    }
    
    public SyntaxAnalizer(java.io.InputStreamReader in)
    {
        this();
        lexer = new MPLexer(in);
    }
 
    private void InitializeStack()
    {
        workingStack.push(sym.EOF);
        workingStack.push(sym.SelectStatement);
    }
    
    private void InitializeRules()
    {
        rules = new Rule[9];
        
        rules[0] = new Rule(new int[] {sym.SELECT, sym.BEGIN, sym.CaseList, sym.END});
        rules[1] = new Rule(new int[] {sym.Case, sym.CaseListP});
        rules[2] = new Rule(new int[] {});
        rules[3] = new Rule(new int[] {sym.CASE, sym.ID, sym.ARROW, sym.Statement});
        rules[4] = new Rule(new int[] {sym.SelectStatement});
        rules[5] = new Rule(new int[] {sym.ID, sym.ASSIGN, sym.StatementP});
        rules[6] = new Rule(new int[] {sym.ID,sym.SEMICOLON});
        rules[7] = new Rule(new int[] {sym.CONST,sym.SEMICOLON});
        
    }
    
    public boolean SA_LL1() throws IOException
    {
        boolean prepoznat = false;
        boolean greska = false;
        int next = lexer.next_token().m_index;
    resault = new String("");

 

    do {
      int current = syntaxTable.matrix[workingStack.peek()][next];
      switch (current) {
      case SyntaxTable.POP:
        workingStack.pop();
        next = lexer.next_token().m_index;
                    break;
                    
                case SyntaxTable.ACCEPT:
                    prepoznat = true;
                    break;
                    
                case SyntaxTable.ERROR:
                    greska = true;
                    break;
                    
                default:
                    resault += current + " ";
                    workingStack.pop();
                    rules[current].push(workingStack);
                    break;
                    
            }
        }
        while(!(prepoznat || greska));
        
        return prepoznat;
    }
    
    public static void main(String argv[]) {
    if (argv.length == 0) {
      System.out.println("Usage : java SyntaxAnalizer <inputfile>");
    }
    else {
      for (int i = 0; i < argv.length; i++) {
        SyntaxAnalizer analizer = null;
        try {
          analizer = new SyntaxAnalizer( new java.io.FileReader(argv[i]) );
          if(analizer.SA_LL1())
            System.out.println("Ovaj fajl je sintaksno ispravan");
          else
            System.out.println("Ovaj fajl je sintaksno neispravan");
        }
        catch (java.io.FileNotFoundException e) {
          System.out.println("File not found : \""+argv[i]+"\"");
        }
        catch (java.io.IOException e) {
          System.out.println("IO error scanning file \""+argv[i]+"\"");
          System.out.println(e);
        }
        catch (Exception e) {
          System.out.println("Unexpected exception:");
          e.printStackTrace();
        }
      }
    }
  }
}
