# GameKeeb firmware

Firmware for [GameKeeb](https://github.com/JonnyHaystack/GameKeeb) - keyboard to
GameCube adapter. Hardware information is in the main repo.

This is a fork of Arte's
[pico-rectangle](https://github.com/JulienBernard3383279/pico-rectangle)
firmware.

### Safety information

You probably shouldn't have this adapter plugged into PC via USB and via its
Gamecube port at the same time in case the different grounds cause electrical
issues (I dunno I'm not an electrician).

### How to program your board:

- Download the latest release (on the right of the Github page)
- Plug in your Raspberry Pico to your computer via USB while holding the "BOOTSEL" white button on the board.
- The board should appear as an external drive. Put the .uf2 of your choice in there. The board should disconnect and be ready for use.

### Binary notes:

There are multiple .uf2 files in a release (currently 2). Pick one according to
the nerfs you want. You currently get to pick between 2 options: with or without
Peach's Parasol Dashing nerf.

Removing either of these doesn't make your controller non SWT ruleset compliant. Don't use them if you don't want them. Use them if you want true functional equivalence to the Frame1/B0XX layouts.

### Troubleshooting

#### Not working on PC with Mayflash adapter

You need to have both of the Mayflash adapter's USB ports plugged in, otherwise
it doesn't supply the 5V needed to power the keyboard.

### Contact

Discord: Haystack#1872
