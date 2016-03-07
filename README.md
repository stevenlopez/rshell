# rshell program
First/second assignment of the rshell program
Create a program that replicates a terminal

Overall it acts very similar to a terminal

We start by outputting a $ in main which is a loop that is always true
you can either exit with exit or terminate the program, exit works fine
We get input from the user, take that string and pass it to our parse function.
In our parse function we parse it into smaller strings, these strings are done
when it reaches either empty space, ;, ||, or &&. After that it tosses the 
string into our test command. If the previous function was false then it returns without executing. goes back to parse, deletes the string and continues on. It
does this until it reaches an empty string then returns to main. 


Some of the flaws I noticed(edit later when I do proper testing)
Some of the error messages don't match up since I simply do perror("execvp")
I'm not familiar with all the functions; but I attempted to do test which gave
me false, doesn't do anything but makes the others false. It doesn't output an
execvp error even though it should.
Another flaw would be the input is limited(sort of). It allowed you up to 128
inputs for a single command which is more than enough. If there's a connector
then it'll reset, shouldn't have a problem. I made it just return and output
"input too long"
Another error even though it's minor is the #, I can mkdir "#" in a real 
terminal but this one would delete the #

SECOND PART: ERRORS
Fixed error for the first part.
1: returning the wrong value in some cases. I assumed it only returned 1 or 0 but it could return 2, fixed for this one

The comment with mkdir "#" still does the same thing
When the execute string has a space such as (ls ) then it gives an execvp error, treats it as size 2 rather than 1.
There was one case that failed for the precedence, can't remember which one, it was a bit complex.
When the input is "junk" such as (ls(ls)ls) the terminal makes sure that it's valid information then starts evaluating, the rshell just attempts to compute it, which it shouldn't. 
There may be other special cases that fail but haven't tested all of them.
