@echo off
REM ********   PODESAVANJA - MENJA STUDENT *********
set JCUP_HOME="C:\Users\Stefan\Desktop\VII-Semestar\Programski Prevodioci\Alati\java_cup_v10k"
set JAVA_HOME="C:\Program Files\Java\jre1.8.0_311"
set PARSER_CLASS_NAME="MPParserSemantics"
set CUP_SPEC_NAME="MPParserSemantics.cup"


REM ********   POZIV JAVA CUP APLIKACIJE  ***********
echo vrednost : %JCUP_HOME%
%JAVA_HOME%\bin\java -classpath %JCUP_HOME% java_cup.Main -parser %PARSER_CLASS_NAME% -symbols sym < %CUP_SPEC_NAME%

PAUSE
