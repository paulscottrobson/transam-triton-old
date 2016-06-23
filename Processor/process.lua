--[[

																	Z80 Emulator Core Generator
--]]

-- these range from 000-4FF : 0xx normal, 1xx CB, 2xx DD, 3xx ED, 4xx FD code.

local mnemonicList = {} 																	-- mnemonics
local codeList = {} 																		-- code associated with mnemonics

function processString(str,opcode,adjusted)
	local reg = { "C","D","E","H","L","(HL)","A" } reg[0] = "B"
	str = str:gsub("@N",reg[adjusted])
	local rsub = reg[adjusted]:lower()
	if adjusted == 6 then rsub = "readMemory(HL)" end
	str = str:gsub("@R",rsub):gsub("@B",adjusted.."")
	local cc = { "Z","NC","C","PO","PE","P","M" } cc[0] = "NZ"
	str = str:gsub("@C",cc[adjusted])

	local cx = { "szValue == 0","carry == 0","carry != 0", "overflow == 0", "overflow != 0"," (szValue & 0x80) == 0","(szValue & 0x80) != 0" }
	cx[0] = "szValue != 0"
	str = str:gsub("@T",cx[adjusted])
	str = str:gsub("@O", ("%02x"):format(adjusted*8))
	return str
end

function processRange(shift,range,tstates,mnemonic,code)
	local rem,step = range:match("^(.*),(%d+)$") 											-- process step.
	if step ~= nil then
		step = tonumber(step,16) 
		range = rem
	else
		step = 1
	end
	if #range == 2 then range = range .. "-" .. range end 									-- expand nn to nn-nn
	first = tonumber(range:sub(1,2),16) last = tonumber(range:sub(4,5),16)					-- extract start and end values.
	if shift > 0 then shift = math.floor(shift / 16) - 0xB end 								-- convert Cx Dx Ex Fx to 1,2,3,4

	local opcode = first
	while opcode <= last do
		local ref = shift * 256 + opcode 													-- where the opcode goes
		--print(ref,mnemonicList[ref],mnemonic)
		assert(mnemonicList[ref] == nil," Duplicate mnemonic " .. mnemonic .. " ") 			-- check it is unique
		local adjust = (opcode-first) / step												-- offset adjusted by step
		mnemonicList[ref] = processString(mnemonic,opcode,adjust) 							-- copy mnemonic and opcode into place.
		codeList[ref] = processString(code,opcode,adjust)			

		local s = tstates 																	-- number of T-States
		if adjust == 6 and code:match("@R") ~= nil then s = s + 3 end  						-- if using (HL) then 3 more T-states
		codeList[ref] = "TSTATE(" .. s .. ");" .. codeList[ref] 							-- put the TSTATES macro in.
		opcode = opcode + step 																-- go to the next one.
	end
end

function processFile(definitionFile)
	print("Processing " .. definitionFile)
	local src = io.open(definitionFile,"r") 												-- open source file
	assert(src ~= nil)
	for line in src:lines() do																-- read each line in turn
		local n = line:find("//") 															-- remove comments
		if n ~= nil then line = line:sub(1,n-1) end
		while line:match("%s$") do line = line:sub(1,#line-1) end 							-- remove trailing spaces
		line = line:gsub("%s"," "):match("^%s*(.*)$")										-- tabs to space, remove leading spaces.
		if line ~= "" then																	-- if any content remaining.
			local range,tstates,mnemonic,code = 											-- split it up into components
								line:match('^([%x%:%,%-]+)%s+(%d+)%s+%"([%w%,%(%)%s%@]+)%"%s+(.*)$')
			assert(range ~= nil,"Syntax error in "..line)									-- check the split worked.
			local shift = 0 																-- shift is the 256 byte group it is in.
			if range:match("%:") then														-- is there a shift (e.g. xx:)
				shift = tonumber(range:sub(1,2),16)											-- work out the shift.
				range = range:sub(4)														-- remove it from the range.
			end
			processRange(shift,range,tstates,mnemonic,code) 								-- process the range.
			if shift == 0xDD then 															-- if it is DD then do IY as well.
				processRange(0xFD,range,tstates,mnemonic:gsub("IX","IY"),code:gsub("ix","iy"))
			end
		end
	end
	src:close()
end

function generateMnemonics(mneFile)
	local h = io.open(mneFile,"w")
	h:write("/* Automatically generated code */\n\n")
	h:write("static char *_mnemonics[5*256+1] = {\n    ")
	for i = 0,256*5-1 do
		local m = mnemonicList[i]
		if m ~= nil then m = '"'..m:lower()..'"' else m = "NULL" end
		h:write(m..",")
		if i % 8 == 7 then h:write("\n    ") end
	end
	h:write('"" };\n')
	h:close()
end

function generateCode(codeFile) 
	local h = io.open(codeFile,"w")
	h:write("/* Automatically generated code */\n\n")
	local shiftLookup = { 0xCB, 0xDD, 0xED, 0xFD } shiftLookup[0] = 0 
	for i = 0,256*5 do
		if mnemonicList[i] ~= nil then
			if mnemonicList[i]:sub(1,1) ~= "(" then
				local realOp = shiftLookup[math.floor(i/256)] * 256 + i % 256
				h:write( ("case 0x%03x : /* %-4X %s */\n"):format(i,realOp,mnemonicList[i]))
				h:write("        "..codeList[i] .. ";break;\n")
			end
		end
	end
	h:close()
end

mnemonicList[0xCB] = "(shift)"																-- not opcodes - they are 'shifts' to 2 byte opcodes
mnemonicList[0xDD] = "(shift)"
mnemonicList[0xED] = "(shift)"
mnemonicList[0xFD] = "(shift)"

processFile("load8bit.def")
processFile("load16bit.def")
processFile("exblock.def")
processFile("alu8bit.def")
processFile("general.def")
processFile("alu16bit.def")
processFile("rotate.def")
processFile("bitop.def")
processFile("jump.def")
processFile("call.def")
processFile("io.def")

generateMnemonics("z80_mnemonics.h")
generateCode("z80_opcodes.h")











