#ifndef PACMAN_H
#define PACMAN_H

// all the external functions come from game.syms extracted like this:
// mips64r5900el-ps2-elf-nm -f posix SLUS_202.24 | grep " T " | awk '{print $1 " = 0x" $3 ";"}' > game.syms
// im unsure if other versions have full debug symbols, but this is for SLUS 2.0 specifically




///////// standard headers /////////




/*	Write formatted output to stdout.

	This function is a possible cancellation point and therefore not
	marked with __THROW.  */
extern int printf(const char *format, ...);




///////// pmw2 headers /////////

typedef struct
{
	/// @brief this is 1 if the sound is active, zero if it is inactive
	int status;
	unsigned int handle;
	int pitch;
	int paused_pitch;
	int pending;
	char *name;
	int loaded;
	int zone;
	/// @brief if status is 0 this is not reset normally
	int voll;
	/// @brief if status is 0 this is not reset normally
	int volr;
} ACTIVESOUNDS;

/// active_sounds addr
#define ACTIVE_SOUNDS_ADDR 0x46ac20
/// active_sounds size
#define ARRAY_SIZE 48

extern void soundUpdate(void);

/*	Writes formatted string to the screen at the specified coords
	
	This may not work depending on where you are calling it from

	X/Y ranges from 0 to 1
*/
extern void font_printfXY(float x, float y, char *fmt);




#endif // PACMAN_H