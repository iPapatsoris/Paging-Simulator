# Paging-Simulator
Virtual memory & page replacement simulation in Operating Systems, as a project for the course.
Receive page requests by 2 processes concurrently and perform memory management using either LRU or Working Set methods for page replacement.

## Usage
**```./psim -a <algorithm> -f <frames> -q <quantum> -m <max> -w <window> ```**
* **``` <algorithm>```** : Either *lru* or *ws*  
* **``` <frames>```**: Number of frames in memory
* **``` <quantum>```**: Number of page requests from each process before switching
* **``` <max>```**: Max number of requests for each process (receive a portion of the input)
* **``` <window>```**: Working set window size

Arguments can be provided in any order. -m is optional and -w is only needed when using the Working Set method. Receive input from *.trace* files.

## toDo
 - disk read
 - working set restoration: page fault? yes
 - -m receives from both or in total?
