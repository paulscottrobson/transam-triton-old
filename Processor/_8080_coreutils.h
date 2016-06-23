//*******************************************************************************************************
//*******************************************************************************************************
//
//      Name:       _8080_CoreUtils.H
//      Purpose:    Utility functions for 8080 CPU Core 
//      Author:     Paul Robson
//      Date:       5th February 2014
//
//*******************************************************************************************************
//*******************************************************************************************************

#ifndef _8080COREUTILS_H
#define _8080COREUTILS_H

#include "general.h"																// Pull in typedefs and constants

//*******************************************************************************************************
//											Z80 Registers
//*******************************************************************************************************

static BYTE8 a,b,c,d,e,h,l,i,r;														// 8 bit Z80 Registers
static WORD16 pc,sp;																// 16 bit Z80 Registers
static BYTE8 carry,halfCarry,overflow,negate;										// 1 bit values that are parts of the Flag register
static BYTE8 intEnabled,intMode;													// Interrupt enabled, Interrupt mode.
static BYTE8 szValue; 																// Value used to calculate S and Z flags in Flag register
static WORD16 tState;																// Number of t-states in the frame.

static WORD16 temp16;																// Temporary values.
static BYTE8  temp8;

#define BC ((((WORD16)b) << 8) | c)													// Shorthand for BC,DE,HL
#define DE ((((WORD16)d) << 8) | e)
#define HL ((((WORD16)h) << 8) | l)

#define INC16(upper,lower) { lower++;if (lower == 0) upper++; }						// Increment of paired 8 bit registers.
#define DEC16(upper,lower) { lower--;if (lower == 0xFF) upper--; }					// Decrement of paired 8 bit registers

#define FETCHWORD() { temp16 = fetch();temp16 |= (((WORD16)fetch()) << 8); } 		// Fetch 16 bit value to temp16

#define POP() 	readMemory(sp++)													// Push and Pop Macros.
#define PUSH(v) writeMemory(--sp,v)

#define SWAP(a,b) { temp8 = a;a = b;b = temp8; }									// 8 bit Swap Macro

static BYTE8 readMemory(WORD16 address); 											// Forward definitions.
static void writeMemory(WORD16 address,BYTE8 data);
static BYTE8 readInputPort(WORD16 port);
static void writeOutputPort(WORD16 port,BYTE8 data);
static void haltCode(void);
static BYTE8 fetch(void);

//*******************************************************************************************************
//							Build the actual F register value from composites
//*******************************************************************************************************

static BYTE8 constructF(void) {
	 BYTE8 flag = carry | (negate << 1) | (overflow << 2) | (halfCarry << 4);		// Construct ..?H?VNC
	 if (szValue == 0) flag |= 0x40;												// Add Z
	 return flag | (szValue & 0x80);												// Add S and return value.
}

//*******************************************************************************************************
//								Explode F register value into composites
//*******************************************************************************************************

static void explodeF(BYTE8 f) {
	carry = f & 1; 																	// Extract out C N V H as inidividual bits.
	negate = (f >> 1) & 1;
	overflow = (f >> 2) & 1;
	halfCarry = (f >> 4) & 1;
	szValue = f & 0x80; 															// If S is set then szValue must be signed.
	if ((f & 0x40) == 0) szValue |= 1;												// If Z bit is clear make szValue non-zero
}

//*******************************************************************************************************
//											8 Bit Add with Carry
//*******************************************************************************************************

static BYTE8 add8BitCarry(BYTE8 n1,BYTE8 n2) {
	WORD16 result = n1 + n2 + carry; 												// Calculate the result
	halfCarry = (((n1 & 0xF) + (n2 & 0xF) + carry) >= 0x10) ? 1 : 0;				// Calculate half-carry result.
	carry = result >> 8; 															// Extract the carry flag.
	negate = 0;																		// Clear negate flag.
	overflow = ((n1 & 0x80) == (n2 & 0x80) && 										// Calculate overflow result.
									(n1 & 0x80) != (result & 0x80)) ? 1 : 0;
	szValue = result; 																// Use this value for S and Z flags.
	return result;
}

//*******************************************************************************************************
//											8 Bit Subtract with Carry
//*******************************************************************************************************

static BYTE8 sub8BitCarry(BYTE8 n1,BYTE8 n2) {
	carry ^= 1;																		// Toggle carry (z80 uses logic '1' borrow)
	BYTE8 result = add8BitCarry(n1,n2 ^ 0xFF);										// Use 2's complement to subtract
	carry ^= 1; halfCarry ^= 1;negate = 1; 											// Toggle carry, half carry and set 'N' flag.
	return result;
}

//*******************************************************************************************************
//										16 Bit Add without Carry
//*******************************************************************************************************

static WORD16 add16BitNoCarry(WORD16 n1,WORD16 n2) {
	LONG32 result = n1 + n2; 														// Calculate the result
	carry = result >> 16; 															// Extract the carry flag.
	negate = 0;																		// Clear negate flag.
	return result;
}

//*******************************************************************************************************
//											8 bit Increment
//*******************************************************************************************************

static BYTE8 increment8Bit(BYTE8 n) {
	n++;																			// Do the increment
	szValue = n;																	// Set S & Z
	negate = 0;																		// Clear N
	overflow = (n == 0x80) ? 1 : 0;													// Overflow set if it was $7F before.
	halfCarry = ((n & 0x0F) == 0) ? 1 : 0;											// Half carry set if it was $xF before 
	return n;
}

//*******************************************************************************************************
//											8 bit Decrement
//*******************************************************************************************************

static BYTE8 decrement8Bit(BYTE8 n) {
	n--;																			// Do the decrement
	szValue = n;																	// Set S & Z
	negate = 1;																		// Set N
	overflow = (n == 0x7F) ? 1 : 0;													// Overflow set if it was $80 before.
	halfCarry = ((n & 0x0F) == 0xF) ? 1 : 0;										// Half carry set if it was $x0 before 
	return n;
}

//*******************************************************************************************************
//												DAA code
//*******************************************************************************************************

// This if from http://www.worldofspectrum.org/faq/reference/z80reference.htm

static void daaCode(void) {
	BYTE8 correction = 0x00;
	BYTE8 originalA = a;

	if (a > 0x99 || carry != 0) { 													// If A > 0x99 or Carry flag is set
		correction = 0x60;															// Upper four bits of correction are 6
		carry = 1; 																	// Carry flag is set.
	} else {
		carry = 0; 																	// Carry flag is cleared (upper 4 bits already zero)
	}

	if ((a & 0x0F) > 9 || halfCarry != 0) { 										// If lower 4 bits of A are > 9 or half carry is set.
		correction |= 0x6;															// The lower four bits of correction factor are set to 6.
	}																				// (else - lower 4 bits already zero)

	if (negate == 0) a = a + correction; 											// If N is clear then add correction to A
	else             a = a - correction; 											// Else subtract correction from A

	szValue = a; 																	// SZ Value is set as per result.

	halfCarry = ((originalA ^ a) >> 4) & 1;											// Half carry = A (before) ^ A (after), bit 4.

	// N is unchanged.
}

#endif // _8080COREUTILS_H
