*This project has been created as part of 42 curriculum by lmatthes*

# get_next_line

## 📌 Description

`get_next_line` is a function that reads and returns **one line at a time** from a file descriptor, preserving unread data between function calls using a static variable. It reads efficiently by only fetching new data when needed and stops when a newline or EOF is reached.

The returned line includes the `\n` character when present.
If nothing is left to read or an error occurs, the function returns `NULL`.

## ⚙️ Instructions

### Compile

``` bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

Any BUFFER_SIZE is allowed.

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

## 🔗 Resources

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

## 🧠 Algorithm Overview

1. A static `remainder` stores the leftover text between calls.
2. Read into a buffer until a newline is found or EOF is reached.
3. Extract the next line from `remainder`.
4. Remove the extracted part and keep the rest for the next call.
5. Return the line, or `NULL` when there is nothing left to read.

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
