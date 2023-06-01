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
