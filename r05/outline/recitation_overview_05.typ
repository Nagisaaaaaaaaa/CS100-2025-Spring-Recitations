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

== 1. Warming up (5 min)
- Sign-in & Attendance.
- Some comments on homework and quiz.

== 2. Main Session \#1 (45 min)
- Review of HW2 Problem5 (D$acute(e)$j$grave(a)$ Vu!)
- Review of several quiz problems.
- Introduction to variable lifetimes.

== 3. Main Session \#2 (45 min)
- Review of struct in C.
- Function pointers.
- File I/O & redirection.

== 4. Bonus Application (30 min)
- VSCode training: settings that promote your productivity.

== Supplementary Materials
- #link("https://code.visualstudio.com/docs")[#underline("VSCode Documentation")]
- #link("https://clangd.llvm.org")[#underline("clangd | teach your editor C++")]
- #link("https://clang.llvm.org/docs/ClangFormat.html")[#underline("ClangFormat Documentation")]
