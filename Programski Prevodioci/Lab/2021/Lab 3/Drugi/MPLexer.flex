// Import sekcija
import java_cup.runtime.*;

%%

// Sekcija opcija i deklaracija

%class MPLexer

%cup

%line
%column

// Konstruktor
%eofval{
    return new Symbol( sym.EOF );
%eofval}

// Dodatne članice klase
%{
    public int getLine()
    {
        return yyline;
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
"/**"                         { yybegin( COMMENT ); }
<COMMENT>~("*/")              { yybegin( YYINITIAL ); }

// Tabulatori
[\t\n\r ] 			{  }


// Zagrade
\(                              { return new Symbol( sym.OPEN_BRACKET ); }
\)                              { return new Symbol( sym.CLOSE_BRACKET ); }
\{                              { return new Symbol( sym.OPEN_CURLY_BRACKET ); }
\}                              { return new Symbol( sym.CLOSE_CURLY_BRACKET ); }


// Operatori
":="                            { return new Symbol( sym.ASSIGN ); }
"<"                             { return new Symbol( sym.LESS ); }
"<="                            { return new Symbol( sym.LESS_OR_EQUAL ); }
"=="                            { return new Symbol( sym.EQUAL ); }
"<>"                            { return new Symbol( sym.NOT_EQUAL ); }
">"                             { return new Symbol( sym.GREATER ); }
">="                            { return new Symbol( sym.GREATER_OR_EQUAL ); }


// Separatori
;                               { return new Symbol( sym.SEMICOLON ); }
:                               { return new Symbol( sym.COLON ); }


// Kljucne reci

"main"                          {   return new Symbol( sym.MAIN );    }
"int"                           {   return new Symbol( sym.INT );     }
"real"                          {   return new Symbol( sym.REAL );    }
"boolean"                       {   return new Symbol( sym.BOOLEAN ); }
"if"                            {   return new Symbol( sym.IF );      }
"elif"                          {   return new Symbol( sym.ELIF );    }
"else"                          {   return new Symbol( sym.ELSE );    }

// bool
"true"|"false"                  { return new Symbol( sym.CONST, Boolean.parseBoolean( yytext() ) ); }

// ID-evi
{slovo}({slovo}|{cifra})*       { return new Symbol( sym.ID, yytext() ); }

// Konstante

// int
(([2-9]|(1[0-6]))?#)?{niz_cifara}                { return new Symbol( sym.CONST, Integer.parseInt( yytext() ) ); }

// double
{niz_cifara}\.({niz_cifara}(E[+-]{niz_cifara})?)?  { return new Symbol( sym.CONST, FLOAT.parseFloat( yytext() ) ); }

// string
\"{niz_znakova}\"               { return new Symbol( sym.CONST, yytext() ); }

// char
'{znak}'                        { return new Symbol( sym.CONST, yytext() ); }


// Greska
.  { if (yytext() != null && yytext().length() > 0) System.out.println( "Error at ln: " + yyline + ", column: " + yycolumn + " -- " + yytext() ); }