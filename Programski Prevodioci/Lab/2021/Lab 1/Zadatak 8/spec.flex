// Import sekcija
import utilities.KWTable;
import utilities.sym;

%%

// Sekcija opcija i deklaracija

%class MPLexer
%function next_token
%line
%column
%char
%debug
%type Yytoken

// Konstruktor
%eofval{
    return new Yytoken( sym.EOF, null, yyline, yycolumn, yychar );
%eofval}

// Dodatne članice klase
%{
    KWTable kwTable = new KWTable();
    Yytoken getKW()
    {
        return new Yytoken( kwTable.find( yytext() ), yytext(), yyline, yycolumn, yychar );       
    }
%}

// Stanja
%xstate COMMENT

// Makroi
cifra = [0-9]
niz_cifara = (0|[1-9]{cifra}*)
slovo = [A-Za-z]
znak = ({cifra}|{slovo})
niz_znakova = {znak}+


%%

// Sekcija pravila

// Komentar
"<-comm" { yybegin( COMMENT ); }
<COMMENT>~("comm->") { yybegin( YYINITIAL ); }

// Tabulatori
[\t\n\r ] { ; }


// Zagrade
\( { return new Yytoken( sym.OPEN_BRACKET, yytext(), yyline, yycolumn, yychar ); }
\) { return new Yytoken( sym.CLOSE_BRACKET, yytext(), yyline, yycolumn, yychar ); }
\{ { return new Yytoken( sym.OPEN_CURLY_BRACKET, yytext(), yyline, yycolumn, yychar ); }
\} { return new Yytoken( sym.CLOSE_CURLY_BRACKET, yytext(), yyline, yycolumn, yychar ); }


// Operatori
\+ { return new Yytoken( sym.PLUS, yytext(), yyline, yycolumn, yychar ); }
\* { return new Yytoken( sym.MULTIPLY, yytext(), yyline, yycolumn, yychar ); }
= { return new Yytoken( sym.ASSIGN, yytext(), yyline, yycolumn, yychar ); }


// Separatori
; { return new Yytoken( sym.SEMICOLON, yytext(), yyline, yycolumn, yychar ); }


// Kljucne reci
\~?{slovo}+ { return getKW(); }

// ID-evi
{slovo}({slovo}|{cifra})* { return new Yytoken( sym.ID, yytext(), yyline, yycolumn, yychar ); }

// Konstante

// int
[-]?{niz_cifara}  { return new Yytoken( sym.ID, yytext(), yyline, yycolumn, yychar ); }

// double
[-]?{niz_cifara}\.{niz_cifara}  { return new Yytoken( sym.ID, yytext(), yyline, yycolumn, yychar ); }

// string
\"{niz_znakova}\"  { return new Yytoken( sym.ID, yytext(), yyline, yycolumn, yychar ); }

// bool
true|false  { return new Yytoken( sym.ID, yytext(), yyline, yycolumn, yychar ); }

// char
'{znak}'  { return new Yytoken( sym.ID, yytext(), yyline, yycolumn, yychar ); }


// Greska
.  { if (yytext() != null && yytext().length() > 0) System.out.println( "Error at ln: " + yyline + ", column: " + yycolumn + " -- " + yytext() ); }