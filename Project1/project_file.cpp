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
#include <map>

using namespace std;
struct function{
	//default function
	vector<string> funct_list; //keeper of all past function names
	string funct_name; //keeper of the current function name
	vector<int> mem_counter; //keep track of input arguments
	map<string, vector<int>> var_dec;
	string var_reg[6] = {"%edi","%esi","%edx","%ecx","%r8d","%r9d"};
	int input_leng;
	string ret_type;
	vector<string> assem_instrs;
	vector<string> arith_opers;
	vector<string> var_declars;
	bool no_more; // is this a leaf function
	bool is_ret;  //is there a return object

};
string trim_tabs_spaces( string  in_str );
ostream& coarse_parse(ostream &out_code, const vector<string> &v_code, int &line_cntr,function &assem_instrs );
ostream& funct_dec(ostream &out_code,const vector<string> &v_code, int &cntr, function &funct);
bool is_funct_dec(const string& line);
void var_dec(string line,const vector<string> &v_code,int & line_cntr,function &funct);
void funct_call(string line,const vector<string> &v_code,int & line_cntr,function &funct);

void arith_state(string line,const vector<string> &v_code,int & line_cntr,function &funct)
{
	//function
	line = v_code[line_cntr];
	funct.assem_instrs.push_back("doing arritmetic\n");  //add instructions like this
        return;

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

	if((incrementFind == string::npos) && (decrementFind == string::npos)){ //checks to see != "==" && != "++" or "--" (== is comparitor)
		
		var0 = line.substr(0,equalFind); //first variable
		var0ArrayFindLeft = var0.find("["); //finds left bracket
		var0ArrayFindRight = var0.find("]"); //finds right bracket 
			
		if((var0ArrayFindLeft == string::npos) && (var0ArrayFindRight == string::npos)){ //not an array
			
			if(multFind != string::npos || divFind != string::npos){ //multiplication or division is present
				
				if((multFind == string::npos) && divFind != string::npos){//division is present

					string var1 = line.substr(equalFind+1,divFind-1); //finds b in a=b/c;
					string var2 = line.substr(divFind+1, lineEnd-1); //finds c in a=b/c;

					//division of variables
				}
				else if((multFind != string::npos) && (divFind == string::npos)){ //multiplication is present
					string var1 = line.substr(equalFind+1, multFind -1); //finds b in a=b*c
					string var2 = line.substr(multFind+1, lineEnd -1); //finds c in a=b*c

					//multiplication of variables
				}

			}

			else if((subFind != string::npos) || (addFind != string::npos)){ //addition or subtraction is present
				
        			if((subFind == string::npos) && (addFind != string::npos)){ //addition is present
					string var1 = line.substr(equalFind+1, addFind -1); //finds b in a=b+c
					string var2 = line.substr(addFind+1, lineEnd -1); //finds c in a=b+c

					//push addl
				}
				else if((addFind == string::npos)&& (subFind != string::npos)){ //subtraction is present
					string var1 = line.substr(equalFind+1, subFind -1); //finds b in a=b-c
					string var2 = line.substr(subFind+1, lineEnd -1); //finds c in a=b-c

					//push subl
				}

			}
			else{//Neither is present, other state -> x=y
				string var2 = line.substr(equalFind, line.length());
				int var2ArrayFindLeft = var2.find("[");
				int var2ArrayFindRight = var2.find("]");
				if((var2ArrayFindLeft == string::npos) && (var2ArrayFindRight == string::npos)){ //not an array
					//set two variables equal to each other
				}
				else{ //y is a variable
					string var2Array = var2.substr(var2ArrayFindLeft+1, var2ArrayFindRight-1); //var2Array => z in x = y[z]
					//set variable equal to number in an array
				}
			}


		}
		else{ //var0 is an array && "=" operation




		}
	}


	//else if(line[equalFind-1] == "=" || line[equalFind+1] != "="){ //"== operation"


	//}
	else if((equalFind == string::npos) && (incrementFind != string::npos)){ //Increments Variable
		var0 = line.substr(0, incrementFind);

	}

	else if((equalFind string::npos) && (decrementFind != string::npos)){ //Decrements Variable
			var0 = line.substr(0, decrementFind); 

	}
	else{ //not "=", "==", "++", or "--"


	}


}


string trim_tabs_spaces( string  in_str ){

	string temp = in_str;
	int i=0;
	for(i;i<temp.length();i++)
	{
		if(temp[i] == ' ' || temp[i] == '\t' )  continue;
		else break;
	}
	return temp.substr(i,temp.length());
}

ostream& coarse_parse(ostream &out_code, const vector<string> &v_code, int &line_cntr, function &assem_instrs )
{
	//cout<<"course parse cntr"<< line_cntr<<"\n"; //debug
	string line = v_code[ line_cntr ];
        //cout<<"course parse line "<<line<<"\n"; //debug

	//seach for a function call (loops through all the functions added to the list)
	for(auto i = assem_instrs.funct_list.begin(); i != assem_instrs.funct_list.end(); i++){
		if( line.find(*i)==0 && line.find("(") < line.length()){
		    //found a function call
		    funct_call(line,v_code,line_cntr,assem_instrs);
		}

	}
        //search for variable declarations
	if( line.find("int") ==0 && line.find(";")<line.length())
	{
	    //cout<<line.find("int")<<" var dec\n";  //debug
	    var_dec(line,v_code,line_cntr,assem_instrs);
	}
	//found an if statement
	else if( line.find("if")<line.length())
	{
	    //out_code<< line.find("if")<<"\n";
	    out_code<<"if_state\n";
	}
	else if( line.find("for")<line.length())
	{
	    //found for statement
	    out_code << "for state\n";

	    //for_state(line);
	}
	else if( line.find("return")<line.length())
	{
	    //found return statement
	    out_code << "return\n";
	    //return_state(line);
	}
	//found function declaration
	else if( is_funct_dec( line ) == true )
	{
	    //cout<< "found a funct dec\n";  //debug
	    funct_dec(out_code, v_code, line_cntr, assem_instrs);

	}
	else{
	    //arithmetic instructions
	    //cout<<"arithmetic instr\n";
            arith_state( line,v_code,line_cntr, assem_instrs);
        }

	return out_code;
}

ostream& funct_dec(ostream &out_code,const vector<string> &v_code, int &cntr, function &funct) //function declaration statement
{

    string preamble = "\tpushq\t%rbp\n\tmoveq\t%rsp, %rbp\n";
    string epilogue =  "\tpopq\t%rbp\n\tret\n";
    //function funct;
    int start, end;
    string line = v_code[cntr];
    funct.ret_type = line.substr(0,line.find(' '));
    if(funct.ret_type == "void"){ // so we know if we need to deal with return variables
	    funct.is_ret = true;
    }else funct.is_ret = false;

    string temp = line.substr(line.find(' ')+1, line.length());
    funct.funct_name = temp.substr(0, temp.find('('));
    funct.funct_list.push_back(funct.funct_name);
    funct.no_more = true; //not calling any more functions
    //cout<<cntr<<"\n";   //debug
    cntr++; //go to the next line in the file
    line = v_code[cntr];
    //cout<<line<<cntr<<"\n";  //debug
    while(line.find('}') > line.length()-1) //until the end of the function declaration
    {
	   //cout<<"line leng  "<<line.length()<<" line find"<<line.find('}')<<"\n"; //debug
	    coarse_parse(out_code, v_code, cntr, funct);
	    cntr++;
	    //cout<<"cntr  "<<cntr<<"\n"; //debug
	    line = v_code[cntr];
    }

    out_code << funct.funct_name << ":"<< "\n";
    out_code << preamble;
    for( auto i=funct.assem_instrs.begin() ; i != funct.assem_instrs.end(); i++){
	    out_code << "\t" << *i <<"\n";
    }
    out_code << epilogue;;
    return out_code;
}

void var_dec(string line,const vector<string> &v_code,int & line_cntr,function &funct)
{
    line = line.substr(line.find(' ')+1, line.length()-1); //remove the "int" and ";"

    char j;
    string var = "";
    int value;
    list vars; // list of the variable names
    list vector<int> values;  // list of the values
    for(int i=0; i<line.length(); i++ ){
        if( isalpha( line[i] ) ){
            var.append( line[i] );
        }
        else if( line[i] == "="){
           i++;
           if( isdigit( line[i] )){
              value = line[i];
              i++;
              while( isdigit( line[i] )){
                  value = 10*value + line[i];
                  i++;
              }

           }
           else if( line[i] = '[]' )
        }




    }



    cout << "currentComma: " << currentComma <<endl << "currentEqual: " << currentEqual <<endl;
    size_t nextComma;
    int nextEqual;
    size_t prevComma;

    //varVecRight.push_back(currentEqual, )

    for(int i = 0;i<countComma;i++){


      if(line.find(",",currentComma+1) != string::npos){
       nextComma = line.find(",", currentComma+1);
       commaFindv.push_back(nextComma);
      }
      else{
        cout << "no next comma";
        nextComma = lineEnd;
        cout << nextComma << "next comma" << endl;
      }

      nextEqual = line.find("=", currentComma);

      if(varVecLeft.empty()){ //at start
        if(line.substr(0, currentComma-1).find("[")!= string::npos){ //if there is an array on the left side
        cout <<"detected";
        isArrayLeft.push_back(true); //pushes true state to isArray

        arrayString = line.substr(0, currentComma); //creates a new string between 0 and ,
        arrayLBracket = arrayString.find("["); //finds [
        arrayRBracket = arrayString.find("]"); //finds ]
        arrayString = arrayString.substr(arrayLBracket+1, arrayRBracket-1); //creates a new string between [ and ]

        arrayVal = stoi(arrayString); //converts the data inside [ and ] into an int

        arrayValueLeft.push_back(arrayVal);

      }
      else{ //if there is no array on the left
        isArrayLeft.push_back(false); //pushes false state
        cout << "Not detected" <<endl;
      }
      if(line.substr(currentEqual+1, currentComma-1).find("[") != string::npos){ //if there is an array on the right side

        isArrayRight.push_back(true); //pushes true state to isArrayRight
        arrayString = line.substr(currentEqual+1, currentComma-1); //creates a new string between = and ,
        arrayLBracket = arrayString.find("["); //finds [
        arrayRBracket = arrayString.find("]"); //finds ]
        arrayString = arrayString.substr(arrayLBracket+1, arrayRBracket-1); //creates a new string between [ and ]

        arrayVal = stoi(arrayString); //converts the data inside [ and ] into an int

        arrayValueRight.push_back(arrayVal); //pushes array value to right
      }
       else{ //if there is no array on the right

        isArrayRight.push_back(false); //pushes false state
        charString = line.substr(currentEqual+1, currentComma-2); //temp string to check for characters
        cout << charString << "THIS IS CHAR STRING" <<endl;
         //searches for 1-9//
        if((charString.find("1") || charString.find("2") || charString.find("3") || charString.find("4") || charString.find("5") || charString.find("6") || charString.find("7") || charString.find("8") || charString.find("9")) != string::npos){
          cout << charString << "charString Detected" << endl;
          isIntChar.push_back(true); //pushes true to isIntChar vector
          //intTemp = stoi(charString); //converts to integer
          //charValue.push_back(intTemp); //pushes integer onto charValue vector

        }
         else{
           isIntChar.push_back(false); //pushes false to isIntChar vector since no integer found
         }
       }//end else
      }
      else{


      if(line.substr(prevComma+1, currentEqual-1).find("[")!= string::npos){ //if there is an array on the left side
        cout <<"detected";
        isArrayLeft.push_back(true); //pushes true state to isArray

        arrayString = line.substr(prevComma+1, nextEqual-1); //creates a new string between start and =
        arrayLBracket = arrayString.find("["); //finds [
        arrayRBracket = arrayString.find("]"); //finds ]
        arrayString = arrayString.substr(arrayLBracket+1, arrayRBracket-1); //creates a new string between [ and ]

        arrayVal = stoi(arrayString); //converts the data inside [ and ] into an int

        arrayValueLeft.push_back(arrayVal);

      }
      else{ //if there is no array on the left
        isArrayLeft.push_back(false); //pushes false state
        cout << "Not detected" <<endl;
      }
      if(line.substr(currentEqual+1, currentComma-1).find("[") != string::npos){ //if there is an array on the right side

        isArrayRight.push_back(true); //pushes true state to isArrayRight
        arrayString = line.substr(currentEqual+1, currentComma-1); //creates a new string between = and ,
        arrayLBracket = arrayString.find("["); //finds [
        arrayRBracket = arrayString.find("]"); //finds ]
        arrayString = arrayString.substr(arrayLBracket+1, arrayRBracket-1); //creates a new string between [ and ]

        arrayVal = stoi(arrayString); //converts the data inside [ and ] into an int

        arrayValueRight.push_back(arrayVal); //pushes array value to right
      }
       else{ //if there is no array on the right

        isArrayRight.push_back(false); //pushes false state
        charString = line.substr(currentEqual+1, currentComma-2); //temp string to check for characters
        cout << charString << "THIS IS CHAR STRING" <<endl;
         //searches for 1-9//
        if((charString.find("1") || charString.find("2") || charString.find("3") || charString.find("4") || charString.find("5") || charString.find("6") || charString.find("7") || charString.find("8") || charString.find("9")) != string::npos){
          cout << charString << "charString Detected" << endl;
          isIntChar.push_back(true); //pushes true to isIntChar vector
          //intTemp = stoi(charString); //converts to integer
          //charValue.push_back(intTemp); //pushes integer onto charValue vector

        }
         else{
           isIntChar.push_back(false); //pushes false to isIntChar vector since no integer found
         }
       }//end else
      }
      if(varVecLeft.empty()){
        cout << currentEqual <<endl;
        varVecLeft.push_back(line.substr(0, currentEqual-1));
        varVecRight.push_back(line.substr(currentEqual+1, currentComma-2));

      }
      else{
      varVecLeft.push_back(line.substr(prevComma, currentEqual-1));
      varVecRight.push_back(line.substr(currentEqual+1, nextComma-1));
      }
      prevComma = currentComma;
      currentComma = nextComma; //updates comma
      currentEqual = nextEqual; //updates equal


    }//end for loop
    cout << "vecleft" <<endl;
    if(varVecLeft.size()==0){
      cout << "left empty";
    }
    else{
      cout << "left size: " << varVecLeft.size();
    }
    if(varVecRight.size()==0){
      cout <<"right empty";
    }
    for(int i = 0;i<varVecLeft.size();i++){
      cout << varVecLeft[i] << endl;
    }
    cout << "vecright" << endl;
    for(int i = 0; i<varVecRight.size();i++){
      cout << varVecRight[i] <<endl;
    }

}

void funct_call(string line,const vector<string> &v_code,int & line_cntr,function &funct)
{
	funct.assem_instrs.push_back("calling function " + line);
	line = v_code[line_cntr];
	return;
}

bool is_funct_dec(const string& line)
{
    if(line.find("int")<line.length() && line.find("(") <= line.length() )
    {
        return true;
    }
    else if( line.find("void")<line.length() && line.find("(") <= line.length() )
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

    ifstream in_code(argv[1], ifstream::in ); //open the file to read from
    ofstream out_code(argv[2], ifstream::out ); //open the assembly code file to write into
    string line;

    //write the preamble
    //out_code << preamble; // maybe should be part of funct handler
    vector<string> v_code;
    //put input into a vector of strings
    while( getline(in_code, line) ){
        string new_line = trim_tabs_spaces( line );
	if( new_line.length() ==0) continue;  //skip blank lines
	//out_code <<new_line<<"\n";   //debug uncoment to write output of vector to source code (debug)
	v_code.push_back(new_line);
    }
    in_code.close();
    //cout<<"v_code_size "<<v_code.size();
    int line_cntr = 0;
    function assem_instrs;
    while( line_cntr < v_code.size() ) //getline(in_code, line)) //iterate over every line in input file
    {
	//out_code<< v_code[line_cntr] <<"\n";  //debug
        //line = v_code[line_cntr];
        //cout<<"calling coarse_parse\n";
	coarse_parse(out_code, v_code, line_cntr, assem_instrs);
	line_cntr++;
    }

    //out_code.close();

    return 0;
}

