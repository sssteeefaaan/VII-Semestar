import java.util.LinkedList;

public class Rule {
    public int left;
    public LinkedList<Integer> right;
    public int size;

    public Rule(int left, LinkedList<Integer> right) {
        this.left = left;

        this.right = new LinkedList<>();
        for (int s : right) {
            this.right.add(s);
        }

        this.size = right.size();
    }
}
