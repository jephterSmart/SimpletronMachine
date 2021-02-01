# The SimpletronMachine

This is a simulation of a machine, the simpletron machine. This machine is simple in the sense that it has few instructions in its instruction set. 

For those of us who do not know what an instuction set is, let me give some preview. A computer normally, does not understand the language we speak, it on understand one's and zero's **(1's and 0's)**. These 1's and 0's represent high and low states or voltages. So to tell the computer to do things for us, we have to encode the information in these 1's and 0's. This what was normally done in the former days of computing with the help of punched card- card in which holes where punched to represent zero and unpunched places to represent one- then a mechanical scanner pass through this card and set the appropriate voltages, and the computer will do the things that we ask it to do. But, this was tedious in that if you punched the wrong place on the card, the computer will something else, hence program development was hard and tedious.

    
The instructions that make up our program that the computer can understand is what is known as the *instruction set* of the computer.  So, for one computer 1000 in binary - i.e., 1 and 0's - may mean print something on the screen while on another computer it may mean move data to the memory.

This simulated machine, therefore has it own instruction set that you use to tell it what to do in 1's and 0's. But to make the computation less easier, you will enter your instruction in hexadecimal, where each hexadecimal is equivalent to 4 bits(4 1's and 0's).

This machine has word length - the size of the instruction the processor can handle in one go - of 5, in hexDigit and can address 1000 memory locations (i.e., 0 - 999).The first two hex digits of the word are the computer instruction(or operator) and the 3 hex digits are the operand(memory) of the instruction.The word is a signed number. Instructions can only be positive, but data can be either positive or negative.
 
The following are the available instuctions this machine has:
  - Read/Write operation
    - 0x10(Read)  - Read from terminal to memory, i.e from stdin
    - 0x11(Write) - Write from memory to terminal, i.e to stdout
  - Load/ Store Operation
    - 0x20(Load)  - Load from memory into the accumalator register
    - 0x21(Store) - Store value in accumulator register into memory
 - Arithmetic operations
    - 0x30(Add)      - Add the value specified by the operand to the value in accumulator register and keep the sum in the register
    - 0x31(Subtract) - Subtract the value specified by the operand from the value in accumulator register and keep the difference in the register
    - 0x32(Divide)   - Divide the value specified by the accumulator register by the value specified by the operand and keep the difference in the register.
    - 0x33(Multiply) - Multiply the value specified by the accumulator register by the value specified by the operand and keep the result in the register.
    - 0x34(Modulus) -  Mod the value specified by the operand by the value specified by in the accumulator and keep the result in the register. i.e., registerValue % valueOfOperand
    - 0x35(Exponential)- Use the accumulator as the base and the value specified as the operand as the exponent and keep the result in the accumulator register.
 
 - Branching operations
    - 0x40(Branch)      - Branch to postion specified by its operand
    - 0x41(BranchNeg)   - Branch to postion specified by its operand if value in register is negative number
    - 0x42(BranchZero)  - Branch to postion specified by its operand if value in register is Zero.
    - 0x43(Halt)        - Halt program execution, i.e terminate the program.

### An example
An inp.txt is added to this repo to enable you run an instruction that loop ten times and find the sum of the numbers you entered. You can change the numbers from line 21 to have different result. This program will also display the sum in the output.
## More to come
I am going to be building a basic compiler for this machine, that will us to talk to this machine in a higher language rather than machine instuction in one's and zero's. 

## Thank You