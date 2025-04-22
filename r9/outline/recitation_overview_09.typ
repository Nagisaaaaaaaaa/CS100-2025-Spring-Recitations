#import "@preview/basic-document-props:0.1.0": *

#show: simple-page.with(
  "TAs: 吴义恒 & 丁麟",
  "wuyh32023@shanghaitech.edu.cn\ndinglin12022@shanghaitech.edu.cn",
  middle-text: "CS100 Recitation - Week 09",
  numbering: false,
)

#let codetxt(txt) = [#text(font: "Segoe UI", fill: blue)[#txt]]
#let r(txt) = [#text(red)[#txt]]

#set text(size: 15pt)

= Overview

== 1. Warming up (10 min)
- Sign-in & Attendance
- Where are we (in the ocean of C++) ? Why do we feel at loss?
- #emoji.lightning Sanity charging #emoji.lightning

== 2. Main Session (#math.infinity min)
- #codetxt[Rvalue references]: a hard battle -- never enough attention on it
- #codetxt[Dynarray]: the rules of 5; exception safety issue; copy-and-swap idiom;
- #codetxt[Value categories]: another hard battle -- never enough attention on that as well
- #codetxt[Constructors]: Default or Copy or Move; copy-elision;
- #codetxt[Const & non-const references]: function overloading; parameter matching;
- #codetxt[Class design]: make your class modern

== 4. Bonus Application -- Tools teaching (15 min)
- What is property? Why property?

== Supplementary Materials
- #link("https://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom")[#underline("What is the copy-and-swap idiom?")]
- #link("https://www.nextptr.com/tutorial/ta1211389378/beware-of-using-stdmove-on-a-const-lvalue")[#underline("Beware of using std::move on a const lvalue")]
