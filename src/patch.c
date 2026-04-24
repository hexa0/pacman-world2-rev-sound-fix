#include "pacman.h"

void pmw2_pre_sound_update_hook()
{
	for (int i = 0; i < ACTIVE_SOUNDS_SIZE; i++)
	{
		// channels 0 and 1 are for the left and right channels of the music
		// i assume since the streaming is hard coded it doesn't ever set status to 1
		// so we need to manually skip those 2 voices

		if (active_sounds[i].status == 0 && i > 1)
		{
			active_sounds[i].voll = 0;
			active_sounds[i].volr = 0;
		}
	}

	// run the actual sound update after our hook
	soundUpdate();

	return;
}