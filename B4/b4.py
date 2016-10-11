from sys import argv

mp = {}
list_statement = []
replace = {}
not_used = []

class ExternalNode():
	variable_identifier = ''
	def __init__(self, identifier):
		self.variable_identifier = identifier


class InternalNode():
	variable_identifier = ''
	operator_value = ''
	lchild = None
	rchild = None
	def __init__(self, val, l, r, id):
		self.operator_value = val	
		self.lchild = l
		self.rchild = r
		self.variable_identifier = id

def read_input(file_name):
	file_var = open(file_name, 'r').read().strip().split("\n")
	for line in file_var:
		if len(line)>=6 and line[:6] == "return":	
			break
		line = line.split(":=")
		value = line[0].strip()

		line [1] = line[1].strip().split(" ")
		first = line[1][0]
		operator = line[1][1]
		second = line[1][2]


		if (operator == '=') or (not first in mp):
			temp_var = ExternalNode(first)
			mp[first] = temp_var
			replace[first] = first
		if not second in mp:
			temp_var = ExternalNode(second)
			mp[second] = temp_var
			replace[second] = second

		list_statement.append(value)
		var = InternalNode(operator, mp[first], mp[second],value)
		mp[value] = var
		replace[value] = value


def print_code():
	for st in list_statement:
		if not st in not_used:
			print mp[st].variable_identifier + " = " +replace[mp[st].lchild.variable_identifier] + " " + mp[st].oper-ator_value + " " + 				replace[mp[st].rchild.variable_identifier]


def optimise():
	for i in range(len(list_statement)):
		for j in range(i, len(list_statement)):
			st = list_statement[i]
			st2 = list_statement[j]
			if mp[st].lchild == mp[st2].lchild and[st].rchild== mp[st2].rchild and mp[st].operator_value ==mp[st2].operator_value:
				replace[st2] = replace[st]
				if st2 != st:
					not_used.append(st2)

if __name__ == "__main__":
	file_name = "intermediate_code"
	if len(argv) == 2:
		file_name = argv[1]
	read_input(file_name)
	optimise()
	print_code()

---------------------------
Intermidiate_code---------------------
t1 := a + b
t2 := c * t1
t3 := a + b
t4 := d * t3
t5 := t2 + t4
t6 := r = t5
t7 := t3 + a
t0 := a = t4
t8 := a + b
t9 := a + b
t10 := t9 + a
t11 := a = l
t12 := a + b
t13 := a + b
t14 := j + t13


Output:
swati@Shree:~/cl1_code/codes/b4$ python b4.py
t1 = a + b
t2 = c * t1
t4 = d * t1
t5 = t2 + t4
t6 = r = t5
t7 = t1 + a
t0 = a = t4
t8 = a + b
t10 = t8 + a
t11 = a = l
t12 = a + b
t14 = j + t12

