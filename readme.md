# Huffman Coding Implementation in C
> This is a tree data structure implementation in C, using Huffman Coding.

## What is Huffman Coding

In computer science and information theory, a Huffman code is a particular type of optimal prefix code that is commonly used for lossless data compression. The process of finding or using such a code proceeds by means of Huffman coding, an algorithm developed by David A. Huffman while he was a Sc.D. student at MIT, and published in the 1952 paper "A Method for the Construction of Minimum-Redundancy Codes".

The output from Huffman's algorithm can be viewed as a variable-length code table for encoding a source symbol (such as a character in a file). The algorithm derives this table from the estimated probability or frequency of occurrence (weight) for each possible value of the source symbol. As in other entropy encoding methods, more common symbols are generally represented using fewer bits than less common symbols. Huffman's method can be efficiently implemented, finding a code in time linear to the number of input weights if these weights are sorted. However, although optimal among methods encoding symbols separately, Huffman coding is not always optimal among all compression methods - it is replaced with arithmetic coding or asymmetric numeral systems if better compression ratio is required.

<img src="img/huffman.png" height = "500" width = "800">

## Used Technologies

I used the C programming language in this project because it is a low-level language, and it is a challenge for me. Tree implementation in C is complicated but improving.

## How the program works

- The program can take input from either terminal or file.
- The program generates a Huffman Tree from given text.

## Screenshots

<img src="img/screenshot1.PNG" height = "400" width = "800">

<img src="img/screenshot2.PNG" height = "400" width = "800">
