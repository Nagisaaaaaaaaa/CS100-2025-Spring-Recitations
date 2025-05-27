#import "@preview/basic-document-props:0.1.0": *

#show: simple-page.with(
  "TAs: 吴义恒 & 丁麟",
  "wuyh32023@shanghaitech.edu.cn\ndinglin12022@shanghaitech.edu.cn",
  middle-text: "CS100 Recitation - Week 13",
  numbering: false,
)

#let codetxt(txt) = [#text(font: "Segoe UI", fill: blue)[#txt]]
#let r(txt) = [#text(red)[#txt]]

#set text(size: 15pt)

= Overview

== 1. Warming up (10 min)
- Sign-in & Attendance
- About the exam
- About hw8
- Intro to Computer Graphics

== 2. Main Session #1 (50 min)
- Interface v.s. Implementation
- What is CMake? Why we need CMake?
- Part1: getting to know CMake
- Part2: add a library with CMake and hide implementations
- Part3: Wanna to hide a class? Pointer to implementation!

== 3. Main Session #2 (50 min)
- #codetxt[template]: Essential motivation of template.
- Template specialization
- Type traits and SFINAE: Substitution Failure Is Not An Error
- #text(gray)[Metaprogramming and template magics]

== Supplementary Materials
- #link("https://cmake.org/cmake/help/latest/guide/tutorial/index.html")[#underline("CMake Official Tutorial")]
- #link("https://cmake.org/cmake/help/latest/index.html")[#underline("CMake Documentation")]
- #link("https://raytracing.github.io/books/RayTracingInOneWeekend.html")[#underline("Ray Tracing in One Weekend")]
- #link("https://www.bilibili.com/video/BV1X7411F744/?share_source=copy_web&vd_source=ca4dac12aaac43f0fc37e931183ee5c9")[#underline("【GAMES101-现代计算机图形学入门-闫令琪】")]
- #link("https://faculty.sist.shanghaitech.edu.cn/faculty/liuxp/flare/gallery.html")[#underline("Flare Lab | Shanghaitech")]
