# Virtual Memory Management

Evan Carlin
5/7/2017

A program to  simulate virtual memory
management using demand paging and a 
variety of replacement policies.

To make:
	$ make all

To run:
	$ ./vmm [-p num_pages] [-f num_frames] [-b block_size] [-r rep_policy] <inst_file>

	[] indicates optional flag
	<> indicates required file

To clean:
	$ make clean


NOTES:
- Running "./vmm 8 4 1024 random in1.txt" will "appear" to execute fine but
  but the parameters 8, 4, 1024,... have no effect. They will only
  have an effect if there is a flag in front. So, the proper 
  way to run the command is "./vmm -p 8 -f 4 -b 1024 -r random in1.txt"

- The CLOCK replacement policy wasn't implemented