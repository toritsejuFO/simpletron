//inclusion of necessary hedaers
#include <stdio.h>
#include <stdlib.h>

//main program
int main( int argc, char * argv[] ){
	int counter = 0;
	int current_instr = 0;
	
	if( argc != 2 ){
		printf( "usage: ./writeSmlProgram [filename]" );
		return 0;
	}
	
	//open file for writing
	FILE* smlFilePtr = fopen(argv[1], "w");
	
	//check value of file pointer
	if(smlFilePtr == NULL){
		printf("Sorry, couldnt open file to write program.\n");
		return;
	}//end if
	else{
		printf("%02d ? ", counter);
		scanf("%d", &current_instr);
		
		//write to file while not at the end
		while(!feof(stdin)){
			fprintf(smlFilePtr, "%d\n", current_instr);
			
			printf("%02d ? ", counter);
			scanf("%d", &current_instr);
			
			counter++;
		}
		
		fclose(smlFilePtr);
	}//end else
	
	getch();
	return;
}
