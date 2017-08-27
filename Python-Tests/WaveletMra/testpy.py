#!/usr/bin/python3.5
import sys

def print_help():
	print("this help")

def main(args):
	print(args)
	print(args[0])
	print(args[1])
	for x in args:
		print (x)


if __name__ == '__main__':
	try:
		main(sys.argv[1:]) 
	except:
		print_help()
		
