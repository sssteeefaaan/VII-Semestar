
public class Rule {
   private int[] rules;
   
    private Rule()
    {
    }
   
    public Rule(int[] newRules)
    {
        rules = new int[newRules.length];
        rules = newRules;
    }
   
    public void push(java.util.Stack alfa)
    {
        if(rules.length == 0)
            return;
        for(int i = rules.length-1; i>= 0; i--)
        {
            alfa.push(rules[i]);
        }
    }
}
