# any_of

## Introduction

A simple library that lets you compare a value against many values using one operator.

E.g.
```c++
x == srp::any_of(1, 2, 3, 4);
```

is equivalent to:
```c++
x == 1 || x == 2 || x == 3 || x == 4;
```

Besides `any_of`, library also provides `none_of`, `all_of` and `one_of`. All of them override `operator==` in an expected way:

`x == srp::none_of(1, 2, 3)` is equivalent to `x != 1 && x != 2 && x != 3`
`x == srp::all_of(1, 2, 3)` is equivalent to `x == 1 && x == 2 && x == 3`
`x == srp::one_of(1, 2, 3)` is equivalent to `(x == 1) + (x == 2) + (x == 3) == 1`

## Custom functions

In addition to these functions, you can define your own functions with custom behaviour using `srp::make_custom_of`. It is a function template taking operator structs defining operators that should be available and return a lambda that can be called just like `srp::any_of`.
Operator struct should define an operator as a friend function.
Library provides `srp::EqOp` that provides `operator==` and `srp::NeqOp` that provides `operator!=`.
