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

// Makroi
niz_cifara = (0|[1-9][0-9]*)
sufiks = [FfLl]
eksponent = ([eE][\+\-]?{niz_cifara})

%%

[\t\n\r ]                                                                   {   ;   }

","                                                                         {   return new Symbol( sym.COMMA,       yytext() ); }
"="                                                                         {   return new Symbol( sym.ASSIGN,      yytext() ); }
"*"                                                                         {   return new Symbol( sym.POINTER,     yytext() ); }

// Celobrojna konstanta
\-?{niz_cifara}                                                             {   return new Symbol( sym.INTCONST,    yytext() ); }

// Realna konstanta
\-?({niz_cifara}?\.{niz_cifara}|{niz_cifara}\.){eksponent}?{sufiks}?        {   return new Symbol( sym.REALCONST,   yytext() ); }

// String kontanta
\"[^\"]*\"                                                                  {   return new Symbol( sym.STRINGCONST, yytext() ); }

// Identifikatori
[A-Za-z_][0-9A-Za-z_]*                                                      {   return new Symbol( sym.ID,           yytext() ); }

.                                                            { System.out.println( "Neprepoznat token '" + yytext() + "' u liniji " + yyline ); }