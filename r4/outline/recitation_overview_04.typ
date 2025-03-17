#import "@preview/basic-document-props:0.1.0": *

#show: simple-page.with(
  "TAs: 吴义恒 & 丁麟",
  "wuyh32023@shanghaitech.edu.cn\ndinglin12022@shanghaitech.edu.cn",
  middle-text: "CS100 Recitation - Week 04",
  numbering: false,
)

#let codetxt(txt) = [#text(font: "Segoe UI", fill: blue)[#txt]]

#set text(size: 15pt)

= Overview

== 1. Warming up (15 min)
- Sign-in & Attendance.
- Review of learned contents.
- Some comments on course setting and goal of teaching.
// - #text(gray)[\* Explain MinGW's artifacts for long double printing.]

== 2. Tools teaching (15 min)
- Review of Git basics: #codetxt([init, status, add, commit, log, diff, push, clone]).
- Productivity enhancements. (Typing \& editing, package management, etc.)

== 3. Main Session \#1 (20 min)
- Pointer conversions.
- Null pointers.
- First encounter with #codetxt([const]).

== 4. Main Session \#2 (40 min)
- Variable length arrays.
- Strings in C language.
- Allocate memory for \"2D\" arrays.

== 5. Bonus Application (30 min)
- How to make your code well-structured and easy to maintain? - Take HW2 Gomoku as an example.

== Supplementary Materials
- #link("https://www.typingtest.com")[#underline("TypingTest | Typing Training")]
- #link("https://scoop.sh")[#underline("Scoop | A command-line installer for Windows")]
