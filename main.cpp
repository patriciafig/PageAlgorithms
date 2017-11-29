
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

using namespace std;

int fifo(const vector<int>& pageNumbers, int frameSize, vector<double>& pageFaultRates) {
    list<int> queue;
    int pageFaults = 0;

    pageFaultRates.clear();

    for (int i = 0, n = pageNumbers.size(); i < n; ++i) {
        if (find(queue.begin(), queue.end(), pageNumbers[i]) == queue.end()) {
            if (queue.size() < frameSize) {
                queue.push_front(pageNumbers[i]);
            } else {
                queue.pop_back();
                queue.push_front(pageNumbers[i]);
            }
            pageFaults++;
        }

        if (i > 0 && i % 2000 == 0) {
            pageFaultRates.push_back((pageFaults * 1.0) / i);
        }
    }

    return pageFaults;
}

int lru(const vector<int>& pageNumbers, int frameSize, vector<double>& pageFaultRates) {
    list<int> stak;
    int pageFaults = 0;

    pageFaultRates.clear();

    for (int i = 0, n = pageNumbers.size(); i < n; ++i) {
        list<int>::iterator it = find(stak.begin(), stak.end(), pageNumbers[i]);
        if (it == stak.end()) {
            if (stak.size() < frameSize) {
                stak.push_front(pageNumbers[i]);
            } else {
                stak.pop_back();
                stak.push_front(pageNumbers[i]);
            }
            pageFaults++;
        } else {
            stak.erase(it);
            stak.push_front(pageNumbers[i]);
        }

        if (i > 0 && i % 2000 == 0) {
            pageFaultRates.push_back((pageFaults * 1.0) / i);
        }
    }

    return pageFaults;
}

int findOptimalPage(vector<int>& frames, const vector<int>& pageNumbers, int index) {
    int res = 0, farthest = index;
    for (int i = 0, n = frames.size(); i < n; i++) {
        int pos;
        for (int j = index, m = pageNumbers.size(); j < m; j++) {
            if (frames[i] == pageNumbers[j]) {
                if (j > farthest) {
                    farthest = j;
                    res = i;
                    pos = j;
                }
                break;
            }
        }

        if (pos == pageNumbers.size())
            return i;
    }

    return res;
}

int optimal(const vector<int>& pageNumbers, int frameSize, vector<double>& pageFaultRates) {
    vector<int> frames;
    int pageFaults = 0;

    pageFaultRates.clear();

    for (int i = 0, n = pageNumbers.size(); i < n; ++i) {

        if (find(frames.begin(), frames.end(), pageNumbers[i]) != frames.end())
        {
            ++pageFaults;
            if (frames.size() < frameSize) {
                frames.push_back(pageNumbers[i]);
            } else {
                int index = findOptimalPage(frames, pageNumbers, i + 1);
                frames[index] = pageNumbers[i];
            }
        }


        if (i > 0 && i % 2000 == 0) {
            pageFaultRates.push_back((pageFaults * 1.0) / i);
        }
    }

    return pageFaults;
}

int lfu(const vector<int>& pageNumbers, int frameSize, vector<double>& pageFaultRates) {
    list<pair<int, int> > lst;
    int pageFaults = 0;

    pageFaultRates.clear();

    for (int i = 0, n = pageNumbers.size(); i < n; ++i) {

        bool found = false;
        for (list<pair<int, int> >::iterator it = lst.begin(); it != lst.end(); ++it) {
            if (it->first == pageNumbers[i]) {
                found = true;
                pair<int, int> temp = *it;
                ++temp.second;
                lst.erase(it);

                for (list<pair<int, int> >::iterator it1 = lst.begin(); it != lst.end(); ++it) {
                    if (temp.second >= it1->second) {
                        lst.insert(it1, temp);
                        break;
                    }
                }

                break;
            }
        }

        if (!found) {
            pageFaults++;

            if (lst.size() == frameSize) {
                lst.pop_back();
            }

            list<pair<int, int> >::iterator pos = lst.end();
            for (list<pair<int, int> >::iterator it = lst.begin(); it != lst.end(); ++it) {
                if (it->second == 1) {
                    pos = it;
                    break;
                }
            }

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

    return pageFaults;
}

int main(int argc, char* argv[]) {
    if (argv != 3) {
        cout << "Invalid number of arguments. " << "Please provide exactly 3 arguments which are the number"
                << " of page frames of the physical memory, the names of an" << " input file, and an output file."
                << endl;
        return 1;
    }

    int frameSize = atoi(argv[1]);
    int numFaults;
    vector<int> pageNumbers = readPageNumbers(argv[2]);
    vector<double> pageFaultRates;

    ofstream fout(argv[2]);
    fout << "\n===============================================\n";
    fout << "\tPage Replacement Algorithm Simulation (frame size = " << frameSize << " )" << "\n";
    fout << "===============================================\n";
    fout << "                         Page fault rates\n";
    fout << "Algorithm   Total page faults\t2000\t4000\t6000\t8000\t10000\n";
    fout << "--------------------------------------------------------------------------------------\n";
    fout << "FIFO        ";

    numFaults = fifo(pageNumbers, frameSize, pageFaultRates);
    cout << numFaults << "\t\t";
    for (int i = 0; i )

    return 0;
}
