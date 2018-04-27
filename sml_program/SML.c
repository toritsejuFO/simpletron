/*
PROGRAM: SML.c : Simpleton Machine Language
USE: A program written to accept programs written in the sml 
language--though this version is modified to read input from 
files with predefined sml instructions--and run it thus.
AUTHOR: ToriBoi
*/

//inclusion of necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SML_FUNCTION.h" //

//main program
int main( int argc, char* argv[] ){
	//give user hints on operation codes
	print_program_instr();
	
	//vars created to enable instruction intake
	int counter = 0;
	int current_instr = 0;
	
	//string variable to store name of sml file user wants to read sml program from
	char inFileName[30];
	printf("Enter name of input file with extension: ");
	scanf("%s", inFileName);
	
	//string variable to store name of sml file user wants to write sml program output to
	char outFileName[30];
	printf("Enter name of output file with extension: ");
	scanf("%s", outFileName);
		
	//open file from which program is to be read from
	FILE* smlInFilePtr = fopen(inFileName, "r");
	
	//end program if infile could not be open
	if(smlInFilePtr == NULL){
		printf("Sorry, couldnt open file to read program or invalid filename.\n");
		return 0;
	}
	
	//open file to which sml output is to be written to
	FILE* smlOutFilePtr = fopen(outFileName, "w");
	
	//end program if outfile could not be open
	if(smlOutFilePtr == NULL){
		fclose(smlInFilePtr);
		printf("Sorry, couldnt open file for writing or invalid filename.\n");
		return 0;
	}
	
	//get all instructions till end_of_file indicator and load in memory
	fscanf(smlInFilePtr, "%d", &current_instr);
	while(!feof(smlInFilePtr)){
		if(current_instr != -99999){
			memory[counter] = current_instr;
		}//end if
		
		fscanf(smlInFilePtr, "%d", &current_instr);
		counter++;
	}//end while
	
	printf("*** Program loading completed ***\n"
		   "*** Program execution begins ***\n");
	
	//loop through memory executing valid operation codes until halt is found
	while( operationCode != HALT ){
		//extract next instruction from memory
		instructionRegister = memory[instructionCounter];
		
		//ensure correct capture of operand's memory and operation codes
		if(instructionRegister > 9999){
			operationCode = (int)instructionRegister / 1000;
			operand = (int)instructionRegister % 1000;
		}//end if
		else{
			operationCode = (int)instructionRegister / 100;
			operand = (int)instructionRegister % 100;
		}//end else
		
		// carry out instruction according to operation code
		switch( operationCode ){
			case READ:
				printf("?");
				scanf("%lf", &memory[operand]);
				instructionCounter++;
				break;
				
			case WRITE:
				printf("%.4f\n", memory[operand]);
				instructionCounter++;
				break;
				
			case LOAD:
				accumulator = memory[operand];
				instructionCounter++;
				break;
				
			case STORE:
				memory[operand] = accumulator;
				instructionCounter++;
				break;
				
			case ADD:
				accumulator += memory[operand];
				instructionCounter++;
				break;
				
			case SUBTRACT:
				accumulator -= memory[operand];
				instructionCounter++;
				break;
				
			case DIVIDE:
				if(memory[operand] == 0){
					printf("\n*** Attempt to divide by zero ***\n");
					printf("*** Simpletron execution abnormally terminated *** ");
					fclose(smlInFilePtr); //close infile pointer
					dump_info(stdout);
					dump_info(smlOutFilePtr);
					return 0;
				}
				accumulator /= memory[operand];
				instructionCounter++;
				break;
				
			case MULTIPLY:
				accumulator *= memory[operand];
				instructionCounter++;
				break;
				
			case REMAINDER:
				accumulator = (int)accumulator % (int)memory[operand];
				instructionCounter++;
				break;
				
			case EXPONENT:
				accumulator = pow(accumulator, memory[operand]) ;
				instructionCounter++;
				break;
				
			case BRANCH:
				instructionCounter = operand;
				break;
				
			case BRANCHZERO:
				if(accumulator == 0){
					instructionCounter = operand;
				}else{
					instructionCounter++;
				}
				break;
				
			case BRANCHNEG:
				if(accumulator < 0){
					instructionCounter = operand;
				}else{
					instructionCounter++;
				}
				break;
				
			case NEWLINE:
				printf("\n");
				instructionCounter++;
				break;
				
			case HALT:
				printf("\n*** Simpleton execution terminated ***\n");
				break;
				
			default:
				printf("\n*** execution of invalid operation code ***\n");
				printf("*** Simpletron execution abnormally terminated *** ");
				fclose(smlInFilePtr); //close infile pointer
				dump_info(stdout);
				dump_info(smlOutFilePtr);
				return 0;
				
		}
	}//end while
	
	//print memory related info
	dump_info(stdout);
	dump_info(smlOutFilePtr);
	
	//close infile pointer
	fclose(smlInFilePtr);
	
	getchar();
	return 0;
}

