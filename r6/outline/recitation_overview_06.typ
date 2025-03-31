#import "@preview/basic-document-props:0.1.0": *

#show: simple-page.with(
  "TAs: 吴义恒 & 丁麟",
  "wuyh32023@shanghaitech.edu.cn\ndinglin12022@shanghaitech.edu.cn",
  middle-text: "CS100 Recitation - Week 06",
  numbering: false,
)

#let codetxt(txt) = [#text(font: "Segoe UI", fill: blue)[#txt]]
#let r(txt) = [#text(red)[#txt]]

#set text(size: 15pt)

= Overview

== 1. Warming up (10 min)
- Sign-in & Attendance.
- A few comments on code check.
- A few comments on HW4.

== 2. Main Session \#1 (30 \~ 40 min)
- Demo of good practices: using struct to pack things up
- Union -- shared memory space for different type interpretations
- Bit-fields -- low level optimizing technique

#align(right, [#text(size: 10pt)[C has become our old friend.] #emoji.hands.shake])
#v(-10pt)
#line(length: 100%)
#v(-10pt)
#align(left, [#text(size: 10pt)[From now on, we dive into the world of C++ !] #emoji.party #emoji.party])


== 3. Main Session \#2 (60 min)
- Introduction to #r([RAII]) (Resource Acquisition Is Initialization)
- C and C++ as memery-unsafe languages
- Why RAII? How does RAII protect our programs?

== 5. Bonus Application (10 min)
- Maybe we will talk a little bit more about clang-format.

== Supplementary Materials
- #link("https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#e6-use-raii-to-prevent-leaks")[#underline("CppCoreGuidelines | Use RAII to prevent leaks")]
- #link("https://youtu.be/Rfu06XAhx90?si=F9bs9hH1KkI6M7OD")[#underline("Back to Basics:  RAII in C++ - Andre Kostur - CppCon 2022 | Youtube")]
- #link("https://youtu.be/ZMzdrEYKyFQ?si=CJWRfnMuo8dfvxip")[#underline("the cleanest feature in C that you've probably never heard of | Youtube")]
