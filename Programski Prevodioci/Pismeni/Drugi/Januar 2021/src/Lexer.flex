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
    public int getLine()
    {
        return yyline;
    }
%}


%%


[\t\r\n ]+                                  { ; }

// Kljucne reci
"["                                         {   return new Symbol(  sym.OPENPAR,    yytext() );  }
"]"                                         {   return new Symbol(  sym.CLOSEPAR,   yytext() );  }
","                                         {   return new Symbol(  sym.COMMA,      yytext() );  }
":"                                         {   return new Symbol(  sym.COLON,       yytext() ); }

// Celobrojna konstanta
(0[xX][0-9A-Fa-f])|(0|\-?[1-9][0-9]*)     {   return new Symbol(  sym.INTCONST,    yytext());  }
\"[^\"]*\"                                   {   return new Symbol(  sym.STRINGCONST, yytext());  }

// Identifikator
[A-Za-z_][0-9A-Za-z_]*                      {   return new Symbol(  sym.ID,        yytext() );   }

.                                           {     System.out.println( "Greska: " + yytext() );    }