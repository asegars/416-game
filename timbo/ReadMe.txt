Tim Curtis
CpSc 416
10/5/09

ReadMe.txt

This program was successfully compiled and executed on the vector5 lab machine.
A makefile is included, so simply type 'make' to compile the program.  To
execute, just use './run'.

When this program was checked with Valgrind, only a loss of 8 bytes was recorded
in two blocks due to SDL library code:

==22062== LEAK SUMMARY:
==22062==    definitely lost: 8 bytes in 2 blocks.
==22062==      possibly lost: 0 bytes in 0 blocks.
==22062==    still reachable: 29,891 bytes in 387 blocks.
==22062==         suppressed: 0 bytes in 0 blocks.
==22062== Reachable blocks (those to which a pointer was found) are not shown.
==22062== To see them, rerun with: --show-reachable=yes

As a starting point, the basic ball animation framework was used (found on the
course website assignment page).  From there, the first change that was
implemented was on the cushion for the viewport.  These were changed to always
have the player in the middle of the screen.  Additionally, if the cushion was
lessened for a different effect, the player would no longer be bounded on the
bottom cushions when traveling in the negative X or Y directions (extra checks
were added to the player.cpp 'update' function).  Also, the player sprite now
turns (flips) when traveling in positive and negative X directions, 
respectively.

As a second extension, you will find that fireballs have been added in the
background.  These fireballs travel around the full screen independent from the
viewport, and are drawn into view when they happen to be passing through the
viewport coordinates.  The number of fireballs can be changed in manager.cpp by
reinitializing the const value 'MAX_BALLS'.

As a third extension, collision detection between the fireballs and the player
have been added.  This is apparent when the program is run, because a new sprite
representing an exploding player is blitted onto the screen as it is colliding
with a fireball.  Once the player the collision is no longer, the original
player is blitted back to the screen, since the snowman is inherently
invincible.

All sprites for this assignment were created using GIMP on the lab machines.

If you have any problems compiling or executing this program, or any questions
in general about the code, please email me:  tjcurti@clemson.edu.
