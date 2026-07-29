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

- **Divisibility into page/block size:** Powers of 2 divide evenly into the
  kernel's page size and typical filesystem block size (commonly 4096 bytes),
  meaning buffer-sized chunks never straddle a page boundary with an awkward
  remainder. In practice this has little measurable effect on this program's
  performance, since the kernel's readahead logic determines actual disk I/O
  independently of the buffer size passed to `read()` and glibc's `malloc`
  doesn't allocate power-of-2 sizes any more efficiently than other sizes.
  This choice is mostly one of conceptual tidiness.

- **Memory usage:** Benchmarks were run with the help of Valgrind to study what
  buffer sizes minimized memory usage when handling various types of files
  (measured by total bytes allocated, not peak memory usage). A smaller
  `BUFFER_SIZE` requires more `read()` calls and more buffer/node allocations to
  span a single line, while a larger `BUFFER_SIZE` risks allocating chunks much
  bigger than the actual line length, especially for files with shorter lines.
  In summary, the number of allocations/frees decreases as buffer size
  increases, while the total memory allocated is minimized when the buffer size
  is closest to the actual line length in the file. After running benchmarks for
  different types of test files, a `BUFFER_SIZE` of 64 bytes was found to sit
  close to the point where total memory usage was lowest. Minimizing memory
  usage was prioritized as a metric over minimizing the number of syscalls and
  memory allocations due to the 42 subject's recommendation to read as little as
  possible each time `get_next_line()` is called.

### Linked list for storing read() buffers

The buffers from each `read()` syscall are stored in nodes of a linked list
structure, which persists across calls to `get_next_line()` via a `static
t_list *` pointer. This approach minimizes the number of allocations and the
amount of memory allocated by never copying or merging buffer contents until a
line is actually ready to be returned: each `read()` call's buffer is stored
as-is in its own node (via `lst_append`), and nodes accumulate until a `\n` is
found in one of them (checked via `find_newline`).

Once a newline is found, `extract_line` walks the list exactly once, copying
only the bytes belonging to the completed line into a single exact-sized buffer.
Any data past the newline (belonging to the *next* line) is preserved by
`trim_list`, which allocates a new exact-sized buffer for the remainder
(calculated via `get_remainder`) and discards the now-fully-consumed nodes via
`lst_freeuntil`. This means that the list holds as many nodes as `read()`
calls were needed to reach the next newline and that no node's content is ever
recopied more than once.

#### Implementing bonus requirements

The ability to handle multiple file descriptors was implemented using a `static
t_list *` array of size `FD_MAX`, a macro set as 1024, to allow keeping multiple
linked lists indexed directly by their respective file descriptor. Each `fd` has
its own assigned slot in the array (`buffer_list[fd]`), so the partial read
state for one file descriptor is never affected by reads on another. `fd` values
are bounds-checked against `FD_MAX` before use to avoid writing outside the
array. Using a single static array for storing the multiple lists also satisfies
the bonus requirement of using only one static variable.

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
