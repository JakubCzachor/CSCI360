/* Part of variable parsing */
#include <iostream>
#include <vector>
#include <string>
using namespace std;
//variable declaration, sorting by commas //
//left side of equation is stored in varVecLeft, right side is stored in varVecRight. That way, we know varVecLeft[0] = varVecRight[0]
// isArrayLeft[i] matches up with varVecLeft, isArrayRight[i] matches up with varVecRight
// isIntChar checks the right side of equation for each declaration, matches up with isArrayRight[i] and varVecRight[i]
// If isArrayLeft is true, then the value is stored in order on arrayValueLeft, same with isArrayRight, and isIntChar -> arrayValueRight, charValue.



string line  = "x=b,x=c;" ;
int countComma = 0;
for(int i=0; i<line.length();i++){
  if(line[i] == ','){
    countComma++;
  }
}
cout << "countComma count: " << countComma << endl;
//Needs some testing, but much cleaner solution

vector<int> commaFindv;
vector<int> equalFindv;
vector<bool> isArrayLeft;
vector<bool> isArrayRight;
vector<bool> isIntChar;
vector<int> charValue;
vector<int> arrayValueLeft;
vector<int> arrayValueRight;


int arrayVal;
int arrayLBracket;
int arrayRBracket;
int intTemp;
int lineEnd = line.find(";");
string arrayString;
string charString;
vector<string> varVecRight;
vector<string> varVecLeft;

size_t currentComma = line.find(",");
int currentEqual = line.find("=");
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

