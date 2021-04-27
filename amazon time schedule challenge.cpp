#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Time {
    int hr;
    int min;
};

struct Slot {
    Time start;
    Time end;
    
//     Slot& operator< (Const Slot) {
    
//     }
};



// sort ascending order by beginning time
// void sort(vector<Slot>& v, int n) {
//     struct Slot curr;
//     int pos;

//     for (int i = 1; i < n; i++) {
//         curr = v[i]; 
//         pos = i;
        
//         while (pos > 0 && v[pos - 1].start.hr >= curr.start.hr) {
//             if (v[pos - 1].start.hr == curr.start.hr) {
//                 if (v[pos - 1].start.min >= curr.start.min) {
//                     v[pos] = v[pos - 1]; 
//                     pos--;
//                 }
//                 else
//                     break;
//             }
//             else {
//                 v[pos] = v[pos - 1]; 
//                 pos--;
//             }
//         }
        
//         if (pos != i)  
//             v[pos] = curr; 
//     }
//     // for (auto t : v) {
//     //     cout << t.start.hr << " " << t.start.min << " " << t.end.hr << " " << t.end.min << endl;
//     // }
        
// }

// insertion sort ascending order by start.hr > start.min > end.hr > end.min
void sort(vector<Slot>& v, int size) {
    int j;
    Slot curr;
    for (int i = 1; i < size; i++) {
        j = i;
        curr = v[i];
        if (!(curr.start.hr == v[j - 1].start.hr && curr.start.min == v[j - 1].start.min)) {
            while (j > 0 && curr.start.hr <= v[j - 1].start.hr) {   // while current start hr is <= previous
                if (v[j - 1].start.hr == curr.start.hr) {   // if hrs are equal, compare the mins
                    if (curr.start.min <= v[j - 1].start.min) {
                        v[j] = v[j - 1];
                        j--;
                    }
                    else 
                        break;
                }
                else {
                    v[j] = v[j - 1];
                    j--;
                }
            }
        }
        else {
            while (j > 0 && (curr.start.hr == v[j - 1].start.hr &&
                curr.start.min == v[j - 1].start.min) && curr.end.hr <= v[j - 1].end.hr) {
                if (v[j - 1].end.hr == curr.end.hr) {   // if hrs are equal, compare the mins
                    if (curr.end.min <= v[j - 1].end.min) {
                        v[j] = v[j - 1];
                        j--;
                    }
                    else
                        break;
                }
                else {
                    v[j] = v[j - 1];
                    j--;
                }


            }
        }
        if (j != i)
            v[j] = curr;

    }
    // for (auto t : v) {
    //     cout << t.start.hr << " " << t.start.min << " " << t.end.hr << " " << t.end.min << endl;
    // }
}

// Print available time slots in correct manner
void printTimeSlots(Time start, Time end) {
    string strStart, strEnd, strSlot;
    
    strStart = (start.hr < 10) ? "0" + to_string(start.hr) : to_string(start.hr);
    strStart += " ";
    strStart += (start.min < 10) ? "0" + to_string(start.min) : to_string(start.min);
    
    strEnd = (end.hr < 10) ? "0" + to_string(end.hr) : to_string(end.hr);
    strEnd += " ";
    strEnd += (end.min < 10) ? "0" + to_string(end.min) : to_string(end.min);
    
    strSlot = strStart + " " + strEnd;
    
    cout << strSlot << endl;
}

void difference(vector<Slot>& v, int K) {
    struct Time prev = {0,0};
    int diff;
    for (Slot s : v) {
        diff = (s.start.hr - prev.hr) * 60; // convert to minutes
        diff += s.start.min - prev.min;
        if (diff >= K) {
            printTimeSlots(prev, s.start);
        }
        prev = s.end;
    }
    
    // subtract last time slot from 24:00
    diff = (24 - prev.hr) * 60; // convert to minutes
    if (prev.hr == 0)   // fix the 24 - 0 case so diff doesnt equal 24 * 60
        diff = 0;
    diff += 0 - prev.min;
    if (diff >= K) {
        struct Time zero = {0,0};
        printTimeSlots(prev, zero);
    }
    return;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int M, K;
    cin >> M;
    cin >> K;
    vector<Slot> timeSlots; // store busy time slots
    
    for (int i = 0; i < M; i++) {
        // get start time
        struct Time temp1;
        cin >> temp1.hr;
        cin >> temp1.min;
        
        // get end time
        struct Time temp2;
        cin >> temp2.hr;
        cin >> temp2.min;
        
        // insert start/end time pair as a time slot into a vector
        struct Slot temp = {temp1, temp2};
        timeSlots.push_back(temp);
    }
    
    sort(timeSlots, M);
    difference(timeSlots, K);
    return 0;
}
