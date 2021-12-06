public class Element {
    public int token;
    public String token_text;
    public int state;

    public Element(int token, int state) {
        this.token = token;
        this.state = state;
    }

    public Element(String token_text, int state) {
        this.token_text = token_text;
        this.state = state;
    }
}
