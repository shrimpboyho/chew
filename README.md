[chew]() - Some ninja stuff...
====
<img src="ninja.jpg" width="50%">

```chew``` aims to be a command line utility that one can use to share files in an encyrpted, extremely secret manner. ```chew``` splits a file into several pieces and encrypts it. It can also assemble the file back together.

##How to Use

To split a file invoke ```chew``` with the filename, followed by the number of chunks you want to file split into, followed by an encryption key you want. Each chunk will have a randomly generated file name, and a ```.bit``` extension.
```bash
# WARNING: ONLY SPLIT INTO A MAX OF 10 TO AVOID FILE DETERIORATION
$ chew file.avi 7 82ha23fj
```

To assemble a file, ```cd``` into a directory with ```.bit``` files, and invoke the following command with the encryption key.
```bash
$ chew 82ha23fj
```

##What it Can Do
Currently, ```chew``` can only split files. There is no encryption feature yet, and the splitting in itself is a bit buggy.
