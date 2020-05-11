start:  lodd on:
        stod 4095		
        call xbsywt: 		    
		loco str1: 		
		call nextWord:	
		call input:	
    	lodd binnum:	
		stod sum:		
		
		loco str1:	
		call nextWord:		
	
		call input:		
		lodd binnum:	
		addd sum:	
		stod sum:	
		stod ans:	
	
		jneg end:		

		call xbsywt:	    
		loco str2:		
		call nextWord:		

		call xbsywt:	
		call offset:		
		call xbsywt:	
		lodd zero:	

		halt

end:	loco str3:		
		call nextWord:	
		lodd cneg1:		
		halt 	
		
nextWord:  pshi
        addd c1:
        stod pstr1:
        pop
        jzer carry:
        stod 4094
        push
        subd c255:
        jneg carry:
        call sb:
        insp 1
        push
        call xbsywt:
        pop
        stod 4094
        call xbsywt:
        lodd pstr1:
        jump nextWord:

carry:   lodd cr:
        stod 4094
        call xbsywt:
        lodd nl:
        stod 4094
        call xbsywt:
	retn

input:	lodd on:
	stod 4093
	call rbsywt:
	lodd 4092
	subd numoff:
	push

nextNum:	call rbsywt:
	lodd 4092
	stod nxtchr:
	subd nl:
        jzer endnum:
	mult 10
	lodd nxtchr:
	subd numoff:
	addl 0
	stol 0
	jump nextNum:
endnum: pop
	stod binnum:
        lodd 4092
        loco 0
	retn
sb:     loco 8
loop1:  jzer finish:
        subd c1:
        stod lpcnt:
        lodl 1
        jneg add1:
        addl 1
        stol 1
        lodd lpcnt:
        jump loop1:
add1:   addl 1
        addd c1:
        stol 1
        lodd lpcnt:
        jump loop1:

finish: lodl 1			
        retn

offset:	lodd on:
	stod 4095
	lodd cneg1:	
	push 			
	lodd mask:	
	push     	

main:	lodd ans:		
	jzer print:	
	lodd mask:
	push		
	lodd ans:	
	push
	div			
	pop			
	stod ans:		
	pop
	insp 2		
	addd numoff:	
	push 	
	jump main:		

print:	pop			
	jneg done:	
	stod 4094		
	call xbsywt:	
	jump print:		

done: retn 			


numoff: 48
nxtchr: 0
binnum: 0
lpcnt:  0
mask:   10
on:     8
nl:     10
cr:     13
c1:     1
c255:   255
cneg1:	-1 			; constant -1
pstr1:  0
str1:   "Please enter a 1-5 digit number followed by enter."
str2:   "The sum of the two numbers is: "
str3:   "The sum has endflowed."
sum:	0			; stores the first number
ans:	0			; stores the sum
zero:	0

