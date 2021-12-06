import java.util.LinkedList;

public class Rule {
    public String left;
    public LinkedList<String> right;
    public int size;

    public Rule(String left, LinkedList<String> right)
    {
        this.left = left;

        this.right = new LinkedList<>();
        for (String s : right) {
            this.right.add(s);
        }
        
        this.size = right.size();
    }
}
