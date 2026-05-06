# push_swap

> Sort a stack of integers using a restricted instruction set — a 42 school project written in C.

`push_swap` reads a list of integers, then prints the shortest sequence of stack operations that sorts them in ascending order on stack `a`. It uses two stacks (`a` and `b`) and a limited set of operations: `pa`, `pb`, `ra`, `rb`, `rr`, `rra`, `rrb`, `rrr`, `sa`, `sb`, `ss`.

The bonus `checker` reads operations from stdin, applies them to the input stack, and prints `OK` if sorted or `KO` otherwise.

## Features

- Sorts up to 500 numbers well below the 42 evaluation thresholds (≤5 ops for 3, ≤12 for 5, ≤700 for 100, ≤5500 for 500).
- Hybrid algorithm:
  - **Small stacks (≤5):** brute-force optimal sequence.
  - **Big stacks:** chunk-based unstack → restack with rotation optimization that merges `ra`/`rb` into `rr` (and `rra`/`rrb` into `rrr`) when possible.
- Doubly-linked circular stack structure for O(1) head access and rotations.
- Bonus `checker` binary to validate any operation sequence.

## Requirements

- `cc` (gcc or clang) with `-Wall -Wextra -Werror` clean
- GNU `make`
- POSIX environment (Linux/macOS)

## Build

```bash
make           # builds ./push_swap
make bonus     # builds ./checker
make re        # full rebuild
make fclean    # remove binaries and objects
```

The bundled `libft` is built automatically.

## Usage

Pass integers as separate args or as a single quoted string:

```bash
./push_swap 3 1 4 1 5 9 2 6
./push_swap "3 1 4 1 5 9 2 6"
```

Output is one operation per line:

```
pb
ra
sa
...
```

### Pipe into the checker

```bash
ARG="3 1 4 1 5 9 2 6"
./push_swap $ARG | ./checker $ARG
# OK
```

### Helper scripts

```bash
./generate_random_list.sh 100      # print 100 unique shuffled ints
./run_push_swap.sh 100             # run push_swap on 100 random ints, count ops
./run_checker.sh 100               # run + validate via checker_linux
```

> [!NOTE]
> `run_checker.sh` invokes `./checker_linux`, the official 42 binary. Drop it next to the script, or replace with `./checker` (built via `make bonus`).

## Operations

| Op | Effect |
|----|--------|
| `sa` / `sb` / `ss` | swap top 2 of `a` / `b` / both |
| `pa` / `pb` | push top of the other stack onto `a` / `b` |
| `ra` / `rb` / `rr` | rotate `a` / `b` / both up |
| `rra` / `rrb` / `rrr` | rotate `a` / `b` / both down |

## Project layout

```
src/                  push_swap sources (sort, stack, op buffer, restack)
push_swap_checker/    bonus checker sources
includes/push_swap.h  shared header
libft/                bundled libft
tools/                debug helpers (stack_print, op_buffer_print)
Makefile              all / bonus / clean / fclean / re
```

## Algorithm sketch

1. **Parse + index** input into stack `a`; each value gets a sorted rank (`key`), so the target becomes `1..n`.
2. **Unstack:** push from `a` to `b` in chunks sized by rank ranges, choosing direction (`ra` vs `rra`, `rb` vs `rrb`) that minimizes moves.
3. **Restack:** pop from `b` back to `a`, inserting at the position closest to the top.
4. **Optimize:** post-process the operation buffer to fuse simultaneous `a`/`b` rotations into `rr` / `rrr`.

See `src/sort_big_stack.c`, `src/unstack.c`, `src/restack.c`, `src/restack_optimize.c`.
