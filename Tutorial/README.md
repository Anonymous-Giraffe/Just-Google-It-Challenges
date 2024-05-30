This problem is based on the example found [here](https://samsclass.info/127/proj/p7-heap0.htm).

# Setup
Tested on Ubuntu 18.04.

Compile binary (or use the one in this folder):
`gcc tutorial.c`

Add `flag.txt` file containing the flag in the same folder where the program will be run.

#Description
We've come across a service written located at `<ip> <port>` and would like to force it to 
print out the flag. We've uncovered the [binary](https://link) and the [source code](https://link), 
and we've noticed that it is looking for a passphrase. Can you figure out what it is and print the flag?

# Interviewer script for walking through the Tutorial
<Let them read the challenge description and download and open the source code>

For this tutorial and the actual challenge you will solve today, you will be able to work on the development environment to build your exploit. You will be able to confirm it is working locally before transitioning to attempting the solution at the remote location. This will become more clear later in the problem, so lets dive in.

This is a relatively straightforward tutorial problem that I will walk you through to give you a chance to familiarize yourself with the development environment, the available tools, and the remote/local problem structures. For both this tutorial challenge and the actual problem challenge you will solve today, your goal is to either run the flag function or access a flag variable. In this case, we can see a flag function defined at the top of the file on line 7.

If we do a quick scan of the rest of the code, we see we are fortunate enough that the flag function is actually called on line 36 if we pass what seems to be a comparison between our input and a key value on line 35. Now, this problem is simple enough that we can reconstruct what the key is just by reading the source code; we see it's a combination of the variables almost and final on lines 32 and 33. And almost is a combination of pass and temp on lines 23 and 24. But that is more difficult than it needs to be. For both this problem and the actual challenge problem you will solve today, I recomend using GDB to dynamically analyze aspects of the problem. So, in this case, why don't you open this binary in GDB, set a breakpoint at line 35, and then print out the value of the key variable so we can see what it is? You can do this by navigating to the tutorial folder on the development environment, or by running GDB on your own machine if you prefer.

<Let them attempt to do all these steps on their own, but don't let them get stuck unnecessarily; this is the tutorial, after all>
<After printing out the value of the key variable>

Right, so now that we have the value of the key, let's try providing that as input to the program and see if we can get the flag function to run.

<Let them run the program and see the flag function gets executed. The fake flag.txt file with the value "notflag{Just a placeholder}" should be printed to the screen since they are running the local copy>

So, you see, the flag that got printed isn't exactly in the format we want, right? That is because we developed and ran our "exploit" on the local environment which does not have access to the true flag value. If you go back and reference the challenge description on the CTF website, this is where the remote IP and Port come into play, as I briefly mentioned earlier. In order to properly solve the challenges, your "exploit" needs to work both locally and remotely. This abstraction is to prevent you from modifying the source code or simply opening the flag file without utilizing the exploit. Effectively, the local/remote problem structure forces you to solve the challenge in the way we want.

That being said, let's use Netcat, a command line tool, to connect to the IP and port and provide it our input.

<Walk them through Netcat syntax and connect to the remote instance. They should provide the key value and get the actual flag value back.>

Great! Now, before we continue to try any of the actual challenge problems, do you have any specific questions about anything we've covered so far? This can include clarification about that local/remote problem structure, using any of the commands in the Reference CTF sheet, or any other aspect of the interview.

<If they have additional questions about any commands, walk them through using the command in the context of the tutorial problem.>


Great! If you don't have any other questions, let me tell you what problem you're going to solve today and then I'll start the one hour timer.

