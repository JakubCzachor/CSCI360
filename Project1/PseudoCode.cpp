/* Authors: Clayton Broman, Jakub Czachor
   Project: Assembly Code Compiler
   Date: 3/01/2021
   Course: CSCI 360 
   Professor: Xiaojie Zhang
*/
#include <iostream> 
#include <fstream> 
   
 
    using 
    namespace 
    std;  
   
 
       
   
 
    int 
    main( 
    int 
    argc,  
    char 
    ** argv)  
   
 
    {  
   
 
     if(argc != 3 ){ //./compiler input_code.c output_code.s 
   

     //check for input file 
   

     return error message 
   
 
       } 
   
 
    ifstream in_code(argv[1] ); //open the file to read from 
   

     ofstream out_code(argv[2] ); //open the assembly code file to write into 
   

     string line; 
   
 
    //write the preamble 
   

     while(getline(in_code, line)){ //iterate over every line in input file 
   

     // bulk of the work for next time 
   

     // 
   

     } 
   

     //write the post script 
   

     in_code.close(); 
   

     out_code.close(); 
   
return 0;
}
