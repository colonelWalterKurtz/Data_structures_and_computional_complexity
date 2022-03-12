# Data structures and computional complexity
## Insertion Sort, Merge Sort, Bubble Sort and Quick Sort
C++ was chosen as the programming language in which the all presented algorithms are written.File 'liczby.txt' contains 1M random integer generated numbers. Program 'sorting_algorithms':
1.  gets first 10, 50, 100, 500, 1k, 2k, 5k, 10k, 20k, 50k, 100k, 200k, 300k, 500k, 700k, 900k and eventually 1M first numbers
2. performs the sort
3. writes the execution time to a file
    1. each time sprogram is executed, there are taken at least 10 sort attempts of each kind
    2. execution time is an avereage or a median of those attempts
    3. if a result significantly different from the others was found during the test, it is ignored
    4. there is provided an option to save sorted data, to a comparison