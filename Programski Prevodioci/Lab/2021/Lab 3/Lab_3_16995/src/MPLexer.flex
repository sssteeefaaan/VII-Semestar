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
"<-comm"                        { yybegin( COMMENT ); }
<COMMENT>~("comm->")            { yybegin( YYINITIAL ); }

// Tabulatori
[\t\n\r ] 			{  }


// Zagrade
\(                              { return new Symbol( sym.OPEN_BRACKET ); }
\)                              { return new Symbol( sym.CLOSE_BRACKET ); }
\{                              { return new Symbol( sym.OPEN_CURLY_BRACKET ); }
\}                              { return new Symbol( sym.CLOSE_CURLY_BRACKET ); }


// Operatori
\+                              { return new Symbol( sym.PLUS ); }
\*                              { return new Symbol( sym.MULTIPLY ); }
=                               { return new Symbol( sym.ASSIGN ); }


// Separatori
;                               { return new Symbol( sym.SEMICOLON ); }


// Kljucne reci

"strategy"                      {   return new Symbol( sym.STRATEGY_BEGIN );    }
"~strategy"                     {   return new Symbol( sym.STRATEGY_END );      }
"declaration"                   {   return new Symbol( sym.DECLARATION_BEGIN ); }
"~declaration"                  {   return new Symbol( sym.DECLARATION_END );   }
"int"                           {   return new Symbol( sym.INT );               }
"double"                        {   return new Symbol( sym.DOUBLE );            }
"string"                        {   return new Symbol( sym.STRING );            }
"bool"                          {   return new Symbol( sym.BOOL );              }
"char"                          {   return new Symbol( sym.CHAR );              }
"repeat"                        {   return new Symbol( sym.REPEAT );            }
"less"                          {   return new Symbol( sym.LESS );              }
"equal"                         {   return new Symbol( sym.EQUAL );             }
"greater"                       {   return new Symbol( sym.GREATER );           }
"numInstances"                  {   return new Symbol( sym.NUM_INSTANCES );     }
"service"                       {   return new Symbol( sym.SERVICE_BEGIN );     }
"~service"                      {   return new Symbol( sym.SERVICE_END );       }
"serviceName"                   {   return new Symbol( sym.SERVICE_NAME );      }
"executedBy"                    {   return new Symbol( sym.EXECUTED_BY );       }
"if"                            {   return new Symbol( sym.IF );                }
"then"                          {   return new Symbol( sym.THEN );              }
"scale"                         {   return new Symbol( sym.SCALE );             }
"redeployOn"                    {   return new Symbol( sym.REDEPLOY_ON );       }
"optimize"                      {   return new Symbol( sym.OPTIMIZE );          }

// bool
"true"|"false"                  { return new Symbol( sym.CONST, Boolean.parseBoolean( yytext() ) ); }

// ID-evi
{slovo}({slovo}|{cifra})*       { return new Symbol( sym.ID, yytext() ); }

// Konstante

// int
[-]?{niz_cifara}                { return new Symbol( sym.CONST, Integer.parseInt( yytext() ) ); }

// double
[-]?{niz_cifara}\.{niz_cifara}  { return new Symbol( sym.CONST, Double.parseDouble( yytext() ) ); }

// string
\"{niz_znakova}\"               { return new Symbol( sym.CONST, yytext() ); }

// char
'{znak}'                        { return new Symbol( sym.CONST, yytext() ); }


// Greska
.  { if (yytext() != null && yytext().length() > 0) System.out.println( "Error at ln: " + yyline + ", column: " + yycolumn + " -- " + yytext() ); }