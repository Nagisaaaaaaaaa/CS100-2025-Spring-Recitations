#import "@preview/basic-document-props:0.1.0": *

#show: simple-page.with(
  "TAs: 吴义恒 & 丁麟",
  "wuyh32023@shanghaitech.edu.cn\ndinglin12022@shanghaitech.edu.cn",
  middle-text: "CS100 Recitation - Week 11",
  numbering: false,
)

#let codetxt(txt) = [#text(font: "Segoe UI", fill: blue)[#txt]]
#let r(txt) = [#text(red)[#txt]]

#set text(size: 15pt)

= Overview

== 1. Warming up (10 min)
- Sign-in & Attendance
- Syncing with other recitation classes
- About the exam and our review class

== 2. Main Session #1 (40 min)
- Why we need class derivation? - From a renderer's prospective.
- #codetxt[public v.s. private derivation]: IS-A or HAS-A?
- #codetxt[base constructors in derived classes]: whether / when it is called?

== 3. Main Session #2 (40 min)
- #codetxt[virtual function]: pure virtual function, override.
- #codetxt[implicit upcasting]: base pointer points to derived classes
- #codetxt[destructors in derivation]: when / why virtual?

== 4. Bonus Application (20 min)
- How to prepare your exam?
- What are the priorities?
- How to prepare a cheat sheet.

== Supplementary Materials
- #link("https://github.com/PacktPublishing/Hands-On-Design-Patterns-with-CPP-Second-Edition/?tab=readme-ov-file")[#underline("Hands-On Design Patterns with C++ - Second Edition | GitHub")]
- #link("https://raytracing.github.io/books/RayTracingInOneWeekend.html")[#underline("Ray Tracing in One Weekend")]
