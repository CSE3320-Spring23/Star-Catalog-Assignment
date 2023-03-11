# Star-Catalog-Assignment

Description

In this assignment you are provided code that serially calculate the average angular distance between 50,000 stars in the Tycho Star Catalogue.  This code, running serially, takes a significant amount of time to run.

## Requirements

1. Using a timing method of your choice get a baseline time for the unmodified code to compute the angular distances.
2. Multi-thread this application using pthreads.
3. Determine the optimal number of threads, 2, 4, 10, 25, 100, and 1000, for calculating the minimum, maximum, mean angular distance on your codespace. 
4. Add the command line parameter -t to allow the user to specify the number of threads to use.
5. The code must not deadlock or exhibit any race conditions.
6. The code must still calculate the same answer as the single threaded application.
7. You must include a report documenting your results. It must contain:
- A brief executive summary/ overview
- A description of your effort to include which libraries, if any, you used, and the reasons you chose your timing methods.
- Results in both graph and table form.
- A discussion of any anomalies you found in the resulting data.
- A conclusion explaining the optimal number of threads.
- The report must be in PDF form and submitted to your repository. Any other format will not be accepted.

## Administrative

This assignment must be coded in C. Any other language will result in 0 points. You 
programs will be compiled and graded on the course GitHub Codespace. Code that does not compile 
with the provided makefile will result in a 0.

Your program is to be turned in via the Feedback GitHub pull request. **Do not merge this pull request**.  Submission time is determined by 
the GitHub system time. You may push your code as often as you wish. Only your 
last submission will be graded. 

There are coding resources and working code you may use in the course GitHub repositories.  You are free to use any of that code in your program if needed. You may use no other outside code.

## Academic Integrity
This assignment must be 100% your own work. No code may be copied from friends, 
previous students, books, web pages, etc. All code submitted is automatically checked 
against a database of previous semester’s graded assignments, current student’s code 
and common web sources. By submitting your code on GitHub you are attesting that 
you have neither given nor received unauthorized assistance on this work. Code that 
is copied from an external source or used as inspiration, excluding the 
course github, will result in a 0 for the assignment and referral to 
the Office of Student Conduct.

