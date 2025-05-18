---
title: "The Bloody Way to C"
subtitle: "A Brutalist Approach to C Language—No Boilerplate"
author: "Simone Lungarella (simonelungarella@gmail.com)"
date: "2025-05-11"
lang: "en"
geometry: margin=1in
fontfamily: lmodern
toc: true
toc-depth: 2
numbersections: true
colorlinks: true
header-includes:
  - \usepackage{float}
  - \let\origfigure\figure
  - \let\endorigfigure\endfigure
  - \renewenvironment{figure}[1][2]{\expandafter\origfigure\expandafter[H]}{\endorigfigure}
---

# Preface {-}

This book is a humble attempt to capture every piece of information given by Salvatore Sanfilippo—aka [antirez](https://github.com/antirez)—in his C course presented on YouTube.

Each chapter is written following each lesson and, if needed, integrated with personal consideration. Each snippet is written and tested by me and may vary from what is stated in the lessons.

# Introduction {-}

## The C language, as an idea of computation {-}
C was invented in [Bell Labs](https://it.wikipedia.org/wiki/Bell_Laboratories) when [Ken Thompson](https://it.wikipedia.org/wiki/Ken_Thompson) was working on Unix. Following the idea that a good operating system should have had a high level compiled language. After abandoning the first attempt on creating a compiler for [`Fortran`](https://it.wikipedia.org/wiki/Fortran), a smaller new language was created and named [`B`](https://en.wikipedia.org/wiki/B_(programming_language)). `B` better fitted [P2P11](https://en.wikipedia.org/wiki/PDP-11) but was not enough to port Unix from Assembly. [`C`](https://en.wikipedia.org/wiki/C_(programming_language)) was created with a set of feature that were missing in `B` and was a much better fit for the Unix system.

`C` was a better language mainly because its multiple distinct types:

- pointers;
- integer;
- floating point numbers: float;

In that sense, `C` language can be visualized as `B` with types where all types can also be imagined as integers since pointers—in very simple terms—are integers and so are structures. In fact, structures are a set of integers representing offsets of each field position in memory and values of the very same fields. This simplicity can be considered the strength of the language as it can be easily picked up by new developers, layered to build a powerful abstraction and, with that, imagine in simple terms complex topics and algorithms.

## The CLI, as a lifestyle {-}

To understand every aspect of `C`, many tools will be used and all examples will refer to [CLI](https://en.wikipedia.org/wiki/Command-line_interface) commands. I will be using [Neovim](https://neovim.io/) as text editor and operate on a Linux machine. The output of commands and all examples may differ from machine to machine but the concepts will remain valid.

I strongly believe that the best way to develop software is by using `CLI` and lightweight text editors such as `neovim` or `vim`. Whenever is possible I will avoid using browsers to search for documentation by preferring usage of `man` directly into the terminal. This will keep low the friction and avoid the necessity to leave the home row of my keyboard.

# Anatomy of a C program

## Execute a C program

`C` is a compiled language, this means you cannot execute a file containing the main function. It requires to be compiled.

You can use: `cc` to compile a `C` program. `cc` is a Unix command that let you easily communicate with the compiler. You can use: `cc --version` to check what compiler does it use.

```bash
> cc --version
cc (GCC) 14.2.1 20240912 (Red Hat 14.2.1-3)
Copyright (C) 2024 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

Let's consider the following simple `C` program contained in a file named—for instance—`hello_world.c` (how original):

```c
#include <stdio.h>

int main(void) {
  printf("Hello World\n");
  return 0;
}
```

You can use: `cc hello_world.c` to compile it to an executable program.

The compiler generates an executable binary file named: `a.out`. This file is executable and runs your program. You can use: `file a.out` to check information about the generated file.

```bash
> file a.out
./a.out: ELF 64-bit LSB executable, x86-64, version 1 (SYSV), dynamically linked, \
interpreter /lib64/ld-linux-x86-64.so.2, \
BuildID[sha1]=d589730d718a032a35f848fe8d280063a6cee18c, \
for GNU/Linux 3.2.0, not stripped
```

If you want to check the content of the generated binary file, you can use: `hexdump -C a.out`.

```bash
> hexdump -C a.out
00000000  7f 45 4c 46 02 01 01 00  00 00 00 00 00 00 00 00  |.ELF............|
00000010  02 00 3e 00 01 00 00 00  40 10 40 00 00 00 00 00  |..>.....@.@.....|
00000020  40 00 00 00 00 00 00 00  f0 38 00 00 00 00 00 00  |@........8......|
00000030  00 00 00 00 40 00 38 00  0d 00 40 00 20 00 1f 00  |....@.8...@. ...|
00000040  06 00 00 00 04 00 00 00  40 00 00 00 00 00 00 00  |........@.......|
00000050  40 00 40 00 00 00 00 00  40 00 40 00 00 00 00 00  |@.@.....@.@.....|
00000060  d8 02 00 00 00 00 00 00  d8 02 00 00 00 00 00 00  |................|
[...]
```

You can also generate [Assembly](https://en.wikipedia.org/wiki/Assembly_language) code using: `cc -S hello_world.c` if the compiler supports this feature.

```bash
> cat hello_world.s
	.file	"hello_world.c"
	.text
	.section	.rodata
.LC0:
	.string	"Hello World"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$.LC0, %edi
	call	puts
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (GNU) 14.2.1 20240912 (Red Hat 14.2.1-3)"
	.section	.note.GNU-stack,"",@progbits
```

With a given compiler, you can tweak many compilation aspects. For instance, `cc -O2 hello_world.c` tells the compiler to optimize the generated executable. A more optimized version of the executable is also slower to be generated and, if that does not make much sense for small programs, it can output a much better version of the program when a high enough level of complexity has been reached.

With [GCC](https://en.wikipedia.org/wiki/GNU_Compiler_Collection) compiler, you can see that our simple program make use of `puts` [syscall](https://en.wikipedia.org/wiki/System_call), however, this depends on the compiler itself and, often, with different compilers, the line: `printf("Hello World\n");` is compiled using `printf` syscall instead.

Using `-O2` flag can make the compiler use `puts` as this syscall is faster than `printf`. This is a simple, yet meaningful, example but in such a small program it does make no difference in terms of execution speed. The compiler is very good at improving written programs if given enough time. While developing, though, a low compilation time is often preferred.

> You can check the standard C library from the terminal using `man` or `--help` flags. For example, you can use `man 3 puts` or `man 3 printf` to check documentation of both syscalls (3 makes sure to output the C library description).

## Include other source code
In the very first line of our simple program, you can see a [preprocessor](https://en.wikipedia.org/wiki/Preprocessor) [directive](https://en.wikipedia.org/wiki/Directive_(programming)). This line simply tells to the compiler that a file need to be included into the program. The compiler, before the compilation, take the content of the file and _paste_ it at the location. In this case, `<stdio.h>` declares the prototype of `printf` function so to instruct the compiler on how to execute that specific call. To prove this point, you can remove the first line and replace it with: `int printf(const char *restrict format, ...);` which is the prototype of the function we want to call.

```c
int printf(const char *restrict format, ...);

int main(void) {
  printf("Hello World\n");
  return 0;
}
```

`#include` can also be used to include `C` files. In fact, you can move a single line to a different file and than compile a program that includes the file on the line you want it to be replaced.

```c
#include <stdio.h>

int main(void) {
  #include "file.c"
  return 0;
}
```

The generated assembly or machine code will be equivalent.
