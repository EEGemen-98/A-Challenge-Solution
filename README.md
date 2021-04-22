# A-Challenge-Solution
My solution in C++ to a hard coding challenge problem from the Amazon Hackerrank contest (after contest ended). 

Link to problem: https://www.hackerrank.com/contests/amazon/challenges/meeting-schedules/problem



> _I recommend reading problem description before my thought process_

My thought process to solve this problem was to find a way to efficiently store the time slots, design an algorithm that can compute the available time slots, 
and a function that prints the available time slots in the required manner. 

_Storage_

For storage, I chose to create two structs called Time (stores hours and minutes) and Slot (stores a start and finish Time). This way I can neatly keep track 
of the time data that is being read in via stdin. Each line read is one Slot, containing two Times. After each Slot is initialized, it is stored in a vector 
containing all of the busy time slots in the input order.

_Algorithm_

The algorithm I came up with to compute available time slots was to sort the timeSlots vector in ascending order in terms of starting time. I decided to use selection sort
for mainly for simplicity reasons. The sorting algorithm sorts by start Time hour values, and if they are the same then it compares minutes. Once the vector is sorted, 
my algorithm will subtract adjacent Times in order. The first subtraction is always going to be time 00:00 with the start Time in the first Slot (index 0). The following
subtractions will be the start Time of the current Slot minus the end Time of the previous Slot until it reaches the last slot. The last slot end Time will be subtracted
from 24:00. If the end Time is 00:00 the difference is overwritten to 0, since numerically 24 and 0 are different but in terms of time they are the same.

_Results_

Finally, I have a helper printing function that is called everytime the difference function finds an available time slot that satisfies the K minutes condition. This
will print the correct time slots in the correct order as described below.

_Needed improvements_

Currently my solution passes the tests below and 6/9 tests. From testing I figured out that my solution does not handle cases where different slots have same start times
but different end times. My sorting algorithm is not able to sort by end time quite yet, I tried to find an easy solution but it's going to take more work than I thought.
I need to have logic for the case where if the start times are identical (first check hour then minute values) then I will need to compare their end times (first hour then
minute).

My solution does however handle cases where start time hours are same but minutes aren't. It also handles cases where there is not a single available time slot.



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
