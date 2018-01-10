# Project 2

## Team

| Team Member        | Git Username | B-Number  |
|--------------------|--------------|-----------|
| Yongheng Li        | yonhenli     | B00000000 |
| Victoria Fabrizio  | vfabrizio    | B00000000 |

## Contributions

In this subsection, write one to two brief paragraphs for each team member describing their contributions to the project. You may find the following resources useful:

- **Yongheng Li:** Most of the code was written on his computer and committed from there. Both Victoria and Yongheng worked on this code together but did it on Yongheng's computer. This made it easier to prevent merge issues. It also helped us write efficient code as a team. Worked specifically on fixing read_txt() to function when the fields were out of order. Worked together on write_txt(), write_bin(), and read_bin(). Specifically worked on list_students() (lines 634-644), list_courses() (lines 646-717), enroll_student() (lines 496-523)
- **Victoria Fabrizio:** Made major fixes once code was writen. Worked specifically on add_course() (lines 547-576), remove_course() (lines 579-609), remove_student() (lines 527-544), and delete_all() (lines 611-631). Wrote the Makefile and added the error_string data. Tested the corner cases with Yongheng to remove bugs. Wrote a lot for read and write_bin()

## Tasks

- [X] **Read and understand the instructions** in [instructions.pdf](instructions.pdf).
- [X] Complete the Makefile to produce `libparser.so`, `driver`, and any other targets necessary to your project. You will be graded on this Makefile.
- [X] Create and complete `parser.c` such that it implements all functions declared in `parser.h`.
- [X] Build `libparser.so` and verify that when used with `driver` it produces outputs identical to when `libparser.a` is used with static-driver.
- [X] Complete the Contributions subsection in this README.
