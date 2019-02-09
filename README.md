# Sound-Reverse
This C code snippet reverses a .WAV file using libsndfile library (The library is uploaded)

Download the libsndfile-1.0.26.zip from my repository or go to http://www.mega-nerd.com/libsndfile/ and follow the download link and download libsndfile-x.x.xx.tar.gz (all the x's should be replaced with proper version numbers)
To work with the library, you should use either the shell in cssgate or a similar command window in cygwin.
Once you have downloaded the .gz file mentioned above, uncompress it with two linux commands:
$ gunzip libsndfile-x.x.xx.tar.gz
$ tar xf libsndfile-x.x.xx.tar
After these two commands, you should now have a folder called libsndfile-x.x.xx
Keep this folder in your root.

The reverse.c reads one .WAV file and makes up a new one with the recording reversed. The program takes two command line arguments, first the name of the original file and second the name of the new file. For example:
$ ./reverse myfile.wav backward.wav
