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

%%

// Beli simboli
[\t\n\r ]                               {   ;   }

// Kljucne reci
"{"                                     { return new Symbol( sym.OPENCURLY,     yytext() ); }
"}"                                     { return new Symbol( sym.CLOSECURLY,    yytext() ); }
","                                     { return new Symbol( sym.COMMA,         yytext() ); }
":"                                     { return new Symbol( sym.COLON,         yytext() ); }

// Int const
(0[xX][0-9A-Fa-f]+)|(0|\-?[1-9][0-9]*)  {   return new Symbol( sym.INTCONST,    yytext() );   }

// Real const
\-?[0-9]\.[0-9]+[eE]\-?[1-9][0-9]*      {   return new Symbol( sym.REALCONST,   yytext() );   }

// String const
\"[^\"]*\"                              {   return new Symbol( sym.STRINGCONST, yytext() );   }

// Identifikator
[A-Za-z_][0-9A-Za-z_]*                  {   return new Symbol( sym.ID,          yytext() );   }

// Greska
.                                   {   System.out.println("Greska, prepoznat token nije deo gramatike!");  }