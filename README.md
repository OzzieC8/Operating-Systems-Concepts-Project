# Operating-Systems-Concepts-Project
This project uses three seperate files to demonstrate basic process management functions within applications 
and permission inheritance works between parent and child processes.

## Author information
- Author: Ozzie Cano
- Email: ozziec86@csu.fullerton.edu

## Project instructions and information
[project_Spring2024.pdf](https://github.com/OzzieC8/Operating-Systems-Concepts-Project/files/15050332/project_Spring2024.pdf)

## Setup

### Prerequisites

- Linux
- IDE
- Terminal
- g++ compiler
- C++

### Instructions

- Clone or download this repository.
- Compile using:
  
      g++ -o part1Shell part1Shell.cpp
      g++ -o part2Parallel part2Parallel.cpp
      g++ -o part2Serial part2Serial.cpp
  
- Execute using:

      ./part1Shell
      ./part2Parallel
      ./part2Serial

## Finding the execution times for parallel and serial fetchers

- After compilation use the command for both fetchers:

      time ./part2Parallel
      time ./part2Serial

  ### Execution times for both fetchers:

  #### Parallel Fetcher

      real    0m0.545s

      user    0m0.099s

      sys     0m0.014s

  #### Serial Fetcher

      real    0m2.652s

      user    0m0.094s

      sys     0m0.010s

## Questions
1. In the output of time, what is the difference between real, user, and sys times?
    
    A: Real time is the total elapsed time from start to finsih. User time is the total amount of time the CPU
       spent time in user mode. Sys time is the total amount of time the CPU spent executing system calls in
       the kernel.

2. Which is longer: user time or sys time? Use your knowledge to explain why.
    
    A: User time is typically longer because the computing of running the code could be longer than sys time. 
       In this case of the project the user time is faster but the sys time could be faster depending on the 
       system and if there is a problem wrong with it.


3. When fetching all of the locations in the file, which fetcher finishes faster? Why do you think that is?
    
    A: The parallel fetcher finishes the fastest because of the real time being significantly slower for the 
       serial fetcher. I think this could be because of the amount of processes being made is more intensive
       rather than the parallel fetcher being less intensive.

4. Suppose one of the fetcher children crashes. Will this affect other children? Explain. 
   What is your conclusion regarding the benefits or disadvantages of isolating each fetch task within a different process?
    
    A: If one of the fetcher children crashes it wont effect the other children as it's isolated. The benefits of 
       isolating is that the program still works if one crashes. This shows it's somewhat realiability being isolated
       because the program will work when it is executed.
