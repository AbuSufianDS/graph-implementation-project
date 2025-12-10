# Graph Implementation Project

## Overview
Implementation of directed graphs with adjacency list representation and topological sort algorithms.

## Files
- `graph.h` - Header file with declarations
- `graph.c` - Implementation of graph functions
- `main.c` - Test program with Figure 9.1 graph
- `Makefile` - Build automation

## Features
1. Adjacency list representation of directed graphs
2. Graph construction from adjacency matrix
3. Graph printing function (`printGraph()`)
4. Two topological sort implementations:
   - Using adjacency matrix
   - Using adjacency linked lists
5. Queue data structure for Kahn's algorithm

## Compilation & Execution
```bash
make        # Compile
./graph_program  # Run
make clean  # Clean build files