#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sndfile.h>

short *CharArrays[127];

/* https://stackoverflow.com/questions/5156192/programmatically-increase-the-pitch-of-an-array-of-audio-samples/5362025 */
float InterpolateHermite4pt3oX(short* x, float t)
{
    float c0 = x[1];
    float c1 = .5F * (x[2] - x[0]);
    float c2 = x[0] - (2.5F * x[1]) + (2 * x[2]) - (.5F * x[3]);
    float c3 = (.5F * (x[3] - x[0])) + (1.5F * (x[1] - x[2]));
    return (((((c3 * t) + c2) * t) + c1) * t) + c0;
}

void ScratchMix(short* outwave, short* inwave, float rate, int inputLen)
{
   float index = 0;
   while (index < inputLen)
   {
      int i = (int)index;          
      float frac = index-i;      //will be between 0 and 1
      short s1 = inwave[i];
      short s2 = inwave[i+1];
      *outwave++ = InterpolateHermite4pt3oX(inwave+i-1,frac);
      index+=rate;
   }
}

int main(int argc, char* argv[])
{
    /* Check arguments */
    if(argc < 2)
    {
        printf("usage: %s [string]\n", argv[0]);
        exit(1);
    }
    
    /* Initialize char arrays */
    printf("initializing Duck, please wait...\n");
    SF_INFO *quackinfo = (SF_INFO*)malloc(sizeof(SF_INFO));
    SF_INFO *outinfo = (SF_INFO*)malloc(sizeof(SF_INFO));
    SNDFILE* quack = sf_open("quack16.wav", SFM_READ, quackinfo) ;
    outinfo->samplerate = quackinfo->samplerate;
    outinfo->format = quackinfo->format;
    outinfo->channels = quackinfo->channels;
    SNDFILE* out = sf_open("out.wav", SFM_WRITE, outinfo);
    int fr = quackinfo->frames;
    
    /* Build reference quack */
    short *quackarray = (short*)(malloc(fr * sizeof(short)));
    sf_readf_short(quack, quackarray, quackinfo->frames);

    /* Build a sample for each char */
    for(char c = (char)0; c <= 'z'; c++)
    {
        CharArrays[c] = malloc(fr * sizeof(short));
        float factor = 0.5f;
        int offset = c;
        factor += 0.0075 * offset;
        ScratchMix(CharArrays[c], quackarray, factor, fr);
    }

    size_t sz = strlen(argv[1]);
    for(size_t i = 0; i < sz; i++)
    {
        sf_count_t ret = sf_write_short(out, CharArrays[argv[1][i]], fr);
    }

    sf_write_sync(out);
    sf_close(quack);
    sf_close(out);
    return 0;
}
