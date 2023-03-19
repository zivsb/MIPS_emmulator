# MIPS emulator

## Project overview

This project develops a MIPS emulator in C++, by Peiyang Song and Ziv Weissman (names sorted by alphabet instead of evaluation of contribution). This is designed as the authors' final project for the W23 CMPTGCS 1B (Computer Organization and Logic Design) class co-taught by Dr. Jonathan Balkind and Dr. Ziad Matni (names sorted by alphabet), and the authors would like to thank the professors for their invaluable advice and amazing lectures.

## Live demo

In this section, we begin our introduction with a live demo. In the video, we first create a test file to show how our MIPS emulator successfully handle several core functions and instructions in MIPS (including loop, if-else branching, input and output, basic calculations, etc.). Then we move on to discuss how we have employed an exception handling mechanism to report possible errors.

Click here to view our (6-minute) video:

<a href="https://drive.google.com/file/d/161vrtKg-xAKOXflVabYhqqd9-HBka9oC/view?usp=share_link" title="Project Preview"><img src="./VideoPreview.png" alt="View Preview Vid" /></a>

## File structure

In this section, we give a brief description of each file in this repo as follows.

1. example_input: this folder contains 1) the input for our test file, in instructions.txt.
                                       2) the process that we used to generate the input file, in storeAndPrintHI.txt.
Note: a) you may find both decimal and hex values in our input file, as this is supported by C++ (hex values start with 0x).
      b) specifically, what you will find in our second file is a conversion path for each input line. Every conversion path goes from the natural language description of a line's purpose, to the equivalent code in a MIPS program, and finally the corresponding machine language for this line. If there is any confusion towards our first input file, looking into its corresponding parts in our second file can be helpful.
      
2. exceptions: this folder contains 1) classes for exceptions that will be thrown when encountering errors, in Error.h.
                                    2) a single class signaling that we do not encounter any errors and successfully quit the program, in SuccessfulQuit.h.

3. os.cpp: simulates the function of an operating system layer

4. cpu.cpp, cpu.h: simulates the function of a central processing unit layer.

5. Makefile.

More detailed information will be elaborated in the next section.

## Supported features

In this section, we describe the several core features that our MIPS simulator supports.

1. Approaches to take inputs.
      We supports two approaches to fetch input instructions: 1) If a test file is detected, we directly read all the instructions from it.
                                                              2) Otherwise, we open an interactive window, taking users inputs line by line.
2. 

## Acknowledgement
