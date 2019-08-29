.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1
		fork	%:l2
wall:
		ld	%0, r2
		st	r2, -31
		st	r2, -40
		st	r2, -49
		st	r2, -58
		st	r2, -67
		st	r2, -76
		st	r2, -85
		st	r2, -94
		st	r2, -103
		st	r2, -112
		st	r2, -121
		st	r2, -130
		st	r2, -139
		st	r2, -148
		st	r2, -157
		st	r2, -166
		st	r2, -175
		st	r2, -184
		st	r2, -193
		st	r2, -202
		st	r2, -211
		st	r2, -220
		st	r2, -229
		st	r2, -238
		st	r2, -247
		st	r2, -256
		st	r2, -265
		st	r2, -274
		st	r2, -283
		st	r2, -292
		st	r2, -301
		st	r2, -310
		st	r2, -319
		st	r2, -328
		st	r2, -337
		st	r2, -346
		st	r2, -355
		st	r2, -364
		st	r2, -373
		st	r2, -382
		st	r2, -391
		st	r2, -400
		st	r2, -409
		st	r2, -418
		st	r2, -427
		st	r2, -436
		st	r2, -445
		st	r2, -454
		st	r2, -463
		st	r2, -472
		st	r2, -481
		st	r2, -490
		st	r2, -499
		st	r2, -508
		live	%1
		zjmp 	%:wall
