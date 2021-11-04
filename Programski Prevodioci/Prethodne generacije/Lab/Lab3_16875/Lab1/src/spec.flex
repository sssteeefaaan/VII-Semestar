
%%
%class MPLexer
%function next_token
%line
%column
%debug
%type Yytoken

%eofval{
return new Yytoken( sym.EOF, null, yyline, yycolumn);
%eofval}

%{
KWTable kwTable = new KWTable();
Yytoken getKW()
{
	return new Yytoken( kwTable.find( yytext() ),
	yytext(), yyline, yycolumn );
}
%}

%xstate COMMENT
abeceda = [a-zA-Z]
cifre = [0-9]
cifreHexa = [0-9A-F]
cifreOcta = [0-7]
%%

"%" { yybegin( COMMENT ); }
<COMMENT>~(%) { yybegin( YYINITIAL ); }

[\t\n\r ] { ; }

\( { return new Yytoken( sym.LEFTBRACKET, yytext(), yyline, yycolumn ); }
\) { return new Yytoken( sym.RIGHTTBRACKET, yytext(), yyline, yycolumn ); }
\{ { return new Yytoken( sym.LEFTCURLY, yytext(), yyline, yycolumn ); }
\} { return new Yytoken( sym.RIGHTCURLY, yytext(), yyline, yycolumn ); }
\? { return new Yytoken( sym.EPSILON, yytext(), yyline, yycolumn ); }

= { return new Yytoken( sym.ASSIGN,yytext(), yyline, yycolumn ); }
> { return new Yytoken( sym.GREATER,yytext(), yyline, yycolumn ); }
\&& {return new Yytoken( sym.LOGICAND,yytext(), yyline, yycolumn ); }
"||" {return new Yytoken( sym.LOGICOR,yytext(), yyline, yycolumn ); }
\< { return new Yytoken( sym.LESS,yytext(), yyline, yycolumn ); }
== { return new Yytoken( sym.EQUAL,yytext(), yyline, yycolumn ); }
>= { return new Yytoken( sym.GREATEREQ,yytext(), yyline, yycolumn ); }
\<= { return new Yytoken( sym.LESSEQ,yytext(), yyline, yycolumn ); }
\!= { return new Yytoken ( sym.NOTEQ, yytext(), yyline, yycolumn); }

; { return new Yytoken( sym.SEMICOLON, yytext(), yyline, yycolumn ); }
, { return new Yytoken( sym.COMMA, yytext(), yyline, yycolumn ); }


//bool
"true" { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }
"false" { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }

{abeceda}+ { return getKW(); }

({abeceda}|"_")({abeceda}|{cifre}|"_")* { return new Yytoken(sym.ID, yytext(),yyline, yycolumn ); }
//int
0#x{cifreOcta}+|0#x{cifreHexa}+|0#d{cifre}+|{cifre}+ { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }
//char
'[^]' { return new Yytoken( sym.CONST,yytext(), yyline, yycolumn ); }
//float
0\.{cifre}+(E[+-]?{cifre}+)? { return new Yytoken( sym.CONST,yytext(), yyline, yycolumn ); }

. { if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: " + yytext() ); }
