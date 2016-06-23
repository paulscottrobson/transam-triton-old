import re

src = open("font.txt","r").readlines()
src = [x.strip() for x in src if x[:2] != "//"]
src = [x for x in src if x != ""]

fontData = [ None ] * 128
current = -1

for l in src:
	m = re.match("^\\:\\s*(\d+)",l)
	if m is not None:
		current = int(m.group(1))
		assert fontData[current] is None
		fontData[current] = []
	else:
		l = l.replace(".","0").replace("X","1")
		assert len(l) == 8 
		assert re.match("^[01]+$",l) is not None
		fontData[current].append(int(l,2))

for i in range(0,128):
	assert fontData[i] is not None
	assert len(fontData[i]) == 8
	fontData[i] = ",".join(["0x{0:02x}".format(x) for x in fontData[i]])

fontData = ",".join(fontData)
assert len(fontData.split(",")) == 128 * 8

open("_font.h","w").write(fontData)