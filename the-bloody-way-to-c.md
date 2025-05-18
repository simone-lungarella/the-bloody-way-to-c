---
title: "The Bloody Way to C"
subtitle: ""
author: "Simone Lungarella (simonelungarella@gmail.com)"
date: "2025-05-11"
lang: "it"
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

This book is a humble attempt to capture every piece of information given by Salvatore Sanfilippo—aka [antirez](https://github.com/antirez)—in his C course presented in Italian on YouTube.

Each chapter is written following each lesson and, if needed, integrated with personal consideration. Each snippet is written and tested by me and may vary from what is stated in the lessons.

# Introduction {-}

## The C language, as an idea of computation {-}
C was invented in [Bell Labs](https://it.wikipedia.org/wiki/Bell_Laboratories) when [Ken Thompson](https://it.wikipedia.org/wiki/Ken_Thompson) was working on Unix. Following the idea that a good operating system should have had a high level compiled language. After abandoning the first attempt on creating a compiler for [`Fortran`](https://it.wikipedia.org/wiki/Fortran), a smaller new language was created and named [`B`](https://en.wikipedia.org/wiki/B_(programming_language)). `B` better fitted [P2P11](https://en.wikipedia.org/wiki/PDP-11) but was not enough to port Unix from Assembly. [`C`](https://en.wikipedia.org/wiki/C_(programming_language)) was created with a set of feature that were missing in `B` and was a much better fit for the Unix system.

`C` was a better language mainly because its multiple distinct types:

- pointers;
- integer;
- floating point numbers: float;

In that sense, `C` language can be visualized as `B` with types where all types can also be imagined as integers since pointers—in very simple terms—are integers and so are structures. In fact, structures are a set of integers representing offsets of each field position in memory and values of the very same fields. This simplicity can be considered the strength of the language as it can be easily picked up by new developers, layered to build a powerful abstraction and, with that, imagine in simple terms complex topics and algorithms.

