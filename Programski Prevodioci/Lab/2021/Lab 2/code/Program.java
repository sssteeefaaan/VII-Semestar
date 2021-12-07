import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.HashMap;

public class Program {
    public static void main(String[] argv) {
        try {
            if (argv.length != 1)
                throw new Exception("Args[0] must be a path to input file!");

            int i = 0;
            for (HashMap<Integer, String> state : SintaxTable.getSintaxTable()) {
                i++;
                System.out.println("State " + i + ":");
                System.out.println("--------------------------\n");
                for (int key : state.keySet()) {
                    System.out.println("Simbol " + key + ": " + state.get(key));
                }
                System.out.println("\n");
            }
            Reader reader = new InputStreamReader(new FileInputStream(argv[0]));
            SyntaxAnalizator sa = new SyntaxAnalizator(reader);

            System.out.println(sa.LR());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
