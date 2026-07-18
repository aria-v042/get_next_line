*// work in progress ...*

*This project has been created as part of the 42 curriculum by frodrig2.*

# get_next_line

*Version: 14.3*

## Description

**get_next_line** implements a function for getting the next line from a file.
The `get_next_line()` function receives a *file descriptor* as a parameter, and
can be called inside a loop to read a file line-by-line. Each successful call
returns the next line (including `\n`) from the given file. When there's nothing
else to be read or if an error occurs, it returns `NULL`.

`get_next_line()` utilizes the `read()` system call to read from the given file
descriptor in fixed-sized chunks determined by the value of a `BUFFER_SIZE` macro (64
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
needed, **the allocated memory must be freed**.*

Example: using `get_next_line()` to get the next line from the file "example.txt"

```
fd = open("example.txt", 0_RDONLY);
line = get_next_line(fd);
// ...
free(line);
```

---

## Design choices and technical notes

### Buffer size

The default `BUFFER_SIZE` value of 64 bytes was chosen based on the following
criteria:

- **Power of 2:** Most efficient alignment with the kernel's
  page cache, the filesystem's block size and the pipe buffer size, which are
  almost always powers of 2. A buffer size that's divisible with those boundaries
  avoids partial-page reads and reduces the number of underlying I/O operations
  that the kernel has to stitch together.

- **Benchmarks:** Performance tests were run in order to study what buffer sizes
  were more memory efficient while handling various types of files. The
  number of allocations (and frees) decreases linearly the larger the buffer
  size is, while the total allocated memory is optimal when the buffer size is
  closest to the size of the lines in the file. After some investigation
  regarding line size averages across different types of files, I concluded that
  64 bytes was the best average value and set it as the default `BUFFER_SIZE`.

### Linked list for storing read() buffers

The buffers from `read()` system calls are stored in nodes of a linked list
structure. This approach minimizes the number of allocations and the amount of
memory allocated

> [TODO]

### Error management

> [TODO]

---

## Testing

> [TODO]

---

## Resources

### Reference material

> [TODO]

### Use of AI (LLMs)

An LLM was used as an aid for comparing the efficiency of two different
algorithms for the `trim_list()` function. However, I ended up disagreeing with
its recommendation of choosing practicality over optimization due to function
size constraints and ended up resolving the matter on my own.

The same model was also used to generate a file with adequate characteristics
(such as a combination of shorter and longer lines) for testing the performance
of the algorithms in terms of memory management for benchmarking purposes.

Finally, the LLM was employed to analyse the results of the benchmarks I ran and
generate a graphic that helped me decide on an optimal default `BUFFER_SIZE`
value.

> ...
