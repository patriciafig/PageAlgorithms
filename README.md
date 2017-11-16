**CSCI 3453 – Operating Systems Concepts**

Programming Assignment 3 – Simulating Page Replacement Algorithms

Due Nov. 29, 2017 

-----------------

# Goal of this Programming Assignment  

The primary goal of this lab assignment is to exercise four paging replacement algorithms and evaluate the effectiveness of each algorithm which affects the performance of memory management.

-----------------
# Part I - Description  

Write a C or C++ program that simulates the operation of 4 page replacement algorithms used in a virtual memory management system:
> - First-in-First-out (FIFO) algorithm >
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


----------------- 

# Output Details  

