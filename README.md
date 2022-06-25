# Data structures and computional complexity

Polish version [https://www.overleaf.com/read/xvxzgzjjhmpm](https://www.overleaf.com/read/xvxzgzjjhmpm)

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

The complexity of the Prim's algorithm depends on the implementation of the queue. However, inside the algorithm we go through all $n$ elements of the queue and update $n$ neighbors each time. This means that the algorithm itself has a complexity of $n^2$.

[shortcut to ipynb notebook](https://github.com/colonelWalterKurtz/Data_structures_and_computional_complexity/tree/master/notebooks/prim_algo.ipynb)

[shortcut to folder with implementations of sorting algorithms](https://github.com/colonelWalterKurtz/Data_structures_and_computional_complexity/tree/master/mst_tree)

## Dijkstra shortest path (heap)

Dijkstra's algorithm finds the shortest paths from a certain vertex to all the paths reached from it. It is an example of a greedy algorithm. The weights of the graph must be non-negative.
The implementation code of Dijkstra's algorithm in this case is array-based. It is not optimal because the search for the minimum value in the loop is linear $O(n)$ by which the algorithm eventually achieves a quadratic complexity of $O(n^2)$.

[shortcut to ipynb notebook](https://github.com/colonelWalterKurtz/Data_structures_and_computional_complexity/tree/master/notebooks/dijkstra_shortest_path.ipynb)

[shortcut to folder with implementations of sorting algorithms](https://github.com/colonelWalterKurtz/Data_structures_and_computional_complexity/tree/master/shortest_path)

## Building AVL tree

An AVL tree, also called an admissible tree, is a balanced binary search tree (BST) in which the heights of the left and right subtrees of each node differ by at most one. AVL trees are often compared to red-black trees because they allow the same operations (addition, deletion, and element search) to be performed with equal pessimistic time complexity $O(log n)$. Building this type of tree will therefore be done with time complexity $O(nlogn)$.

[shortcut to ipynb notebook](https://github.com/colonelWalterKurtz/Data_structures_and_computional_complexity/tree/master/notebooks/avl_tree.ipynb)

[shortcut to folder with implementations of sorting algorithms](https://github.com/colonelWalterKurtz/Data_structures_and_computional_complexity/tree/master/avl_trees)

## Compilation

All writen implementations of algorithms compile successfully by ***GCC*** compiler.

Example commands:

- *$ g++ main.cpp*
- compilation for the external use:
  - ***>g++ -static-libgcc -static-libstdc++ -static -lpthread -o sortowanie.exe main.cpp***
