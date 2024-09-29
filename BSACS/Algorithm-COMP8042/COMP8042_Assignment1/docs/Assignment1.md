Assignment 1 - Book Reservation Management System
================================================================
---

In this assignment, we plan to develop a reservation management system using which we can keep track of the availability 
of the books in the library. The users can reserve the books to check out and return the books.
To accomplish this task, you will need to implement a `Stack`, and a `CircularQueue` as the required datastructures. 
Browsing `include` directory, you can find the initially necessary datastructures in `Utils.h`. 
As well, you can find the ADT designs of the two required datastructures in `Stack.h`, and `CircularQueue.h`. 
You need to implement the specified functions of each header file in a .cpp file with the exact same name (i.e. 
`Stack.cpp`, and `CircularQueue.cpp`) inside `src/` directory. 
Please do not modify the header files as you will not be submitting those files at the end.

Step-by-step guide:
-------------------
* **Important note**: for each module, after the implementation make sure its provided test cases run flawlessly.
  * running the test cases will give you the grade that you will get for that module. 
  * You are **not allowed** to use any STL data structures in your final submission except for `vector` and `list`.
  * You are allowed to use the `algorithm` library in the `.cpp` files you implement.

1. After the _Stack and Queue_ lecture, complete both implementations of `Stack` and `CircularQueue` and test them using 
   `tests/StackTests.h` and `tests/CircularQueueTests.h`.
2. Using the implemented modules implement the `BookReservation` class which can be used in the following scenario:

- Call `indexBookToDB` a number of times to store the books registered in the library inside `booksDB`.

- Call `enqueueReservation` a number of times to store all the reservation requests in the format of (target `patron` id,
  `book` ISBN) pairs. Since the library can only keep track of so many reservation requests, make sure to reject the 
  request for the cases that the library has already stored `maxPendingReservation` requests. 

- Calling `processReservation` will approve the first possible reservation request and move it to the stack of 
  `fulfilledReservations`. To implement this function, you need to return the first reservation which points to a book
  with an available copy in the library (from `booksDB` with `copies` value bigger than zero). Make sure you put
  the reservation requests for unavailable books to the back of the queue (in the same order you dequeued them) so they 
  can be accepted next time that the requested book became available. Raise an exception if none of the books in the 
  `pendingReservations` are available at the time of calling `processReservation`. Don't forget to reduce the number of 
  available books as soon as you approved a request!

  
## Submission and Grading:

As stated earlier, you are not supposed to change the content of the files inside `docs`, `include` and `tests` folders.
Therefore, zip out your `src` folder which is expected to contain `Stack.cpp`, `CircularQueue.cpp`, and
`BookReservation.cpp` and submit it. Your submitted `src` files must be able to be compiled and run with the provided
`CMakeLists.txt` file. If you compile and run the `main.cpp` file, you must be able to see the grade which will be 
submitted to https://learn.bcit.ca for this assignment. If you have done everything properly, you will see the following
output:
```
>> Stack:		        Total tests passed: 30 out of 30 (100%)
>> CircularQueue:		Total tests passed: 30 out of 30 (100%)
>> Book Reservation System: 	Total tests passed: 45 out of 45 (100%)
```

### Rubric:
As the feedback you will receive an output similar to the one posted above, with a difference; if your tests fail or the
submission crashes you will also receive the error message, so you can follow up on the error to improve your 
understanding of this assignment. Here is the breakdown of the grades for this assignment:

* Stack: 15 marks
* CircularQueue: 15 marks
* Book Reservation System: 10 marks
* Documentation inside the code for public functions: 4 marks
* Submission of extra files in addition to requested (`Stack.cpp`, `CircularQueue.cpp`, `BookReservation.cpp`) penalty: -2 marks

Your final grade for assignment 1 will therefore be calculated from 44 marks.

### Important Notes Regarding Your Submission:
* I will be compiling/testing your code on a Linux OS, so please do not put in any Windows-specific code in your submission.
  I want to emphasize on this point specially since some of you use VSCode in Windows, and it tends to have its own
  default settings which in the past has led to confusion and grade deductions.
  * Please **do make sure** your code
    compiles and runs without any specific dependency on Windows.
  * Please note, it does not matter if the code runs on your
    machine! it must run on my machine. I hope this reduces the need for me to recite this in a few future correspondences!
* Your submission has a maximum allowed time to run! if it does not finish running in 2 minutes, it is considered timed
  out and will receive an automatic grade of 0.
* Please make sure you submit the final source files and download and check your files after the final submission.
  I have had students who accidentally had forgotten to check the files, and it had turned out that they had submitted
  the original assignment files instead of the completed assignment. Please do check this, as once the grading is done
  and the assignment is graded 0, nothing can be done (if such a thing happened please do not email me, as I will give
  you the exact same answer as is written here).
* As mentioned earlier, I will throw away any files submitted in addition to the requested three `.cpp` files (and you
  will receive 2 marks penalty if anything extra is submitted), so please make sure you do not rely on changing the
  content of any file in `include` and `tests` directories as they will not be present in my side and your code will be
  broken and will receive a 0 for compilation errors.

Good luck and happy programming!