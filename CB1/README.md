# Setup
Tested on Ubuntu 18.04.

Compile binary without stack protection (not necessary if using the binary already in this folder)
`gcc buffer.c -o buffer -fno-stack-protector -z execstack -no-pie -fno-pie`

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
and we've noticed that it takes in input from stdin but does not seem to check the 
length of the input. Can you come up with an input that will force the program to print the flag?

# Hints

##Name of Vuln
Buffer Overflow

## Where
On line 13, the length of the input is not checked.

## Vague solution strategy
Find the right input to trigger a buffer overflow and call the `flag` function.

## First steps to the solution
Use `gdb` to disassemble the code and get the address of the function `flag`. You will need to pass this address to stdin at some offset which will overwrite `RBP`.
-Allow them to try and interpret the disassembled output and potentially make a mistake identifying the address. Correct mistaken address at this point.

# Solution
Use `gdb` to disassemble the code and get the address of the function `flag`. In this case, the
address is `0x004006c7`. 

Now we need to figure out the offset with which to pass this address so that we can overwrite `RBP`. We
can use a tool like `cyclic` to generate a pattern that does not repeat, and we can pass it as 
input to `gdb`. After running the program with this input, it should segfault. We can investigate 
that value at the top of the stack (pointed to by `RSP`) in `gdb` and use `cyclic -l <seg_fault_address>` 
to get the offset. For this binary, the offset is 56. 

We can then use the command `python2 -c 'print "A"*56 + "\xc7\x06\x40\x00"'` to force the service
to jump to the `flag` function and print out the flag.

This payload should work exactly the same on both the local and remote copy if properly configured
#