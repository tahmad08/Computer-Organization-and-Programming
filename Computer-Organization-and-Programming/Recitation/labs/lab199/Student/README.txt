======================================================================
CS2110                        Lab 19                      Fall 2018
======================================================================
Read the instructions in the pixels.c file

Dependencies
------------

NOTE: This has changed since last lab!

On Docker, re-run the cs2110docker.sh script to update the image.

On virtual machines or native installs, you need:

	$ sudo apt update
	$ sudo apt install gcc-arm-none-eabi cs2110-gba-linker-script nin10kit mednafen



(If you don't have it already from installing complx, you may need to
 add Brandon's 2110 package repository with

    $ sudo add-apt-repository ppa:tricksterguy87/ppa-gt-cs2110

 and then re-run the two commands above.)



Assignment
----------

HAPPY HALLOWEEN EVERYBODY!

For this spooky lab, cd into the directory containing bouncingghost.c
and the Makefile. To build and run the emulator, run:

    $ make emu 


You should see Trevor the ghost. You can move Trevor around the screen
by pressing any of the arrow keys. Whenever Trevor moves, he leaves his
ghost residue everywhere! This is because the pixels on the screen where
Trevor was are not being reset to the color of the screen background
(black) after he leaves.

Your assignment is to move Trevor cleanly around the screen. How? Call
drawRectangle() on the portion of the screen that Trevor just exited.

As well, the image is being drawn too quickly! At the bottom of the
while loop there should be a call to a function that waits for the
screen to refresh.

When you are done, come show it to us.
