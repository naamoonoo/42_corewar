# define WRITE_TO_MEM(MEM, VALUES, SIZE) \
	for (int i = 0; i < SIZE; i++) \
	{ \
		MEM->data = VALUES[i]; \
		MEM = MEM->next; \
	} \
