#!/usr/bin/python3
from argparse import ArgumentParser
from sys import stdout
from itertools import dropwhile
import re

parser = ArgumentParser(description="Load a header and extract all markdown from it.")
parser.add_argument('input')
parser.add_argument('--lang', '-l', nargs=1)
args = parser.parse_args()

infile = open(args.input, 'r') # Binary, since we don't really care about the encoding of the input

language = "cpp"
mdblockStarted = False

curCodeBlock = []

endBlockOn = ('public:', "class", "{", '};', '//~!')
newLineOn  = ('#', '===', '---')

removeEx  = [re.compile('template<.*?>')]

infile.seek(0)

lastLineBlank = True
def outnl():
	global lastLineBlank
	if lastLineBlank == False:
		lastLineBlank = True
		print()
	
def out(*arg):
	global lastLineBlank
	lastLineBlank = False
	print(*arg)

def popCodeBlock():
	global curCodeBlock
	for ex in removeEx:
		curCodeBlock = [re.sub(ex, '', line) for line in curCodeBlock]
	curCodeBlock = list(filter(lambda x: len(x.lstrip().rstrip()) != 0, curCodeBlock))
	if len(curCodeBlock) > 0:
		intendation  = [len(a) - len(a.lstrip()) for a in curCodeBlock]
		baseIntend   = min(intendation)
		out("```"+language)
		for line in curCodeBlock:
			out(line[baseIntend:])
		out("```")
		outnl()
	curCodeBlock = []

for line in infile:
	line = line.rstrip()
	stripped = line.lstrip() # Will strip whitespace if called without arguments
	
	if stripped.startswith(endBlockOn):
		mdblockStarted = False
		popCodeBlock()
	elif stripped.startswith("//~ "):
		mdblockStarted = True
		popCodeBlock()
		md = stripped[len('//~ '):]
		if md.startswith(newLineOn):
			outnl()
		out(md)
		if md.startswith(newLineOn):
			outnl()
	else:
		if mdblockStarted:
			curCodeBlock.append(line)
		
popCodeBlock()