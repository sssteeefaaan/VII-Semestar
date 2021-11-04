import java.util.ArrayList;
import java.util.Stack;

public class RuleObject {
	public int ruleNumber;
    public ArrayList<Integer> rightSide;
    public int leftSide;
    
    public RuleObject(int ruleNumber, int leftSide, int rightSide[])
    {
        this.ruleNumber = ruleNumber;
        this.rightSide = new ArrayList<>();
        this.leftSide = leftSide;
        
        for (int i = 0; i < rightSide.length; i++)
        {
            this.rightSide.add(new Integer(rightSide[i]));
        }
    }
    
     public int getLeft(){
           return this.leftSide;
       }
        
    
    //za izbacivanje 2*rule[k].size
     public void popFromStack(Stack<Integer> stack)
    {
        int size = this.rightSide.size();
        for(int i =0; i<size*2; i++){ //prvo postavljeno bez +2
            stack.pop();
        }
    }
    
     //za dodavanje leve strane
      public void pushOnStack(Stack<Integer> stack)
    {
        stack.push(this.leftSide);
    }
}
