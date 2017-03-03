# ArraySort-Using-Threads

This code takes an int[] as input from the user, and displays it after sorting it using threads.
It divides the array into halves and sends each half into a thread to get sorted, and merges the sorted halves using a 3rd thread.
  
  >> gcc multisort.c -pthread

  >> ./a.out
