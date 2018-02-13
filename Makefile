all: enc dec
	
enc:
	gcc duck_enc.c -O0 -o duck_enc -lsndfile

dec:
	gcc duck_dec.c -O0 -o duck_dec -lsndfile

clean:
	rm -f duck_enc duck_dec

.PHONY: all enc dec clean
