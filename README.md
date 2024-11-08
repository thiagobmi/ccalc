<div align="center">
<img src="https://github.com/user-attachments/assets/a13be581-ef1c-43ec-a748-b1d69adbc39a" width="550"/>
</div>
<p align="center">
    <p align="center">
        <a href="#overview">Overview</a> &#183;
        <a href="#features">Features</a> &#183;
        <a href="#how-to-use">How to Use</a>
    </p>
</p>

## Overview
Command-line math expression parser and calculator, inspired by GNU calc.

## Disclaimer
This project was made purely for fun and in my free time. It's full of bad practices. I just tried to do it in my own way, without any previous knowledge on lexical analysis or mathematical expressions parsing. So **this code is not meant to be taken as a serious math expression parser**.

## Features
- Validates the input expression for correctness.
- Adds brackets to expressions following precedence order for accurate parsing.
- Parses and calculates mathematical expressions, supporting basic arithmetic operations: addition (+), subtraction (-), multiplication (*), division (/), and exponentiation (^).
- Shows the result of each step during the calculation process.

## How to Use

You can directly pass the input as an argument to the program, like in the 'calc' command:
```bash
ccalc "(((56-23)*2^2-7)/12.5+(10-4+(10/5*3+54+2^2)+1)+1-2)/2^2.5"
```

![image](https://github.com/user-attachments/assets/39494c14-c0e8-403e-a0ac-270f6a2e5b6a)



