#import "@preview/basic-document-props:0.1.0": *

#show: simple-page.with(
  "TAs: 吴义恒 & 丁麟",
  "wuyh32023@shanghaitech.edu.cn\ndinglin12022@shanghaitech.edu.cn",
  middle-text: "CS100 Recitation - Week 05",
  numbering: false,
)

#let codetxt(txt) = [#text(font: "Segoe UI", fill: blue)[#txt]]

#set text(size: 15pt)

= Overview

== 1. Warming up (10 min)
- Sign-in & Attendance.
- Some comments on homework and quiz.

== 2. Main Session \#1 (50 min)
- Review of HW2 Problem5 (D$acute(e)$j$grave(a)$ Vu!)
- Review of several quiz problems.
- Introduction to variable lifetimes.

== 3. Main Session \#2 (50 min)
- Review of struct in C.
- Function pointers.
- File I/O & redirection.

== 4. Bonus Application (30 min)
- ...

== Supplementary Materials
- #link("https://code.visualstudio.com/docs")[#underline("VSCode Documentation")]
- #link("https://clang.llvm.org/docs/ClangFormat.html")[#underline("ClangFormat Documentation")]
