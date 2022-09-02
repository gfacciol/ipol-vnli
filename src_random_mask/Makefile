OPTS= -O3 -ftree-vectorize -funroll-loops -fopenmp

RBIN=random_mask

RSRC=io_png.c random_mask.c drawtext.c

CFLAGS= $(OPTS) -Wall -std=c99 -Wextra -pedantic

LDFLAGS= -lpng -lfftw3 -lgomp -lm


all:  $(RBIN)

$(RBIN): $(RSRC:.c=.o)
	$(CC) $(RSRC:.c=.o) -o $(RBIN) $(LDFLAGS) 

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(RSRC:.c=.o)
	rm -f $(FBIN)
	rm -f $(RBIN)


