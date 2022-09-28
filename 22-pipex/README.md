# pipex

### pipe
- `create descriptor pair` for interprocess communication.
- allows `unidirectional` data flow.
- By convention, `first descriptor` connects to the `read end` of the pipe, the `second` connects to the `write end`.
```c
#include <unistd.h>

int	pipe(int fildes[2]);
```


## Subject
### Allowed function
```c
open, close, read, write,
malloc, free, `perror`,
`strerror`, `access`, `dup`, `dup2`,
`execve`, exit, `fork`, `pipe`,
`unlink`, `wait`, `waitpid`
```

### Mandatory
```c
/pipex file1 cmd1 cmd2 file2
```
- It must take 4 arguments:
	- file1 and file2 are `file names`.
	- cmd1 and cmd2 are `shell commands` with their parameters.
- example
```c
./pipex infile "ls -l" "wc -l" outfile

- Should behave like: < infile ls -l | wc -l > outfile
```
```c
./pipex infile "grep a1" "wc -w" outfile

- Should behave like: < infile grep a1 | wc -w > outfile
```

### Bonus
- Handle multiple pipes.
- example
```c
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2

- Should behave like: < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
```

- Support « and » when the first parameter is "here_doc".
- example
```c
./pipex here_doc LIMITER cmd cmd1 file

- Should behave like: cmd << LIMITER | cmd1 >> file
```
