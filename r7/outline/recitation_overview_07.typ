#import "@preview/basic-document-props:0.1.0": *

#show: simple-page.with(
  "TAs: 吴义恒 & 丁麟",
  "wuyh32023@shanghaitech.edu.cn\ndinglin12022@shanghaitech.edu.cn",
  middle-text: "CS100 Recitation - Week 07",
  numbering: false,
)

#let codetxt(txt) = [#text(font: "Segoe UI", fill: blue)[#txt]]

#set text(size: 15pt)

= Overview

== 1. Warming up (10 min)
- Sign-in & Attendance
- Some comments on homework 4
- Some comments on AI abuse #emoji.face.sad

== 3. Main Session \#1 (50 min)
- Review of RAII -- at a much slower pace
- Understanding ownership?

== 2. Main Session \#2 (50 min)
- Reference #codetxt([\&]) in real practice
- #codetxt([auto]) in real practice
- First encounter with namespaces


== 4. Bonus Application -- Tools teaching (10 min)
- What if I don't want some files to be tracked by git?
- An introduction to .gitignore file

== Supplementary Materials
- #link("https://git-scm.com/docs/gitignore")[#underline("gitignore Documentation")]
- #link("https://en.cppreference.com/w/cpp/utility/pair")[#underline("std::pair | cppreference")]
- #link("https://google.github.io/styleguide/cppguide.html#Namespaces")[#underline("Namespace | Google C++ Style Guide")]
