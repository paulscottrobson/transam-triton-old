case 0x00: /*** nop ***/
   {};tState += 4;;break;
case 0x01: /*** ld bc,@2@1 ***/
   c = fetch();b = fetch();tState += 10;;break;
case 0x02: /*** ld (bc),a ***/
   writeMemory(BC,a);tState += 7;;break;
case 0x03: /*** inc bc ***/
   INC16(b,c);tState += 6;;break;
case 0x04: /*** inc b ***/
   b = increment8Bit(b);tState += 4;;break;
case 0x05: /*** dec b ***/
   b = decrement8Bit(b);tState += 4;;break;
case 0x06: /*** ld b,@1 ***/
   b = fetch();tState += 7;;break;
case 0x07: /*** rlca ***/
   carry = (a >> 7) & 1;a = (a << 1) | carry;negate = halfCarry = 0;;tState += 4;;break;
case 0x09: /*** add hl,bc ***/
   temp16 = add16BitNoCarry(HL,BC);l = temp16 & 0xFF;h = temp16 >> 8;tState += 11;;break;
case 0x0a: /*** ld a,(bc) ***/
   a = readMemory(BC);tState += 7;;break;
case 0x0b: /*** dec bc ***/
   DEC16(b,c);tState += 6;;break;
case 0x0c: /*** inc c ***/
   c = increment8Bit(c);tState += 4;;break;
case 0x0d: /*** dec c ***/
   c = decrement8Bit(c);tState += 4;;break;
case 0x0e: /*** ld c,@1 ***/
   c = fetch();tState += 7;;break;
case 0x0f: /*** rrca ***/
   carry = a & 1;a = (a >> 1) | (carry << 7);negate = halfCarry = 0;;tState += 4;;break;
case 0x11: /*** ld de,@2@1 ***/
   e = fetch();d = fetch();tState += 10;;break;
case 0x12: /*** ld (de),a ***/
   writeMemory(DE,a);tState += 7;;break;
case 0x13: /*** inc de ***/
   INC16(d,e);tState += 6;;break;
case 0x14: /*** inc d ***/
   d = increment8Bit(d);tState += 4;;break;
case 0x15: /*** dec d ***/
   d = decrement8Bit(d);tState += 4;;break;
case 0x16: /*** ld d,@1 ***/
   d = fetch();tState += 7;;break;
case 0x17: /*** rla ***/
   temp16 = (a << 1) | carry;carry = (temp16 >> 8);a = temp16 & 0xFF;negate = halfCarry = 0;;tState += 4;;break;
case 0x19: /*** add hl,de ***/
   temp16 = add16BitNoCarry(HL,DE);l = temp16 & 0xFF;h = temp16 >> 8;tState += 11;;break;
case 0x1a: /*** ld a,(de) ***/
   a = readMemory(DE);tState += 7;;break;
case 0x1b: /*** dec de ***/
   DEC16(d,e);tState += 6;;break;
case 0x1c: /*** inc e ***/
   e = increment8Bit(e);tState += 4;;break;
case 0x1d: /*** dec e ***/
   e = decrement8Bit(e);tState += 4;;break;
case 0x1e: /*** ld e,@1 ***/
   e = fetch();tState += 7;;break;
case 0x1f: /*** rra ***/
   temp16 = a | (((WORD16)carry) << 8);carry = temp16 & 1;a = (temp16 >> 1) & 0xFF;tState += 4;;break;
case 0x21: /*** ld hl,@2@1 ***/
   l = fetch();h = fetch();tState += 10;;break;
case 0x22: /*** ld (@2@1),hl ***/
   FETCHWORD();writeMemory(temp16,l);writeMemory(temp16+1,h);tState += 16;;break;
case 0x23: /*** inc hl ***/
   INC16(h,l);tState += 6;;break;
case 0x24: /*** inc h ***/
   h = increment8Bit(h);tState += 4;;break;
case 0x25: /*** dec h ***/
   h = decrement8Bit(h);tState += 4;;break;
case 0x26: /*** ld h,@1 ***/
   h = fetch();tState += 7;;break;
case 0x27: /*** daa ***/
   daaCode();tState += 4;;break;
case 0x29: /*** add hl,hl ***/
   temp16 = add16BitNoCarry(HL,HL);l = temp16 & 0xFF;h = temp16 >> 8;tState += 11;;break;
case 0x2a: /*** ld hl,(@2@1) ***/
   FETCHWORD();l = readMemory(temp16);h = readMemory(temp16+1);tState += 16;;break;
case 0x2b: /*** dec hl ***/
   DEC16(h,l);tState += 6;;break;
case 0x2c: /*** inc l ***/
   k = increment8Bit(k);tState += 4;;break;
case 0x2d: /*** dec l ***/
   k = decrement8Bit(k);tState += 4;;break;
case 0x2e: /*** ld l,@1 ***/
   k = fetch();tState += 7;;break;
case 0x2f: /*** cpl ***/
   a = a ^ 0xFF;negate = 1;halfCarry = 1;;tState += 4;;break;
case 0x31: /*** ld sp,@2@1 ***/
   FETCHWORD();sp = temp16;tState += 10;;break;
case 0x32: /*** ld (@2@1),a ***/
   FETCHWORD();writeMemory(temp16,a);tState += 13;;break;
case 0x33: /*** inc sp ***/
   sp++;tState += 6;;break;
case 0x34: /*** inc (hl) ***/
   temp16 = HL;writeMemory(temp16,increment8Bit(readMemory(temp16)));tState += 11;;break;
case 0x35: /*** dec (hl) ***/
   temp16 = HL;writeMemory(temp16,decrement8Bit(readMemory(temp16)));tState += 11;;break;
case 0x36: /*** ld (hl),@1 ***/
   writeMemory(HL,fetch());tState += 10;;break;
case 0x37: /*** scf ***/
   carry = 1;tState += 4;;break;
case 0x39: /*** add hl,sp ***/
   temp16 = add16BitNoCarry(HL,sp);l = temp16 & 0xFF;h = temp16 >> 8;tState += 11;;break;
case 0x3a: /*** ld a,(@2@1) ***/
   FETCHWORD();a = readMemory(temp16);tState += 13;;break;
case 0x3b: /*** dec sp ***/
   sp--;tState += 6;;break;
case 0x3c: /*** inc a ***/
   a = increment8Bit(a);tState += 4;;break;
case 0x3d: /*** dec a ***/
   a = decrement8Bit(a);tState += 4;;break;
case 0x3e: /*** ld a,@1 ***/
   a = fetch();tState += 7;;break;
case 0x3f: /*** ccf ***/
   carry ^= 1;tState += 4;;break;
case 0x40: /*** ld b,b ***/
   b = b;tState += 4;;break;
case 0x41: /*** ld b,c ***/
   b = c;tState += 4;;break;
case 0x42: /*** ld b,d ***/
   b = d;tState += 4;;break;
case 0x43: /*** ld b,e ***/
   b = e;tState += 4;;break;
case 0x44: /*** ld b,h ***/
   b = h;tState += 4;;break;
case 0x45: /*** ld b,l ***/
   b = k;tState += 4;;break;
case 0x46: /*** ld b,(hl) ***/
   b = readMemory(HL);tState += 7;;break;
case 0x47: /*** ld b,a ***/
   b = a;tState += 4;;break;
case 0x48: /*** ld c,b ***/
   c = b;tState += 4;;break;
case 0x49: /*** ld c,c ***/
   c = c;tState += 4;;break;
case 0x4a: /*** ld c,d ***/
   c = d;tState += 4;;break;
case 0x4b: /*** ld c,e ***/
   c = e;tState += 4;;break;
case 0x4c: /*** ld c,h ***/
   c = h;tState += 4;;break;
case 0x4d: /*** ld c,l ***/
   c = k;tState += 4;;break;
case 0x4e: /*** ld c,(hl) ***/
   c = readMemory(HL);tState += 7;;break;
case 0x4f: /*** ld c,a ***/
   c = a;tState += 4;;break;
case 0x50: /*** ld d,b ***/
   d = b;tState += 4;;break;
case 0x51: /*** ld d,c ***/
   d = c;tState += 4;;break;
case 0x52: /*** ld d,d ***/
   d = d;tState += 4;;break;
case 0x53: /*** ld d,e ***/
   d = e;tState += 4;;break;
case 0x54: /*** ld d,h ***/
   d = h;tState += 4;;break;
case 0x55: /*** ld d,l ***/
   d = k;tState += 4;;break;
case 0x56: /*** ld d,(hl) ***/
   d = readMemory(HL);tState += 7;;break;
case 0x57: /*** ld d,a ***/
   d = a;tState += 4;;break;
case 0x58: /*** ld e,b ***/
   e = b;tState += 4;;break;
case 0x59: /*** ld e,c ***/
   e = c;tState += 4;;break;
case 0x5a: /*** ld e,d ***/
   e = d;tState += 4;;break;
case 0x5b: /*** ld e,e ***/
   e = e;tState += 4;;break;
case 0x5c: /*** ld e,h ***/
   e = h;tState += 4;;break;
case 0x5d: /*** ld e,l ***/
   e = k;tState += 4;;break;
case 0x5e: /*** ld e,(hl) ***/
   e = readMemory(HL);tState += 7;;break;
case 0x5f: /*** ld e,a ***/
   e = a;tState += 4;;break;
case 0x60: /*** ld h,b ***/
   h = b;tState += 4;;break;
case 0x61: /*** ld h,c ***/
   h = c;tState += 4;;break;
case 0x62: /*** ld h,d ***/
   h = d;tState += 4;;break;
case 0x63: /*** ld h,e ***/
   h = e;tState += 4;;break;
case 0x64: /*** ld h,h ***/
   h = h;tState += 4;;break;
case 0x65: /*** ld h,l ***/
   h = k;tState += 4;;break;
case 0x66: /*** ld h,(hl) ***/
   h = readMemory(HL);tState += 7;;break;
case 0x67: /*** ld h,a ***/
   h = a;tState += 4;;break;
case 0x68: /*** ld l,b ***/
   l = b;tState += 4;;break;
case 0x69: /*** ld l,c ***/
   l = c;tState += 4;;break;
case 0x6a: /*** ld l,d ***/
   l = d;tState += 4;;break;
case 0x6b: /*** ld l,e ***/
   l = e;tState += 4;;break;
case 0x6c: /*** ld l,h ***/
   l = h;tState += 4;;break;
case 0x6d: /*** ld l,l ***/
   l = k;tState += 4;;break;
case 0x6e: /*** ld l,(hl) ***/
   l = readMemory(HL);tState += 7;;break;
case 0x6f: /*** ld l,a ***/
   l = a;tState += 4;;break;
case 0x70: /*** ld (hl),b ***/
   writeMemory(HL,b);tState += 7;;break;
case 0x71: /*** ld (hl),c ***/
   writeMemory(HL,c);tState += 7;;break;
case 0x72: /*** ld (hl),d ***/
   writeMemory(HL,d);tState += 7;;break;
case 0x73: /*** ld (hl),e ***/
   writeMemory(HL,e);tState += 7;;break;
case 0x74: /*** ld (hl),h ***/
   writeMemory(HL,h);tState += 7;;break;
case 0x75: /*** ld (hl),l ***/
   writeMemory(HL,k);tState += 7;;break;
case 0x76: /*** halt ***/
   haltCode();tState += 4;;break;
case 0x77: /*** ld (hl),a ***/
   writeMemory(HL,a);tState += 7;;break;
case 0x78: /*** ld a,b ***/
   a = b;tState += 4;;break;
case 0x79: /*** ld a,c ***/
   a = c;tState += 4;;break;
case 0x7a: /*** ld a,d ***/
   a = d;tState += 4;;break;
case 0x7b: /*** ld a,e ***/
   a = e;tState += 4;;break;
case 0x7c: /*** ld a,h ***/
   a = h;tState += 4;;break;
case 0x7d: /*** ld a,l ***/
   a = k;tState += 4;;break;
case 0x7e: /*** ld a,(hl) ***/
   a = readMemory(HL);tState += 7;;break;
case 0x7f: /*** ld a,a ***/
   a = a;tState += 4;;break;
case 0x80: /*** add a,b ***/
   carry = 0;a = add8BitCarry(a,b);tState += 4;;break;
case 0x81: /*** add a,c ***/
   carry = 0;a = add8BitCarry(a,c);tState += 4;;break;
case 0x82: /*** add a,d ***/
   carry = 0;a = add8BitCarry(a,d);tState += 4;;break;
case 0x83: /*** add a,e ***/
   carry = 0;a = add8BitCarry(a,e);tState += 4;;break;
case 0x84: /*** add a,h ***/
   carry = 0;a = add8BitCarry(a,h);tState += 4;;break;
case 0x85: /*** add a,l ***/
   carry = 0;a = add8BitCarry(a,k);tState += 4;;break;
case 0x86: /*** add a,(hl) ***/
   carry = 0;a = add8BitCarry(a,readMemory(HL));tState += 7;;break;
case 0x87: /*** add a,a ***/
   carry = 0;a = add8BitCarry(a,a);tState += 4;;break;
case 0x88: /*** adc a,b ***/
   a = add8BitCarry(a,b);tState += 4;;break;
case 0x89: /*** adc a,c ***/
   a = add8BitCarry(a,c);tState += 4;;break;
case 0x8a: /*** adc a,d ***/
   a = add8BitCarry(a,d);tState += 4;;break;
case 0x8b: /*** adc a,e ***/
   a = add8BitCarry(a,e);tState += 4;;break;
case 0x8c: /*** adc a,h ***/
   a = add8BitCarry(a,h);tState += 4;;break;
case 0x8d: /*** adc a,l ***/
   a = add8BitCarry(a,k);tState += 4;;break;
case 0x8e: /*** adc a,(hl) ***/
   a = add8BitCarry(a,readMemory(HL));tState += 7;;break;
case 0x8f: /*** adc a,a ***/
   a = add8BitCarry(a,a);tState += 4;;break;
case 0x90: /*** sub a,b ***/
   carry = 0;a = sub8BitCarry(a,b);tState += 4;;break;
case 0x91: /*** sub a,c ***/
   carry = 0;a = sub8BitCarry(a,c);tState += 4;;break;
case 0x92: /*** sub a,d ***/
   carry = 0;a = sub8BitCarry(a,d);tState += 4;;break;
case 0x93: /*** sub a,e ***/
   carry = 0;a = sub8BitCarry(a,e);tState += 4;;break;
case 0x94: /*** sub a,h ***/
   carry = 0;a = sub8BitCarry(a,h);tState += 4;;break;
case 0x95: /*** sub a,l ***/
   carry = 0;a = sub8BitCarry(a,k);tState += 4;;break;
case 0x96: /*** sub a,(hl) ***/
   carry = 0;a = sub8BitCarry(a,readMemory(HL));tState += 7;;break;
case 0x97: /*** sub a,a ***/
   carry = 0;a = sub8BitCarry(a,a);tState += 4;;break;
case 0x98: /*** sbc a,b ***/
   a = sub8BitCarry(a,b);tState += 4;;break;
case 0x99: /*** sbc a,c ***/
   a = sub8BitCarry(a,c);tState += 4;;break;
case 0x9a: /*** sbc a,d ***/
   a = sub8BitCarry(a,d);tState += 4;;break;
case 0x9b: /*** sbc a,e ***/
   a = sub8BitCarry(a,e);tState += 4;;break;
case 0x9c: /*** sbc a,h ***/
   a = sub8BitCarry(a,h);tState += 4;;break;
case 0x9d: /*** sbc a,l ***/
   a = sub8BitCarry(a,k);tState += 4;;break;
case 0x9e: /*** sbc a,(hl) ***/
   a = sub8BitCarry(a,readMemory(HL));tState += 7;;break;
case 0x9f: /*** sbc a,a ***/
   a = sub8BitCarry(a,a);tState += 4;;break;
case 0xa0: /*** and a,b ***/
   carry = 0;szValue = a = (a & b);negate = 0;halfCarry = 1;;tState += 4;;break;
case 0xa1: /*** and a,c ***/
   carry = 0;szValue = a = (a & c);negate = 0;halfCarry = 1;;tState += 4;;break;
case 0xa2: /*** and a,d ***/
   carry = 0;szValue = a = (a & d);negate = 0;halfCarry = 1;;tState += 4;;break;
case 0xa3: /*** and a,e ***/
   carry = 0;szValue = a = (a & e);negate = 0;halfCarry = 1;;tState += 4;;break;
case 0xa4: /*** and a,h ***/
   carry = 0;szValue = a = (a & h);negate = 0;halfCarry = 1;;tState += 4;;break;
case 0xa5: /*** and a,l ***/
   carry = 0;szValue = a = (a & k);negate = 0;halfCarry = 1;;tState += 4;;break;
case 0xa6: /*** and a,(hl) ***/
   carry = 0;szValue = a = (a & readMemory(HL));negate = 0;halfCarry = 1;;tState += 7;;break;
case 0xa7: /*** and a,a ***/
   carry = 0;szValue = a = (a & a);negate = 0;halfCarry = 1;;tState += 4;;break;
case 0xa8: /*** xor a,b ***/
   carry = 0;szValue = a = (a ^ b);negate = 0;halfCarry = 0;;tState += 4;;break;
case 0xa9: /*** xor a,c ***/
   carry = 0;szValue = a = (a ^ c);negate = 0;halfCarry = 0;;tState += 4;;break;
case 0xaa: /*** xor a,d ***/
   carry = 0;szValue = a = (a ^ d);negate = 0;halfCarry = 0;;tState += 4;;break;
case 0xab: /*** xor a,e ***/
   carry = 0;szValue = a = (a ^ e);negate = 0;halfCarry = 0;;tState += 4;;break;
case 0xac: /*** xor a,h ***/
   carry = 0;szValue = a = (a ^ h);negate = 0;halfCarry = 0;;tState += 4;;break;
case 0xad: /*** xor a,l ***/
   carry = 0;szValue = a = (a ^ k);negate = 0;halfCarry = 0;;tState += 4;;break;
case 0xae: /*** xor a,(hl) ***/
   carry = 0;szValue = a = (a ^ readMemory(HL));negate = 0;halfCarry = 0;;tState += 7;;break;
case 0xaf: /*** xor a,a ***/
   carry = 0;szValue = a = (a ^ a);negate = 0;halfCarry = 0;;tState += 4;;break;
case 0xb0: /*** or a,b ***/
   carry = 0;szValue = a = (a | b);negate = 0;halfCarry = 0;;tState += 4;;break;
case 0xb1: /*** or a,c ***/
   carry = 0;szValue = a = (a | c);negate = 0;halfCarry = 0;;tState += 4;;break;
case 0xb2: /*** or a,d ***/
   carry = 0;szValue = a = (a | d);negate = 0;halfCarry = 0;;tState += 4;;break;
case 0xb3: /*** or a,e ***/
   carry = 0;szValue = a = (a | e);negate = 0;halfCarry = 0;;tState += 4;;break;
case 0xb4: /*** or a,h ***/
   carry = 0;szValue = a = (a | h);negate = 0;halfCarry = 0;;tState += 4;;break;
case 0xb5: /*** or a,l ***/
   carry = 0;szValue = a = (a | k);negate = 0;halfCarry = 0;;tState += 4;;break;
case 0xb6: /*** or a,(hl) ***/
   carry = 0;szValue = a = (a | readMemory(HL));negate = 0;halfCarry = 0;;tState += 7;;break;
case 0xb7: /*** or a,a ***/
   carry = 0;szValue = a = (a | a);negate = 0;halfCarry = 0;;tState += 4;;break;
case 0xb8: /*** cp  a,b ***/
   carry = 0;sub8BitCarry(a,b);tState += 4;;break;
case 0xb9: /*** cp  a,c ***/
   carry = 0;sub8BitCarry(a,c);tState += 4;;break;
case 0xba: /*** cp  a,d ***/
   carry = 0;sub8BitCarry(a,d);tState += 4;;break;
case 0xbb: /*** cp  a,e ***/
   carry = 0;sub8BitCarry(a,e);tState += 4;;break;
case 0xbc: /*** cp  a,h ***/
   carry = 0;sub8BitCarry(a,h);tState += 4;;break;
case 0xbd: /*** cp  a,l ***/
   carry = 0;sub8BitCarry(a,k);tState += 4;;break;
case 0xbe: /*** cp  a,(hl) ***/
   carry = 0;sub8BitCarry(a,readMemory(HL));tState += 7;;break;
case 0xbf: /*** cp  a,a ***/
   carry = 0;sub8BitCarry(a,a);tState += 4;;break;
case 0xc0: /*** ret nz ***/
   if (szValue != 0) { temp16 = POP();temp16 = temp16 | (((WORD16)POP()) << 8); TSTATE(6); SETPC(temp16); };tState += 5;;break;
case 0xc1: /*** pop bc ***/
   c = POP();b = POP();tState += 10;;break;
case 0xc2: /*** jp nz,@2@1 ***/
   FETCHWORD();if (szValue != 0) SETPC(temp16);tState += 10;;break;
case 0xc3: /*** jp @2@1 ***/
   FETCHWORD();SETPC(temp16);tState += 10;;break;
case 0xc4: /*** call nz,@2@1 ***/
   FETCHWORD();if (szValue != 0) { PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(temp16);TSTATE(7); };tState += 10;;break;
case 0xc5: /*** push bc ***/
   PUSH(b);PUSH(c);tState += 11;;break;
case 0xc6: /*** add a,@1 ***/
   carry = 0;a = add8BitCarry(a,fetch());tState += 7;;break;
case 0xc7: /*** rst 00 ***/
   PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(0x00);tState += 11;;break;
case 0xc8: /*** ret z ***/
   if (szValue == 0) { temp16 = POP();temp16 = temp16 | (((WORD16)POP()) << 8); TSTATE(6); SETPC(temp16); };tState += 5;;break;
case 0xc9: /*** ret ***/
   temp16 = POP();temp16 = temp16 | (((WORD16)POP()) << 8);SETPC(temp16);tState += 10;;break;
case 0xca: /*** jp z,@2@1 ***/
   FETCHWORD();if (szValue == 0) SETPC(temp16);tState += 10;;break;
case 0xcc: /*** call z,@2@1 ***/
   FETCHWORD();if (szValue == 0) { PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(temp16);TSTATE(7); };tState += 10;;break;
case 0xcd: /*** call @2@1 ***/
   FETCHWORD();PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(temp16);tState += 17;;break;
case 0xce: /*** adc a,@1 ***/
   a = add8BitCarry(a,fetch());tState += 7;;break;
case 0xcf: /*** rst 08 ***/
   PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(0x08);tState += 11;;break;
case 0xd0: /*** ret nc ***/
   if (carry == 0) { temp16 = POP();temp16 = temp16 | (((WORD16)POP()) << 8); TSTATE(6); SETPC(temp16); };tState += 5;;break;
case 0xd1: /*** pop de ***/
   e = POP();d = POP();tState += 10;;break;
case 0xd2: /*** jp nc,@2@1 ***/
   FETCHWORD();if (carry == 0) SETPC(temp16);tState += 10;;break;
case 0xd3: /*** out (@1),a ***/
   temp8 = fetch();writeOutputPort(temp8,a);tState += 11;;break;
case 0xd4: /*** call nc,@2@1 ***/
   FETCHWORD();if (carry == 0) { PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(temp16);TSTATE(7); };tState += 10;;break;
case 0xd5: /*** push de ***/
   PUSH(d);PUSH(e);tState += 11;;break;
case 0xd6: /*** sub a,@1 ***/
   carry = 0;a = sub8BitCarry(a,fetch());tState += 7;;break;
case 0xd7: /*** rst 10 ***/
   PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(0x10);tState += 11;;break;
case 0xd8: /*** ret c ***/
   if (carry != 0) { temp16 = POP();temp16 = temp16 | (((WORD16)POP()) << 8); TSTATE(6); SETPC(temp16); };tState += 5;;break;
case 0xda: /*** jp c,@2@1 ***/
   FETCHWORD();if (carry != 0) SETPC(temp16);tState += 10;;break;
case 0xdb: /*** in a,(@1) ***/
   temp16 = a; temp16 = (temp16 << 8) | fetch();a = readInputPort(temp16);;tState += 11;;break;
case 0xdc: /*** call c,@2@1 ***/
   FETCHWORD();if (carry != 0) { PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(temp16);TSTATE(7); };tState += 10;;break;
case 0xde: /*** sbc a,@1 ***/
   a = sub8BitCarry(a,fetch());tState += 7;;break;
case 0xdf: /*** rst 18 ***/
   PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(0x18);tState += 11;;break;
case 0xe0: /*** ret po ***/
   if (overflow == 0) { temp16 = POP();temp16 = temp16 | (((WORD16)POP()) << 8); TSTATE(6); SETPC(temp16); };tState += 5;;break;
case 0xe1: /*** pop hl ***/
   l = POP();h = POP();tState += 10;;break;
case 0xe2: /*** jp po,@2@1 ***/
   FETCHWORD();if (overflow == 0) SETPC(temp16);tState += 10;;break;
case 0xe3: /*** ex (sp),hl ***/
   temp8 = h;h = readMemory(sp+1);writeMemory(sp+1,temp8);temp8 = l;l = readMemory(sp);writeMemory(sp,temp8);tState += 19;;break;
case 0xe4: /*** call po,@2@1 ***/
   FETCHWORD();if (overflow == 0) { PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(temp16);TSTATE(7); };tState += 10;;break;
case 0xe5: /*** push hl ***/
   PUSH(h);PUSH(l);tState += 11;;break;
case 0xe6: /*** and a,@1 ***/
   carry = 0;szValue = a = (a & fetch());negate = 0;halfCarry = 1;;tState += 7;;break;
case 0xe7: /*** rst 20 ***/
   PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(0x20);tState += 11;;break;
case 0xe8: /*** ret pe ***/
   if (overflow != 0) { temp16 = POP();temp16 = temp16 | (((WORD16)POP()) << 8); TSTATE(6); SETPC(temp16); };tState += 5;;break;
case 0xe9: /*** jp (hl) ***/
   SETPC(HL);tState += 4;;break;
case 0xea: /*** jp pe,@2@1 ***/
   FETCHWORD();if (overflow != 0) SETPC(temp16);tState += 10;;break;
case 0xeb: /*** ex de,hl ***/
   SWAP(d,h);SWAP(e,l);tState += 4;;break;
case 0xec: /*** call pe,@2@1 ***/
   FETCHWORD();if (overflow != 0) { PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(temp16);TSTATE(7); };tState += 10;;break;
case 0xee: /*** xor a,@1 ***/
   carry = 0;szValue = a = (a ^ fetch());negate = 0;halfCarry = 0;;tState += 7;;break;
case 0xef: /*** rst 28 ***/
   PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(0x28);tState += 11;;break;
case 0xf0: /*** ret p ***/
   if ( (szValue & 0x80) == 0) { temp16 = POP();temp16 = temp16 | (((WORD16)POP()) << 8); TSTATE(6); SETPC(temp16); };tState += 5;;break;
case 0xf1: /*** pop af ***/
   explodeF(POP());a = POP();tState += 10;;break;
case 0xf2: /*** jp p,@2@1 ***/
   FETCHWORD();if ( (szValue & 0x80) == 0) SETPC(temp16);tState += 10;;break;
case 0xf3: /*** di ***/
   intEnabled = 0;tState += 4;;break;
case 0xf4: /*** call p,@2@1 ***/
   FETCHWORD();if ( (szValue & 0x80) == 0) { PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(temp16);TSTATE(7); };tState += 10;;break;
case 0xf5: /*** push af ***/
   PUSH(a);PUSH(constructF());tState += 11;;break;
case 0xf6: /*** or a,@1 ***/
   carry = 0;szValue = a = (a | fetch());negate = 0;halfCarry = 0;;tState += 7;;break;
case 0xf7: /*** rst 30 ***/
   PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(0x30);tState += 11;;break;
case 0xf8: /*** ret m ***/
   if ((szValue & 0x80) != 0) { temp16 = POP();temp16 = temp16 | (((WORD16)POP()) << 8); TSTATE(6); SETPC(temp16); };tState += 5;;break;
case 0xf9: /*** ld sp,hl ***/
   sp = HL;tState += 6;;break;
case 0xfa: /*** jp m,@2@1 ***/
   FETCHWORD();if ((szValue & 0x80) != 0) SETPC(temp16);tState += 10;;break;
case 0xfb: /*** ei ***/
   intEnabled = 1;tState += 4;;break;
case 0xfc: /*** call m,@2@1 ***/
   FETCHWORD();if ((szValue & 0x80) != 0) { PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(temp16);TSTATE(7); };tState += 10;;break;
case 0xfe: /*** cp  a,@1 ***/
   carry = 0;sub8BitCarry(a,fetch());tState += 7;;break;
case 0xff: /*** rst 38 ***/
   PUSH(pc >> 8);PUSH(pc & 0xFF);SETPC(0x38);tState += 11;;break;
