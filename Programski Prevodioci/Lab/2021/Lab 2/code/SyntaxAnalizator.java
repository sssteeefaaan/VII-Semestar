import java.io.Reader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Stack;

public class SyntaxAnalizator {

    private Stack<Element> stack;
    private MPLexer lexicAnalizator;
    private ArrayList<Rule> rules;
    private List<HashMap<String, String>> sintaxTable; 

    SyntaxAnalizator(Reader in, List<Rule> rules, List<HashMap<String, String>> sintaxTable) {
        this.stack = new Stack<>();
        this.lexicAnalizator = new MPLexer(in);

        this.rules = new ArrayList<>();
        for(Rule r : rules)
            this.rules.add(r);

        this.sintaxTable = new ArrayList<>();
        for(HashMap<String, String> entry : sintaxTable)
        {
            int size = this.sintaxTable.size();
            this.sintaxTable.add(new HashMap<String, String>());
            for(String key : entry.keySet())
                this.sintaxTable.get(size).put(key, entry.get(key));
        }
    }

    public int LR()
    {
        int accepted = 0,
                error = 0;

        Yytoken next = nextlex();
        Element current = null;
        push(0, 0);

        String action;

        do {
            current = top();
            action = action(current, next.m_index);
            switch (action.split(" ")[0]) {
                case ("sk"):
                    push(next.m_index, Integer.parseInt(action.split(" ")[1]));
                    next = nextlex();
                    break;

                case ("rk"):
                    int k = Integer.parseInt(action.split(" ")[1]);
                    pop(rules.get(k).size);
                    push(rules.get(k).left, goTo(rules.get(k).left));
                    break;

                case ("acc"):
                    accepted = 1;
                    break;

                case ("err"):
                    error = 1;
                    break;
            }
        } while (!(accepted == 1 || error == 1));

        return accepted;
    }
    
    private int goTo(String reduction) {
        try{
            return Integer.parseInt(this.sintaxTable.get(top().state).get(reduction));
        }
        catch(Exception e)
        {
            e.printStackTrace();
        }
        return -1;
    }

    private void pop(int amount) {
        try {
            for (int i = 0; i < amount; i++)
                this.stack.pop();
        } catch (Exception e) {
            e.printStackTrace();
            ;
        }
    }

    private void push(int token, int state) {
        this.stack.push(new Element(token, state));
    }

    private void push(String token, int state) {
        this.stack.push(new Element(token, state));
    }

    private Yytoken nextlex() {
        try{
        return this.lexicAnalizator.next_token();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    private String action(Element current, int next)
    {
        try {
            System.out.println("Element: " + current.state + " " + current.state);
            System.out.println("Next: " + next);
            return this.sintaxTable.get(current.state).get(next);
        } catch (Exception e) {
            e.printStackTrace();
        }

        return "err";
    }
    
    private Element top() {
        try{
            return this.stack.peek();
        }
        catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }
    
}
