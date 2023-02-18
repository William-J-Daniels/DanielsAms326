I intend to use this repository to host all the code I write for this class (AMS 326).
My intent is to maintain this repo during the semester with my implimentations and solutions so that I can easily share my code.
For each submission, I will record the commit which corresponds to my final commit before the deadline.
This will be much easier than trying to get all of the relevant files on brightspace or google dirve.

# Directory structure:
The directory structure is informed by the build system, cmake.
Cmake makes it easy to have modular libraries that can be linked to other sub-projects within the master project by way of the include_subdirectory function.
My libraries will be clearly named, as will the directories corresponding to my assignments (HomeworkOne, ExamOne, etc).

Each directory will contain, as necessary, the subdirectories examples/ include/ and src/ which contain driver code, public header files, and implimentation files respectively.
Directores for assignments will additionally contain a subdirectory docs/ which contains the writeup for the assignment.
Any directory which requires data to be written to or read from the disk will contain a subdirectory data/ and any directory that requires additional tools such as a plotting script will contain a subdirectory tools/.

Executable files are genarated in a subdirectory of the build directory corresponding to the location of the source.
For example, to run the executable genarated by HomeworkOne/examples/problem_one.cpp, go to build/HomeworkOne and run ./problem_one.cpp

# Build instructions:
Clone the repository and change into it. Then, create a new build directory, change into it, run cmake a directory up, and run make.
On linux, this corresponds to

git clone git@github.com:William-J-Daniels/DanielsAms326.git

cd DanielsAms326 && mkdir build && cd build && cmake .. && make
