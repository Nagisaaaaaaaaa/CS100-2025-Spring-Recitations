#import "@preview/basic-document-props:0.1.0": *

#show: simple-page.with(
  "TAs: 吴义恒 & 丁麟",
  "wuyh32023@shanghaitech.edu.cn\ndinglin12022@shanghaitech.edu.cn",
  middle-text: "CS100 Recitation - Week 02",
  numbering: false,
)

#let codetxt(txt) = [#text(font: "Segoe UI", fill: blue)[#txt]]

#set text(size: 15pt)

= Overview

== 1. Warming up (10 min)
- Sign-in & Attendance.
- Review of last week.
- Homework submission instructions.

== 2. Tools teaching -- Diving into Git (15 \~ 20 min)
- Review of #codetxt([git clone]), #codetxt([git pull]).
- What is Git? What does Git do? Why should you use it?
- #text(red)[Version control] + Cloud backup + Multi-developer cooperation
- Local Git operations, #codetxt([init, add, commit, log, reset]).


== 3. Main Session (50 \~ 70 min)
- Undefined behavior
- Integer promotion
- Binary number representaion
- Arithmetic Types, #codetxt([sizeof]), floating-point errors
- Literals
- Operator precedence, associativity, order of evaluation
- #text(gray)[\* Bitwise operators]
- The free Q&A session.

== 4. Bonus Application (15 \~ 20 min)
- Continue with some basic drawing techniques with C.

~

== Supplementary Materials
- #link("https://github.com/Nagisaaaaaaaaa/CS100-2025-Spring-Recitations")[#underline("Git Tutorial for Beginners: Learn Git in 1 Hour")]
- #link("https://docs.github.com/en/get-started/git-basics")[#underline("Git basics | GitHub")]
- #link("https://ieeexplore.ieee.org/document/8766229")[#underline("IEEE Standard for Floating-Point Arithmetic | 754-2019")]
- #link("https://en.cppreference.com/w/c/language/operator_arithmetic")[#underline("Learn definition of C/C++ overflow with cppreference (homework-related)")]
- #link("https://en.wikipedia.org/wiki/Horner%27s_method")[#underline("Horner's Method (homework-related)")]
