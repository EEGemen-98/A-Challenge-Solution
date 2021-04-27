# A-Challenge-Solution
My solution in C++ to a hard coding challenge problem from the Amazon Hackerrank contest (after contest ended). The problem starts with only a blank main method, no given
methods to fill out. I am continuing to enhance my solution for my own learning benefit. Some parts of my code that are not well commented are still being improved.

Link to problem: https://www.hackerrank.com/contests/amazon/challenges/meeting-schedules/problem



> _I recommend reading problem description at the bottom of the page or link above before my thought process_

My thought process to solve this problem was to find a way to efficiently store the time slots, design an algorithm that can compute the available time slots, 
and a function that prints the available time slots in the required manner. 

_Storage_

For storage, I chose to create two structs called Time (stores hours and minutes) and Slot (stores a start and finish Time). This way I can neatly keep track 
of the time data that is being read in via stdin. Each line read is one Slot, containing two Times. After each Slot is initialized, it is stored in a vector 
containing all of the busy time slots in the input order.

_Algorithm_

The algorithm I came up with to compute available time slots was to sort the timeSlots vector in ascending order in terms of starting time. Since I wasn't actually competing
but rather solving the problem for fun, I decided to save some time and work off a sorting algorithm I found online (https://github.com/edwardmartins/Sorting-Algorithms ). I decided to use insertion sort mainly for simplicity reasons. I had to modify and create new logic to fit the sorting algorithm to this problem. The sorting algorithm sorts by start Time hour values, and if they are the same then it compares minutes. Once the vector is sorted, my algorithm will subtract adjacent Times in order. The first subtraction is always going to be time 00:00 from the start Time in the first Slot (index 0). The following subtractions will be the start Time of the current Slot minus the end Time of the previous Slot until it reaches the last slot. The last slot end Time will be subtracted from 24:00. If the end Time is 00:00 the difference is overwritten to 0, since numerically 24 and 0 are different but in terms of time they are the same.

_Results_

Finally, I have a helper printing function that is called everytime the difference function finds an available time slot that satisfies the K minutes condition. This
will print the correct time slots in the correct order as described below.

_Needed improvements_

Check change log below for updated status about this solution. The first uploaded version passed 6/9 tests however it lacked the ability to sort inputs with slots that have identical start times. The current version I'm working on has a (better?) sorting function that can sort by end times if start times are identical however it has a bug that causes infinite loops that needs to be fixed.

My solution does however handle cases where start time hours are same but minutes aren't. It also handles cases where there is not a single available time slot.

_Runtime & Space Complexity_

The practical runtime of my solution is O(n^2) due to the insertion sort algorithm. Insertion sort is not ideal for a large input. The space complexity is O(n) because of the vector that stores the given time slots. I made sure to pass by reference to other functions so that this vector (which may be very large) is not copied.

![image](https://user-images.githubusercontent.com/54004471/115653091-61fa4680-a2e3-11eb-84e7-9389abd30040.png)

## Change Log:
(4/26/21)
- Implemented logic to sort function to sort by end time if and only if the start times are identical
- Program can now properly sort and extract available times with an input containing duplicated start times

TO DO:
- The new sorting function is causing infinite loops, some tests are timing out for unknown reason
- simplify code using operator overloading

## Problem Description:
Given M busy-time slots of N people, You need to print all the available time slots when all the N people can schedule a meeting for a duration of K minutes.

Event time will be of form HH MM ( where 0 <= HH <= 23 and 0 <= MM <= 59 ), K will be in the form minutes.

**Input Format:**

M K [ M number of busy time slots , K is the duration in minutes ]

Followed by M lines with 4 numbers on each line.

Each line will be of form StartHH StartMM EndHH EndMM  [ Example 9Am-11Am time slot will be given as 9 00 11 00 ]

An event time slot is of form [Start Time, End Time ) . Which means it inclusive at start time but doesn’t include the end time. 

So an event of form 10 00  11 00 => implies that the meeting start at 10:00 and ends at 11:00, so another meeting can start at 11:00.


**Sample Input:**

5 120

16 00 17 00

10 30 14 30

20 45 22 15

10 00 13 15

09 00 11 00

**Sample Output:**

00 00 09 00

17 00 20 45

**Sample Input:**

8 60

08 00 10 15

22 00 23 15

17 00 19 00

07 00 09 45

09 00 13 00

16 00 17 45

12 00 13 30

11 30 12 30

**Sample Output:**

00 00 07 00

13 30 16 00

19 00 22 00

**Constraints :**

1 <= M <= 100

**Note: **24 00 has to be presented as 00 00.
