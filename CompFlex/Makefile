all: tokenizer.l parser.y helper.cpp helper.h
	lex tokenizer.l
	yacc -d parser.y 
	yacc parser.y -o gm.cc
	cc -c lex.yy.c -o lex.yy.o
	g++ -c helper.cpp -o helper.o
	g++ -c this.cpp -o this.o
	# g++ lex.yy.o gm.cc helper.cpp this.cpp -o genTemp

run: genTemp code.cpp
	./genTemp code.cpp

clean:
	rm -f genTemp
	rm -f gm.cc lex.yy.c y.tab.h lex.yy.o y.tab.c