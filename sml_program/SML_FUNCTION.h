//Input/output operations
#define READ 10
#define WRITE 11

//Load/store operations
#define LOAD 20
#define STORE 21

//Arithmetic operations
#define ADD 30
#define SUBTRACT 31
#define DIVIDE 32
#define MULTIPLY 33
#define REMAINDER 34
#define EXPONENT 35

//Transfer of control operations
#define BRANCH 40
#define BRANCHNEG 41
#define BRANCHZERO 42
#define HALT 43

//other operations
#define NEWLINE 50

//memory size
#define SIZE 1000

double memory[SIZE] = {0};
double accumulator = +0000;	//accumulator register
int instructionCounter = 00;	//location in memory of currently executing instruction
double instructionRegister = +0000;	//to hold instruction to be currently executed
int operationCode = 00;		//operation currently executing
int operand = 00;	//operand currently being worked with/on

//print header on program run
void print_program_instr(){
	printf("*** Welcome to Simpleton! ***\n"
		   "*** Please enter your program one instruction ***\n"
		   "*** (or data word) at a time. I will type the ***\n"
		   "*** location number and a question mark (?).  ***\n"
		   "*** You then type the word for that location. ***\n"
		   "*** Type the sentinel -99999 to stop entering ***\n"
		   "*** your program. ***\n\n");
	
	printf( "Input/output operations\n"
			"READ 10\n"
			"WRITE 11\n\n"

			"Load/store operations\n"
			"LOAD 20\n"
			"STORE 21\n\n"

			"Arithmetic operations\n"
			"ADD 30\n"
			"SUBTRACT 31\n"
			"DIVIDE 32\n"
			"MULTIPLY 33\n"
			"REMAINDER 34\n"
			"EXPONENT 35\n\n"

			"Transfer of control operations\n"
			"BRANCH 40\n"
			"BRANCHNEG 41\n"
			"BRANCHZERO 42\n"
			"HALT 43\n\n"
			
			"Other operations\n"
			"NEWLINE 5000\n\n");
}

/*
print out memory related info for user to be able to examine
input and output by viewing internally what went on in memory
as their program ran
*/
void dump_info(FILE* stream){
	if(stream != stdout){
		fprintf(stream, "Dump info from last run of sml program");
	}
	
	fprintf(stream,

		   "\n\nREGISTERS:\n"
		   "accumulator			%+6.04d\n"
		   "instructionCounter		%6.02d\n"
		   "instructionRegister		%+6.04d\n"
		   "operationCode			%6.02d\n"
		   "operand				%6.02d\n",
		   accumulator, instructionCounter, instructionRegister,
		   operationCode, operand);
		   
	fprintf(stream, "\nMEMORY:\n");
	
	int i;
	
	for(i = 0; i < 10; i++){
		if(i == 0){
			fprintf(stream, "%13d", i);
		}
		else{
			fprintf(stream, "%10d", i);
		}
	}
	
	fprintf(stream, "\n%3d", 0);
	for(i = 0; i < SIZE; i++){
		if(memory[i] == 0){
			fprintf(stream, "%+10.04f", memory[i]);
			if( (i % 10) == 9 ){
				if(i != 999){
					fprintf(stream, "\n%3d", i+1);
				}
			}
		}
		else if( ( ( memory[i] - ((int)(memory[i])) ) > 0.0 ) || 
				 ( ( memory[i] - ((int)(memory[i])) ) < 0.0 ) ){
			fprintf(stream, "%+10.04f", memory[i]);
			if( (i % 10) == 9 ){
				if(i != 999){
					fprintf(stream, "\n%3d", i+1);
				}
			}
		}
		else{
			fprintf(stream, "%+10.0f", memory[i]);
			if( (i % 10) == 9 ){
				if(i != 999){
					fprintf(stream, "\n%3d", i+1);
				}
			}
		}
	}
	
	//close outfile pointer
	fclose(stream);
}
