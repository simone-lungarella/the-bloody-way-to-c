---
title: "A _bloody_ approach to C"
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

Each chapter is written following each lesson and, if needed, integrated with personal consideration. Each snippet is written and tested by the author and may vary from what is stated in the lessons.

# Acknowledgments {-}



# Introduction {-}

## The C language, as an idea of computation {-}
C was invented in [Bell Laboratories](https://it.wikipedia.org/wiki/Bell_Laboratories) in the period [Ken Thompson](https://it.wikipedia.org/wiki/Ken_Thompson) was working on Unix. Following the idea that a good operating system should have had a high level language compiler—an attempt on creating a compiler for [`Fortran`](https://it.wikipedia.org/wiki/Fortran) was made. After failing this task, a new language was created and named [`B`](https://en.wikipedia.org/wiki/B_(programming_language)). `B` was not enough to port Unix from Assembly though so [`C`](https://en.wikipedia.org/wiki/C_(programming_language)) was invented.

`C` was a better language mainly because it has multiple distinct types:

- pointers;
- integer;
- floating point numbers: float;

In that sense, `C` language can be visualized as `B` with types where all types can also be imagined as integers since pointers—in simple terms—are integers and so are structures. In fact, structures are a set of integers representing offset of each field and values of the very same fields. This simplicity can be considered the strength of the language as it can be easily picked up by new developers, layered to build a powerful abstraction and, with that, achieve a higher level of abstraction to imagine in simple terms complex topics and algorithms.

# Chapter

