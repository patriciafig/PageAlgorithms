**CSCI 3453 – Operating Systems Concepts**

Programming Assignment 3 – Simulating Page Replacement Algorithms

Due Nov. 29, 2017 


# execute by: 

g++ -std=c++11 main.cpp 

# succesfully run the program by:

./main [frame-size] pg-reference.txt [outputfile.txt]


-----------------

# Goal of this Programming Assignment  

The primary goal of this lab assignment is to exercise four paging replacement algorithms and evaluate the effectiveness of each algorithm which affects the performance of memory management.

# Part I - Description  

Write a C or C++ program that simulates the operation of 4 page replacement algorithms used in a virtual memory management system:
> - First-in-First-out (FIFO) algorithm 
> - Least Recently Used (LRU) algorithm
> - Least Frequently Used (LFU) algorithm
> - Optimal algorithm

You will simulate each algorithm on the input data sets and report the performance of each. A description of each of these algorithms appears in Chapter 9 of our text.

-----------------

# Part II - Specifications

In this lab assignment, you will be calculating the page fault rate of the each different page replacement algorithms for the given page reference string for one process only. Your program should accept three arguments, which are the number of page frames of the physical memory, the names of an input file, and an output file. The input file contains the page reference string in the order of page request, and the output file stores the display events and the analysis results. You will run each algorithms four times, the first time with 128 page frames, the second time with 256 page frames, the third time with 512 page frames, and the 4th time with 1024 frames.

Sample usage is 
>prompt> memsim frame_size input.dat output.dat where

1. frame_size: no. of page frames in the primary memory
2. input.dat: refers to the input file and
3. output.dat: the name of the output file.


----------------- 

# Input Details  

> - **No. of frames:**
It is a single number that indicates the number of frames in the primary memory. So a number 128 will indicate that there are 128 frames of primary memory for this process. Your program will be tested with four different size of primary memory: 128, 256, 512 and 1024 frames.
> - **Input file:**
The file contains the memory page request sequence string for only one process. The each line represents a page number which is being accessed by the process. Assume a process can have up to 4096 pages, and the pages being numbered from 0-4095. This implies that no number in the reference stream will fall outside that range. There will be exactly 10,000 references in the page reference string. In other word, the input file has 10,000 lines. For your test, you may use my sample input file from the class web-site.


# Output Details  

The output file should print out the page fault rates for each of the four page replacement algorithms specified above based on the input page reference string at intervals of 2000 pages. Sample output format is shown below. For example, the column under 8000 lists the page fault rates for the first 8000 page references for all algorithms. Note that these are just sample values.

![enter image description here](https://lh3.googleusercontent.com/VA-2fZ2V99RZDE7eo-RVOlOOmp5k_K4-87TdaeAArbYnzcw9wqSU192AAAz449attrh7Ut8XBCGH=s625 "sample_output.png")






