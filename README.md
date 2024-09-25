# SimplifiedDESEncryption
Simplified DES Encryption algorithm originally intended for a software security course at Ohio University. It is a direct implementation of the algorithm, using the same permutations and steps as in the original paper.


It may not be the *most* efficient in the world, but it works! Lots of bit shifting and such. 

## Usage
The program is intended to take in standard input, but can work with a file as well. As there is no way of knowing when you reach the end of the input, once you are done you have to give it the ole' Ctrl-C.
Standard use:
```sh
$ ./des_encrypt 10_BIT_KEY
```
If you want to read in a file, you can either pipe it in using standard input OR you can give a command line argument for it to actually close.
```sh
$ ./des_encrypt 10_BIT_KEY FILENAME
```

Sample usage where filename contains: "Hello World!"
```sh
$ ./des_encrypt 0x2aa filename
�迿	�(	Q���
```
Yes, it's unreadable. Good thing that's what we wanted.