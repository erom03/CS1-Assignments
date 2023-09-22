# Assignment-2-Rescue-Mission
## Objective
Give practice with binary search in C.

## Story
It seems that one of the ships did not heed your storm warning. You received a single
transmission before your lost contact. They reported that the ship cannot change its speed.
You know that the max speed is S knots (nautical miles per hour). The ship should be traveling
in the positive x-direction at an integral speed (in the range of 0 to S). Based on the
transmission quality you know that the ship transmitted from an integral x location in the range
of 0 to L inclusive.

You will send a team to save them, but the rescue team will only be able to be sent once to a
single location and takes 1 hour to arrive, so you must determine the exact location of the ship.
Luckily you are able to borrow a satellite that passes over the ocean every hour. It can take a
photo of only 1 nautical mile, but you can use this to determine if the ship has passed the
location by picking up the traces of a wake, if the ship is at that location by picking up the picture
of the ship, or if the ship has not yet reached that location by picking up nothing in the picture.

You want to ensure that the ship is not stranded for too long. The ship has to be rescued in 24
hours (at most 23 pictures). Keep in mind that after the last picture the ship will move for a full
hour while you launch the rescue team. Finally, your first photo will be exactly 1 hour after the
initial distress signal was sent.

## Problem
Write a program that when given the maximum starting speed of the ship and the maximum x
coordinate, can ask for information at specific x-coordinates at most 23 times, and can at any
point after a query can report the current location of the ship.

## Input
Input will begin with a line containing 2 integers, S and L (1 ≤ S, L ≤ 100), representing the
maximum possible speed of the ship in Knots and the maximum possible starting coordinate of
the ship, respectively. Following this will be multiple lines. Each line contains a single response
to one of your queries.  The responses will be one of the following strings
* Wake - The ship has already passed by
* No Wake - The ship has not passed this location as of yet
* Boat! - The ship was captured in the photo

The testing system will allow you to read the response only after your program prints the query
and flushes the standard output (use fflush(stdout)).

## Output
To make the queries your program should print to standard output. To ask for a photo of a
location your program should output “? x” where x is the location to take the photo. To send the
rescue team your program should output “! x” where x is the location of the ship. Your program
must flush the output (use fflush(stdout)) after each query and after your command to send the
rescue team.
