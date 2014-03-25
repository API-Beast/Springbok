//  Copyright (C) 2014 Manuel Riecke <spell1337@gmail.com>
//  Licensed under the terms of the WTFPL.
//
//  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
//  0. You just DO WHAT THE FUCK YOU WANT TO.

#pragma once

inline const char* KeyCodeToKeyName(short i)
{
	switch(i)
	{
		#define Key(A, B) case B: return A;
		Key("Space", 32);
		Key("'", 39); 
		Key(",", 44); 
		Key("-", 45); 
		Key(".", 46); 
		Key("/", 47); 
		Key("0", 48);
		Key("1", 49);
		Key("2", 50);
		Key("3", 51);
		Key("4", 52);
		Key("5", 53);
		Key("6", 54);
		Key("7", 55);
		Key("8", 56);
		Key("9", 57);
		Key(";", 59); 
		Key("=", 61); 
		Key("A", 65);
		Key("B", 66);
		Key("C", 67);
		Key("D", 68);
		Key("E", 69);
		Key("F", 70);
		Key("G", 71);
		Key("H", 72);
		Key("I", 73);
		Key("J", 74);
		Key("K", 75);
		Key("L", 76);
		Key("M", 77);
		Key("N", 78);
		Key("O", 79);
		Key("P", 80);
		Key("Q", 81);
		Key("R", 82);
		Key("S", 83);
		Key("T", 84);
		Key("U", 85);
		Key("V", 86);
		Key("W", 87);
		Key("X", 88);
		Key("Y", 89);
		Key("Z", 90);
		Key("LEFT_BRACKET", 91); 
		Key("BACKSLASH", 92); 
		Key("RIGHT_BRACKET", 93); 
		Key("GRAVE_ACCENT", 96); 
		Key("WORLD_1", 161);
		Key("WORLD_2", 162);

		/* Function keys */
		Key("Esc", 256);
		Key("Enter", 257);
		Key("Tab", 258);
		Key("Backspace", 259);
		Key("Insert", 260);
		Key("Delete", 261);
		Key("Right", 262);
		Key("Left", 263);
		Key("Down", 264);
		Key("Up", 265);
		Key("Page Up", 266);
		Key("Page Down", 267);
		Key("Home", 268);
		Key("End", 269);
		Key("Caps Lock", 280);
		Key("Scroll Lock", 281);
		Key("Num Lock", 282);
		Key("Print", 283);
		Key("Pause", 284);
		Key("F1", 290);
		Key("F2", 291);
		Key("F3", 292);
		Key("F4", 293);
		Key("F5", 294);
		Key("F6", 295);
		Key("F7", 296);
		Key("F8", 297);
		Key("F9", 298);
		Key("F10", 299);
		Key("F11", 300);
		Key("F12", 301);
		Key("F13", 302);
		Key("F14", 303);
		Key("F15", 304);
		Key("F16", 305);
		Key("F17", 306);
		Key("F18", 307);
		Key("F19", 308);
		Key("F20", 309);
		Key("F21", 310);
		Key("F22", 311);
		Key("F23", 312);
		Key("F24", 313);
		Key("F25", 314);
		Key("Keypad 0", 320);
		Key("Keypad 1", 321);
		Key("Keypad 2", 322);
		Key("Keypad 3", 323);
		Key("Keypad 4", 324);
		Key("Keypad 5", 325);
		Key("Keypad 6", 326);
		Key("Keypad 7", 327);
		Key("Keypad 8", 328);
		Key("Keypad 9", 329);
		Key("Keypad ,", 330);
		Key("Keypad /", 331);
		Key("Keypad *", 332);
		Key("Keypad -", 333);
		Key("Keypad +", 334);
		Key("Keypad Enter", 335);
		Key("Keypad =", 336);
		Key("Shift", 340);
		Key("Ctrl", 341);
		Key("Alt", 342);
		Key("Meta", 343);
		Key("Shift (Right)", 344);
		Key("Ctrl  (Right)", 345);
		Key("Alt   (Right)", 346);
		Key("Meta  (Right)", 347);
		Key("Menu", 348);
		
		default: return "Unknown Key";
	};
};