import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.io.Reader;

public class Program {
    public static void main(String[] argv) {
        try {
            if (argv.length != 1)
                throw new Exception("Args[0] must be a path to input file!");

            Reader reader = new InputStreamReader(new FileInputStream(argv[0]));
            SyntaxAnalyzer sa = new SyntaxAnalyzer(reader);

            System.out.println(sa.LR());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
