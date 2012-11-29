// Name: Corey Burmeister
// Course: CSCI480 Section 2
// Assignment: 2
// Due: 11/8/2012

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	
	int pipe1[2], pipe2[2]; // create pipes
	
  FILE *fp, *fp_write, *fp_read; // create file pointers
  
  int size = 256; // set size of buffer
  char buffer[size]; // create buffer with size
  
  // start first pipe
  if(pipe(pipe1)) {            
    fprintf (stderr, "Error. 1st Pipe Failed.\n");
    exit(-1);
  }
  
  // start second pipe
  if(pipe(pipe2)) {
    fprintf (stderr, "Error. 2nd Pipe Failed.\n");
    exit(-1);
  }
  
	pid_t pid = fork(); // fork & create child process
	
	// error occured
	if(pid < 0) {
		fprintf (stderr, "Error. Fork Failed.\n");
    exit(-1);
	} else if(pid == 0) { // child process
		
		// close ends of the pipes
    close(pipe1[1]);
    close(pipe2[0]);

    // convert pipes to file pointers
    dup2(pipe1[0], 0);
    dup2(pipe2[1], 1);

    // close ends of the pipes
    close(pipe1[0]);
    close(pipe2[1]);

    // run the sort command
    execlp("sort", "sort", NULL);
		
	} else { // parent process
	
    // close unneeded ends of pipes
    close(pipe1[0]);
    close(pipe2[1]);

    // convert ends of pipes to file pointers with fdopen()
    fp_write = fdopen(pipe1[1], "w");
    fp_read = fdopen(pipe2[0], "r");

    // open file
    fp = fopen(argv[1], "r");
    
    // file successfully opened
    if(fp != NULL) {
      
      // while there are lines in the file
      while(fgets(buffer, sizeof buffer, fp) != NULL) {
        fprintf(fp_write, buffer); // write line to the pipe
      }

      // close the pipe
      fclose(fp_write);
      close(pipe1[1]);
      
      // close file pointer
      fclose(fp);
                
    }
    else { // file failed to open
      fprintf(stderr, "Error. File failed to open.\n");
      exit(-1);
    }
      
    wait(); // wait for child process to finish sorting
      
    // if there is sorted data from pipe
    while(fgets(buffer, sizeof buffer, fp_read) != NULL) {
      fputs (buffer, stdout); // output sorted contents
    }

    //close the pipe
    fclose (fp_read);
    close (pipe2[0]);
	
	}
	
	return 0;
	
} // end main
