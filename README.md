*This project has been created as part of 42 curriculum by lmatthes.*

# get_next_line

## ℹ️ Description

`get_next_line` is a function that reads and returns **one line at a time** from a file descriptor, preserving unread data between function calls using a static variable. It reads efficiently by only fetching new data when needed and stops when a newline or EOF is reached.

The returned line includes the `\n` character when present.
If nothing is left to read or an error occurs, the function returns `NULL`.

## 🧠 Algorithm Overview

`get_next_line` returns **one complete line per call** by keeping unread data between calls.
The algorithm works as follows:
1. **Accumulate data into a static remainder** until a newline is found or `read()` returns 0.
This done in `fill_remainder()`, which reads in `BUFFER_SIZE` chunks and appends them to the remainder.
2. **Extract the line** (including the newline character, if present) using `extract_line()`.
This returns exactly the portion that should be output for this call.
3. **Trim the remainder** using `trim_remainder()`, removing the returned part and keeping only leftover data for the next call.
4. **Return the extracted line**, or `NULL` if no data is left.

This design avoids re-reading previously processed data, handles parial lines correctly, and ensures that each call returns exactly one line as required.

### Flowchart

``` ascii
get_next_line
    │
    ├── invalid fd or BUFFER_SIZE ≤ 0 → return NULL
    │
    ├── remainder = gnl_fill_remainder(fd, remainder)
    │
    ├── remainder == NULL → return NULL
    │
    ├── line = gnl_extract_line(remainder)
    │
    ├── line == NULL → free(remainder), remainder = NULL → return NULL
    │
    ├── remainder = gnl_trim_remainder(remainder)
    │
    └── return line
```

## ⚙️ Instructions

### Use it in a program

``` C
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(void)
{
	int		fd = open("file.txt", O_RDONLY);
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
}
```

### Compile & Run

``` bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o program
./program
```

Any BUFFER_SIZE is allowed.


## 🌐 Resources

- `man 2 open` & `man 2 read`
- [get_next_line | Guide](https://42-cursus.gitbook.io/guide/1-rank-01/get_next_line)
- [File descriptors (FD) | Guide](https://42-cursus.gitbook.io/guide/useful-tools/file-descriptors-fd)
- [comprendre get_next_line - YouTube](https://www.youtube.com/watch?v=-Mt2FdJjVno)
- [Static Variables in C](https://www.geeksforgeeks.org/c/static-variables-in-c/)

### AI Usage

AI assistance was used **only for learning support**, including:
- developing a study plan to structure my learning of get_next_line
- clarifying memory behavior and static variable usage
- improving naming consistency and documentation wording

**All code logic, structure, and implementation were written and understood by me.**
