import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;

public class Program {

    private static List<Rule> _rules = null;
    private static List<HashMap<String, String>> _sintaxTable = null;

    public static void main(String[] argv) {
        try {
            if (argv.length != 1)
                throw new Exception("Args != 1");
                
            Reader reader = new InputStreamReader(new FileInputStream(argv[0]));
            SyntaxAnalizator sa = new SyntaxAnalizator(reader, getRules(), getSintaxTable());

            System.out.println(sa.LR());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static List<Rule> getRules() {
        if (_rules == null)
            _rules = new LinkedList<Rule>() {
                {
                    // #1
                    add(new Rule("Statements'", new LinkedList<>() {
                        {
                            add("Statements");
                        }
                    }));
                    // #2
                    add(new Rule("Statements", new LinkedList<String>() {
                        {
                            add("Statements");
                            add(";");
                            add("Statement");
                        }
                    }));
                    // #3
                    add(new Rule("Statements", new LinkedList<String>() {
                        {
                            add("Statement");
                        }
                    }));
                    // #4
                    add(new Rule("Statement", new LinkedList<String>() {
                        {
                            add("Assignment");
                        }
                    }));
                    // #5
                    add(new Rule("Statement", new LinkedList<String>() {
                        {
                            add("WhileStatement");
                        }
                    }));
                    // #6
                    add(new Rule("Assignment", new LinkedList<String>() {
                        {
                            add("ID");
                            add("=");
                            add("Term");
                        }
                    }));
                    // #7
                    add(new Rule("Assignment", new LinkedList<String>() {
                        {
                            add("ID");
                            add("=");
                            add("Term");
                            add("+");
                            add("Term");
                        }
                    }));
                    // #8
                    add(new Rule("WhileStatement", new LinkedList<String>() {
                        {
                            add("repeat");
                            add("(");
                            add("Term");
                            add(")");
                            add("{");
                            add("Statements");
                            add("}");
                        }
                    }));
                    // #9
                    add(new Rule("Term", new LinkedList<String>() {
                        {
                            add("ID");
                        }
                    }));
                    // #10
                    add(new Rule("Term", new LinkedList<String>() {
                        {
                            add("CONST");
                        }
                    }));
                }
            };

        return _rules;
    }

    public static List<HashMap<String, String>> getSintaxTable() {
        if (_sintaxTable == null)
            _sintaxTable = new ArrayList<HashMap<String, String>>() {
                {
                    // #0
                    add(new HashMap<String, String>() {
                        {
                            put("ID", "sk 7");
                            put("repeat", "sk 14");
                            put("Statements", "1");
                            put("Statement", "4");
                            put("Assignment", "5");
                            put("WhileStatement", "6");
                        }
                    });
                    // #1
                    add(new HashMap<String, String>() {
                        {
                            put(";", "sk 2");
                            put("#", "acc");
                        }
                    });
                    // #2
                    add(new HashMap<String, String>() {
                        {
                            put("ID", "sk 7");
                            put("repeat", "sk 14");
                            put("Assignment", "5");
                            put("WhileStatement", "6");
                        }
                    });
                    // #3
                    add(new HashMap<String, String>() {
                        {
                            put(";", "rk 1");
                            put("}", "rk 1");
                            put("#", "rk 1");
                        }
                    });
                    // #4
                    add(new HashMap<String, String>() {
                        {
                            put(";", "rk 2");
                            put("}", "rk 2");
                            put("#", "rk 2");
                        }
                    });
                    // #5
                    add(new HashMap<String, String>() {
                        {
                            put(";", "rk 3");
                            put("}", "rk 3");
                            put("#", "rk 3");
                        }
                    });
                    // #6
                    add(new HashMap<String, String>() {
                        {
                            put(";", "rk 4");
                            put("}", "rk 4");
                            put("#", "rk 4");
                        }
                    });
                    // #7
                    add(new HashMap<String, String>() {
                        {
                            put("=", "sk 8");
                        }
                    });
                    // #8
                    add(new HashMap<String, String>() {
                        {
                            put("ID", "sk 12");
                            put("CONST", "sk 13");
                            put("Term", "9");
                        }
                    });
                    // #9
                    add(new HashMap<String, String>() {
                        {
                            put(";", "rk 5");
                            put("+", "sk 10");
                            put("}", "rk 5");
                            put("#", "rk 5");
                        }
                    });
                    // #10
                    add(new HashMap<String, String>() {
                        {
                            put("ID", "sk 12");
                            put("CONST", "sk 13");
                            put("Term", "11");
                        }
                    });
                    // #11
                    add(new HashMap<String, String>() {
                        {
                            put(";", "rk 6");
                            put("}", "rk 6");
                            put("#", "rk 6");
                        }
                    });
                    // #12
                    add(new HashMap<String, String>() {
                        {
                            put(";", "rk 7");
                            put("+", "rk 7");
                            put(")", "rk 7");
                            put("}", "rk 7");
                            put("#", "rk 7");
                        }
                    });
                    // #13
                    add(new HashMap<String, String>() {
                        {
                            put(";", "rk 8");
                            put("+", "rk 8");
                            put(")", "rk 8");
                            put("}", "rk 8");
                            put("#", "rk 8");
                        }
                    });
                    // #14
                    add(new HashMap<String, String>() {
                        {
                            put("(", "sk 15");
                        }
                    });
                    // #15
                    add(new HashMap<String, String>() {
                        {
                            put("ID", "sk 12");
                            put("CONST", "sk 13");
                            put("Term", "16");
                        }
                    });
                    // #16
                    add(new HashMap<String, String>() {
                        {
                            put(")", "sk 17");
                        }
                    });
                    // #17
                    add(new HashMap<String, String>() {
                        {
                            put("{", "sk 18");
                        }
                    });
                    // #18
                    add(new HashMap<String, String>() {
                        {
                            put("ID", "sk 7");
                            put("repeat", "sk 14");
                            put("Statements", "1"); //// !!!!!!!!!!!!!!!!!!!!!!!!!
                            put("Statement", "4");
                            put("Assignment", "5");
                            put("WhileStatement", "6");
                        }
                    });
                    // #19
                    add(new HashMap<String, String>() {
                        {
                            put("}", "sk 20");
                        }
                    });
                    // #20
                    add(new HashMap<String, String>() {
                        {
                            put(";", "rk 9");
                            put("}", "rk 9");
                            put("#", "rk 9");
                        }
                    });
                }
            };

        return _sintaxTable;
    }
}
