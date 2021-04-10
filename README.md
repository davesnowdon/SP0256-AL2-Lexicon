# SP0256-AL2 Lexicon

This project is an extends the functionality of the [SpeechChip Arduino library created by Jacob Field](https://www.instructables.com/id/Arduino-Vintage-Speech-Chip/).  The SP0256-AL2 Lexicon program uses a large dictionary--the [CMUDict](https://github.com/cmusphinx/cmudict) created for the [CMUSphinx](https://github.com/cmusphinx)--to translate user entered sentences into words and then into allophones for use with the SP0256-AL2 speech chip.  The Lexicon program creates an Arduino .ino file to upload to an Arduino as shown in the [Arduino Speech Chip project by Jacob Field](https://www.instructables.com/id/Arduino-Vintage-Speech-Chip/).

The output to stdout also includes the decimal codes of the allophones to facilitate other uses of the  SP0256-AL2 chip such as with the [MG005 board](https://www.tindie.com/products/mrgelee/mg005-speech-synthesiser-designed-for-rc2014/) for the [RC2014](https://rc2014.co.uk/) system.

It's not 100% perfect, given that there are allophones the SP0 does not support, so you may have to change a few allophones in the output file to dial things in.  That being said, for anyone trying to get their RadioShack speech chips to crank out full sentences it's certainly a time saver.  The code should also be adaptable to other similar speech chips, like the insanely expensive Votrax chips.

# Building
This project uses CMake to build the code and the [GoogleTest](https://github.com/google/googletest) library to run the tests. It also requires the [conan](https://conan.io/) package manager to install GoogleTest