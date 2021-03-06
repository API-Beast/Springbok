#!/usr/bin/python3
from argparse import ArgumentParser
import os

parser = ArgumentParser(description="Create a new header file which includes all headers in the given directory.")
parser.add_argument('directory')
args = parser.parse_args()

directory = args.directory
headers = [x for x in os.listdir(directory) if x.endswith(".h") or x.endswith(".hpp") and not x.endswith("_Templates.hpp")]
docs    = [x for x in os.listdir(directory) if x.endswith(".md")]
headerDir = directory.rstrip('/.\\').lstrip('/.\\')

print("// Springbok Collection Header")
print("// This file was automatically generated by 'gencompheader.py'")
print()
for header in headers:
	print("#include <Springbok/{0}/{1}>".format(headerDir, header))
print()
for md in docs:
	title = "Documentation included from: {0}/{1}".format(headerDir, md)
	intend = " * "
	print("/* "+title)
	print(intend+"{0}".format("=" * len(title)))
	print(intend)
	for line in open(directory+"/"+md):
		print(intend+line.rstrip())
	print("*/")
	print()