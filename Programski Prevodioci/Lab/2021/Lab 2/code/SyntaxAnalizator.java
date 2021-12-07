import java.io.Reader;
import java.util.HashMap;
import java.util.List;
import java.util.Stack;

public class SyntaxAnalizator {

    private List<Rule> rules;
    private Stack<Integer> stack;
    private MPLexer lexicAnalizator;
    private List<HashMap<Integer, String>> sintaxTable;

    SyntaxAnalizator(Reader in) {
        this.stack = new Stack<>();
        this.lexicAnalizator = new MPLexer(in);

        this.rules = SintaxTable.getRules();
        this.sintaxTable = SintaxTable.getSintaxTable();
    }

    public int LR() {
        int accepted = 0,
                error = 0;

        Yytoken next = nextlex();
        this.stack.push(0);

        String action;

        do {
            for (Integer n : this.stack)
                System.out.print(n + " ");
            System.out.println();
            action = action(top(), next);
            switch (action.split(" ")[0]) {
                case ("sk"):
                    push(next.m_index, Integer.parseInt(action.split(" ")[1]));
                    next = nextlex();
                    break;

                case ("rk"):
                    int k = Integer.parseInt(action.split(" ")[1]);
                    pop(2 * rules.get(k).size);
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

    private int goTo(Integer reduction) {
        int ret = -1;
        try {
            ret = Integer.parseInt(this.sintaxTable.get(top()).get(reduction));
            System.out.println("Goto(" + top() + ", " + reduction + ") = " + ret);
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
            ;
        }
    }

    private void push(int token, int state) {
        this.stack.push(token);
        this.stack.push(state);
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
        try {
            System.out.println("Element: " + alpha);
            System.out.println("Next: " + next.m_text);
            return this.sintaxTable.get(alpha).get(next.m_index);
        } catch (Exception e) {
            e.printStackTrace();
        }

        return "err";
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
