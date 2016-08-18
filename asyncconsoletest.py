#!/usr/bin/env python

import os

if os.name == 'nt':
	import win32api
	import win32con
	import time

	keypress = win32api.GetAsyncKeyState
	spacekey = win32con.VK_SPACE
else:
	import curses
	stdscr = curses.initscr()
	curses.noecho()
	curses.cbreak()
	stdscr.keypad( True )
	stdscr.timeout( 0 )

	spacekey = 32
	def keypress( ch ):
		c = stdscr.getch()
		if c < 0:
			return 0
		elif c == ch:
			return 1
		else:
			return 0

count = 0

while True:
	print( count )
	count = count + 1

	if keypress( spacekey ):
		break;

	time.sleep( 0.1 )

if os.name != 'nt':
	curses.nocbreak()
	stdscr.keypad( False )
	curses.echo()
	curses.endwin()

