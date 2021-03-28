void var_dec(string line,const vector<string> &v_code,int & line_cntr,function &funct)
{
    line = line.substr(line.find(' ')+1, line.length()-1); //remove the "int" and ";"

    string var="";
    int value;
    vector<int> values;  // list of the values
    int i=0;
    while( i < line.length()-1)
    {
        //cout<<line[i]<<endl; //debug
        if( isalpha( line[i] ))
        {
            while(isalpha( line[i] ) )
            {
                cout<<line[i];
                var= var+line[i] ;
                i++;
                cout<<i;
            }
        }
        cout<<"var "<<var<<" "<<line[i];
        while( line[i] == ' '){ i++; }//skip spaces
        if( line[i] == '[')
        {
            while(line[i] != ']'){
                i++;
            }
            i++;
        }
        if( line[i] == '='){   //declared int

           i++;
           if( isdigit( line[i]  )){ //ints
              cout<<"found digit "<<line[i];
              value = (int)(line[i]-48);
              i++;
              while( isdigit( (int)(line[i]) )){
                  value = 10*value + (int)(line[i])-48;
                  i++;
              }
              values.push_back(value);
              cout<<value<<" ";
            }
            else if( line[i] == '{' ){ //arrays
               while(line[i] != '}'){
                  i++;
                  if( isdigit( line[i] )){
                     value = (int)(line[i]-48);
                     i++;
                     while( isdigit( line[i] )){
                        value = 10*value + (int)(line[i])-48;
                        i++;
                     }
                     values.push_back(value);
                     cout<<value<<" ";
                  }
               }
            }
        }
        i++;
        cout<<'\n';
        // "," are skipped undeclared variables are automatically added
        funct.var_dec[var] = values;
        var = "";
        values.clear();

    }
        //now write to the registers if variables are declared
    for ( const auto &var : funct.var_dec ) {
        cout << var.first;
        for (const auto &vals : funct.var_dec[var.first] ){
            cout<<" "<< vals;
        }
        cout<<"\n";
    }
}
