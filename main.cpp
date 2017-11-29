// Created by Patricia on 11/16/17.
/*
 Page Replacing Algorithms
 Description: Simulation of Page Replacement Algorithms  to evaluate
 the performance of memory management
 */

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <utility>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iterator>
using namespace std;

/**
 * Implements FIFO Algorithm
 * This function returns the pageFaultRates in the passed argument
 * Returns the number of page faults
 */
int fifo(const vector<int>& pageNumbers, int frameSize, vector<double>& pageFaultRates) {
    list<int> lst;
    int pageFaults = 0;
    
    pageFaultRates.clear();
    
    for (int i = 0, n = pageNumbers.size(); i < n; ++i) {
        // List is maintained in first in first out order, i.e.
        // newest element is at top and oldest at the last.
        
        // If element is not found in the list, i.e in case of MISS,
        // If list is not full then add an element at top of list
        if (find(lst.begin(), lst.end(), pageNumbers[i]) == lst.end()) {
            
            // If list is not full
            if (lst.size() < frameSize) {
                // Add an element at the end
                lst.push_front(pageNumbers[i]);
            } else {
                // Remove oldest element
                lst.pop_back();
                
                // Add a new element at top
                lst.push_front(pageNumbers[i]);
            }
            pageFaults++;
        }
        
        if (i > 0 && i % 2000 == 0) {
            pageFaultRates.push_back((pageFaults * 1.0) / i);
        }
    }
    
    pageFaultRates.push_back((pageFaults * 1.0) / pageNumbers.size());
    
    return pageFaults;
}

/**
 * Implements LRU Algorithm
 * This function returns the pageFaultRates in the passed argument
 * Returns the number of page faults
 */
int lru(const vector<int>& pageNumbers, int frameSize, vector<double>& pageFaultRates) {
    list<int> stak;
    int pageFaults = 0;
    
    pageFaultRates.clear();
    
    for (int i = 0, n = pageNumbers.size(); i < n; ++i) {
        // Stack is maintained in lru order i.e. top most element
        // is most recently used and last element is least recently used
        
        list<int>::iterator it = find(stak.begin(), stak.end(), pageNumbers[i]);
        
        // In case of MISS
        if (it == stak.end()) {
            
            // Add the element at the top if list is not full
            if (stak.size() < frameSize) {
                stak.push_front(pageNumbers[i]);
            } else {
                
                // If list is full then remove the last element and add a new element at top
                stak.pop_back();
                stak.push_front(pageNumbers[i]);
            }
            pageFaults++;
        } else {
            
            // In case of HIT, move the element to the top of stack.
            // So remove it from it's current position and reinsert it at top
            stak.erase(it);
            stak.push_front(pageNumbers[i]);
        }
        
        if (i > 0 && i % 2000 == 0) {
            pageFaultRates.push_back((pageFaults * 1.0) / i);
        }
    }
    
    pageFaultRates.push_back((pageFaults * 1.0) / pageNumbers.size());
    
    return pageFaults;
}

int optimal(const vector<int>& pageNumbers, int frameSize, vector<double>& pageFaultRates) {
    vector<int> frames;
    vector<int> temp(frameSize, -1);
    int pageFaults = 0;
    
    pageFaultRates.clear();
    
    for (int i = 0, n = pageNumbers.size(); i < n; ++i) {
        bool found = false;
        
        for (int j = 0; j < frames.size(); ++j) {
            if (frames[j] == pageNumbers[i]) {
                found = true;
                break;
            }
        }
        
        
        // In case of MISS
        if (!found) {
            
            // Add the element at the end if size of frames is less than frameSize
            if (frames.size() < frameSize) {
                frames.push_back(pageNumbers[i]);
            } else {
                
                // Otherwise find the best page number to remove
                
                int pos;
                bool flag = false;
                
                // Store the index of next occurrence of each page number in temp array
                for (int j = 0; j < frameSize; ++j) {
                    temp[j] = -1;
                    
                    for (int k = i + 1; k < pageNumbers.size(); ++k) {
                        if (frames[j] == pageNumbers[k]) {
                            temp[j] = k;
                            break;
                        }
                    }
                }
                
                // If there is a page number which is not referenced again, then remove it
                for (int j = 0; j < frameSize; ++j) {
                    if (temp[j] == -1) {
                        pos = j;
                        flag = true;
                        break;
                    }
                }
                
                // If all pages are referenced again in future, then find the
                // page which is referenced later
                if (!flag) {
                    
                    int max = temp[0];
                    pos = 0;
                    
                    for (int j = 1; j < frameSize; ++j) {
                        if (temp[j] > max) {
                            max = temp[j];
                            pos = j;
                        }
                    }
                }
                
                frames[pos] = pageNumbers[i];
            }
            pageFaults++;
        }
        
        if (i > 0 && i % 2000 == 0) {
            pageFaultRates.push_back((pageFaults * 1.0) / i);
        }
    }
    pageFaultRates.push_back((pageFaults * 1.0) / pageNumbers.size());
    
    return pageFaults;
}

/**
 * Implements LFU Algorithm
 * This function returns the pageFaultRates in the passed argument
 * Returns the number of page faults
 */
int lfu(const vector<int>& pageNumbers, int frameSize, vector<double>& pageFaultRates) {
    
    // In this list is maintained in lfu order, so
    // topmost element is most frequently used.
    // The frequency of each element
    // is stored along with it.
    
    // pair.first is the value of the element and pair.second is its frequency
    
    list<pair<int, int> > lst;
    int pageFaults = 0;
    
    pageFaultRates.clear();
    
    for (int i = 0, n = pageNumbers.size(); i < n; ++i) {
        
        bool found = false;
        
        // Find the element in the list
        for (list<pair<int, int> >::iterator it = lst.begin(); it != lst.end(); ++it) {
            // In case of HIT, move the element to
            // the correct position so that elements above it will have highest frequency
            // and also this element maintains the FIFO order with the elements
            // of same frequency
            if (it->first == pageNumbers[i]) {
                found = true;
                pair<int, int> temp = *it;
                ++temp.second;
                lst.erase(it);
                
                // Find the position and insert it
                for (list<pair<int, int> >::iterator it1 = lst.begin(); it != lst.end(); ++it) {
                    if (temp.second >= it1->second) {
                        lst.insert(it1, temp);
                        break;
                    }
                }
                
                break;
            }
        }
        
        // In case of MISS
        if (!found) {
            pageFaults++;
            
            // Remove the last element from the list
            if (lst.size() == frameSize) {
                lst.pop_back();
            }
            
            // Find the position to add the element
            list<pair<int, int> >::iterator pos = lst.end();
            for (list<pair<int, int> >::iterator it = lst.begin(); it != lst.end(); ++it) {
                if (it->second == 1) {
                    pos = it;
                    break;
                }
            }
            
            // insert the element at desired position
            if (pos != lst.end()) {
                lst.insert(pos, make_pair(pageNumbers[i], 1));
            } else {
                lst.push_back(make_pair(pageNumbers[i], 1));
            }
        }
        
        if (i > 0 && i % 2000 == 0) {
            pageFaultRates.push_back((pageFaults * 1.0) / i);
        }
    }
    
    pageFaultRates.push_back((pageFaults * 1.0) / pageNumbers.size());
    
    return pageFaults;
}

vector<int> readPageNumbers(const char* inputFile) {
    ifstream fin(inputFile);
    vector<int> pageNumbers;
    
    // Read all the lines of file into a vector
    copy(istream_iterator<int>(fin), istream_iterator<int>(), back_inserter(pageNumbers));
    return pageNumbers;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cout << "Invalid number of arguments. " << "Please provide exactly 3 arguments which are the number"
        << " of page frames of the physical memory, the names of an" << " input file, and an output file."
        << endl;
        return 1;
    }
    
    int frameSize = atoi(argv[1]);
    int numFaults;
    vector<int> pageNumbers = readPageNumbers(argv[2]);
    vector<double> pageFaultRates;
    
    ofstream fout(argv[3]);
    fout << "\n===============================================\n";
    fout << "\tPage Replacement Algorithm Simulation (frame size = " << frameSize << " )" << "\n";
    fout << "===============================================\n";
    fout << "                         Page fault rates\n";
    fout << "Algorithm   Total page faults\t2000\t4000\t6000\t8000\t10000\n";
    fout << "--------------------------------------------------------------------------------------";
    
    numFaults = fifo(pageNumbers, frameSize, pageFaultRates);
    fout << "\nFIFO     \t\t\t" << numFaults << "\t\t";
    for (int i = 0; i < pageFaultRates.size(); ++i) {
        fout << setprecision(3) << pageFaultRates[i] << "\t";
    }
    
    numFaults = lru(pageNumbers, frameSize, pageFaultRates);
    fout << "\nLRU      \t\t\t" << numFaults << "\t\t";
    for (int i = 0; i < pageFaultRates.size(); ++i) {
        fout << setprecision(3) << pageFaultRates[i] << "\t";
    }
    
    numFaults = lfu(pageNumbers, frameSize, pageFaultRates);
    fout << "\nLFU      \t\t\t" << numFaults << "\t\t";
    for (int i = 0; i < pageFaultRates.size(); ++i) {
        fout << setprecision(3) << pageFaultRates[i] << "\t";
    }
    
    
    numFaults = optimal(pageNumbers, frameSize, pageFaultRates);
    fout << "\nOptimal  \t\t\t" << numFaults << "\t\t";
    for (int i = 0; i < pageFaultRates.size(); ++i) {
        fout << setprecision(3) << pageFaultRates[i] << "\t";
    }
    
    return 0;
}
