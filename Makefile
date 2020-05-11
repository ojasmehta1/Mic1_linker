linker : linker.c
	gcc -ansi -Wall -o linker linker.c

run :
	./masm_mrd -o < main.asm > main.obj
	./masm_mrd -o < xbsywt.asm > xbsywt.obj
	./masm_mrd -o < rbsywt.asm > rbsywt.obj
	./linker main.obj xbsywt.obj rbsywt.obj > main.exe
	./mic1 prom_mrd.dat main.exe 0 2048

dump :
	./masm_mrd -o < main.asm > main.obj
	./masm_mrd -o < xbsywt.asm > xbsywt.obj
	./masm_mrd -o < rbsywt.asm > rbsywt.obj
	./linker -o main.obj xbsywt.obj rbsywt.obj 

clean :
	rm *.obj
	rm main.exe
	rm linker
