.name "leapfrog"
.comment "darn you IDX_MOD"

# register 2 is the program's relative offset (0 for p1 and 16 for p2)
# registers 3-6 store the frog's bytecode

sti		r1, %:frog, %1

fork	%41

program1:
	ldi		%:frog, %0, r3	# load 01 __ __ __
	ldi		%:frog, %4, r4	# load __ 0b 64 03
	ld		%32440843, r5	# load 01 ef 02 0b
	ld		%1677984237, r6	# load 64 04 01 ed
	ld		%0, r2			# set offset to 0 and also set carry
	zjmp	%:frog

program2:
	ld		%16, r2			# set offset to 20
	ld		%34300933, r3	# load 02 0b 64 05
	ld		%32178699, r4	# load 01 eb 02 0b
	ld		%1678115305, r5	# load 64 06 01 e9
	ld		%34144727, r6	# load 02 09 01 d7
	ld		%0, r15			# set carry

frog:
	live	%0				# 01 __ __ __ __
	sti		r3, %495, r2	# 0b 64 03 01 ef 02
	sti		r4, %493, r2	# 0b 64 04 01 ed 02
	sti		r5, %491, r2	# 0b 64 05 01 eb 02
	sti		r6, %489, r2	# 0b 64 06 01 e9 02
	zjmp	%471			# 09 01 d7
