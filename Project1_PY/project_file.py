import argparse
import sys

class funct:
    def __init__(self):
        pass

    funct_list = []
    funct_name = ""

    variables = {}

    var_registers = ["movl  ${},  %edi","movl   ${},  %esi","movl   ${},  %edx","movl   ${},  %ecx","movl    ${},  %r8d","movl    ${},  r9d","pushq    ${}","pushq ${}","pushq  ${}"]
    assem_instrs = []
    arith_opers = ""
    mem_offset = 0
    ret_type = ""   #return type
    red_zone = False
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
def funct_dec(out_code, v_code, line_cntr, func):
    preamble = "\tpushq\t%rbp\n\tmovq\t%rsp, %rbp\n"
    epilogue =  "\tpopq\t%rbp\n\tret\n"


    line = v_code[line_cntr]
    print("funct dec ",line)
    func.ret_type = line.split(" ")[0]
    if func.ret_type == "void": # so we know if we need to deal with return variables
	    func.is_ret = False
    else:
        func.is_ret = True

    temp = line.split(" ")[1]
    #print(temp)
    func.funct_name = temp.split("(")[0]
    #print("funct name:    ", func.funct_name)
    func.funct_list.append(func.funct_name)
    line_cntr+=1  #go to the next line in the file
    line = v_code[line_cntr]
    while True:  # until the end of the function declaration
        if '}' in line and '{' not in line:

            break
        coarse_parse(out_code, v_code, line_cntr, func);
        line_cntr+=1
        line = v_code[line_cntr]
        print(line)
    #output the function call
    out_code.write(func.funct_name + ":\n")
    out_code.write(preamble)

    #for i in func.assem_instrs:
	#    out_code.write("\t" + i + "\n")

    if not func.is_leaf or func.mem_offset > 128:     #red zone thing
        out_code.write("\tsubq    $" + str(func.mem_offset)+",  %rsp")

    out_arr = []
    #print("AHSDFIHASLDFASLDFN ",func.funct_name," ",func.variables,"\n")
    for var in func.variables:
        i=0
        for val in func.variables[var]["vals"]:
            #arr_mem_offset.append(func.mem_offset)
            func.mem_offset += 4
            out_arr.insert(0, "\tmovel   ${},  {}(%rbp)\n".format(val, func.variables[var]["mem_loc"][i]))  # reverse the order of which they
            i+=1
    for line in out_arr:
        out_code.write(line)

    out_code.write( epilogue )
    func.variables.clear()
    #pop all variables from dictionary before returning
    func.mem_offset = 0
    return out_code, line_cntr

def arith_state(out_code, v_code, line_cntr, funct):
    line = v_code[line_cntr]
    print("arithmeticing")


    #for demo
    funct.assem_instrs.append(" move to reg ")


def var_dec(out_code, v_code, line_cntr, funct):
    """ types to worry about:
           undeclared ints a
           declared ints  a = 14
           declared int array a[3] = {1,2,3}"""

    print("variable declaration")
    print("saldfknalsdfn   ",funct.funct_name)
    line = v_code[line_cntr].rstrip(';\n')
    temp = line.split("int ")[1] #will always be int for our purposes
    #funct.__init__()
    #print("vars ", line)
    temp = temp.split(",")
    if '\n' in temp:
        temp.pop('\n')
    if ';' in temp:
        temp.pop(';')
    print("temp ",temp) #debug
    i = 0

    while i < len(temp):
        vals = []
        var = ""
        var_def = {}
        if '={' in temp[i]:  #found a declared array
            var =  temp[i].split('[')[0]
            vals.append( temp[i].split('={')[1] )
            i+=1
            funct.mem_offset-=4

            while '}' not in temp[i]:
                vals.append( int(temp[i]) )
                funct.mem_offset -= 4
                i+=1
            last_val = int(temp[i].split('}')[0])
            vals.append(last_val)

        elif '=' in temp[i]: #found a declared int
            #print("found declared int")  #debug
            var, val = temp[i].split('=')
            vals= [ (int(val)) ]
            funct.mem_offset -= 4
        else: #found an undeclared int
            var = temp[i]
            vars = []
            funct.mem_offset -= 4
        #add to a new dict
        var_def['vals'] = vals

        funct.variables[var] = var_def
        i+=1

    # associate variables to memory offsets
    temp = funct.mem_offset
    for var in funct.variables:
        arr_mem_offset = []
        if not funct.variables[var]["vals"]:   # none declared vars
            arr_mem_offset.append(funct.mem_offset)
            funct.mem_offset += 4
        for val in funct.variables[var]["vals"]:
            arr_mem_offset.append(funct.mem_offset)  #more neg to less neg
            funct.mem_offset += 4
        funct.variables[var]["mem_loc"] = arr_mem_offset
        #print("var ",var, funct.variables[var]["mem_loc"],"\n")
    funct.mem_offset = temp
    #print("is this working? ",funct.variables['a']['mem_loc'])


def funct_call(out_code, v_code, line_cntr, funct):
    line = v_code[line_cntr]
    funct.is_leaf = False
    print("function call ",line)

def if_state(out_code, v_code, line_cntr, funct):
    line = v_code[line_cntr]
    print("found an if state")

def for_loop(out_code, v_code, line_cntr, funct):
    line = v_code[line_cntr]
    print("found a for loop")

def return_state(out_code, v_code, line_cntr, funct):
    line = v_code[line_cntr]
    print("found a return state")


def coarse_parse(out_code, v_code, line_cntr, funct):
    line = v_code[line_cntr]
    #print(funct)
    # seach for a function call (loops through all the functions added to the list)
    if funct != None and funct.funct_list:
        for i in funct.funct_list :
            if i in line:
                #print("found a function call")
                funct_call(line, v_code, line_cntr, funct);

    # search for variable declarations
    if "int" in line and  ";" in line:
        #print("found a var dec" ) #; // debug)
        var_dec(line, v_code, line_cntr, funct);

    # search for if statements
    elif "if" in line:
        #print("found if statement")
        #out_code << "if_state\n";
        if_state(out_code, v_code, line_cntr, funct)

    elif "for" in line:
        #print("found for statement")
        #found for statement
        #out_code << "for state\n";
        for_loop(out_code, v_code, line_cntr, funct)

    elif "return" in line:
        #print("found return statement")
        #out_code << "return\n";
        return_state(out_code, v_code, line_cntr, funct)

    #look for function declarations
    elif is_funct_dec(line) == True:
        #print("found a funct dec\n") # debug
        out_code, line_cntr = funct_dec(out_code, v_code, line_cntr,funct);

    # found arithmetic instructions
    else:
        #print(("found arithmetic statement"))
        #cout << "arithmetic instr\n";
        arith_state(line, v_code, line_cntr, funct);

    return out_code, line_cntr

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
    func = funct()
    line_cntr = 0
    while(line_cntr < len(v_code) ):
        out_code, line_cntr = coarse_parse(out_code,v_code,line_cntr,func)
        line_cntr += 1

    out_code.close()

if __name__ == '__main__':
    main(sys.argv[1:])