# Duck
This... thing generates WAV files filled in with duck quacks corresponding to the given string.

# Usage
`duck_enc [string] [out]` generates an `out` file containing the duck quack thing.

`duck_dec [wav file] [out]` reads back the original string described in the file and writes it back into the `out` file.

# Compilation
First you need libsndfile : http://www.mega-nerd.com/libsndfile/

Then you can invoke `make` to build the thing.

# Example
`duck_enc dummy.txt out.wav` creates `out.wav`, an audio file playable by any sound player, from the contents of the `dummy.tmp` file.

`duck_dec out.wav dummy.raw` writes back the contents embedded in `out.wav` into `dummy.raw`.

# Why ?
Don't ask me.

# Notes
The code is crappy, malloc-d arrays aren't freed and stuff.

I wrote that in a hurry, I might fix this later.
