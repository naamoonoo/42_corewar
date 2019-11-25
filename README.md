# Corewar

Corewar is a School 42 project. The purpose of this project is an implementation of the programming game **[“Core War”](https://www.corewars.org/)**. This game's goal is occupying more memory space by competeting with other players. Each champion has own scenario to win the game, and virtual machine takes player and schedule their play strategy. Their scenario is written in assembly code, [Redcode](https://en.wikibooks.org/wiki/Core_War/Redcode), which is needed to assemble to bytecode.

[corewar.en.pdf](/resources/corewar.en.pdf) is the task file. [epitech_version](/resources/corewar.epitech.pdf) has much detailed instruction.

## Project Structure

This project consists of five parts:

* Champion
* Assembler
* Disassembler (Bonus)
* Virtual Machine
* Visualizer (Bonus)

Assembler + Disassembler are modules of the program `asm`.

Virtual Machine + Visualizer are modules of the program `corewar`.

## How to clone?

you can use the following command:

```
git clone <repository url>
```

## Installation

Clone repository and then go into the created directory and run the following command:

```
make
```

## Usage

### `asm`

```
Usage: ./asm | [-d file.cor] | file.s
    champion.s   — from assemble to bytecode
    champion.cor — from bytecode to assemble
```

### `corewar`

```
usage: ./corewar [-v text | SDL][-dump nbr_cycles] [[-n number] champion1.cor] ...
    -v          : visualizer with text or SDL
    -dump <num> : Dump memory (32 octets per line) after <num> cycles and exit
    -n    <num> : Set <num> of the next player
    -champion   : lot's of champions has each scenario to occupy more memory with defeating each other
```

## Visualizer

Visualizer is made up of [SDL2](https://www.libsdl.org/download-2.0.php) graphic library

![Visualizer](/resources/corewar.gif)
