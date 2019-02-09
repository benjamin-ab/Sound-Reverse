/*
 * File: reverse.c
 * Course: TCSS 333 – Winter 2016
 * Assignment 6 – Sound Files
 * Copyright 2016 Benjamin Abdipour
 */

/*
   This program takes two arguments. First is a WAV file to be reversed and
   the second argument is the file name of the new file. The first file to 
   be reversed should be in specific format and sample rate and number of 
   channels. The first 44 bytes of the original file are the header of the
   file and the program does not change these information. However, I got 
   the same result with changing the header information.
 */
 
#include <stdio.h>
#include <malloc.h>
#include <sndfile.h>

#define VARIABLES 3
#define HEADER 44

int main(int argc, char *argv[]) {
    if (argc != VARIABLES) {
        fprintf(stderr, "Error in reading the arguments.\n");
        return 1;
    }

    // Opening input file
    SF_INFO sndInfo;

    SNDFILE *sndFileIn = sf_open(argv[1], SFM_READ, &sndInfo);
    if (sndFileIn == NULL) {
        fprintf(stderr, "Error reading the input file.\n");
        return 1;
    }

    // Setting file settings
    SF_INFO info;
    info.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    info.channels = sndInfo.channels;
    info.samplerate = sndInfo.samplerate;

    // Checking format
    if (sndInfo.format != (SF_FORMAT_WAV | SF_FORMAT_PCM_16)) {
        fprintf(stderr, "Input file should be 16bit and of type WAV.\n");
        sf_close(sndFileIn);
        return 1;
    }

    // Checking number of channels
    if (sndInfo.channels != info.channels) {
        fprintf(stderr, "The channels should be %d.\n", info.channels);
        sf_close(sndFileIn);
        return 1;
    }

    // Allocating memory
    double *buffer = (double *) malloc(
            sndInfo.frames * sizeof(double) * sndInfo.channels);
    if (buffer == NULL) {
        fprintf(stderr,
                "Could not allocate enough memory for the input file.\n");
        sf_close(sndFileIn);
        return 1;
    }

    // Loading from the input file
    double data[sndInfo.frames * sndInfo.channels];
    long numFrames = sf_readf_double(sndFileIn, data,
            sndInfo.frames * sndInfo.channels);

    // Checking correct number of frames loaded from the input file
    if (numFrames != sndInfo.frames) {
        fprintf(stderr, "Error in reading the correct number of frames.\n");
        sf_close(sndFileIn);
        free(buffer);
        return 1;
    }

    // Closing the input file
    sf_close(sndFileIn);

    // Opening output file for writing
    SNDFILE *sndFileOut = sf_open(argv[2], SFM_WRITE, &info);
    if (sndFileOut == NULL) {
        fprintf(stderr, "Error opening the output file.\n");
        free(buffer);
        return -1;
    }

    // Re-arranging frames
    long writtenFrames = 0;
    int start = HEADER;
    int end = sndInfo.frames * sndInfo.channels - 1;

    while (start < end) {
        double temp = data[start];
        data[start] = data[end];
        data[end] = temp;
        start++;
        end--;
    }

    // Writing frames
    writtenFrames = sf_writef_double(sndFileOut, data, numFrames);

    // Checking correct number of frames written to the output file
    if (writtenFrames != sndInfo.frames) {
        fprintf(stderr, "Error in writing the correct number of frames.\n");
        sf_close(sndFileOut);
        return 1;
    }

    // Closing the output file
    sf_close(sndFileOut);

    return 0;
}
