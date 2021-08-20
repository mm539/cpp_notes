// FILE STREAMING
// opening and reading a file

#include <fstream>
#include <string>
#include <iostream>

// input file stream
int main(){
    std::ifstream my_file("board.txt");
    // same as:
    // std::ifstream my_file;
    // my_file.open("files/1.board");
    if (my_file){
        std::string line;
        while (getline(my_file, line)){ // the getline function is important!
            // what is getline?
            // it is a method that takes two arguments
            // the first is the file, the second is a string to write the line to
            // what does it return?
            std::cout << line << "\n";
        }
    }
}
