/*
 * This is a simulation of a machine, the simpletron machine. 
 * This machine is simple in the sense that it has few instructions in its instruction set.
 * This machine has word length of 4, in decimal and can address MEMORY_SIZE memory location 
 * (i.e., 0 - MEMORY_SIZE -1).
 * The first two hex digits of the word are the computer instructions(or operator) 
 * and the last MEMORY_SIZE - 2 hex digits are the operand(memory) of the instruction.
 * The word is a signed number. Instructions can only be positive, 
 * but data can be either positive or negative.
 * 
 * The following are the available instuctions this machine has:
 * - Read/Write operation
 *    - 10(Read)  - Read from terminal to memory, i.e from stdin
 *    - 11(Write) - Write from memory to terminal, i.e to stdout
 * - Load/ Store Operation
 *    - 20(Load)  - Load from memory into the accumalator register
 *    - 21(Store) - Store value in accumulator register into memory
 * - Arithmetic operations
 *    - 30(Add)      - Add the value specified by the operand to the value in accumulator register
 *                     and keep the sum in the register
 *    - 31(Subtract) - Subtract the value specified by the operand from the value in accumulator register
 *                     and keep the difference in the register
 *    - 32(Divide)   - Divide the value specified by the accumulator register by the value specified by the
 *                     operand and keep the difference in the register.
 *    - 33(Multiply) - Multiply the value specified by the accumulator register by the value specified by the
 *                     operand and keep the result in the register.
 *    - 34(Modulus) -  Mod the value specified by the operand by the value specified by in the accumulator
 *                      and keep the result in the register. i.e., registerValue % valueOfOperand
 *    - 35(Exponential)- Use the accumulator as the base and the value specified as the operand as the exponent
 *                        and keep the result in the accumulator register.
 * 
 * - Branching operations
 *    - 40(Branch)      - Branch to postion specified by its operand
 *    - 41(BranchNeg)   - Branch to postion specified by its operand if value in register is negative number
 *    - 42(BranchZero)  - Branch to postion specified by its operand if value in register is Zero.
 *    - 43(Halt)        - Halt program execution, i.e terminate the program.
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MEMORY_SIZE 1000

//global varaible
typedef unsigned int uint;



//Function prototypes
void comp_dump(double accumulator, uint instructionCounter, int instructionRegister, long long int memory[]);


int main(void){
    printf("\n*** Welcome to Simpletron! ***\n"
    "*** Please enter your program one instruction ***\n"
    "*** (or data word) at a time. I will type the ***\n"
    "*** location number and a question mark (?).  ***\n"
    "*** You then type the word for that location. ***\n"
    "*** Type the sentinel -99999 to stop entering ***\n"
    "*** your program. ***\n");
    long long int memory[MEMORY_SIZE] = {0LL};
    const long long int MaxLimit = 0xfffdLL; // if arithmetic result in value greater or -ve value lesser than its -ve.
    uint instructionCounter = 0; // This gives us the number of the instruction we are executing.
    int instructionRegister = 0; // This what holds the current instruction to be executed.
    int operationCode = 0; //This is the first 2 digits
    int operand = 0; //This is the last 2 digits.
    double accumulatorRegister = 0.0;

    int *temp = malloc(sizeof(int));
    
    for(uint i =0; i<MEMORY_SIZE; i++){
        printf("\nmemory Address -> %02d ?  ",i);
        scanf(" %X",temp);
        if(*temp == -0xfffff) {
            printf("\n*** Program loading completed ***\n"  
            "*** Program execution begins  ***\n\n");
            break;
        }
            
        else 
            memory[i] = *temp; 
    }
    free(temp);
    temp = NULL;
    
    
    instructionCounter = 0;
    int strCount = 0;
    char character = 0; // Use to store each character that is to be added to memory
   for(; ; ){
       instructionRegister = memory[instructionCounter];
       operationCode = (instructionRegister) / 4096; // since 3 hex digit for address, 16 * 16 * 16
       operand = instructionRegister % 4096;
       instructionCounter++;
         
       switch(operationCode){
           case 0x10: // For reading from terminal, i.e., keyboard
                 
                printf("\n ?  ");
                scanf("%d",&memory[operand]);
                 
                break;
           case 0x11: // For writing to terminal, i.e screen
                printf("\n\n %d", memory[operand]);
               
                break;
           case 0x12: //For Reading String from terminal
                printf("\nNumber Of character in String + \"\\0\" ?  ");
                scanf(" %d",&strCount);
                memory[operand] = (unsigned char)strCount;
                memory[operand] = (uint)memory[operand] << 8; // Push 1 byte to store new Byte.
                printf("\nNow Enter String ?: ");
                for(uint j = 0; j < strCount-1; j++){
                    scanf(" %c",&character);
                    if(j == 0) 
                        (uint)memory[operand] | character;
                    else if(j % 2 == 0){
                        (uint)memory[operand] | character;

                        // For conditions  where it is next to last.
                        if(j == strCount -2){
                        operand++;
                        memory[operand] = '\0';
                        memory[operand] = (uint)memory[operand] << 8;  
                        }
                    }
                    else{
                        operand++;
                        memory[operand] = character;
                        memory[operand] = (uint)memory[operand] << 8;

                        // For conditions  where it is next to last.
                        if(j == strCount -2){
                              (uint)memory[operand] | '\0';
                        }
                    }
                }
                break;
           case 0x20: // load into register from memory
                accumulatorRegister = memory[operand];
                
                break;
           case 0x21: // store from register into memory
                memory[operand] = accumulatorRegister;
                break;
           case 0x30: //add to register
                
                accumulatorRegister += memory[operand];
                if(accumulatorRegister > MaxLimit){
                    printf("\n***Memory Overflow has occurred ***\n"
                    "*** Terminating Program ***\n");
                    exit(2);
                }
                break;
           case 0x31: // subtract from register
                
                accumulatorRegister -= (double)memory[operand];
                
                
                 if((int)accumulatorRegister < -MaxLimit){
                    printf("\n***Memory Overflow has occurred ***\n"
                    "*** Terminating Program ***\n");
                    exit(2);
                }
                break;
           case 0x32: // Divide register by value in operand
                if(memory[operand] == 0){
                     printf("\n*** Divide by Zero Error ***\n"
                    "*** Terminating program ***\n");
                    exit(2);
                }
                if(accumulatorRegister < -MaxLimit){
                    printf("\n***Memory Overflow has occurred ***\n"
                    "*** Terminating Program ***\n");
                    exit(2);
                }
                accumulatorRegister = accumulatorRegister / memory[operand];
                break;
           case 0x33: //Multiply by what is in register 
                accumulatorRegister *= memory[operand];
                if(accumulatorRegister < -MaxLimit || accumulatorRegister > MaxLimit){
                    printf("\n***Memory Overflow has occurred ***\n"
                    "*** Terminating Program ***\n");
                    exit(2);
                }
                break;
           case 0x34: //Modulus on what is on register 
                    if((uint)memory[operand] == 0){
                     printf("\n*** Divide by Zero Error ***\n"
                    "*** Terminating program ***\n");
                    exit(2);
                }
                accumulatorRegister = (int)accumulatorRegister % (int)memory[operand];
                break;
          case 0x35: accumulatorRegister = pow(accumulatorRegister,memory[operand]);
                 if(accumulatorRegister < -MaxLimit || accumulatorRegister > MaxLimit){
                    printf("\n***Memory Overflow has occurred ***\n"
                    "*** Terminating Program ***\n");
                    exit(2);
                }
                break;
          case 0x40: // Branch to operand
                instructionCounter = operand;
                break;
          case 0x41: // Branch if Accumulator register is negative.
                if(accumulatorRegister < 0)
                    instructionCounter = operand;
                break;
          case 0x42: // Branch if Accumulator register is Zero.
            if(accumulatorRegister == 0)
                 instructionCounter = operand;
            break;
          case 0x43: // Halt program, i.e., finish program execution
                printf("\n*** Simpletron execution terminated ***\n");
                
                comp_dump( accumulatorRegister, instructionCounter, instructionRegister, memory);
                exit(EXIT_SUCCESS);
                break;
         case 0x50: printf("\n"); break;
       } // End Switch statement.
    

   }// End For loop
    return 0;
}

void comp_dump(double accumulator, uint instructionCounter, int instructionRegister, long long int memory[]){
    printf("\nREGISTERS:\n");
    printf("accumulator              %+06d"
    "\ninstructionCounter          %03u"
    "\ninstructionRegister     %#05X"
    "\noperationCode              %#02X"
    "\noperand                    %#03X", 
    (int)accumulator,instructionCounter,instructionRegister, instructionRegister / 4096 , instructionRegister % 4096);
    printf("\n\n\nMEMORY\n");
    printf("     ");
    for(uint i = 0; i < 12; i++){
        printf("%7d  ",i); // Print top row
    }
    for(uint i = 0; i < 84; i++){
        printf("\n%2d   ",i * 12);
        for(uint j = 0; j<12; j++){
            if((j+(i * 12)) > MEMORY_SIZE -1) break;
           printf("%+07d  ",memory[j+ (i * 12)]); 
        }
    }// print memory element
    printf("\n\n");
}