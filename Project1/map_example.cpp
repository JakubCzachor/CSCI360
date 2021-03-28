
#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main(void){
   map< string, vector<string>> var_to_mem;
   vector<double> nan_test;
   nan_test.reserve(10);   
   vector<string> regs1{"-4(%rbp)"};
   vector<string> regs2{"-8(%rbp)","-12(%rbp)"};
   vector<string> regs3;
   
   var_to_mem["var1"] = regs1;
   var_to_mem["arr1"] = regs2;
   var_to_mem["undec_var"] = regs3;

   //accessing the variable registers 
   cout<<"var1 "<<var_to_mem["var1"][0]<<"\n";
   cout<<"arr2[1] "<<var_to_mem["arr1"][1]<<"\n";
   cout<<"nan test "<<nan_test[5]<<"\n";
}
