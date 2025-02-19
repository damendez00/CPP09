# CPP09

This repository contains three C++ exercises demonstrating various programming concepts and algorithms.

## Exercises

### ex00: Bitcoin Exchange
A program that processes Bitcoin transactions based on historical data.

**Features:**
- Reads Bitcoin exchange rates from a CSV database
- Processes input files with date|value pairs
- Validates input format and values
- Calculates Bitcoin values based on historical rates

**Usage:**
```bash
make -C ex00
./ex00/btc input.txt
```

### ex01: RPN Calculator
A Reverse Polish Notation calculator implementation.

**Features:**
- Evaluates mathematical expressions in RPN format
- Supports basic arithmetic operations (+, -, *, /)
- Validates input format
- Uses stack-based calculation

**Usage:**
```bash
make -C ex01
./ex01/RPN "3 4 + 2 *"
```

### ex02: PmergeMe
A sorting algorithm comparison between vector and list containers.

**Features:**
- Implements merge-insertion sort algorithm
- Compares performance between std::vector and std::list
- Measures and displays execution time
- Handles large input sequences

**Usage:**
```bash
make -C ex02
./ex02/PmergeMe 3 5 9 1 2 8 7
```

## Compilation
Each exercise has its own Makefile. To compile:
```bash
make -C ex00
make -C ex01
make -C ex02
```

## Requirements
- C++ compiler (g++ or clang++)
- Make
- C++ Standard Library

## Author
damendez
