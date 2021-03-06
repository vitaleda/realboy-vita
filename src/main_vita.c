/* RealBoy Emulator: Free, Fast, Yet Accurate, Game Boy/Game Boy Color Emulator.
 * Copyright (C) 2013 Sergio Andrés Gómez del Real
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include "gboy.h"
#include "main.h"
#include "file_chooser.h"

static const char *supported_ext[] = {
	"gb", "gbc", "sgb", NULL
};

int main()
{
	char rom_path[PATH_MAX];

	printf("\nRealBoy %s\n", "0.2.2");

	sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);

	vita2d_init();
	vita2d_set_clear_color(RGBA8(0, 0, 0, 0xFF));

	while (1) {
		strcpy(current_dir, "ux0:");

		int ret = file_choose(
			current_dir,
			rom_path,
			"Choose a GB/GB Color/Super GB ROM:",
			supported_ext
			);

		if (ret == -1)
			break;

		if ( (rom_file = fopen(rom_path, "r")) == NULL) {
			printf("\nError opening %s\n", rom_path);
			continue;
		}

		file_path = strndup(rom_path, 256);

		if (rom_file != NULL)	{
			init_conf();
			int ret_val; // value returned from emulation
			/* Start Virtual Machine */
			ret_val = start_vm();
			/* Error returned if file not valid */
			if (ret_val == -1) {
				printf("File %s not a gb binary\n\n", rom_path);
			}
		}

		free(file_path);
	}

	vita2d_fini();

	sceKernelExitProcess(0);
	return 0;
}
