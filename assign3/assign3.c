// Name: Corey Burmeister
// Course: CSCI480 Section 2
// Assignment: 3
// Due: 11/28/2012

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[]) {

  FILE *fp; // create file pointers

  // open file
  fp = fopen(argv[1], "r+");
  
  // file successfully opened
  if(fp != NULL) {
  
    // repeat 10 times
    for(int i=0; i<10; i++) {
      
      int num, sum = 0; // integer storage
      
      int fd = fileno(fp); // find file descriptor
      lockf(fd, F_LOCK, 0); // lock the file

      // repeat 3 times
      for(int j=0; j<3; j++) {
      
        fscanf(fp, "%d", &num); // extract integers from line
        printf("%d\n", num);
      
        sum += num; // add to sum
      
      }

      rewind(fp); // set position indicator to beginning of file
      
      sleep(5); // wait for 5 seconds
      
      // repeat 3 times
      for(int k=0; k<3; k++) {
        fprintf(fp, "%d\n", sum); // write sum to file
      }
      
      rewind(fp); // set position indicator to beginning of file
      
      lockf(fd, F_ULOCK, 0); // unlock file
      
    }
    
    fclose(fp); // close file
    
  } else { // file failed to open
    
    fprintf(stderr, "Error. File failed to open.\n");
    exit(-1);
  
  }
	
	return 0;
	
} // end main
