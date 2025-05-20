#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

/*I Alexis Fenderson here certify that this programming assignment reflects my own work,
without the use of any external individuals (other than course/department staff ), generative-AI,
or any other forbidden resources. I understand/accept the consequences of cheating as outlined
in the course syllabus
 */

 /*
 Define a 64 element character array with the same name as the register (no need to include the % symbol). 
 For example, one of the register arrays is called rax. The character arrays store ’0’ or ’1’.
 Please initialize the contents of all registers to ’0’ for each entry.
 
 Assume that element ’0’ contains the least significant bit, 
 and element 63 contains the most significant bit.
 */
 typedef struct _regFile {

char rax[64]; char rcx[64];
char rdx[64]; char rbx[64]; //could probably organize better but
char rsi[64]; char rdi[64]; // registers 
char rsp[64]; char rbp[64];
char r8[64];  char r9[64];
char r10[64]; char r11[64];
char r12[64]; char r13[64];
char r14[64]; char r15[64];

char ZF[1]; char CF[1]; // And declaration of four status registers
char SF[1]; char OF[1];

 } regFile; // with typedef regFile


 /*
 The "movs" function copies the contents of source to destination registers similar to the mov function,
 except the higher order bits are sign-extended in accordance with the most significant bit
 that is transferred from the source.
 
 For example, if the suffix is ’b’, examine the most significant bit of the lower order byte to determine the sign extension.
  The suffix character is assumed to be one of ’b’, ’w’, ’l’, or ’q’
 */

void movs(char * sourceReg, char * DestReg, char suffix, regFile * registers) {
    // To copy source to destination it depends on byte size
    //Each one takes up a different amount so we need to take that into
    // consideration
 
    int typeSize = 0;
        
    if (suffix == 'b') {  //Takes up 1 byte
        typeSize = 56;  
    }
    else if (suffix == 'w') { // Takes up 2 bytes
        typeSize = 48; 
    }
    else if (suffix == 'l') { //Long takes up for bytes
        typeSize = 32;

    }
    else if (suffix == 'q') { // Quad takes up all 8 bytes
        typeSize = 0; 

    } 
    
    // Now run a for loop through type size to copy from source to dest
    for (int x = 0; x < typeSize; x++) {
        DestReg[x] = sourceReg[x];
    }

    // Find the most significant bit and sotre it in the destination reg
    char MostSig = sourceReg[typeSize - 1];

    for (int y = typeSize; y < 64; y++) {
        DestReg[y] = MostSig;

    }
}

/* 
The "and" function performs the bitwise "and" of the portions of the source and destination register
 denoted by the suffix, and stores the result in the destination register. For example, if
 the suffix is is ’w’, then the bitwise and occurs on the lower order 2 bytes of source and
 destination. The suffix character is assumed to be one of ’b’, ’w’, ’l’, or ’q’. */


/* The status registers should be appropriately updated based on this operation. */

void and(char * sourceReg, char * DestReg, char suffix, regFile * registers) {
   // we dont need msb in add
    int typeSize = 0;
    int ZeroFlag = 1;

    if (suffix == 'b') { // So intead just set there depicted sizes
        typeSize = 8; //Byte is 8 bits
    } else if (suffix == 'w') {  //Word 16 bits
        typeSize = 16;
    } else if (suffix == 'l') { //Long is 32 bits
        typeSize = 32;
    } else if (suffix == 'q') { //Quad is 64 bits
        typeSize = 64;
    }

    /*
    Bitwise info:
    1+1 = 1
    1 + 0 = 0
    0 + 0 = 0
    */

    for (int a = 0; a < typeSize; a++) {
        if (sourceReg[a] == '1' && DestReg[a] == '1') { // And logic
            ZeroFlag = 0; // Since were working with bits if 1 and 1 then 0
            DestReg[a] = '1'; // Zero flag works backwards, if its 1 then zeroflag is zero
                                // since the addition would not be zero
        } else {
            DestReg[a] = '0'; 
        }
    }
    for (int i = typeSize; i < 64; i++) {
        DestReg[i] = '0'; //Zero out upper bits
    }
    if (ZeroFlag) { //Set the actual register zero flag
        registers->ZF[0] = '1'; 
    } else {
        registers->ZF[0] = '0'; 
    }

    
    registers->SF[0] = DestReg[typeSize - 1]; //Sign flag updated based on the result
    // 0 is positive in 2's complement and 1 is neg
}

/*
The "xor" function performs the bitwise "xor" of the portions of the source and destination register
 denoted by the suffix, and stores the result in the destination register.
 
 For example, if the suffix is is ’w’, then the bitwise and occurs on the lower order 2 bytes of source and
 destination. The suffix character is assumed to be one of ’b’, ’w’, ’l’, or ’q’.

 The status registers should be appropriately updated based on this operation.
*/ 

/*
Xor operation
 1 ^ 1 = 0
 1 ^ 0 = 1
 0 ^ 0 = 0

*/

void xor(char * sourceReg, char * DestReg, char suffix, regFile * registers) {

    int typeSize = 0;
    int zeroFlag = 1;

    if (suffix == 'b') { // Do same thing for XOR
        typeSize = 8;
    } else if (suffix == 'w') {
        typeSize = 16;
    } else if (suffix == 'l') {
        typeSize = 32;
    } else if (suffix == 'q') {
        typeSize = 64;
    }

    for (int i = 0; i < typeSize; i++) {

        if (sourceReg[i] != DestReg[i]) { //As long as two compared bits dont match 
            DestReg[i] = '1'; // it will store a 1
            zeroFlag = 0;
        } else {
            DestReg[i] = '0'; // Anything else will store 0
        }
    }

    for (int i = typeSize; i < 64; i++) {
        DestReg[i] = '0'; // Clear upper bits
    }
}

/*
The "add" function performs 2s complement addition of the source and destination values, and stores the result in
 DestReg. 
 
 @param addition occurs over the entire 64 bits. 
 
 If source is a register operand, it should obtain the data from the register, and then perform addition. If the register is
 an immediate value, it should be prefixed by a "$" in the first character, and the values
 should be read in as a decimal quantity (so one would first need to convert to a 64 bit binary
 quantity).

 The status registers should be appropriately updated based on this operation.
*/

void add(char * source, char * DestReg, regFile * registers) {

    char carry = '0';
    int Zeroflag = 1;


    for (int i = 0; i < 64; i++) { 
        int sourceB = 0;
        int destinationB = 0;

        // Since our registers are stored in a char arrat
    if (source[i] == '1') { // We need to use them as ints to calculate them
        sourceB = 1; // 

    } else {
            sourceB = 0; 
        }
        if (DestReg[i] == '1') { // Same thing for dest since we are 
                                    //Adding them together
            destinationB = 1;
        } else {
            destinationB = 0;
        }

        // To evaluate if a value was carried, we need to change it from a char to an int
        int outcome = destinationB + sourceB + (carry == '0');  
        if (outcome % 2 == 1) { // To check whether there is a carry

            DestReg[i] = '1'; // We can check if the output is even or odd
        } else { // Determining what to store in Dest reg based on the calcualation
            DestReg[i] = '0'; // This updates the registers, not the fake dest we used to calculate it
        }

        if (outcome >= 2) {
            carry = '1';

        } else {
            carry = '0';
        }
    }

    /* Flag Updates */

    for (int i = 0; i < 64; i++) {
        if (DestReg[i] == '1') { // Have to update zero flag with every operation
            Zeroflag = 0; // Loop through and if theres a 1 then zeroflag is 0
            
        }
    }
    if (Zeroflag == 1) { //The update accordingly
        registers -> ZF[0] = '1';

    } else {
        registers -> ZF[0] = '0'; // Of course anything else it would be 0
    }

    //DestReg is the MSB so the source flag will map to it
    registers -> SF[0] = DestReg[0];  

    if ((DestReg[0] != carry && (DestReg[0] == source[0]))) {
        registers -> OF[0] = '1'; // Over flow logic, if carry out does not equal carry in
    } else { // Then overflow
        registers -> OF[0] = '0'; // Otherwise theres no overflow
    }

    registers -> CF[0] = carry; // After everything is done carry is updated


}


/*
This is a helper method to be able to convert the source and
reg into a hexcidecimal value

We cant calculate binary using char so we need to work with said numbers
in their integer format
*/
int convertingBi(char * stringFormat) {

    int final = 0;
    int arrayValues[] = {8, 4, 2, 1}; // These store the decimal value of converting to binary
                                        // for example 2^1 or 2^2 etc
    for (int x = 3; x >= 0; x--) { // We loop from LSB to MSB

        if (stringFormat[x] == '1') {
            final += arrayValues[x]; // We add the values to the found bit (1) to create a binary number
        }

    }
    return final; // Then return that number

    }


/* Prints a hex representation of the contents of a register to the
 console*/

void hexRep(char * reg) {

    printf("0x "); // Start of hex format

    for (int x = 0; x < 64; x += 4) { // Loop in groups of 4 bits

        char stringFormat[4]; // Temp store the bits in an array
        for (int i = 0; i < 4; i++) {
            stringFormat[i] = reg[x + i];

        printf("%x", convertingBi(stringFormat)); // Then using the function make a hex digit out of it

        }
    }

    return;
}
/*
@param must free all allocated space
*/

void freeRegs(regFile * pointer) {

    free(pointer -> rax); free(pointer -> rcx); // Just point to the allocated register
    free(pointer -> rdx); free(pointer -> rbx);
    free(pointer -> rsi); free(pointer -> rdi);
    free(pointer -> rsp); free(pointer -> rbp);
    free(pointer -> r8); free(pointer -> r9);
    free(pointer -> r10); free(pointer -> r11);
    free(pointer -> r12); free(pointer -> r13);
    free(pointer -> r14); free(pointer -> r15);
}

 int main(void) {
    
}


  /* Resources: 
       Understanding and Using C Pointers,
       GeeksforGeeks, 
       C programming for dummies, 
       Intermediate C Programming,
       stackoverflow 
       Reddit
       Computer Architecture: A Quantitative Approach
    */
