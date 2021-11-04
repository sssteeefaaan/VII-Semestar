public class Rules {
private RuleObject[] rules;
public  Rules() {
	rules = new RuleObject[9];

  int[] rightSide1 = {sym2.LOOP, sym2.LEFTBRACKET,sym2.Expression, sym2.RIGHTBRACKET, sym2.Statement};  
  rules[0] = new RuleObject(1, sym2.RedoLoop, rightSide1);
  
  int[] rightSide2 = {sym2.Expression, sym2.LOGICOR, sym2.AndExpression};
  rules[1] = new RuleObject(2, sym2.Expression,rightSide2); 
  
  int[] rightSide3 = {sym2.AndExpression};
  rules[2] = new RuleObject(3, sym2.Expression,rightSide3);
  
  int[] rightSide4 = {sym2.AndExpression, sym2.LOGICAND, sym2.Term};
  rules[3] = new RuleObject(4, sym2.AndExpression,rightSide4);
  
  int[] rightSide5 = {sym2.Term};
  rules[4] = new RuleObject(5, sym2.AndExpression, rightSide5);
  
  int[] rightSide6 = {sym2.ID};
  rules[5] = new RuleObject(6, sym2.Term, rightSide6);
  
  int[] rightSide7 = {sym2.CONST};
  rules[6] = new RuleObject(7, sym2.Term, rightSide7);
  
  int[] rightSide8 = {sym2.RedoLoop};
  rules[7] = new RuleObject(7, sym2.Statement, rightSide8);
  
  int[] rightSide9 = {sym2.ID, sym2.ASSIGN, sym2.Expression};
  rules[8] = new RuleObject(7, sym2.Statement, rightSide9);
}
public RuleObject getRule(int i){
    return rules[i - 1]; 
}
}
