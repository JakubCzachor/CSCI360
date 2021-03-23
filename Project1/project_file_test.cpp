/* Part of variable parsing */
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//variable declaration, sorting by commas //
//left side of equation is stored in varVecLeft, right side is stored in varVecRight. That way, we know varVecLeft[0] = varVecRight[0]
int countComma = 0;
for(int i=0; i<line.length();i++){
  if(line[i] == ','){
    countComma++;
  }
}
//Needs some testing, but much cleaner solution
vector<int> commaFindv;
vector<int> equalFindv;
vector<string> varVecRight;
vector<string> varVecLeft;
size_t currentComma = line.find(",");
int currentEqual = line.find("=");
size_t nextComma;
int nextEqual;

commaFindv.push_back(line.find(",")); //first comma
equalFindv.push_back(line.find("=")); //first equal sign.

for(int i = 0;i<countComma;i++){
if(commaFindv.size()<countComma){
  
  nextComma = line.find(",", currentComma);
  nextEqual = line.find("=", currentEqual);
  commaFindv.push_back(nextComma)
  varVecLeft.push_back(line.substr(currentComma+1, nextEqual-1));
  varVecRight.push_back(line.substr(nextEqual+1, nextComma-1));
  
  currentComma = nextComma; //updates comma
  currentEqual = nextEqual; //updates equal
  
  }
}
/*
int commaFind0 = line.find(",");
int equalFind0 = line.find("=");
int num_declared = 0;
if(commaFind0 != -1){
  size_t commaFind0_st = line.find(","); //size_t required for find function
  int equalFind1 = line.find("=", commaFind0_st); //searches for "=" after first ","
  num_declared++;
}
else{
  cout<<"no multiple variable declarations here";
}


int commaFind1 = line.find(",",commaFind0_st); //checks if more than 2 variables declared
if(commaFind1 != -1){
  num_declared++;
  size_t commaFind1_st = line.find(",",commaFind0_st); //size_t value
  int commaFind2 = line.find(",",commaFind1_st); //checks to see if more than 3 variables are declared.
  int equalFind2 = line.find("=", commaFind1_st); //finds place of third "="
  
  if(commaFind2 != -1){
    num_declared++;
    size_t commaFind2_st = line.find("=", commaFind1_st); //size_t value
    int commaFind3 = line.find(",", commaFind2_st); //checks to see if more than 4 variables are declared
    int equalFind3 = line.find("=", commaFind2_st); //finds place of fourth "="
    
    if(commaFind3 != -1){
      num_declared++; 
      size_t commaFind3_st = line.find("=", commaFind2_st); //size_t value
      int equalFind4 = line.find("=", commaFind3_st);
      if(line.find(",", commaFind3_st){
        cout << "Error, maximum of 5 variables are allowed in a single line";
    }
  }
} //other variable initializiation
cout << "Number of variables declared:" << num_declared << endl;
  
string var0_left; 
string var0_right;
string var1_left; 
string var1_right;
string var2_left;
string var2_right;
string var3_left;
string var3_right;
string var4_left;
string var4_right;

       
int lineEnd = line.find(";");
for(int i=0;i<line.size();i++){
  if(equalFind0 != -1 && commaFind0 != -1){ //if equal is present, and comma is also present, meaning x=x,b=c;
    
    var0_left = line.substr(0, equalFind0 -1); //0 to first equal sign
    var0_right = line.substr(equalFind0+1, commaFind0-1); //equal sign to first comma
    
    var1_left = line.substr(commaFind0+1, equalFind1-1); //first comma to equal sign
    
    if(commaFind1 != -1){ //checks to see if the second "," exists
      var1_right = line.substr(equalFind1+1, commaFind1-1); //second equal sign to second comma
     
      var2_left = line.substr(commaFind1+1, equalFind2-1); //second comma to third equal sign
                              
      if(commaFind2 != -1){ //checks to see if third "," exists
       var2_right = line.substr(equalFind2+1, commaFind2-1); //third equal sign to third comma
       
       var3_left = line.substr(commaFind2+1, equalFind3-1); //third comma to fourth equal sign
        
       if(commaFind3 != -1){//checks to see if fourth "," exists
        var3_right = line.substr(equalFind3+1, commaFind3-1); //fourth equal sign to fourth comma
          
        var4_left = line.substr(commaFind3+1, equalFind4-1);  //fourth comma to fifth equal sign
        var4_right = line.substr(equalFind4+1, lineEnd); //since num_declare <5, equal to line ned
       }
        else{ //no fourth "," - only 4 declarations
          
         var3_right = line.substr(equalFind3+1, lineEnd-1) //fourth equalsign to lineEnd
          
        }
     }
      else{ // no third "," - only 3 declarations
        var2_right = line.substr(equalFind2+1, lineEnd-1); //third equal sign to line end
      }
                               
    else{ //no second "," - only 2 declarations
       var1_right = line.substr(equalFind1+1, lineEnd-1); //second equal sign to line end
       
      
  }
  
}
  
*/
//Recursively//
/*
for(int i<

*/
    //Array Parsing//
/*

Check if any arrays in entire line:
T-> check each variable for [] -> allocate size if initialied for variable that is []
F -> Skip

Check if variable
T->if _right = any previous declared variables -> check map for previous variables and the correct parameter
F-> _right is an integer -> if integer then variable value is "$"+_right

*/

