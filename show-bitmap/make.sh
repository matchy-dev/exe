#!/bin/sh -x

windres -o res.o res.rc
gcc -o showbitmap.exe showbitmap.c res.o -mwindows
