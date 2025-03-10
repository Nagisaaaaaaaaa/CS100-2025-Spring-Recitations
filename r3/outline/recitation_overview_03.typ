#import "@preview/basic-document-props:0.1.0": *

#show: simple-page.with(
  "TAs: 吴义恒 & 丁麟",
  "wuyh32023@shanghaitech.edu.cn\ndinglin12022@shanghaitech.edu.cn",
  middle-text: "CS100 Recitation - Week 03",
  numbering: false,
)

#let codetxt(txt) = [#text(font: "Segoe UI", fill: blue)[#txt]]

#set text(size: 15pt)

= Overview

== 1. Warming up (15 min)
- Sign-in & Attendance.
- Review of last week.
- #text(gray)[\* Explain MinGW's artifacts for long double printing.]
- Review of Homework\#1.

== 2. Tools teaching -- Git with GitHub (15 min)
- Review of local operations: #codetxt([init, status, add, commit, diff, log]).
- Connecting your local Git with GitHub (using git-credential-helper).
- Version Control + #text(red)[Cloud Backup] + Multi-developer cooperation
- Remote Git operations: #codetxt([clone, push]).

== 3. Main Session \#1 (50 min)
- Learn control flow with GDB. (\<15 min)
- Pointers and arrays. (35 min)

== 4. Main Session \#2 (40 min)
- Preprocessor Directives.
- Introduction to macro basics.

== 5. Bonus Application (0 min)
#list[Today we will not spend time on bonus applications (due to the heavy workload).
  Interested students may help themselves with the materials in
  #link("https://github.com/Nagisaaaaaaaaa/CS100-2025-Spring-Recitations/tree/main/r3/supp")[
    #underline("the class Git repository")]
  or contact TAs for detailed instructions.]

== Supplementary Materials
- #link("https://docs.github.com/en/get-started/git-basics/caching-your-github-credentials-in-git")[#underline("Caching your GitHub credentials in Git | GitHub Official Documentation")]
- #link("https://stackoverflow.com/questions/188461/switch-statement-fall-through-should-it-be-allowed")[#underline("Should switch fall-through be allowed? | Stackoverflow")]
