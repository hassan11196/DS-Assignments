# Data Structures Assignments

## Assignment 1
### Problem 1- Way-Out from a Maze
This problem uses DynamicSafe2DArray as discussed during the lecture. A maze is an object of
DynamicSafe2DArray of char type. The content of the array can be any character {- (path), *
(block), s (start), e (end), ! (visited)}.
The input maze may contain only one-path and you need to implement a recursive path finding
approach that enumerate all cell of the array that are on the path in order of traverse from start s to
end e. Here is an example of a maze.

    * s * * * * * * * *
    * - - * * * * * * *
    * * - - * * * * * *
    * * * - * * * * * *
    * * * - - - - * * *
    * * * * * * - * - e
    * * * * * * - * - *
    * * * * * * - * - *
    * * * * * * - - - *
    * * * * * * * * * *

All you need to develop a recursive routine for finding path, the search is only allowed to follow
{Left, Right, Up and Down} from any location. The output for this problem is complete path from
starting to end location. The validation of input cases required as start and end location must be at
the boundary of the maze. There may be one or no path for all valid input cases.


### Problem 2 – Brute Force Sequence matching
In bioinformatics, a sequence alignment is a way of arranging the sequences of DNA, RNA, or
protein to identify regions of similarity that may be a consequence of functional, structural, or
evolutionary relationships between the sequences. In this problem there are two sequences of
variable length given to you, you can keep them in simple DynamicSafeArray. The brute force
sequence matching algorithm finds the maximum sequence of match from the two given sequence.
Obviously this maximum match would not be larger than the smaller sequence. The sequence
matching may disallow characters in either sequence that already appears in the earlier match, but
missing from the next possible match. For example, consider the sequence S1 and S2

    S1: ACTTGTTACTGTTACCT

    S2: ACTGTACTGTACT

    Matched: ACT*GT*ACTGT*AC*T

Here the matched sequence is greater than the length of the smallest sequence as we are
disallowing match of a character that earlier matched. In the above example there are four such
instances hence the match sequence is of length |s2| + 4.

### Problem 3 – KQUERY

You are given an array of numbers, there can be n numbers where n is between (1 <= n <= 30000).
Each number is between (1 <= ai <= 109). You are also given “t” queries of the form qt ( i, j, k)
where ( 1 <= i <= j <=n) for each query you need to return the number of elements greater than k
in the sub-sequence ai, ai+1, ....., aj you need to process all t queries in the same fashion.


## Assignment 2
### Problem 1- Optimal Way-Out from a Maze

You are now well aware of how to get a solution rom a maze. The content of the array can be
any character {1 (path), 0 (block), s (start), e (end), ! (visited)}.
The input maze may contain multiple-paths and you need to implement a recursive path finding
approach that enumerate all cell of the array that are on the unique path in order of traverse from
start s to end e. You need to enumerate all paths. Here is an example of a maze.

    s 1 1 1 1 1 0
    1 0 0 1 1 0 1
    1 0 0 0 1 0 1
    1 1 1 e 1 1 1

There are three possible paths:

Path#1= {(0,0),(0,1),(0,2),(0,3),(1,3),(2,3),(3,3)} Cost=7

Path#2= {(0,0),(1,0),(2,0),(3,0),(3,1),(4,1),(4,2),(4,3),(3,3)} Cost=9

Path#3= {(0,0),(1,0),(2,0),(3,0),(4,0),(4,1),(4,2),(4,3),(3,3)} Cost=9

All you need to develop a recursive routine for finding path, the search is only allowed to follow
{Left, Right, Up and Down} from any location. The output for this problem is complete path from
starting to end location. The validation of input cases required as start and end location must be at
the boundary of the maze. There can be several paths for all valid input cases. You need to
enumerate all paths from starting to each cell followed till the end. The cost of a path is total
number of cell traveled. Hence the shortest path or optimal path is the minimum length path.

### Problem 2- Infix to Postfix conversion and evaluation

Arithmetic expressions are made of operators (+, -, /, *, ^, etc.) and operands (either numbers,
variables or, recursively, smaller arithmetic expressions). The expressions can be written in a
variety of notations. In this problem, you will focus on two standard arithmetic expression
notations: infix and postfix. In Infix expression, operators are written in-between their operands.
This is the usual way we write expressions, for example x+y. Similarly, Postfix notation (also
known as "Reverse Polish notation"): x y + Operators are written after their operands. There is a
general algorithm that convert an infix expression to postfix using stack (data structure).

### Problem 3- Simulation of Queuing Systems

The Shop-n-Carry (SC) is a big chain of departmental stores. The SC would like to improve its
customer services. There has been a complained for some period that the waiting time to avail
Point-of-Sale terminal services is unbearable for some areas in stores. SC is planning to improve
the services by means of installing more POS terminals to those stores, which are in heavy use,
and customers have to wait for making payments. You have been hired, as a consultant by the SC
president to determine whether this idea is feasible or not. The management has decided that if the
average waiting time of a user at a POS is greater than 3 minutes to get their services. They will
install one more POS terminal machine. It is provided that the arrival rate of POS customer is
anytime within the opening hours and the average service time is between 3 to 8 minutes. The POS
is operational 18 X 7. Your job is to run a simulation program for SC POS for 18 hours, and
calculate the average waiting time for customers on hourly basis. Identify the busy hours. Use the
least count of the clock as discrete unit of minutes. Put the entire statistic in the output file which
is as follows:
- Number of customers
- Average waiting time (for each hour – in a separate line)
- Average Customers (for each hour – in a separate line)
- POS utilization time (Average Service Time)

## Assignment 3

### Problem 1- Determining compatible set of intervals for media channel.

One of the main application of Binary Search Trees are for handling a dynamically changing
datasets. This can be very efficient choice for deciding many compatible issues. One of the media
channel is looking to decide a non-overlapping intervals for their transmission. Each program from
the channel is comprises of a start time, duration and commercial time for the program. For an
example an Interval I (start_time, duration, ctime) = (2, 6, 3) implies that the program starts at 2
and can be finish by 11 with commercial time included for on airing the show. The program
managers collect all programs information is a single file. There are 5 program managers and each
provides program information in a file. All you need to maintain a combine data structures that
maintain a non-overlapping compatible set of programs for the channel and maintain a separate
file for all those program that are conflicting in time. 

For example, consider the files from the 2 programs managers:

Program Manager #1 

    5
    2 3 2
    54 5 2
    9 10 1
    26 10 4
    65 5 4

Program Manager #2

    3
    16 4 4
    7 5 3
    3 3 1

The channel does not want a silent period of transmission and select a program that is close to reduce the silent time.

Compatible Programs 

    2 3 2
    7 5 3
    16 4 4
    26 10 4
    54 5 2
    65 5 4

Conflicting programs

    3 3 1
    9 10 1

You need to maintain a BST for maintaining a set of compatible programs. The searching and
finding a conflict in program can be perform in log n time.