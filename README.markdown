cpp-signal
==========

Introduction
------------

This is a simple C++ callback library. It's conceptually similar to FastDelegate,
with a primary goal of having an extremely simple, clean API. Secondary goals
include low memory (low template bloat), zero external dependencies, and a high
level of portability.

Usage
-----

Using the library is incredibly simple. First, add the files to your project, Makefile,
IDE, etc. Then, to use the library, simply include "signal.h".

Here's a simple example:

	#include "signal.h"
	
	void beep() { /* make speaker beep */ }

	void flash() { /* make screen flash */ }

	int main(int arg, char** argv)
	{
		// create a signal which we'll emit any time a button is pressed
		signal<void> button_pressed;

		// connect (i.e. subscribe) functions to the signal
		button_pressed.connect(&beep);
		button_pressed.connect(&flash);

		// main loop, check for button press, and call signal
		while ( true )
		{
			if ( is_button_pressed() )
			{
				// call signal, which in turn calls all slot functionss (i.e. subscribers)
				button_pressed();
			}
		}
	}

TO DO
-----

* better documentation
* consistent code cleanup
* generate.rb creates a single header file
* add License clause to source and LICENSE file

