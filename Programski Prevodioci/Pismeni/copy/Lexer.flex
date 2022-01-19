import java_cup.runtime.*;

%%

%class Lexer
%cup
%line
%column

%eofval{
    return new Symbol( sym.EOF );
%eofval}

%{
    public int getLine(){
        return yyline;
    }
%}

niz_cifara=(0|[1-9][0-9]*)
niz_cifara_oktal=0[1-7][0-7]*
niz_cifara_heksa=0[xX][0-9A-Fa-f]+

%%

// Beli simboli
[\t\n\r ]+                                                   {   ;   }

// Kljucne reci
"enum"                                                      {   return new Symbol( sym.ENUM,        yytext() ); }
":"                                                         {   return new Symbol( sym.COLON,       yytext() ); }
"{"                                                         {   return new Symbol( sym.OPENCURLY,   yytext() ); }
"}"                                                         {   return new Symbol( sym.CLOSECURLY,  yytext() ); }
"INT"                                                       {   return new Symbol( sym.INT,         yytext() ); }
"STRING"                                                    {   return new Symbol( sym.STRING,      yytext() ); }
","                                                         {   return new Symbol( sym.COMMA,       yytext() ); }

// Int konstanta
(\-?{niz_cifara}|\-?{niz_cifara_oktal}|{niz_cifara_heksa})  {   return new Symbol( sym.INTCONST,    yytext() ); }

// String konstanta
\"[^\"]+\"                                                  {   return new Symbol( sym.STRINGCONST, yytext() ); }

// Identifikator
[A-Za-z_][0-9A-Za-z_]*                                      {   return new Symbol( sym.ID,          yytext() ); }

// Greska (sve sto nije moglo da se prepozna)
.                                                { System.out.println( "Greska: Token " + yytext() + " nije deo gramatike!"); }
