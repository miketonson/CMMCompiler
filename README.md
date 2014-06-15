CMM compiler
===============
####CMM language or C-- is a C style lightweight language

##Project progress

- [x] Lexical Analysis
- [x] Syntax Analysis 
- [x] Semantic Analysis
- [x] Intermediate-code Generator
- [x] Machine-code Generator

##Important date

* Sun Mar 9 18:58:19 2014 First push to GitHub
* Wed Mar 12 19:59:33 2014 Lexical Analysis finished
* Thu Mar 27 14:26:24 2014 Syntax Analysis finished
* Thu Apr 24 23:52:14 2014 Semantic Analysis finished
* Wed May 21 13:22:26 2014 Intermediate-code Generator finished
* Fri Jun 13 10:26:44 2014 All finished

##Support Environment

* GNU Flex version 2.5.35
* GNU Bison version 2.5
* GCC version 4.6.3
* GNU Linux Release: Ubuntu 12.04, kernel version 3.2.0-29
* SPIM Version 8.0

##Usage method

First you have to have all the suppport environment, both flex, bision, and spim.

Put your cmm code into test.cmm or other .cmm file, and new a file name code.s or other .s file.

	make
	./parser test.cmm code.s
	spim -file code.s

####Copy Right &copy;miketonson

####Referance
1. *Compilers: Principles, Techniques and Tools  Second Edition*
2. *Project guide for Compiler class* by Prof.Chang Xu
