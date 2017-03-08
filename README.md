# ArraySort-Using-Threads

This code takes an array as input from the user from the command line, and displays it after sorting it using threads.
It divides the array into two halves and sends each half into a thread to get it sorted, and merges the sorted halves using a 3rd thread.
  
  >> gcc multisort.c -pthread -o arraySort

  >> ./arraySort < array elements separated by spaces >
