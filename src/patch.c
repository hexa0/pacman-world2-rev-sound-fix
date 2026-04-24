#include "pacman.h"

void pmw2_pre_sound_update_hook()
{
	ACTIVESOUNDS *sounds = (ACTIVESOUNDS *)ACTIVE_SOUNDS_ADDR;

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