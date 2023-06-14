## Grammar for handling '*', '/', '+', '-'
```
expr: term((PLUS | MINUS) term)*
term: factor((MUL | DIV) factor)*
factor: INTEGER
```

## Grammar for handling '(...)', '*', '/', '+', '-' 
```
expr: term((PLUS | MINUS) term)*
term: factor((MUL | DIV) factor)*
factor: INTEGER | LPAREN expr RPAREN
```

## Grammar for handling pascal program (part-9)
```
program: compound_statement DOT

compound_statement: BEGIN statement_list END
statement_list: statement | statement SEMI statement_list

statement: compound_statement | assignment_statement | empty
assignment_statement: variable ASSIGN expr
variable: ID

empty: 

expr: term((PLUS | MINUS) term)*
term: factor((MUL | DIV) factor)*
factor: PLUS factor | MINUS factor | INTEGER | LPAREN expr RPAREN | variable
```

## Grammar for handling a more complex pascal program (part-10)
```
program : PROGRAM variable SEMI block DOT

block : declarations compound_statement

declarations : VAR (variable_declaration SEMI)+
| empty

variable_declaration : ID (COMMA ID)* COLON type_spec

type_spec : INTEGER | REAL

compound_statement : BEGIN statement_list END

statement_list : statement
| statement SEMI statement_list

statement : compound_statement
| assignment_statement
| empty

assignment_statement : variable ASSIGN expr

empty :

expr : term ((PLUS | MINUS) term)*

term : factor ((MUL | INTEGER_DIV | FLOAT_DIV) factor)*

factor : PLUS factor
| MINUS factor
| INTEGER_CONST
| REAL_CONST
| LPAREN expr RPAREN
| variable

variable: ID
```
