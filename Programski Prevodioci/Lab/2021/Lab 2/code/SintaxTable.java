import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

import utilities.sym;

public class SintaxTable {

  public final static int STATEMENTS_PRIME = 100;
  public final static int STATEMENTS = 101;
  public final static int STATEMENT = 102;
  public final static int ASSIGNMENT = 103;
  public final static int WHILE_STATEMENT = 104;
  public final static int TERM = 105;

  private static ArrayList<HashMap<Integer, String>> _sintaxTable;
  private static ArrayList<Rule> _rules;

  public SintaxTable() {
  }

  public static List<HashMap<Integer, String>> getSintaxTable() {
    if (_sintaxTable == null)
      _sintaxTable = new ArrayList<HashMap<Integer, String>>() {
        {
          // #0
          add(new HashMap<Integer, String>() {
            {
              put(sym.ID, "sk 7");
              put(sym.REPEAT, "sk 14");
              put(STATEMENTS, "1");
              put(STATEMENT, "4");
              put(ASSIGNMENT, "5");
              put(WHILE_STATEMENT, "6");
            }
          });
          // #1
          add(new HashMap<Integer, String>() {
            {
              put(sym.SEMICOLON, "sk 2");
              put(sym.EOF, "acc");
            }
          });
          // #2
          add(new HashMap<Integer, String>() {
            {
              put(sym.ID, "sk 7");
              put(sym.REPEAT, "sk 14");
              put(ASSIGNMENT, "5");
              put(WHILE_STATEMENT, "6");
            }
          });
          // #3
          add(new HashMap<Integer, String>() {
            {
              put(sym.SEMICOLON, "rk 1");
              put(sym.OPEN_CURLY_BRACKET, "rk 1");
              put(sym.EOF, "rk 1");
            }
          });
          // #4
          add(new HashMap<Integer, String>() {
            {
              put(sym.SEMICOLON, "rk 2");
              put(sym.OPEN_CURLY_BRACKET, "rk 2");
              put(sym.EOF, "rk 2");
            }
          });
          // #5
          add(new HashMap<Integer, String>() {
            {
              put(sym.SEMICOLON, "rk 3");
              put(sym.OPEN_CURLY_BRACKET, "rk 3");
              put(sym.EOF, "rk 3");
            }
          });
          // #6
          add(new HashMap<Integer, String>() {
            {
              put(sym.SEMICOLON, "rk 4");
              put(sym.OPEN_CURLY_BRACKET, "rk 4");
              put(sym.EOF, "rk 4");
            }
          });
          // #7
          add(new HashMap<Integer, String>() {
            {
              put(sym.ASSIGN, "sk 8");
            }
          });
          // #8
          add(new HashMap<Integer, String>() {
            {
              put(sym.ID, "sk 12");
              put(sym.CONST, "sk 13");
              put(TERM, "9");
            }
          });
          // #9
          add(new HashMap<Integer, String>() {
            {
              put(sym.SEMICOLON, "rk 5");
              put(sym.PLUS, "sk 10");
              put(sym.OPEN_CURLY_BRACKET, "rk 5");
              put(sym.EOF, "rk 5");
            }
          });
          // #10
          add(new HashMap<Integer, String>() {
            {
              put(sym.ID, "sk 12");
              put(sym.CONST, "sk 13");
              put(TERM, "11");
            }
          });
          // #11
          add(new HashMap<Integer, String>() {
            {
              put(sym.SEMICOLON, "rk 6");
              put(sym.OPEN_CURLY_BRACKET, "rk 6");
              put(sym.EOF, "rk 6");
            }
          });
          // #12
          add(new HashMap<Integer, String>() {
            {
              put(sym.SEMICOLON, "rk 7");
              put(sym.PLUS, "rk 7");
              put(sym.CLOSE_BRACKET, "rk 7");
              put(sym.OPEN_CURLY_BRACKET, "rk 7");
              put(sym.EOF, "rk 7");
            }
          });
          // #13
          add(new HashMap<Integer, String>() {
            {
              put(sym.SEMICOLON, "rk 8");
              put(sym.PLUS, "rk 8");
              put(sym.CLOSE_BRACKET, "rk 8");
              put(sym.OPEN_CURLY_BRACKET, "rk 8");
              put(sym.EOF, "rk 8");
            }
          });
          // #14
          add(new HashMap<Integer, String>() {
            {
              put(sym.OPEN_BRACKET, "sk 15");
            }
          });
          // #15
          add(new HashMap<Integer, String>() {
            {
              put(sym.ID, "sk 12");
              put(sym.CONST, "sk 13");
              put(TERM, "16");
            }
          });
          // #16
          add(new HashMap<Integer, String>() {
            {
              put(sym.CLOSE_BRACKET, "sk 17");
            }
          });
          // #17
          add(new HashMap<Integer, String>() {
            {
              put(sym.OPEN_CURLY_BRACKET, "sk 18");
            }
          });
          // #18
          add(new HashMap<Integer, String>() {
            {
              put(sym.ID, "sk 7");
              put(sym.REPEAT, "sk 14");
              put(STATEMENTS, "19");
              put(STATEMENT, "4");
              put(ASSIGNMENT, "5");
              put(WHILE_STATEMENT, "6");
            }
          });
          // #19
          add(new HashMap<Integer, String>() {
            {
              put(sym.SEMICOLON, "sk 2");
              put(sym.OPEN_CURLY_BRACKET, "sk 20");
            }
          });
          // #20
          add(new HashMap<Integer, String>() {
            {
              put(sym.SEMICOLON, "rk 9");
              put(sym.OPEN_CURLY_BRACKET, "rk 9");
              put(sym.EOF, "rk 9");
            }
          });
        }
      };

    return _sintaxTable;
  }

  public static List<Rule> getRules() {
    if (_rules == null)
      _rules = new ArrayList<Rule>() {
        {
          // #0
          add(new Rule(SintaxTable.STATEMENTS_PRIME, new LinkedList<Integer>() {
            {
              add(SintaxTable.STATEMENTS);
              add(sym.SEMICOLON);
              add(SintaxTable.STATEMENT);
            }
          }));
          // #1
          add(new Rule(SintaxTable.STATEMENTS, new LinkedList<Integer>() {
            {
              add(SintaxTable.STATEMENT);
            }
          }));
          // #2
          add(new Rule(SintaxTable.STATEMENT, new LinkedList<Integer>() {
            {
              add(SintaxTable.ASSIGNMENT);
            }
          }));
          // #3
          add(new Rule(SintaxTable.STATEMENT, new LinkedList<Integer>() {
            {
              add(SintaxTable.WHILE_STATEMENT);
            }
          }));
          // #4
          add(new Rule(SintaxTable.ASSIGNMENT, new LinkedList<Integer>() {
            {
              add(sym.ID);
              add(sym.ASSIGN);
              add(SintaxTable.TERM);
            }
          }));
          // #5
          add(new Rule(SintaxTable.ASSIGNMENT, new LinkedList<Integer>() {
            {
              add(sym.ID);
              add(sym.ASSIGN);
              add(SintaxTable.TERM);
              add(sym.PLUS);
              add(SintaxTable.TERM);
            }
          }));
          // #6
          add(new Rule(SintaxTable.WHILE_STATEMENT, new LinkedList<Integer>() {
            {
              add(sym.REPEAT);
              add(sym.OPEN_BRACKET);
              add(SintaxTable.TERM);
              add(sym.CLOSE_BRACKET);
              add(sym.OPEN_CURLY_BRACKET);
              add(SintaxTable.STATEMENTS);
              add(sym.CLOSE_CURLY_BRACKET);
            }
          }));
          // #7
          add(new Rule(SintaxTable.TERM, new LinkedList<Integer>() {
            {
              add(sym.ID);
            }
          }));
          // #8
          add(new Rule(SintaxTable.TERM, new LinkedList<Integer>() {
            {
              add(sym.CONST);
            }
          }));
        }
      };

    return _rules;
  }
}
