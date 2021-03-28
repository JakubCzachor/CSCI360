#include <iostream>
#include <string>
#include <vector>
using namespace std;


bool isArrayCheck(string s){ //checks if input is array
  if(s.find("[")!= string::npos){ //if [ exists
    return true; //returns true
  }
  else{
    return false; //returns false
  }

}

bool isDigitCheck(string s){ //checks if digit
  if(s.find_first_not_of("0123456789") == std::string::npos){ //if it is a digit
    return true; //returns true
  }
  else{
    return false; //returns false
  }
}

int main(){

    string line  = "a,b=2,zaza[4]={1,2,3,4},g=321;" ;
    int countComma = 0;
    for(int i=0; i<line.length();i++){//loops through text
      if(line[i] == ','){ //checks for ','
        countComma++; //counts the number of commas
      }
    }

    vector<int> commaFindv;  //unused for now
    vector<int> equalFindv;  //unused for now

    vector<bool> isArrayLeft; //1 if arrayon left var, 0 if not
    vector<bool> isArrayRight; //1 if array on right var, 0 if not
    vector<bool> isIntCharLeft; //1 if left side is int, 0 if not
    vector<bool> isIntCharRight; //1 if right side is int, 0 if not

    vector<int> charValueLeft; //if not a char, the value will be -1
    vector<int> charValueRight; //if not a char, the value will be -1
    vector<int> arrayValueLeft; //if not an array, the value will be -1
    vector<int> arrayValueRight; //if not an array, the value will be -1

    int arrayVal;
    size_t arrayLBracket; //used to get pos of left side bracket
    size_t arrayRBracket; //used to get pos of the right side bracket
    int intTemp;

    int lineEnd = line.find(";"); //finds the end of line
    string arrayString;
    string charString;
    vector<string> varVecRight; //vector of right variables
    vector<string> varVecLeft; //vector of left variables

    size_t currentComma = line.find(","); //finds first comma
    size_t currentEqual = line.find("="); //finds first equal
    size_t nextComma; //initializes nextComma
    size_t nextEqual; //initializes nextEqual
    size_t prevComma = 0;
    size_t tempVal; //temporary variable to find range for substr function
    size_t tempValArray;
    tempVal = currentEqual-prevComma;  //sets original tempVal

    for(int i = 0;i<countComma+1;i++){

      nextEqual = line.find("=", currentComma+1); //finds next equal

      if(prevComma == 0){ //at start
         varVecLeft.push_back(line.substr(prevComma, tempVal)); //pushes left side to left vector
         isArrayLeft.push_back(isArrayCheck(line.substr(prevComma, tempVal))); //checks if variable is a vector
         isIntCharLeft.push_back(isDigitCheck(line.substr(prevComma, tempVal))); //checks if variable is aninteger


      if(isArrayCheck(line.substr(prevComma, tempVal)) == true){ //if left side start is an arrray
        arrayLBracket = line.find("["); //finds the left Bracket
        arrayRBracket = line.find("]"); //finds the right bracket
        tempValArray = arrayRBracket - arrayLBracket; //finds the distance between the two values
        arrayString = line.substr(arrayLBracket+1, tempValArray-1); //converts the numbers in the array brackets into a seperate string
        arrayValueLeft.push_back(stoi(arrayString)); //pushes the string to vector after converting to an integer
        charValueLeft.push_back(-1); //pushes -1 since if its a char, it isnt a
    /*
        //debugging
        cout << "Array L Bracket: " << arrayLBracket << endl;
        cout << "Array R Bracket: " << arrayRBracket << endl;
        cout << tempValArray<< endl;
        cout << arrayString << "ARRAY STRING" <<endl;
          cout << arrayValueLeft[0] <<"VECTOR STRING" <<endl;
        //end debugging
        */
      }

      else{ //if left side is not array
        arrayValueLeft.push_back(-1); //pushes -1 if it is not an array

        if(isDigitCheck(line.substr(prevComma, tempVal)) == true){ //checks to see if its an integer
        charValueLeft.push_back(stoi(line.substr(prevComma,tempVal))); //converts it into an int, pushes it onto charValueLeft.
        }//end if
        else{
          charValueLeft.push_back(-1); //pushes -1 to value instead.
        }
      }//end else


      //right side start//
      tempVal = (currentComma-currentEqual); //updates tempVal value for right side
      varVecRight.push_back(line.substr(currentEqual+1, tempVal-1)); //pushes right side to right vector
      isArrayRight.push_back(isArrayCheck(line.substr(currentEqual+1, tempVal-1))); //pushes if array, pushes to vector
      isIntCharRight.push_back(isDigitCheck(line.substr(currentEqual+1, tempVal-1))); //checks if integer, pushes to vector

      if(isArrayCheck(line.substr(currentEqual+1, tempVal)) == true){ //if right side is an array
        arrayLBracket = line.find("[",currentEqual+1); //finds the left Bracket
        arrayRBracket = line.find("]",currentEqual+1); //finds the right bracket
        tempValArray = arrayRBracket - arrayLBracket; //finds the distance between the two values
        arrayString = line.substr(arrayLBracket+1, tempValArray-1); //converts the numbers in the array brackets into a seperate string
        arrayValueRight.push_back(stoi(arrayString)); //pushes the string to vector after converting to an integer
        charValueRight.push_back(-1); //since its an array, it cannot be an integer.
        /*
        //debugging
        cout << "Array L Bracket: " << arrayLBracket << endl;
        cout << "Array R Bracket: " << arrayRBracket << endl;
        cout << tempValArray<< endl;
        cout << arrayString << "ARRAY STRING" <<endl;
          cout << arrayValueRight[0] <<"VECTOR STRING" <<endl;
        //end debugging
        */
       }//end if

       else{ //if not array
        arrayValueRight.push_back(-1); //pushes -1 if it is not an array

        if(isDigitCheck(line.substr(currentEqual+1, tempVal-1)) == 1){ //checks to see if its an integer
        charValueRight.push_back(stoi(line.substr(currentEqual+1,tempVal-1))); //converts it into an int, pushes it onto charValueLeft.
        }//end if

        else{//if not an integer
          charValueRight.push_back(-1); //pushes -1 to value instead.

      }//end else

       }//end else

      }//end if

      else{ //not at start

      //left side//
      tempVal = (currentEqual-prevComma); //updates tempval
      varVecLeft.push_back(line.substr(prevComma+1, tempVal-1)); //pushes left side to left
      isArrayLeft.push_back(isArrayCheck(line.substr(prevComma+1, tempVal-1))); //checks if variable is a vector
      isIntCharLeft.push_back(isDigitCheck(line.substr(prevComma+1, tempVal-1))); //checks if variable is aninteger

      if(isArrayCheck(line.substr(prevComma+1, tempVal)) == true){ //if left side is an array
        arrayLBracket = line.find("[",prevComma+1); //finds the left Bracket
        arrayRBracket = line.find("]",prevComma+1); //finds the right bracket
        tempValArray = arrayRBracket - arrayLBracket; //finds the distance between the two values
        arrayString = line.substr(arrayLBracket+1, tempValArray-1); //converts the numbers in the array brackets into a seperate string
        arrayValueLeft.push_back(stoi(arrayString)); //pushes the string to vector after converting to an integer
        charValueLeft.push_back(-1); //not an integer if an array
    /*
        //debugging
        cout << "Array L Bracket: " << arrayLBracket << endl;
        cout << "Array R Bracket: " << arrayRBracket << endl;
        cout << tempValArray<< endl;
        cout << arrayString << "ARRAY STRING" <<endl;
        cout << arrayValueLeft[1] <<"VECTOR STRING" <<endl;
        //end debugging
      */
      }//end if

      else{ //if left side is not array
        arrayValueLeft.push_back(-1); //pushes -1 if it is not an array
        if(isDigitCheck(line.substr(prevComma+1, tempVal-1)) == 1){ //checks to see if its an integer
        charValueLeft.push_back(stoi(line.substr(prevComma+1,tempVal-1))); //converts it into an int, pushes it onto charValueLeft.
        }//end if
        else{//if not an integer
          charValueLeft.push_back(-1); //pushes -1 to value instead.

      }//end else

      }//end else


      tempVal = (currentComma-currentEqual); //updates tempval for right side
      varVecRight.push_back(line.substr(currentEqual+1, tempVal-1)); //pushes right side to right vector
      isArrayRight.push_back(isArrayCheck(line.substr(currentEqual+1, tempVal-1))); //pushes if array, pushes to vector
      isIntCharRight.push_back(isDigitCheck(line.substr(currentEqual+1, tempVal-1))); //checks if integer, pushes to vector


      if(isArrayCheck(line.substr(currentEqual, tempVal)) == true){ //if right side is an array
        arrayLBracket = line.find("[",currentEqual); //finds the left Bracket
        arrayRBracket = line.find("]",currentEqual); //finds the right bracket
        tempValArray = arrayRBracket - arrayLBracket; //finds the distance between the two values
        arrayString = line.substr(arrayLBracket+1, tempValArray-1); //converts the numbers in the array brackets into a seperate string
        arrayValueRight.push_back(stoi(arrayString)); //pushes the string to vector after converting to an integer
        charValueRight.push_back(-1); //since its an array, cant be an integer

    /*
        //debugging
        cout << "Array L Bracket: " << arrayLBracket << endl;
        cout << "Array R Bracket: " << arrayRBracket << endl;
        cout << tempValArray<< endl;
        cout << arrayString << "ARRAY STRING" <<endl;
        cout << arrayValueRight[1] <<"VECTOR STRING" <<endl;
        //end debugging
      */
      }//end if

      else{ //if right side is not array
        arrayValueRight.push_back(-1); //pushes -1 if it is not an array

        if(isDigitCheck(line.substr(currentEqual+1, tempVal-1)) == 1){ //checks to see if its an integer
        charValueRight.push_back(stoi(line.substr(currentEqual+1,tempVal-1))); //converts it into an int, pushes it onto charValueLeft.
        }//end if
        else{//if not an integer
          charValueRight.push_back(-1); //pushes -1 to value instead.

       }//end else
      }//end else

      } //end else

      prevComma = currentComma; //moves prevComma to currentComma
      nextComma = line.find(",", currentComma+1); //finds next comma

      if(nextComma != string::npos){ //if next comma exists
        currentComma = nextComma; //set currentcomma to next comma
      } //end if
      else{
        currentComma = lineEnd; //if next comma DNE -> currentComma set to lineEnd
      } //end else

      currentEqual = nextEqual; //updates equal

    }//end for loop


    ///JUST FOR CHECKING CODE///
    cout <<"vecleft" <<endl;
    for(int i = 0;i<varVecLeft.size();i++){
     cout << "variable: " <<i <<" " << varVecLeft[i] << endl;
    }
    cout << "vecright" << endl;
    for(int i = 0; i<varVecRight.size();i++){
      cout << "variable: " <<i <<" " << varVecRight[i] <<endl;
    }
    cout <<"arraychecker left" << endl;
    for(int i =0; i<isArrayLeft.size(); i++){
      cout << "variable: " <<i <<" " <<  isArrayLeft[i] <<endl;
    }
    cout << "arraychecker right" <<endl;
    for(int i=0; i<isArrayRight.size(); i++){
      cout << "variable: " <<i <<" " <<  isArrayRight[i] <<endl;
    }
    cout << "digit checker" <<endl;
    for(int i=0; i<isIntCharLeft.size();i++){
      cout << "variable: " <<i <<" " << isIntCharLeft[i] <<endl;
    }
    cout <<" digit checker right" << endl;
    for(int i=0; i<isIntCharRight.size();i++){
      cout << "variable: " <<i <<" " << isIntCharRight[i] << endl;
    }

    cout << "Array Values Left"<<endl;
    for(int i=0; i<arrayValueLeft.size();i++){
      cout << "variable: " <<i <<" " << arrayValueLeft[i] << endl;
    }

    cout << "array Values Right" << endl;
    for(int i=0; i<arrayValueRight.size();i++){
      cout << "variable: " <<i <<" " << arrayValueRight[i] << endl;
    }
    cout <<"char Value Left " << endl;
    for(int i=0;i<charValueLeft.size();i++){
      cout <<"variable: "<< i << " " << charValueLeft[i] <<endl;
    }
    cout <<"char value right: "<< endl;
    for(int i =0; i<charValueRight.size();i++){
      cout <<"variable: "<< i<< " "<< charValueRight[i] << endl;
    }
}
