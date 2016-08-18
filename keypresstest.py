#!/usr/bin/env python

import sys
sys.path.append( 'keypress/build/lib.linux-x86_64-3.5' )
import keypress
import time

# print( help( keypress ) )
# print( dir( keypress ) )
# keypress.helloworld()

count = 0

while True:
	print( count )
	count = count + 1

	if keypress.keypress( " " ):
		break;

	time.sleep( 0.1 )