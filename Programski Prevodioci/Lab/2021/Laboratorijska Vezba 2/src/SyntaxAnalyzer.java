import java.io.Reader;
import java.util.HashMap;
import java.util.List;
import java.util.Stack;

import utilities.sym;

public class SyntaxAnalyzer {

    private List<Rule> rules;
    private Stack<Integer> stack;
    private MPLexer lexicAnalizator;
    private List<HashMap<Integer, String>> syntaxTable;

    SyntaxAnalyzer(Reader in) {
        this.stack = new Stack<>();
        this.lexicAnalizator = new MPLexer(in);

        this.rules = SyntaxTable.getRules();
        this.syntaxTable = SyntaxTable.getSyntaxTable();
    }

    public int LR() {
        push(sym.EOF);
        int accepted = 0,
                error = 0,
                k,
                top_state;
        Yytoken next = nextlex();
        String action;

        do {
            action = action(top(), next);
            switch (action.split(" ")[0]) {
                case ("sk"):
                    push(next.m_index);
                    push(Integer.parseInt(action.split(" ")[1]));
                    next = nextlex();
                    break;

                case ("rk"):
                    k = Integer.parseInt(action.split(" ")[1]);
                    pop(2 * rules.get(k).right.size());

                    top_state = top();
                    push(rules.get(k).left);
                    push(goTo(top_state, rules.get(k).left));
                    break;

                case ("acc"):
                    accepted = 1;
                    break;

                case ("err"):
                    error = 1;
                    break;
            }
        } while (accepted == 0 && error == 0);

        return accepted;
    }

    private int goTo(int alpha, Integer reduction) {
        int ret = -1;
        try {
            ret = Integer.parseInt(this.syntaxTable.get(alpha).get(reduction));
            System.out.println("Goto(" + alpha + ", " + reduction + ") = " + ret);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return ret;
    }

    private void pop(int amount) {
        try {
            for (int i = 0; i < amount; i++)
                this.stack.pop();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void push(int token) {
        this.stack.push(token);
    }

    private Yytoken nextlex() {
        try {
            return this.lexicAnalizator.next_token();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    private String action(int alpha, Yytoken next) {
        String ret = null;
        try {
            System.out.println("State: " + top());
            System.out.println("Next: " + next.m_index + " [" + next.m_text + "]");
            ret = this.syntaxTable.get(alpha).get(next.m_index);
        } catch (Exception e) {
            e.printStackTrace();
        }

        if (ret == null)
            ret = "err";
        return ret;
    }

    private int top() {
        try {
            return this.stack.peek();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return -1;
    }

}
