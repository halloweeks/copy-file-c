#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <iomanip>

int main(int argc, char* argv[]) {
	/* clock_t clock(void) returns the number of clock ticks 
	   elapsed since the program was launched.To get the number  
           of seconds used by the CPU, you will need to divide by  
           CLOCKS_PER_SEC.where CLOCKS_PER_SEC is 1000000 on typical 
           32 bit system.  */
	clock_t start, end; 
	
	// Recording the starting clock tick.
	start = clock(); 
	
	std::ifstream fin(argv[1], std::ios::binary);
	std::ofstream fout(argv[2], std::ios::binary);
	
	unsigned char buffer[65536];
	
	while (fin) {
		fin.read(reinterpret_cast<char*>(&buffer), 65536);
		int len = (int)fin.gcount();
		fout.write(reinterpret_cast<char*>(&buffer), len);
		memset(buffer, 0, 65536);
	}
	
	fin.close();
	fout.close();
	
	// Recording the end clock tick. 
	end = clock();
    
	// Calculating total time taken by the program. 
	double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    
	// print process time
	std::cout << "[TIME] PROCESS COMPLETE IN " << std::fixed << time_taken << std::setprecision(5) << " SEC\n";
	

	return 0;
}