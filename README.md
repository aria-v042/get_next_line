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
fd = open("example.txt", O_RDONLY);
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

#### Invalid arguments

Invalid arguments -- a non-positive `BUFFER_SIZE`, `fd < 0`, and `fd >= FD_MAX`
in the bonus -- are checked at the start of `get_next_line()` and result in
an immediate `NULL` return.

#### read() errors

The function responsible for handling the `read()` syscall, `read_into_list()`,
distinguishes between three conditions on every `read()` call:

- **Data read successfully** (`bytes_read > 0`): the buffer is appended to the
  list via `lst_append()` and reading continues if no newline has been found
  yet.

- **End of file** (`bytes_read == 0`): frees the memory allocated to the buffer
  and returns `0` to signal a clean stop; any data already accumulated in the
  list is still extracted by `extract_line()` as a final line (without a
  trailing `\n`) before the list is freed.

- **Read error** (`bytes_read < 0`): returns `-1`, signaling `get_next_line()`
  to free the entire list via `lst_freeuntil` and return `NULL` to its caller;
  no partial data is returned on a read error, since it can't be trusted to
  represent a complete or correct line.

#### Memory allocation failures

`malloc()` failures are checked at every allocation site: the per-read buffer in
`read_into_list()`, the new list node in `lst_append()`, the extracted line in
`extract_line()`, and the remainder in `get_remainder()`. If a memory allocation
failure is caught, an error code (`-1`) or `NULL` is returned to
`get_next_line()`, signaling it to free the whole static list and return either
`NULL` or, if a line has already been successfully extracted (in case of a
`trim_list()` error), return the extracted line.

---

## Testing

For being able to compile and test `get_next_line()`, a small tester program
(`test.c`)
and a Makefile were written (available in the `.extras/` folder). The Makefile
can be used to compile `test_gnl` with a custom `BUFFER_SIZE` by defining its
value with `make [BUFFER_SIZE=<definition>]`. The tester uses `get_next_line()` to
get and display each line of a given file, or `file.txt` by default.

The following resources were also used:

- **Norm compliance** was checked with
  [norminette](https://github.com/42School/norminette).

- **Additional testing** was done with the help of
  [francinette](https://github.com/thecloudrazor/francinette), including its
  `--strict` mode, which performs fault injection (forcing `malloc` failures) to
  confirm that error paths free all allocated memory and don't crash or return
  corrupted data. This was particularly useful for catching a bug where a
  `malloc` failure partway through `trim_list` had been leaving the static list
  in an inconsistent state (see the Design Choices section on error management
  for how this is now handled).

- **Memory correctness** was checked with Valgrind's `--leak-check=full`
  across a range of test files (empty files, files with no trailing
  newline, single very long lines, many short lines), to
  confirm no leaks or invalid accesses occur regardless of `BUFFER_SIZE` or
  file shape.

- **Performance/memory benchmarking:** a small ***bash*** shell script
  (`benchmark.sh`) was written in order to easily generate benchmarks for
  `get_next_line()` with different types of files and buffer sizes. As described
  in the **Design Choices** section, it uses Valgrind to measure the number of
  alloc/free operations and total bytes allocated across a range of
  `BUFFER_SIZE` values and test files with varying line-length distributions,
  informing the choice of the default `BUFFER_SIZE`.

Edge cases specifically tested include: empty files, files consisting of a
single line with no trailing `\n`, files with consecutive empty lines, lines
longer than `BUFFER_SIZE`, `BUFFER_SIZE` values of `1` and other very small
sizes, reading from a closed or invalid file descriptor, and (for the bonus)
reading from multiple file descriptors in alternation to confirm each
maintains independent state.

---

## Resources

### Learning resources

- Oceano --- [get_next_line explained : develop a function that reads a file line by line](https://youtu.be/8E9siq7apUU) --- for understanding how linked lists could be used to implement a `get_next_line()` function.

### Use of AI

[Claude](https://claude.ai/) was used for comparing the efficiency of two
different algorithms I had implemented for the `trim_list()` function. However,
I ended up disagreeing with its recommendation of choosing practicality over
optimization due to function size constraints and ended up resolving the matter
on my own.

The same LLM was also used to generate a file (`gnl_test.txt`) with adequate
characteristics (such as a combination of shorter and longer lines) for testing
the performance of the algorithms in terms of memory management for benchmarking
purposes.
