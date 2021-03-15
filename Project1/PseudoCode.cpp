/* Authors: Clayton Broman, Jakub Czachor
   Project: Assembly Code Compiler
   Date: 3/01/2021
   Due data: 3/23/2021
   Course: CSCI 360 
   Professor: Xiaojie Zhang
*/
#include <iostream> 
#include <fstream> 
   
struct com{
	string preamble = "main:\n\tpushq\t%rbp\n\tmoveq\t%rsp, %rbp\n";
} line;

//function statements - for a line that calls a function. 
int funct_state(string line){
	write preamle
	parse the line
 	for:
	{
	   return_type;
	   find first space;
	   function name;
	   "\("
           call var_dec(rest of line);
	}
	return
}
int var_dec(string line){
	parse for spaces or "\)": 

	if int -> size=4;
}
int 


int main( int argc,  char **argv){  
 
    if(argc != 3 ){ //./compiler input_code.c output_code.s 
   	//check for input file 
   	return error message 
    } 
 
    ifstream in_code(argv[1] ); //open the file to read from 
    ofstream out_code(argv[2] ); //open the assembly code file to write into 
   
    string line; 
    
    for line in input_file{
	    if starts with (int)
	    {
		could be function declaration -> call funct_state(line)
	        could be variable declaration -> call var_dec(line);
	    }
	    
	    //leaving out while loop 

	    if starts with "if"
	    {
                call if_state(line);
	    }
	    if starts with "for"
	    {
		call for_state(line);
	    }
	    if starts with "var_name":
	    {
	    	call arith_state(line);
	    }
	    if starts with "class":
	    {
		call class_state(line);
	    }
	}	    
    
    for the navigation throughout functions {
	    
    	line_end(string)
    	{
		if ";",  move down line
    	} 

    	curly_start(string)
    	{ 
		if "{" start of new function
    	}

    	curly_end(string);
    	{
		if "}" end function
    	}
	    
    }


    for in line arithmetic{ 
	    
	if "=" //need to also check !"=="
	{
		set_equal(a,b); 
	}
	if !"=" && "=="
	{
		check_equal(a,b);
	}
	if "+"
	{
		addi(a,b);
	}
	if "-"
	{
		sub(a,b);
	}
	if "*"
	{
		mult(a,b);
	}
	if "/" 
	{
		div(a,b);
	}
	if "++"
	{
		addi(a,1);
	}
	if "--"
	{
		sub(a,1);
	}
	  
	   
    }
	
    //write the preamble 
   

     // bulk of the work for next time 
   

     // 
   

     } 
   

     //write the epilogue 
   

     in_code.close(); 
   

     out_code.close(); 
   
return 0;
}
