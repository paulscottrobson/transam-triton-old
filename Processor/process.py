#
#	8080 Preprocessor
#

import re

def processString(s,opcode,adjusted):
	s = s.replace("@N",["B","C","D","E","H","L","(HL)","A"][adjusted])
	s = s.replace("@R",["b","c","d","e","h","k","readMemory(HL)","a"][adjusted])
	s = s.replace("@C", ["NZ","Z","NC","C","PO","PE","P","M"][adjusted])
	cx = ["szValue != 0","szValue == 0","carry == 0","carry != 0", "overflow == 0", "overflow != 0"," (szValue & 0x80) == 0","(szValue & 0x80) != 0"]
	s = s.replace("@T",cx[adjusted])
	s = s.replace("@O", "{0:02x}".format(adjusted*8))	
	return s

sources = "alu16bit.def,alu8bit.def,call.def,exblock.def,general.def,io.def,jump.def,load16bit.def,load8bit.def,rotate.def".split(",")
src = ""
for fileName in sources:
	src = src + "\n".join(open(fileName).readlines()) + "\n"
src = src.replace("\t"," ").split("\n")
src = [x if x.find("//") < 0 else x[:x.find("//")] for x in src]
src = [x.strip() for x in src if x.strip() != ""]
#print("\n".join(src))

mnemonics = [ None ] * 256
code = [ None ] * 256

for s in src:
	m = re.match('^([0-9A-Fa-f\\-\\,]+)\\s*(\\d+)\\s*\\"(.*)\\"\\s*(.*)$',s)
	assert m is not None,s
	r = m.group(1)
	r = r if len(r) != 2 else r + "-" + r
	r = r if len(r) == 7 else r + ",1"
	
	opcode = start = int(r[:2],16)
	adjust = 0
	while opcode <= int(r[3:5],16):
		assert mnemonics[opcode] is None
		tstates = int(m.group(2))
		if adjust == 6 and m.group(4).find("@R") >= 0:
			tstates += 3
		mnemonics[opcode] = processString(m.group(3),opcode,adjust)
		code[opcode] = processString(m.group(4),opcode,adjust)+";tState += {0};".format(tstates)

		opcode += int(r[-1])
		adjust += 1


h = open("_8080_opcodes.h","w")
for i in range(0,256):
	if mnemonics[i] is not None:
		h.write("case 0x{0:02x}: /*** {1} ***/\n".format(i,mnemonics[i].lower()))
		h.write("   "+code[i]+";break;\n")
	else:
		mnemonics[i] = "db {0:02x}".format(i)

open("_8080_mnemonics.h","w").write(",".join('"'+x.lower()+'"' for x in mnemonics))
print("8080 code generated.")
