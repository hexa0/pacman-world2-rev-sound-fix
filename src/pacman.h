#ifndef PACMAN_H
#define PACMAN_H

// all of these come from game.syms extracted like this:
// mips64r5900el-ps2-elf-nm -f posix SLUS_202.24 | grep " T " | awk '{print $1 " = 0x" $3 ";"}' > game.syms
// im unsure if other versions have symbols, but this is for SLUS 2.0 specifically




///////// standard library /////////




/*	Write formatted output to stdout.

	This function is a possible cancellation point and therefore not
	marked with __THROW.  */
extern int printf(const char *format, ...);




///////// game functions /////////




extern void soundUpdate(void);

/*	Writes formatted string to the screen at the specified coords
	
	This may not work depending on where you are calling it from

	X/Y ranges from 0 to 1
*/
extern void font_printfXY(float x, float y, char *fmt);




#endif // PACMAN_H