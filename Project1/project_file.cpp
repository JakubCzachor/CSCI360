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
