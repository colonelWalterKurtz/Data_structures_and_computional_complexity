# Data structures and computional complexity

This repository was created for the college course needs. It features research on the time complexity of algorithms used in Computer Science.

C++ was chosen as the programming language, in which all presented algorithms were implement.

Compiled executible files are controlled by file with .ini extansion.

## Reasearch method

1. Compiled programs collects data from files.
1. The algorithm that is under analysis is being performed.
    - From each executed instance, the execution time is measured.
1. Measurements are saved to the csv extansion file.

## Time complexity of sorting algorithms

### Discussed Algorithms
| Algorithms [name] | Predicted time complexity [O] |
|:-----------------:|:-------------------:|
|    Bubble sort    |        $n^2$        |
|   Insertion sort  |        $n^2$        |
|     Quick sort    |       $n*logn$      |
|     Heap sort     |       $n*logn$      |
|   Counting sort   |        $n+k$        |

In the notebook Sorting Algorithms you will find measurements and diagrams of the written implementations of the algorithms.

![Bubble, Insertion, Quick sorts graph](/images/quick_bubble_insert.png)
![Count, Heap sorts graph](/images/count_heap.png)

[shortcut to ipynb notebook](https://github.com/colonelWalterKurtz/Data_structures_and_computional_complexity/tree/master/notebooks/sorting_algorithms.ipynb)

[shortcut to folder with implementations of sorting algorithms](https://github.com/colonelWalterKurtz/Data_structures_and_computional_complexity/tree/master/sorting_algorithms)

## Minimum spanning tree (MST)

As in the previous ones, program *mst* purpose is to measure the execution time of the algorithm. This time there is built a minimum spanning tree, based on Prim's algorithm. Values of edges are taken from file *macierz.txt* whose content is symmetric matrix created by matlab script *MakeGraph.m*.

## Dijkstra shortest path (heap)

## AVL and BST trees


## Compilation

All writen implementations of algorithms compile successfully by ***GCC*** compiler.

Example commands:

- *$ g++ main.cpp*
- compilation for the external use:
  - ***>g++ -static-libgcc -static-libstdc++ -static -lpthread -o sortowanie.exe main.cpp***
