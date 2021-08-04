# ceval
A C/C++ header for parsing and evaluation of arithmetic expressions.
[README file identical to that of  <a href="https://github.com/e-t-sudo/ceval#readme">ceval</a> library]
## Functions accessibe from main()
<table>
<thead><th>Function</th><th>Argument(s)</th><th>Return Value</th></thead>
<tbody>
 <tr>
  <td><code>ceval_result()</code></td>
  <td>A mathematical expression in the form of a character array or a CPP string</td>
  <td>The result of the expression as a floating point number</td>
</tr>
<tr>
  <td><code>ceval_tree()</code></td>
  <td>A mathematical expression in the form of a character array or a CPP string</td>
  <td>The function prints the parse tree with each node properly indented depending on it's location in the tree structure</td>
</tr>
</tbody>
</table>

## Supported expressions
Any valid combination of the following operators and functions, with floating point numbers as operands can be parsed by <b>ceval</b>. Parenthesis can be used to override the default operator precedences. 

* Arithematic operators

`+` (addition), `-` (subtraction), `*` (multiplication), `/` (division), `%` (modulo), `^` (exponentiation), `\` (quotient), `!` (factorial)
* Relational operators

`==` (equal), `!=` (not equal), `<` (strictly less), `>` (strictly greater), `<=` (less or equal), `>=` (greater or equal) to compare the results of two expressions

* Single-argument functions

`exp()`, `sqrt()`, `cbrt()`, `sin()`, `cos()`, `tan()`, `asin()`, `acos()`, `atan()`, `sinh()`, `cosh()`, `tanh()`, `abs()`, `ceil()`, `floor()`, `log10()`, `ln()`, `deg2rad()`, `rad2deg()`, `signum()`, `int()`, `frac()`

* Two-argument functions

`pow()`, `atan2()`, `gcd()`, `hcf()`, `lcm()`, `log()` (generalized log(b, x) to any base `b`)

* Pre-defined math constants

`PI`, `E`

* The `,` operator

The comma `,` operator is also implemented. It returns the value of it's right-most operand. 

e.g; `2,3` would give `3`; `4,3,0` would be equal to `0`; and `cos(PI/2,PI/3,PI)` would return `cos(PI)` i.e, `-1`

## Installation
```shell
git clone https://github.com/e-t-sudo/ceval-single-header.git /tmp/ceval && \
cd /tmp/ceval && \
sudo make install
```

## Usage
After the installation, just include the ceval library using `#include<ceval/ceval.h>` directive in your C/C++ project. 

The code snippet given below is a console based interpreter that interactively takes in math expressions from stdin, and prints out their parse trees and results. 

```
//lang=c
#include<stdio.h>
#include<stdlib.h>

#include<ceval/ceval.h>

int main(int argc, char ** argv) {
  char expr[100];
  while (1) {
    printf("In = ");
    fgets(expr, 100, stdin);
    if (!strcmp(expr, "exit\n")) {
      break;
    } else if (!strcmp(expr, "clear\n")) {
      system("clear");
      continue;
    } else {
      ceval_tree(expr);
      printf("\nOut = %f\n\n", ceval_result(expr));
    }
  }
  return 0;
}
```

## Test Run
```
In = 3*7^2
                2
        ^
                7
*
        3

Out = 147.000000


In = (3.2+2.8)/2
        2
/
                2.80
        +
                3.20

Out = 3.000000


In = E^PI>PI^E
                2.72
        ^
                3.14
>
                3.14
        ^
                2.72

Out = 1.000000


In = 5.4%2
        2
%
        5.40

Out = 1.400000


In = 5.4\2
        2
\
        5.40

Out = 2.000000


In = 2*2.0+1.4
        1.40
+
                2
        *
                2

Out = 5.400000


In = (5/4+3*-5)+(sin(PI))^2+(cos(PI))^2
                2
        ^
                        3.14
                cos
+
                        2
                ^
                                3.14
                        sin
        +
                                        5
                                -
                        *
                                3
                +
                                4
                        /
                                5

Out = -12.750000


In = 3,4,5,6
        6
,
                5
        ,
                        4
                ,
                        3

Out = 6.000000


In = tanh(2/3)==(sinh(2/3)/cosh(2/3))
                                3
                        /
                                2
                cosh
        /
                                3
                        /
                                2
                sinh
==
                        3
                /
                        2
        tanh

Out = 1.000000


In = (2+3/3+(3+9.7))
                9.70
        +
                3
+
                        3
                /
                        3
        +
                2

Out = 15.700000


In = sin(pi/2)+cos(pi/2)+tan(pi/2)
                        2
                /
                        3.14
        tan
+
                                2
                        /
                                3.14
                cos
        +
                                2
                        /
                                3.14
                sin

[ceval]: tan() is not defined for odd-integral multiples of pi/2

Out = nan


In = asin(2)
        2
asin

[ceval]: Numerical argument out of domain

Out = nan


In = exit
... Program finished with exit code 0

```
