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
%xstate KOMENTAR

//makroi
slovo = [a-zA-Z]
cifra = [0-9]
cifra8 = [0-7]
cifra16= [0-9A-F]
%%

// pravila
\|\* { yybegin( KOMENTAR ); }
<KOMENTAR>~"*|" { yybegin( YYINITIAL ); }

[\t\n\r ] { ; }
\( { return new Yytoken( sym.LEFTPAR, yytext(), yyline, yycolumn ); }
\) { return new Yytoken( sym.RIGHTPAR, yytext(), yyline, yycolumn ); }

//operatori
\< { return new Yytoken( sym.LESS,yytext(), yyline, yycolumn ); }
\<\= { return new Yytoken( sym.LESSEQUAL,yytext(), yyline, yycolumn ); }
\=\= { return new Yytoken( sym.EQUAL,yytext(), yyline, yycolumn ); }
\<\> { return new Yytoken( sym.NOTEQUAL,yytext(), yyline, yycolumn ); }
\> { return new Yytoken( sym.GREATER,yytext(), yyline, yycolumn ); }
\>\= { return new Yytoken( sym.GREATEREQUAL,yytext(), yyline, yycolumn ); }
\=\> { return new Yytoken( sym.ARROW, yytext(), yyline, yycolumn ); }
//separatori
; { return new Yytoken( sym.SEMICOLON, yytext(), yyline, yycolumn ); }
: { return new Yytoken( sym.COLON, yytext(), yyline, yycolumn ); }
, { return new Yytoken( sym.COMMA, yytext(), yyline, yycolumn ); }
\. { return new Yytoken( sym.DOT, yytext(), yyline, yycolumn ); }
:= { return new Yytoken( sym.ASSIGN, yytext(), yyline, yycolumn ); }


//kljucne reci
{slovo}+ { return getKW(); }
//identifikatori
({slovo}|\$)({slovo}|{cifra}|\$)* { return new Yytoken(sym.ID, yytext(),yyline, yycolumn ); }
//konstante

//BOOLEAN
"TRUE" { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }
"FALSE" { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }
//REAL
{cifra}+\.({cifra}+)?(E([+-])?{cifra}+)? { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }
\.{cifra}+(E([+-])?{cifra}+)?  { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }
//CHAR
'[^]' { return new Yytoken( sym.CONST,yytext(), yyline, yycolumn ); }
//INT
{cifra}+ { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }
0{cifra8}+ { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }
0x{cifra16}+ { return new Yytoken( sym.CONST, yytext(), yyline, yycolumn ); }
//obrada gresaka
. { if (yytext() != null && yytext().length() > 0) System.out.println( "ERROR: " + yytext() ); }

