import argparse
import sys

class funct:
    def __init__(self):
        pass
    funct_list = ["thing"]
    funct_name = ""
    variables = {}
    var_registers = ["%edi","%esi","%edx","%ecx","%r8d","%r9d"]
    assem_instrs = []
    arith_opers = ""
    ret_type = ""   #return type
    is_ret = False
    is_leaf = True

def is_funct_dec(line):
    if "int" in line and "(" in line:
        return True
    elif "void" in line and "(" in line:
        return True
    elif "string" in line and "(" in line:
        return True
    elif "bool" in line and "(" in line:
        return True
    else:
        return False
def funct_dec(out_code, v_code, line_cntr, functs):
    preamble = "\tpushq\t%rbp\n\tmoveq\t%rsp, %rbp\n"
    epilogue =  "\tpopq\t%rbp\n\tret\n"

    #function funct
    line = v_code[line_cntr]
    funct.ret_type = line.split(" ")[0]
    if funct.ret_type == "void": # so we know if we need to deal with return variables
	    funct.is_ret = True
    else:
        funct.is_ret = False

    temp = line.split(" ")[1]
    print(temp)
    funct.funct_name = temp.split("(")[0]
    funct.funct_list.append(funct.funct_name)
    #funct.is_leaf = True; #not calling any more functions
    line_cntr+=1  #go to the next line in the file
    line = v_code[line_cntr]
    while '}' not in line: #until the end of the function declaration
	    #cout<<"line leng  "<<line.length()<<" line find"<<line.find('}')<<"\n"; //debug
	    coarse_parse(out_code, v_code, line_cntr, funct);
	    line_cntr+=1
	    #cout<<"cntr  "<<cntr<<"\n"; //debug
	    line = v_code[line_cntr]

    out_code.write(funct.funct_name + ":\n")
    out_code.write(preamble)
    for i in funct.assem_instrs:
	    out_code.write("\t" + i + "\n")

    out_code.write( epilogue )
    return out_code

def arith_state(out_code, v_code, line_cntr, functs):
    line = v_code[line_cntr]
    print("arithmeticing")
    functs.assem_instrs.append(" move to reg ")

def var_dec(out_code, v_code, line_cntr, functs):
    """ types to worry about:
           undeclared ints a
           declared ints  a = 14
           declared int array a[3] = {1,2,3}"""
    line = v_code[line_cntr].rstrip(';\n')
    temp = line.split("int ")[1] #will always be int for our purposes
    #print("vars ", line)
    temp = temp.split(",")
    if '\n' in temp:
        temp.pop('\n')
    if ';' in temp:
        temp.pop(';')
    print("temp ",temp)
    var = ""
    vals = []
    i = 0
    while i < len(temp):
        if '={' in temp[i]:  #found a declared array
            var =  temp[i].split('[')[0]
            val1 = temp[i].split('={')[1]
            functs.variables[var] = [int(val1)]
            i+=1
            while '}' not in temp[i]:
                functs.variables[var].append( int(temp[i]) )
                i+=1
            last_val = int(temp[i].split('}')[0])
            functs.variables[var].append(last_val)
            var = ""

        elif '=' in temp[i]: #found a declared int
            print("found declared int")
            var, val = temp[i].split('=')
            functs.variables[var] = [int(val)]

        else: #found an undeclared int
            var = temp[i]
            functs.variables[var] = []
        i+=1
    print(functs.variables)



def funct_call(out_code, v_code, line_cntr, functs):
    line = v_code[line_cntr]
    print("function call ",line)

def if_state(out_code, v_code, line_cntr, functs):
    line = v_code[line_cntr]
    print("found an if state")

def for_loop(out_code, v_code, line_cntr, functs):
    line = v_code[line_cntr]
    print("found a for loop")

def return_state(out_code, v_code, line_cntr, functs):
    line = v_code[line_cntr]
    print("found a return state")


def coarse_parse(out_code, v_code, line_cntr, functs):
    line = v_code[line_cntr]
    #print(line)
    # seach for a function call (loops through all the functions added to the list)
    if functs.funct_list:
        for i in functs.funct_list :
            if i in line:
                #print("found a function call")
                funct_call(line, v_code, line_cntr, functs);

    # search for variable declarations
    if "int" in line and  ";" in line:
        #print("found a var dec" ) #; // debug)
        var_dec(line, v_code, line_cntr, functs);

    # search for if statements
    elif "if" in line:
        #print("found if statement")
        #out_code << "if_state\n";
        if_state(out_code, v_code, line_cntr, functs)

    elif "for" in line:
        #print("found for statement")
        #found for statement
        #out_code << "for state\n";
        for_loop(out_code, v_code, line_cntr, functs)

    elif "return" in line:
        #print("found return statement")
        #out_code << "return\n";
        return_state(out_code, v_code, line_cntr, functs)

    #look for function declarations
    elif is_funct_dec(line) == True:
        #print("found a funct dec\n") # debug
        funct_dec(out_code, v_code, line_cntr, functs);

    # found arithmetic instructions
    else:
        #print(("found arithmetic statement"))
        #cout << "arithmetic instr\n";
        arith_state(line, v_code, line_cntr, functs);

    return out_code

def main(argv):
    #print(argv)

    if len(argv) < 2:
        print("incorrect number of input arguments, 2 required: input and output files\n")
        return
    v_code = []      # make a list of all the lines of c-code
    with open(argv[0]) as f:
        for line in f:
            if line == "\n":    # remove empty lines
                continue
            nl = line.lstrip()  #strip off leading spaces and tabs
            nl.rstrip()
            v_code.append(nl)
    out_code = open(argv[1],'w')

    #for i in v_code: print(i)
    functs = funct()
    line_cntr = 0
    while(line_cntr < len(v_code) ):
        coarse_parse(out_code,v_code,line_cntr,functs)
        line_cntr += 1

    out_code.close()

if __name__ == '__main__':
    main(sys.argv[1:])