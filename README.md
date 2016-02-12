# rshell program
First assignment of the rshell program
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

That's it for now, will note more when I find them.
