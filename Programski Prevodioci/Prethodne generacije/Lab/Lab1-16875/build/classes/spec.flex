// import sekcija

%%

// sekcija opcija i deklaracija
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
//dodatni clanovi generisane klase
KWTable kwTable = new KWTable();
Yytoken getKW()
{
	return new Yytoken( kwTable.find( yytext() ),
	yytext(), yyline, yycolumn );
}
%}

//stanja
%xstate COMMENT
//makroi
slovo = [a-zA-Z]
cifra = [0-9]
cifraHex = [0-9A-F]
cifraOct = [0-7]

%%

// pravila
"%" { yybegin( COMMENT ); }
<COMMENT>~(%) { yybegin( YYINITIAL ); }

[\t\n\r ] { ; }

\( { return new Yytoken( sym.LEFTBRACKET, yytext(), yyline, yycolumn ); }
\) { return new Yytoken( sym.RIGHTTBRACKET, yytext(), yyline, yycolumn ); }
\{ { return new Yytoken( sym.LEFTCURLY, yytext(), yyline, yycolumn ); }
\} { return new Yytoken( sym.RIGHTCURLY, yytext(), yyline, yycolumn ); }
\? { return new Yytoken( sym.EPSILON, yytext(), yyline, yycolumn ); }
//operatori

> { return new Yytoken( sym.GREATER,yytext(), yyline, yycolumn ); }
\&& {return new Yytoken( sym.LOGICAND,yytext(), yyline, yycolumn ); }
"||" {return new Yytoken( sym.LOGICOR,yytext(), yyline, yycolumn ); }
\< { return new Yytoken( sym.LESS,yytext(), yyline, yycolumn ); }
== { return new Yytoken( sym.EQUAL,yytext(), yyline, yycolumn ); }
>= { return new Yytoken( sym.GREATEREQ,yytext(), yyline, yycolumn ); }
\<= { return new Yytoken( sym.LESSEQ,yytext(), yyline, yycolumn ); }
\!= { return new Yytoken ( sym.NOTEQ, yytext(), yyline, yycolumn); }
//separatori
; { return new Yytoken( sym.SEMICOLON, yytext(), yyline, yycolumn ); }
, { return new Yytoken( sym.COMMA, yytext(), yyline, yycolumn ); }

//kljucne reci
{slovo}+ { return getKW(); }

//ID-s
({slovo}|"_")({slovo}|{cifra}|"_")* { return new Yytoken(sym.ID, yytext(),yyline, yycolumn ); }
//konstante
//int
0#x{cifraOct}+|0#x{cifraHex}+|0#d{cifra}+|{cifra}+ { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }
//char
'[^]' { return new Yytoken( sym.CONST,yytext(), yyline, yycolumn ); }
//float
0\.{cifra}+(E[+-]?{cifra}+)? { return new Yytoken( sym.CONST,yytext(), yyline, yycolumn ); }
//bool
true|false { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }

//obrada gresaka
. { if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: " + yytext() ); }
