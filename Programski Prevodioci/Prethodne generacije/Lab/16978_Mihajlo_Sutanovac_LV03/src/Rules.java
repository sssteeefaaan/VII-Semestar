public class Rules {
private RuleObject[] rules;
public  Rules() {
	rules = new RuleObject[9];

  int[] rightSide1 = {sym2.SELECT, sym2.BEGIN,sym2.CaseList, sym2.END};  
  rules[0] = new RuleObject(1, sym2.SelectStatement, rightSide1);
  
  int[] rightSide2 = {sym2.CaseList, sym2.Case};
  rules[1] = new RuleObject(2, sym2.CaseList,rightSide2); 
  
  int[] rightSide3 = {sym2.Case};
  rules[2] = new RuleObject(3, sym2.CaseList,rightSide3);
  
  int[] rightSide4 = {sym2.CASE, sym2.ID, sym2.ARROW, sym2.Statement};
  rules[3] = new RuleObject(4, sym2.Case,rightSide4);
  
  int[] rightSide5 = {sym2.SelectStatement};
  rules[4] = new RuleObject(5, sym2.Statement, rightSide5);
  
  int[] rightSide6 = {sym2.ID, sym2.ASSIGN, sym2.ID, sym2.SEMICOLON};
  rules[5] = new RuleObject(6, sym2.Statement, rightSide6);
  
  int[] rightSide7 = {sym2.ID, sym2.ASSIGN, sym2.CONST, sym2.SEMICOLON};
  rules[6] = new RuleObject(7, sym2.Statement, rightSide7);
}
public RuleObject getRule(int i){
    return rules[i - 1]; 
}
}
