#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For system calls write, read e close
#include <fcntl.h>

#define BUFFER_SIZE 4096

int main(int argc, char* argv[]) {
	if (argc != 3) {
		printf("Usage %s Src_file Dest_file\n", argv[0]);
		exit(1);
	}
	
    unsigned char buffer[BUFFER_SIZE] = {0};
    ssize_t ReadByte = 0;
    
    int src_fd, dst_fd;
    
    // open file in read mode
    if ((src_fd = open(argv[1], O_RDONLY)) == -1) {
    	printf("Failed to open input file %s\n", argv[1]);
        exit(1);
    }
    
    // open file in write mode and already exists to overwrite
    if ((dst_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 644)) == -1) {
    	printf("Failed to create output file %s\n", argv[2]);
        exit(1);
    }
    
    // loop
    while (1) {
    	// read buffer
    	ReadByte = read(src_fd, buffer, sizeof(buffer));
        // error with reading
        if (ReadByte == -1) {
        	printf("Encountered an error\n");
            break;
        } else if (ReadByte == 0) {
        	// file end exit loop
        	printf("File copying successful.\n");
            break;
        }
        
        // write file
       if (write(dst_fd, buffer, ReadByte) == -1) {
       	printf("Failed to copying file\n");
       	break;
       }
    
    }
    
    // Close file
    close(src_fd);
    close(dst_fd);
    
    exit(0);
}
