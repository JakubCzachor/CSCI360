/* Authors: Clayton Broman, Jakub Czachor
   Project: Assembly Code Compiler
   Date: 3/01/2021
   Course: CSCI 360 
   Professor: Xiaojie Zhang
*/
#include <iostream> 
#include <fstream> 
 
using namespace std;  


int main(int argc, char ** argv)  
    {  
    if(argc != 3 ){ //./compiler input_code.c output_code.s 
    //check for input file 
         cout<<"incorrect number of input arguments requires input and output files\n";
	 return 1;
    }
    string preamble = "main:\n\tpushq\t%rbp\n\tmoveq\t%rsp, %rbp\n";
   
    ifstream in_code(argv[1], ifstream::in ); //open the file to read from 
    ofstream out_code(argv[2], ifstream::out ); //open the assembly code file to write into 
    string line; 
   
    //write the preamble 
    out_code << preamble;

     while(getline(in_code, line)){ //iterate over every line in input file 
          out_code << "\tline\n";

     // bulk of the work for next time 
   

     // 
   

     } 
   

     //write the post script 
     out_code << "\tpopq\t%rbp\n\tret\n";

     in_code.close(); 
     out_code.close(); 
   
return 0;
}
