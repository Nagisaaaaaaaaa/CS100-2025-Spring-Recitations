#import "@preview/basic-document-props:0.1.0": *

#show: simple-page.with(
  "TAs: 吴义恒 & 丁麟",
  "wuyh32023@shanghaitech.edu.cn\ndinglin12022@shanghaitech.edu.cn",
  middle-text: "CS100 Recitation - Week 08",
  numbering: false,
)

#let codetxt(txt) = [#text(font: "Segoe UI", fill: blue)[#txt]]

#set text(size: 15pt)

= Overview

== 1. Warming up (10 min)
- Sign-in & Attendance
- Some comments on code check
- Some comments on homework 5

== 2. Main Session \#1 (60 min)
- References, r-values, and expressions
- The rules of 5

== 3. Main Session \#2 (40 min)
- Why pass-by-view is good?
- Template and class
- The 3 ways to hack OJ

== 4. Bonus Application -- Tools teaching (15 min)
- Simplify math expressions at compile-time
- Vim: How to code fast

== Supplementary Materials
- #link("https://youtu.be/X6AR2RMB5tE?si=ZGvvEAO31AyizPDV")[#underline("Vim As Your Editor - Introduction")]
- #link("https://en.cppreference.com/w/cpp/language/value_category")[#underline("Value categories | cppreference")]
