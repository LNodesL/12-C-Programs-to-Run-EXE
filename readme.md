# 12 Stub.c Files - Unique Run EXE Methods

This repo contains 12 total prototypes. Each program loads a local helloworld.exe, in a unique way. This is meant to help you better understand the many ways of running a program in Windows.

Each iteration (source file) is based on: CryptDemo

https://github.com/LNodesL/CryptDemo

A simple codebase to showcase a very primitive example of loading an exe & pushing to a tmp file and suspended process.

## Setup Example

Compile Hello World program:

```
gcc ./iterations/helloworld.cpp -static -o helloworld -mwindows
```

Compile the 12 prototypes:

```
gcc iterations/1.c -static -o ./dist/1
gcc iterations/2.c -static -o ./dist/2
gcc iterations/3.c -static -o ./dist/3
gcc iterations/4.c -static -o ./dist/4
gcc iterations/5.c -static -o ./dist/5
gcc iterations/6.c -static -o ./dist/6
gcc iterations/7.c -static -o ./dist/7
gcc iterations/8.c -static -o ./dist/8
gcc iterations/9.c -static -o ./dist/9
gcc iterations/10.c -static -o ./dist/10
gcc iterations/11.c -static -o ./dist/11
gcc iterations/12.c -static -o ./dist/12
```

Test the 12 programs:

```
dist/1
dist/2
dist/3
dist/4
dist/5
dist/6
dist/7
dist/8
dist/9
dist/10
dist/11
dist/12
```
