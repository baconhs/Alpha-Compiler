all:
	bison --defines --output=parser.c parser.y
	flex *.l
	gcc -w -g -o calc lex_analyzer.c parser.c utils/symtable.c utils/utils.c utils/final_code.c utils/vm.c -lm
	gcc -w -g -o avm utils/vm.c utils/main.c

clean:
	rm calc alpha_bin.abc tcode_text.abc lex_analyzer.c parser.h parser.c avm