#include "pacman.h"
#include "stdio.h"

// from the NSTC US 2.0 debug symbols
typedef struct ACTIVESOUNDS
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
} active_sounds_t;

/// active_sounds addr
#define ACTIVE_SOUNDS_ADDR 0x46ac20
/// active_sounds size
#define ARRAY_SIZE 48

void pmw2_pre_sound_update_hook()
{
	active_sounds_t *sounds = (active_sounds_t *)ACTIVE_SOUNDS_ADDR;

	for (int i = 0; i < ARRAY_SIZE; i++)
	{
		// channels 0 and 1 are for the left and right channels of the music
		// i assume since the streaming is hard coded it doesn't ever set status to 1
		// so we need to manually skip those 2 voices

		if (sounds[i].status == 0 && i > 1)
		{
			sounds[i].voll = 0;
			sounds[i].volr = 0;
		}
	}

	// run the actual sound update after our hook
	soundUpdate();

	return;
}