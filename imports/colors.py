#!/usr/bin/env python

import os

BOLD = ''
NORM = ''
PURPLE = ''
BLUE = ''
GREEN = ''
YELLOW = ''
RED = ''
WHITE = ''
MAGENTA = ''
UNDERLINE = ''

if os.name is not 'nt':
	PURPLE = '\033[95m'
	BLUE = '\033[94m'
	GREEN = '\033[92m'
	YELLOW = '\033[93m'
	RED = '\033[91m'
	WHITE = '\033[0m'
	MAGENTA = '\033[35m'
	BOLD = '\033[01m'
	UNDERLINE = '\033[04m'

else:
	PURPLE = ''
	BLUE = ''
	GREEN = ''
	YELLOW = ''
	RED = ''
	WHITE = ''
	MAGENTA = ''
	BOLD = ''
	UNDERLINE = ''


def bold(str):
	return BOLD + str + WHITE

def underline(str):
	return UNDERLINE + str + WHITE

def purple(str):
	return PURPLE + str + WHITE

def blue(str):
	return BLUE + str + WHITE

def green(str):
	return GREEN + str + WHITE

def red(str):
	return RED + str + WHITE

def yellow(str):
	return YELLOW + str + WHITE

def white(str):
	return WHITE + str + WHITE
