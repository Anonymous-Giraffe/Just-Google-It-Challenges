This problem is based on the example found [here](https://samsclass.info/127/proj/p7-heap0.htm).

# Setup
Tested on Ubuntu 18.04.

Compile binary (or use the one in this folder):
`gcc source.c -w -g -no-pie -z execstack -o binary -m32`

Disable ASLR on server:
```
# disable in current session
echo 0 | sudo tee /proc/sys/kernel/randomize_va_space

# make change permanent (across reboots)
echo "kernel.randomize_va_space = 0" > /etc/sysctl.d/01-disable-aslr.conf
```

Add `flag.txt` file containing the flag in the same folder where the program will be run.

# Description
We've come across a service written located at `<ip> <port>` and would like to force it to 
print out the flag. We've uncovered the [binary](https://link) and the [source code](https://link), 
and we've noticed that it takes in input from stdin and insecurely checks the length before copying into a buffer. Can you come up with an input that will force the program to print the flag?

# Hints

## Name of Vuln
Integer overflow into a Buffer overflow

## Where
Integer overflow is on lines 18 and 19, Buffer Overflow is on line 25

## Vague solution strategy
We can use an integer overflow to get past the check on line 19 to then utilize the buffer overflow to overwrite the return address for validate_passwd.

## First steps to the solution
First Determine what size ranges allow you to execute the else code on line 23, you could try this by systematically increasing the userinput size until you get past the length check when you shouldn't. Determine the address of flag using dissas and find where user input is stored.

# Solution
Determine that input length is checked on line 19 once but then not before copying into buffer.

Determine that casting length of input to a unsigned char will overflow the char if input is too large (larger than 255 as unsigned char is 0-255)

With that information determine target payload length is 259-263 bytes long.

Next disas flag to get address of flag function for payload: 0x08049256

Use cyclic to generate string long enough to pass input check and overflow buffer: cyclic 260

run program in gdb with input and see where segfault takes you: 0x61616168 Either use cyclic -l 

OR

Use info registers to show address of ESP. 

Print out some info at ESP to see where above segfault is stored.

Count out that the return address is stored with an offset of 28

Build payload with correct offset and additional bytes to reach target length of 259-263
python2 -c 'print "A"*28 + "\x56\x92\x04\x08" + "A"*230'
```
This payload should work on both the local and remote copies of the program if properly configured.
