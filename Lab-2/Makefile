# Copyright (C) 2017 Daniel Page <csdsp@bristol.ac.uk>
#
# Use of this source code is restricted per the CC BY-NC-ND license, a copy of
# which can be found via http://creativecommons.org (and should be included as
# LICENSE.txt within the associated archive or repository).

lab-2_q : lab-2_q.c lab-2_q.h
	@gcc -Wall -std=gnu99 -m64 -O3 -o lab-2_q lab-2_q.c

.DEFAULT_GOAL := all

all   : lab-2_q

clean :
	@rm -f core lab-2_q

labtest : labtest.c
	@gcc -Wall -std=gnu99 labtest.c -o labtest
