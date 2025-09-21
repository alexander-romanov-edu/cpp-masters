# string twine

This project implements string_twine class design for performant string concatenation.

## Install dependencies

To install all needed dependencies run [nix](https://nixos.org/download/)

```sh
nix develop
```

## Build

```sh
meson setup build
meson compile -C build
```

## Benchmarks

```
❯ build/benchmarks/stwine-bench
2025-09-21T14:01:19+03:00
Running build/benchmarks/stwine-bench
Run on (12 X 4400 MHz CPU s)
CPU Caches:
  L1 Data 48 KiB (x6)
  L1 Instruction 32 KiB (x6)
  L2 Unified 1280 KiB (x6)
  L3 Unified 12288 KiB (x1)
Load Average: 0.38, 0.46, 0.40
------------------------------------------------------
Benchmark            Time             CPU   Iterations
------------------------------------------------------
add_bench          307 ns          307 ns      2317938
twine_bench        242 ns          241 ns      2921574
```
