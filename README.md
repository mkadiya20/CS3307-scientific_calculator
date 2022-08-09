# CS3307A Group Project

## Running the software

- The project uses qmake to compile all the source and
header files.
- Simply run `qmake` and then `make` to compile the project and will
generate the appropriate `.o` and `moc` files.
- To run the software, `main/bin/calculator` on linux and the GUI will open.
- Doxygen files can be found in `main/html`. Run the `index.html` file to
open the documentation for the project.

## Additional information
- Project is using one external library `qcustomplots` to generate
the graph and is not included in the doxygen documentation.
- Division is treated as a `Fraction` and it has lower precedence
compared to multiplication.
- Arithmetic for expressions involving variables is limited to same type of `Function`. Meaning
it will not reduce `x+sin(x)+x` to `2x+sin(x)` because it involves
arithmetic between two different types of functions.
- The grammar used in the `Parser.cpp` is as follows:
```
expr = expr + term | expr - term | term
term = term * power | term / power | power
power = factor ^ power | factor
factor = (expr) | number | variable
number = digit number | digit
digit = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
variable = a | b | ... | z
```
