# Duck
This... thing generates WAV files filled in with duck quacks corresponding to the given string.

# Usage
`duck_enc [string]` generates an `out.wav` file containing the duck quack thing.

`duck_dec [wav file]` reads back the original string described in the file.

# Compilation
First you need libsndfile : http://www.mega-nerd.com/libsndfile/

Then you can invoke `make` to build the thing.

# Example
`duck_enc "Hello quack world"` creates `out.wav`, an audio file playable by any sound player.

`duck_dec out.wav` writes back "Hello quack world".

# Why ?
Don't ask me.

# Notes
The code is crappy, malloc-d arrays aren't freed and stuff.

I wrote that in a hurry, I might fix this later.
