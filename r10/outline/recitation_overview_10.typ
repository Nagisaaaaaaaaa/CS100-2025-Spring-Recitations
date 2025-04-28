#import "@preview/basic-document-props:0.1.0": *

#show: simple-page.with(
  "TAs: 吴义恒 & 丁麟",
  "wuyh32023@shanghaitech.edu.cn\ndinglin12022@shanghaitech.edu.cn",
  middle-text: "CS100 Recitation - Week 10",
  numbering: false,
)

#let codetxt(txt) = [#text(font: "Segoe UI", fill: blue)[#txt]]
#let r(txt) = [#text(red)[#txt]]

#set text(size: 15pt)

= Overview

== 1. Warming up (10 min)
- Sign-in & Attendance
- comments on HW5 codecheck

== 2. Main Session #1 (50 min)
- #codetxt[Operator overload]: Let's design our vec2f
- #codetxt[std::sort & std::find]: Multiple ways of working with them
- #codetxt[lambda]: understanding capture

== 2. Main Session #2 (50 min)
- #codetxt[Iterators]: a dream of unification
- #codetxt[Smart pointers]: get rid of naked, C-styled pointers!
- #codetxt[Pass by view]: a deeper look at view
- Some comments on HW6

== Supplementary Materials
- #link("https://stackoverflow.com/questions/356950/what-are-c-functors-and-their-uses")[#underline("What are C++ functors and their uses? | stackoverflow")]
- #link("https://stackoverflow.com/questions/5501959/why-does-c11s-lambda-require-mutable-keyword-for-capture-by-value-by-defau")[#underline("Why does C++11's lambda require \"mutable\" keyword for capture-by-value, by default? | stackoverflow")]
