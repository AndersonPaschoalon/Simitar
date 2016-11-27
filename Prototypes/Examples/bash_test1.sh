#!/bin/bash
source  bash_source.sh


main()
{
	echo "Testing test_ls"
	test_ls;

	echo "Testing print_number -> it should print 42"
	print_number		

}

print_number()
{
	echo "42"

}

main;
