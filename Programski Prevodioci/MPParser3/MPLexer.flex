// import section
import java_cup.runtime.*;

%%
// declaration section
%class MPLexer

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


//states
%state COMMENT
//macros
slovo = [a-zA-Z]
cifra = [0-9]

%%
// rules section
\(\*			{ yybegin( COMMENT ); }
<COMMENT>\*\)	{ yybegin( YYINITIAL ); }
<COMMENT>.		{ ; }

[\t\r\n ]		{ ; }

//operators
\+				{ return new Symbol( sym.PLUS ); }
\*				{ return new Symbol( sym.MUL );  }

//separators
;				{ return new Symbol( sym.SEMI );	}
,				{ return new Symbol( sym.COMMA );	}
\.				{ return new Symbol( sym.DOT ); }
:				{ return new Symbol( sym.DOTDOT ); }
:=				{ return new Symbol( sym.ASSIGN ); }
\(				{ return new Symbol( sym.LEFTPAR ); }
\)				{ return new Symbol( sym.RIGHTPAR ); }

//keywords
"program"		{ return new Symbol( sym.PROGRAM );	}	
"var"			{ return new Symbol( sym.VAR );	}
"integer"		{ return new Symbol( sym.INTEGER );	}
"char"			{ return new Symbol( sym.CHAR );	}
"read"			{ return new Symbol( sym.READ );	}
"write"			{ return new Symbol( sym.WRITE );	}
"if"			{ return new Symbol( sym.IF );	}
"then"			{ return new Symbol( sym.THEN );	}
"else"			{ return new Symbol( sym.ELSE );	}
"begin"			{ return new Symbol( sym.BEGIN );	}
"end"			{ return new Symbol( sym.END );	}

//id-s
{slovo}({slovo}|{cifra})*	{ return new Symbol( sym.ID, yyline, yytext() ); }

//constants
\'[^]\'			{ return new Symbol( sym.CHARCONST, new Character( yytext().charAt(1) ) ); }
{cifra}+		{ return new Symbol( sym.INTCONST, new Integer( yytext() ) ); }


//error symbol
.		{ System.out.println( "ERROR: " + yytext() ); }

