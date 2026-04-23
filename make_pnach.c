#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define GAME_CRC "E7EA3288"
#define CAVE_ADDR 0x00556AD0
#define SOUND_UPDATE_CALL_ADDR 0x0029938C

int main()
{
	FILE *bin = fopen(".tmp/patch.bin", "rb");

	if (!bin)
	{
		fprintf(stderr, "Error: Could not open .tmp/patch.bin\n");
		return 1;
	}

	char filename[32];
	sprintf(filename, "build/%s.pnach", GAME_CRC);
	FILE *out = fopen(filename, "w");

	fprintf(out, "gametitle=Pac-Man World 2 (U)(SLUS-20224) (Greatest Hits)\n");
	fprintf(out, "comment=Fixes the ringing sound after revving up\n\n");
	fprintf(out, "[Fix Tinnitus Sound Glitch]\n");
	fprintf(out, "author=hexa.pet\n");

	uint8_t byte;
	uint32_t current_addr = CAVE_ADDR;

	fprintf(out, "// inject pmw2_pre_sound_update_hook\n");

	while (fread(&byte, 1, 1, bin) == 1)
	{
		fprintf(out, "patch=1,EE,%08x,byte,%02x\n", current_addr, byte);
		current_addr++;
	}

	fclose(bin);

	uint32_t jal_val = (CAVE_ADDR >> 2) | 0x0C000000;

	uint8_t hook_bytes[4];
	hook_bytes[0] = jal_val & 0xFF;
	hook_bytes[1] = (jal_val >> 8) & 0xFF;
	hook_bytes[2] = (jal_val >> 16) & 0xFF;
	hook_bytes[3] = (jal_val >> 24) & 0xFF;

	fprintf(out, "// hook soundUpdate call\n");

	for (int i = 0; i < 4; i++)
	{
		fprintf(out, "patch=1,EE,%08x,byte,%02x\n", SOUND_UPDATE_CALL_ADDR + i, hook_bytes[i]);
	}

	fclose(out);
	printf("created patch %s\n", filename);

	return 0;
}