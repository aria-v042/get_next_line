*// work in progress ...*

# get_next_line

*Version: 14.3*

## Description

**get_next_line** implements a function for getting the next line from a file.
The `get_next_line()` function receives a *file descriptor* as a parameter, and
can be called inside a loop to read a file line-by-line. Each successful call
returns the next line (including `\n`) from the given file. When there's nothing
else to be read or if an error occurs, it returns `NULL`.

`get_next_line()` utilizes the `read()` system call to read from the given file
descriptor in fixed-sized chunks determined by the value of a `BUFFER_SIZE` macro (32
bytes by default), which can be redefined at compilation time.

The bonus part of the project requires implementing the ability to alternate
reading from multiple files without losing track of the reading state of each
file descriptor while using only one static variable.

---

## Instructions

### Compilation

Redefining `BUFFER_SIZE` at compilation time:

```
cc <flags> [-D BUFFER_SIZE=<definition>] <source files>
```

### Usage

**IMPORTANT:** *When the value returned by `get_next_line()` is no longer
needed, the allocated memory must be freed.*

Example: using `get_next_line()` to get the next line from a file

```
fd = open("example.txt", 0_RDONLY);
line = get_next_line(fd);
...
free(line);
```

---

## Design choices and technical notes

### Draft

The `BUFFER_SIZE` default value of *32 bytes* was chosen ... //todo

> The `BUFFER_SIZE` default value of *8192 bytes* was chosen based on the value of
the `BUFSIZ` constant from the ***stdio.h*** library.

> [TODO]

---

## Testing

> [TODO]

---

## Resources

### Reference material

> [TODO]

### Use of AI

An LLM was used as a tool for comparing the efficiency of different algorithms I had implemented for the 'trim_list()' function. However, I ended up disagreeingwith its advice, which recommended choosing practicality over optimization due to function size constraints, and ended up resolving the matter on my own.
