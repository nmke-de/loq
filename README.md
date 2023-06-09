# Loq

**Loq** is a simple diary program, allowing for one-line diary entries.

## But why?

To make keeping a diary easier.

## What about the name?

**LO**g **Q**uickly

## Dependencies

- libc
- Linux (or any OS which supports the same syscalls)
- Any submodule (fetch them with `git submodule update --init --remote` and update them with `git submodule update --remote`)

### Build Dependencies

- C Compiler
- make

## Build

Make sure to have all submodules installed.

Type `make`.

## Usage

```bash
# Add a new diary entry

loq This is my diary entry. Cool, right?

# List diary entries

loq

```
