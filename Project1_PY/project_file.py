import argparse
import sys

class funct:
    def __init__(self):
        pass

    funct_list = []
    funct_name = ""
    funct_call =[]
    variables = {}

    var_registers = ["movl  ${},  %edi","movl   ${},  %esi","movl   ${},  %edx","movl   ${},  %ecx","movl    ${},  %r8d","movl    ${},  r9d","pushq    ${}","pushq ${}","pushq  ${}"]
    assem_instrs = []
    arith_opers = ""
    mem_offset = -8
    ret_type = ""   #return type
    red_zone = False
    is_ret = False
    is_leaf = True
    ifForCounter = 1;
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



    if not func.is_leaf or func.mem_offset > 128:     #red zone thing
        out_code.write("\tsubq    $" + str(func.mem_offset)+",  %rsp")

    out_arr = []
    #print("AHSDFIHASLDFASLDFN ",func.funct_name," ",func.variables,"\n")
    for var in func.variables:
        i=0
        for val in func.variables[var]["vals"]:
            #arr_mem_offset.append(func.mem_offset)
            func.mem_offset += 4
            out_arr.insert(0, "\tmovl   ${},  {}(%rbp)\n".format(val, func.variables[var]["mem_loc"][i]))  # reverse the order of which they
            i+=1
    for line in out_arr:
        out_code.write(line)
    for i in func.assem_instrs:
        out_code.write("\t" + i + "\n")
    out_code.write( epilogue )
    func.variables.clear()
    #pop all variables from dictionary before returning
    func.mem_offset = 0
    return out_code, line_cntr

def arith_state(out_code, v_code, line_cntr, functs):
    line = v_code[line_cntr]
    equalFind = line.find("=")
    lineEnd = line.find(";")
    if (equalFind !=-1): ##checks to make sure that there is an equal sign in the equation
        #print(line_cntr, "THIS IS THE LINE WERE IN") #debug

        if(line.find("*")!=-1):
            #print("Multiplication \n")
            multFind = line.find("*")
            tempString = line[:equalFind] #finds string to equal sign (first variable)
            tempString2 = line[equalFind+1:multFind] #finds second variable
            tempString3 = line[multFind+1:lineEnd] #finds third variable

            if(tempString.find("[") !=-1): #there is an array in tempString
                tempNumArray = int(tempString[tempString.find("[")+1: tempString.find("]")])
            else:
                tempNumArray = 0
            if(tempString2.find("[")!= -1):
                tempNumArray2 = int(tempString2[tempString2.find("[")+1: tempString2.find("]")])
            else: tempNumArray2 = 0
            if(tempString3.find("[") != -1):
                tempNumArray3 = int(tempString3[tempString3.find("[")+1: tempString3.find("]")])
            else:
                tempNumArray3 = 0

            mem_offset_of_tempString = funct.variables[tempString]["mem_loc"][tempNumArray]
            mem_offset_of_tempString2 = funct.variables[tempString2]["mem_loc"][tempNumArray2]
            mem_offset_of_tempString3 = funct.variables[tempString3]["mem_loc"][tempNumArray3]

            AppendString = "movl "+str(mem_offset_of_tempString3)+"(%rbp), %eax"

            functs.assem_instrs.append(AppendString)
            AppendString = "imull " + str(mem_offset_of_tempString2) + "(%rbp), %eax"

            functs.assem_instrs.append(AppendString)
            AppendString = "movl %eax, "+str(mem_offset_of_tempString) +"(%rbp)"

            functs.assem_instrs.append(AppendString)

            #print("String 1", tempString, " String 2", tempString2, " String 3", tempString3)

        elif(line.find("/")!=-1):
            #print("division detected on line", line_cntr," ", line)
            divFind = line.find("/")
            tempString = line[:equalFind] #finds first variable
            tempString2 = line[equalFind+1:divFind] #finds  second variable
            tempString3 = line[divFind+1:lineEnd] #finds third variable

            if(tempString.find("[") !=-1): #there is an array in tempString
                tempNumArray = int(tempString[tempString.find("[")+1: tempString.find("]")])
            else:
                tempNumArray = 0
            if(tempString2.find("[")!= -1):
                tempNumArray2 = int(tempString2[tempString2.find("[")+1: tempString2.find("]")])
            else:
                tempNumArray2 = 0
            if(tempString3.find("[") != -1):
                tempNumArray3 = int(tempString3[tempString3.find("[")+1: tempString3.find("]")])
            else:
                tempNumArray3 = 0

            mem_offset_of_tempString = funct.variables[tempString]["mem_loc"][tempNumArray]
            mem_offset_of_tempString2 = funct.variables[tempString2]["mem_loc"][tempNumArray2]
            mem_offset_of_tempString3 = funct.variables[tempString3]["mem_loc"][tempNumArray3]

            AppendString = "movl "+ str(mem_offset_of_tempString2)+"(%rbp), %eax"

            functs.assem_instrs.append(AppendString)
            AppendString = "cltd"

            functs.assem_instrs.append(AppendString)
            AppendString = "idivl " + str(mem_offset_of_tempString3)+"(%rbp)"

            functs.assem_instrs.append(AppendString)
            AppendString = "movl %eax, "+ str(mem_offset_of_tempString) + "(%rbp)"

            functs.assem_instrs.append(AppendString)
            #print("String 1", tempString, " String 2", tempString2, " String 3", tempString3)

        elif(line.find("+")!=-1 and (line.find("++") ==-1)): #checks to see if addition, and not increment
            plusFind = line.find("+") #finds + sign
            tempString = line[:equalFind] #first variable
            tempString2 = line[equalFind+1:plusFind] #second variable
            tempString3 = line[plusFind+1:lineEnd] #third variable

            if(tempString.find("[") !=-1): #there is an array in tempString
                tempNumArray = int(tempString[tempString.find("[")+1: tempString.find("]")])
            else:
                tempNumArray = 0
            if(tempString2.find("[")!= -1):
                tempNumArray2 = int(tempString2[tempString2.find("[")+1: tempString2.find("]")])
            else:
                tempNumArray2 = 0
            if(tempString3.find("[") != -1):
                tempNumArray3 = int(tempString3[tempString3.find("[")+1: tempString3.find("]")])
            else:
                tempNumArray3 = 0

            mem_offset_of_tempString = funct.variables[tempString]["mem_loc"][tempNumArray]
            mem_offset_of_tempString2 = funct.variables[tempString2]["mem_loc"][tempNumArray2]
            mem_offset_of_tempString3 = funct.variables[tempString3]["mem_loc"][tempNumArray3]

            if((tempString==tempString2) or (tempString==tempString3)): #x=x+a
                #print("equal addition")
                if(tempString == tempString2): #checks to see if x=x+a
                    AppendString = "movl " + str(mem_offset_of_tempString3)  +"(%rbp),  %eax"


                else: #checks to see if x=a+x
                    AppendString = "movl " +str(mem_offset_of_tempString2) +  "(%rbp), %eax"

                functs.assem_instrs.append(AppendString)

                AppendString = "addl %eax, " + str(mem_offset_of_tempString) +"(%rbp)"
                functs.assem_instrs.append(AppendString)


            else:   #x=z+a

                AppendString = "movl "+ str(mem_offset_of_tempString3) + "(%rbp), %edx"
                functs.assem_instrs.append(AppendString)

                AppendString = "movl "+ str(mem_offset_of_tempString2) + "(%rbp), %eax"
                functs.assem_instrs.append(AppendString)

                AppendString = "addl %edx, %eax"
                functs.assem_instrs.append(AppendString)

                AppendString = "movl "+ str(mem_offset_of_tempString) + "(%rbp)"
                functs.assem_instrs.append(AppendString)


            #print("String 1", tempString, " String 2", tempString2, " String 3", tempString3)

        elif(line.find("-")!=-1): #if subtraction
            subFind = line.find("-") #finds location of minus sign
            tempString = line[:equalFind] #first variable
            tempString2 = line[equalFind+1:subFind] #second variable
            tempString3 = line[subFind+1:lineEnd] #third variable

            if((tempString3.isnumeric() == 1) and (tempString2 == tempString)): #if x=x-5

                tempNum = int(tempString3) #changes third variable into a number
                mem_offset_of_tempString = 1 #placeholder funct.variables[tempString]["mem_loc"][0]
                AppendString = "subl $", str(tempNum)+ ", "+str(mem_offset_of_tempString)+ "(%rbp)"

                functs.assem_instrs.append(AppendString)

            elif((tempString3.isnumeric() == 1) and (tempString2 != tempString)): #if x=b-5

                if(tempString.find("[") !=-1): #there is an array in tempString
                    tempNumArray = int(tempString[tempString.find("[")+1: tempString.find("]")])
                    tempString = tempString[:tempString.find("[")]
                else:
                    tempNumArray = 0
                if(tempString2.find("[")!= -1):
                    tempNumArray2 = int(tempString2[tempString2.find("[")+1: tempString2.find("]")])
                    tempString2 = tempString2[:tempString2.find("[")]
                else:
                    tempNumArray2 = 0

                mem_offset_of_tempString = funct.variables[tempString]["mem_loc"][tempNumArray]
                mem_offset_of_tempString2 = funct.variables[tempString2]["mem_loc"][tempNumArray2]

                tempNum = int(tempString3) #changes third variable into a number
                AppendString = "movl "+ str(mem_offset_of_tempString2)+"(%rbp), %eax"
                functs.assem_instrs.append(AppendString)
                AppendString = "subl $"+ tempString3 + " %eax"
                functs.assem_instrs.append(AppendString)
                AppendString = "movel %eax, "+ str(mem_offset_of_tempString) + "(%rbp)"
                functs.assem_instrs.append(AppendString)

            else:#neither is is numeric
                if(tempString.find("[") !=-1): #there is an array in tempString
                    tempNumArray = int(tempString[tempString.find("[")+1: tempString.find("]")])
                    tempString = tempString[:tempString.find("[")]
                    print("ARRAYYY DETECTED IN SUBTRACTION")
                else:
                    tempNumArray = 0
                if(tempString2.find("[")!= -1):
                    tempNumArray2 = int(tempString2[tempString2.find("[")+1: tempString2.find("]")])
                    tempString2 = tempString2[:tempString2.find("[")]
                else: tempNumArray2 = 0
                if(tempString3.find("[") != -1):
                    tempNumArray3 = int(tempString3[tempString3.find("[")+1: tempString3.find("]")])
                    tempString3 = tempString3[:tempString3.find("[")]
                else:
                    tempNumArray3 = 0

                mem_offset_of_tempString = funct.variables[tempString]["mem_loc"][tempNumArray]
                mem_offset_of_tempString2 = funct.variables[tempString2]["mem_loc"][tempNumArray2]
                mem_offset_of_tempString3 = funct.variables[tempString3]["mem_loc"][tempNumArray3]

                AppendString = "movl "+str(mem_offset_of_tempString2)+ "(%rbp, %eax)"
                functs.assem_instrs.append(AppendString)
                AppendString = "subl "+str(mem_offset_of_tempString3)+"(%rbp, %eax)"
                functs.assem_instrs.append(AppendString)
                AppendString ="movl %eax, "+str(mem_offset_of_tempString)+"(%rbp)"
                functs.assem_instrs.append(AppendString)


        elif(line.find("++")!=-1):
            incrFind = line.find("++") #finds increment
            tempString = line[:incrFind] #variable that is going to be incremented
            if(tempString.find("[") !=-1): #there is an array in tempString
                tempNumArray = int(tempString[tempString.find("[")+1: tempString.find("]")])
                tempString = tempString[:tempString.find("[")]
            else:
                tempNumArray = 0

            mem_offset_of_tempString = funct.variables[tempString]["mem_loc"][tempNumArray]
            AppendString ="addl $1, "+ str(mem_offset_of_tempString) + "(%rbp)"
            functs.assem_instrs.append(AppendString)

        else: #direct x=y
            if(equalFind != -1): #double check that there is an equal sign
                tempString = line[:equalFind] #first variable
                tempString2 = line[equalFind+1:lineEnd] #second variable
                if(tempString.find("[") !=-1): #there is an array in tempString
                    tempNumArray = int(tempString[tempString.find("[")+1: tempString.find("]")])
                    tempString = tempString[:tempString.find("[")]
                else:
                    tempNumArray = 0
                mem_offset_of_tempString = functs.variables[tempString]["mem_loc"][tempNumArray] #placeholder


                if(tempString2.isnumeric() == 1): #x=5 for example
                    tempNum = int(tempString2)

                    AppendString = "movl $"+tempString2+ " "+str(mem_offset_of_tempString)+"(%rbp)"
                    functs.assem_instrs.append(AppendString)
                else: #x=b, b is not numeric
                    if(tempString2.find("[") !=-1): #there is an array in tempString
                        tempNumArray2 = int(tempString2[tempString2.find("[")+1: tempString2.find("]")])
                        tempString2 = tempString2[:tempString2.find("[")]
                    else:
                        tempNumArray2 = 0
                    mem_offset_of_tempString2 = funct.variables[tempString2]["mem_loc"][tempNumArray2] #gets memory offset of tempString2
                    AppendString = "movl "+ str(mem_offset_of_tempString2)+ "(%rpb), %eax"
                    functs.assem_instrs.append(AppendString)
                    AppendString = "movl %eax, "+ str(mem_offset_of_tempString)+ "(%rbp)"
                    functs.assem_instrs.append(AppendString)

def var_dec(out_code, v_code, line_cntr, funct):
    """ types to worry about:
           undeclared ints a
           declared ints  a = 14
           declared int array a[3] = {1,2,3}"""


    print("variable declaration")
    print("saldfknalsdfn   ",funct.funct_name)
    line = v_code[line_cntr].rstrip(';\n')
    temp = line.split("int ")[1] #will always be int for our purposes
    temp = temp.split(",")
    if '\n' in temp:
        temp.pop('\n')
    if ';' in temp:
        temp.pop(';')
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
    funct.mem_offset = temp



def funct_call(out_code, v_code, line_cntr, funct):
    line = v_code[line_cntr]
    funct.is_leaf = False
    print("function call ",line)

def if_state(out_code, v_code, line_cntr, funct):
    funct.ifForCounter=funct.ifForCounter+1
    line = v_code[line_cntr]
    parenStart =line.find("(") #finds first parent
    parenEnd = line.find(")") #finds second parentheses

    if(line.find("<", parenStart, parenEnd) != -1 ):
        compareFind = line.find("<")
        tempString = line[parenStart+1:compareFind]
        tempString2 = line[compareFind+1:parenEnd]
        if(tempString.find("[") !=-1): #there is an array in tempString
            tempNumArray = int(tempString[tempString.find("[")+1: tempString.find("]")])
            tempString = tempString[:tempString.find("[")]
        else:
            tempNumArray = 0
        mem_offset_of_tempString = funct.variables[tempString]["mem_loc"][tempNumArray]

        if(tempString2.isnumeric()==1):
            tempNum = int(tempString2)
            AppendString = "cmpl $" + str(mem_offset_of_tempString) + "(%rbp)"

            funct.assem_instrs.append(AppendString)
            AppendString = "jg .L"+ str(funct.ifForCounter)
            funct.assem_instrs.append(AppendString)
            AppendString = "movl $" + str(mem_offset_of_tempString) + "(%rbp)"
            funct.assem_instrs.append(AppendString)


            AppendString = "L"+ str(funct.ifForCounter) +":"
            funct.assem_instrs.append(AppendString)
        else:#no numbers in if statements
            if(tempString2.find("[") !=-1): #there is an array in tempString
                tempNumArray2 = int(tempString2[tempString2.find("[")+1: tempString2.find("]")])
                tempString2 = tempString2[:tempString2.find("[")]
            else:
                tempNumArray2 = 0
            mem_offset_of_tempString2 = funct.variables[tempString2]["mem_loc"][tempNumArray2]
            AppendString = "movl " + str(mem_offset_of_tempString2) +"(%rbp), %eax"
            funct.assem_instrs.append(AppendString)
            AppendString = "cmpl " + str(mem_offset_of_tempString) +"(%rbp), %eax"
            funct.assem_instrs.append(AppendString)
            AppendString = "jge .L" + str(funct.ifForCounter)
            funct.assem_instrs.append(AppendString)

        AppendString = "L"+ str(funct.isForCounter) + ": "
        funct.assem_instrs.append(AppendString)



    elif(line.find(">", parenStart, parenEnd) != -1):

        compareFind = line.find(">")
        tempString = line[parenStart+1:compareFind]
        tempString2 = line[compareFind+1:parenEnd]
        if(tempString.find("[") !=-1): #there is an array in tempString
            tempNumArray = int(tempString[tempString.find("[")+1: tempString.find("]")])
            tempString = tempString[:tempString.find("[")]
        else:
            tempNumArray = 0
        mem_offset_of_tempString = funct.variables[tempString]["mem_loc"][tempNumArray]

        if(tempString2.isnumeric()==1):
            tempNum = int(tempString2)
            AppendString = "cmpl $" + str(mem_offset_of_tempString) + "(%rbp)"

            funct.assem_instrs.append(AppendString)
            AppendString = "jle .L"+ str(funct.ifForCounter)
            funct.assem_instrs.append(AppendString)
            AppendString = "movl $" + str(mem_offset_of_tempString) + "(%rbp)"
            funct.assem_instrs.append(AppendString)


            AppendString = "L"+ str(funct.ifForCounter) +":"
            funct.assem_instrs.append(AppendString)
        else:#no numbers in if statements
            if(tempString2.find("[") !=-1): #there is an array in tempString
                tempNumArray2 = int(tempString2[tempString2.find("[")+1: tempString2.find("]")])
                tempString2 = tempString2[:tempString2.find("[")]
            else:
                tempNumArray2 = 0
            mem_offset_of_tempString2 = funct.variables[tempString2]["mem_loc"][tempNumArray2]
            AppendString = "movl " + str(mem_offset_of_tempString2) +"(%rbp), %eax"
            funct.assem_instrs.append(AppendString)
            AppendString = "cmpl " + str(mem_offset_of_tempString) +"(%rbp), %eax"
            funct.assem_instrs.append(AppendString)
            AppendString = "jle .L" + str(funct.ifForCounter)
            funct.assem_instrs.append(AppendString)

    print("found an if state")

def for_loop(out_code, v_code, line_cntr, funct):
    funct.ifForCounter+=1
    line = v_code[line_cntr]
    findEqual=line.find("=")
    firstColon = line.find(";")
    secondColon = line.find(";",firstColon+1, len(line)) #finds second firstColon
    endLineLoop = line.find(")")
    if(line.find("<")):
        findCompare = line.find("<")
    if(line.find(">")):
        findCompare = line.find(">")
    findINT =line.find("int")
    tempString = line[findINT+3:findEqual] #int i
    tempString2 = line[findEqual+1:firstColon] # 5 in int i =5
    tempString3 = line[firstColon+1:findCompare] #i in i<8
    tempString4 = line[findCompare+1:secondColon] #8 in i<8
    tempString5 = line[secondColon+1:endLineLoop] #i++
    mem_offset_of_tempString = funct.variables[tempString]["mem_loc"][tempNumArray]
    if(tempString2.isnumeric() == 1): #if i=5
        tempNum2 = int(tempString2)
        AppendString  = "movl $" + tempNum2  + ", " + mem_offset_of_tempString +"(%rbp)"
        AppendString  = "jmp .L" +str(funct.ifForCounter)
        funct.ifForCounter+=1
        AppendString = "L" + str(funct.ifForCounter)+":"
    else:
        if(tempString2.find("[") == 1): #if i=b[x]
            tempStringArray2 = tempString2[:tempString2.find("[")]
            tempNumArray2 = int(tempString2[tempString2.find("[")+1:tempString2.find("]")])
        else:#if i=b
            tempNumArray2 = 0
        mem_offset_of_tempString2 = funct.variables[tempString2]["mem_loc"][tempNumArray2]
    if(tempString == tempString3):
        if(tempString4.isnumeric()==1):
            tempNum4 = int(tempString4)
        else:
            if(tempString4.find("[") == 1): #if i<b[x]
                tempStringArray4 = tempString4[:tempString4.find("[")]
                tempNumArray4 = int(tempString4[tempString4.find("[")+1:tempString4.find("]")])
            else:#if i<b
                tempNumArray4 = 0
            mem_offset_of_tempString4 = funct.variables[tempString2]["mem_loc"][tempNumArray2]
    if(tempString5 == tempString1+"++"):
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
    elif '}' in line and '{' not in line:
        pass
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
