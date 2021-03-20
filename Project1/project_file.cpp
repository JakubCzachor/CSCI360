/* Authors: Clayton Broman, Jakub Czachor
   Project: Assembly Code Compiler
   Date: 3/01/2021
   Course: CSCI 360 
   Professor: Xiaojie Zhang
*/
#include <iostream> 
#include <fstream> 
#include <vector>
#include <list> 
#include <iterator>

using namespace std; 

void arith_state(string& line){

	int equalFind = line.find("="); //finds equal sign
	int incrementFind = line.find("++"); //finds addition
	int decrementFind = line.find("--"); //finds decrement
	int multFind = line.find("*"); //finds *
	int divFind = line.find("/"); //finds /
	int addFind = line.find("+"); //finds +
	int subFind = line.find("-"); //finds -
	int lineEnd = line.find(";"); //finds end
	int var0ArrayFindLeft; 
	int var0ArrayFindRight;
		
	string var0; //original variable;
		
	if((line[equalFind-1] != "=" || line[equalFind+1] != "=") && (incrementFind == -1) && (decrementFind == -1)){ //checks to see != "==" && != "++" or "--"
		
		var0 = line.substr(0,equalFind); //first variable
		var0ArrayFindLeft = var0.find("["); //finds left bracket
		var0ArrayFindRight = var0.find("]"); //finds right bracket 
			
		if((arrayFindLeft == -1)) && (arrayFindRight == -1)){ //not an array
			
			if(multFind != -1 || divFind != -1){ //multiplication or division is present
				
				if((multFind == -1) && divFind != -1){//division is present
					string var1 = line.subtr(equalFind+1,divFind-1); //finds b in a=b/c;
					string var2 = line.subtr(divFind+1, lineEnd-1); //finds c in a=b/c;
			
					//division of variables
				}
				else if((multFind != -1) && (divFind == -1)){ //multiplication is present
					string var1 = line.subtr(equalFind+1, multFind -1); //finds b in a=b*c
					string var2 = line.subtr(multFind+1, lineEnd -1); //finds c in a=b*c
						
					//multiplication of variables
				}
        
			}
			else if((subFind != -1) || (addFind != -1)){ //addition or subtraction is present
				
        			if((subFind == -1) && (addFind != -1)){ //addition is present
					string var1 = line.subtr(equalFind+1, addFind -1); //finds b in a=b+c
					string var2 = line.subtr(addFind+1, lineEnd -1); //finds c in a=b+c
						
					//push addl
				}
				else if((addFind == -1)&& (subFind != -1)){ //subtraction is present
					string var1 = line.subtr(equalFind+1, subFind -1); //finds b in a=b-c
					string var2 = line.subtr(subFind+1, lineEnd -1); //finds c in a=b-c
						
					//push subl
				}
					
			}
			else{//Neither is present, other state -> x=y
				string var2 = line.subtr(equalFind, line.length()); 
				int var2ArrayFindLeft = var2.find("[");
				int var2ArrayFindRight = var2.find("]");
				if((var2ArrayFindLeft == -1) && (var2ArrayFindRight == -1)){ //not an array
					//set two variables equal to each other
				}
				else{ //y is a variable
					string var2Array = var2.subtr(var2ArrayFindLeft+1, var2ArrayFindRight-1); //var2Array => z in x = y[z]
					//set variable equal to number in an array
				}
			}
				
				
		}
		else{ //var0 is an array && "=" operation



				
		}
	}
	
		
	else if(line[equalFind-1] == "=" || line[equalFind+1] != "="){ //"== operation"
		
			
	}
	else if((equalFind == -1) && (incrementFind != -1)){ //Increments Variable
		var0 = line.subtr(0, incrementFind);
			
	}
	else if((equalFind == -1) && (decrementFind != -1)){ //Decrements Variable
			var0 = line.subtr(0, decrementFind); 
			
	}
	else{ //not "=", "==", "++", or "--"

			
	}
		
		
}

struct ItLine{
	string word;
	operator string const&() const{return word;}
	friend istream& operator>>(istream& stream, ItLine& line){
		return getline(stream, line.word);
	}
	
};

struct function{
	//default function 
	string funct_name;
	string ret_type;
	vector<string> assem_instrs;
	bool no_more;
};

void trim_tabs_spaces(string& in_str){
	string temp = in_str;
	int i=0;
	for(i;i<temp.length();i++)
	{
		if(temp[i] == ' ' || temp[i] == '\t' )  continue;
		else break;
	}
	in_str = temp.substr(i,temp.length());
}

void funct_dec(string line)
{
    function funct;
    int start, end;

    funct.ret_type = line.substr(0,line.find(' '));
    string temp = line.substr(line.find(' ')+1, line.length());
    funct.funct_name = temp.substr(0, temp.find('('));
    funct.assem_instrs.push_back(funct.funct_name + ":");
    funct.assem_instrs.push_back("pushq %rbp");
    funct.assem_instrs.push_back("movq %rsp,%rbp");
    funct.no_more = true;
    return;
}

bool is_funct_dec(const string& line)
{
    if(line.find("int")<line.length() && line.find("(") <line.length() )
    {
        return true;
    }
    else if( line.find("void")<line.length() && line.find("(") <line.length() )
    {
	return true;
    }
    else if( line.find("string")<line.length() && line.find("(") <line.length() )
    {
	return true;
    }
    else if( line.find("bool")<line.length() && line.find("(") <line.length() )
    {
	return true;
    }

    else return false;
}

int main(int argc, char ** argv)  
{   
    list<string> funct_table;

    if(argc != 3 ){ //./compiler input_code.c output_code.s 
    //check for input file 
         cout<<"incorrect number of input arguments, 2 required: input and output files\n";
	 return 1;
    }
    string preamble = "main:\n\tpushq\t%rbp\n\tmoveq\t%rsp, %rbp\n";
   
    ifstream in_code(argv[1], ifstream::in ); //open the file to read from 
    ofstream out_code(argv[2], ifstream::out ); //open the assembly code file to write into 
    string line; 
   
    //write the preamble 
    //out_code << preamble; // maybe should be part of funct handler
    //istream_iterator<string> fin(in_code);
    istream_iterator<string> eof;
    vector<string> v_line( istream_iterator<ItLine>{in_code}, istream_iterator<ItLine>{});

    for(int i=0;i<3;i++ ) //getline(in_code, line)) //iterate over every line in input file 
    {  

	out_code<<v_line[i]<<"\n";
	
	continue;
	out_code<<"did i get here?";
        trim_tabs_spaces(line);
	if( line.length() ==0) continue;  //skip blank lines
	else if( line.find("int")==0 && line.find(";")==line.length()-1)
	{
	    //found variable declaration
	    //
	    out_code<<"var dec\n";
	    //varable_dec(line);
	}
	else if(line.find("if")<line.length())
	{
	    //found an if statement
	    //
	    out_code<<line.find("if")<<"\n";
	    out_code<<"if_state\n";
	    //if_state(line);
	}
	else if(line.find("for")<line.length())
	{
	    //found for statement
	    out_code << "for state\n";

	    //for_state(line);
	}
	else if(line.find("return")<line.length())
	{
	    //found return statement
	    out_code << "return\n";
	    //return_state(line);
	}
	else if( is_funct_dec(line) == true )
	{
	    //found function declaration
	    //
	    out_code<< "found a funct dec\n";
	    funct_dec(line);
	}
	else{
	    //arithmetic instructions
	    //
	    out_code<<"arithmetic instr\n";
	    //arith_state( line );
        }
   
	out_code << line << "\n"; //for debug

    } 
   
   
    //write the post script 
    //out_code << "\tpopq\t%rbp\n\tret\n"; // handle in fuct handler

    in_code.close(); 
    out_code.close(); 
   
    return 0;
}
