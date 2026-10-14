# Student Gradebook (C++)

A console application that shows **arrays in action**. It manages student scores using 1D and 2D arrays, loops, searching and sorting.

## Where arrays are used

| Array | Type | Purpose |
|-------|------|---------|
| `names[MAX_STUDENTS]` | 1D `string` | Student names |
| `scores[MAX_STUDENTS][SUBJECTS]` | 2D `double` | Score of each student in each subject |
| `totals[]`, `averages[]` | 1D `double` | Computed results |
| `rankOrder[]` | 1D `int` | Student indices sorted by total (bubble sort) |
| `SUBJECT_NAMES[SUBJECTS]` | 1D `string` | Column headings |

## Features

- Add students and enter scores with input validation (0-100)
- View a formatted table of all students with total, average and grade
- Class statistics per subject (average, highest, lowest)
- Ranking by total score
- Search for a student by name
- Save a ranked report to `gradebook_report.txt`
- Load demo data to try it quickly

## Build and run

Requires a C++17 compiler (g++ or clang++).

```bash
git clone https://github.com/<your-username>/gradebook-cpp.git
cd gradebook-cpp
make
./gradebook
```

Without `make`:

```bash
g++ -std=c++17 -Wall -Wextra -O2 -o gradebook src/main.cpp
./gradebook
```

On Windows (MinGW), run `gradebook.exe` instead.

Tip: choose option **7** first to load demo data, then try options 2, 3, 4 and 6.

## Limits

The gradebook holds up to 50 students and 5 subjects (change `MAX_STUDENTS` and `SUBJECTS` at the top of `src/main.cpp`). Data is kept in memory only; the saved report is the only file output.

## Possible improvements

- Replace fixed arrays with `std::vector`
- Save and load the full gradebook from a file
- Add edit and delete student options
- Sort by name or by a chosen subject
