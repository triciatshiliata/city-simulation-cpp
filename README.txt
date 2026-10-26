Simcity Milestone 1
Group members: Eden Kutch, Ronil Doshi, Connor Johnson, Sydney Jones, Patricia Tshiliata

To run the project:

1. Unzip the file and navigate to the directory in your terminal, If you are on Linux use:
	cd [yourpath]/simcity-project-master

2. There is a makefile in this directory, run this command:
	make
	
3. The makefile will make an executable, run this command to run the program:
	./Simcity

4. To clean up the generated files after using the program, run:
	make clean

5. There are also a.exe and a.out files available in the file. Open a.exe in windows, or run ./a.out on Linux

To use the program:

1. Enter '0' for the main program, or '1' for unit testing mode

2. If '0': When the program asks for the config file enter "config1.txt"

3. After the simulation runs you can enter "a" to analyze coordinates, or enter "q" to quit the program.

4. If '1': Observe the unit testing, and either enter '0' to run the main program or '1' to quit at the end.

NOTE: Should the makefile not work for any reason (This will happen on Windows / any Non-Unix OS), as a last resort cd / Set-Location to the directory and type "g++ *.cpp" and then "./a.out" or "./a.exe" if on Windows.


Team: Patricia Tshiliata, Eden Kutch, Ronil Doshi, Connor Johnson, Sydney Jones
Team project for a university software engineering course (UNT, Spring 2024).
