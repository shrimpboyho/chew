[chew]() - Some ninja stuff
====

```chew``` aims to be a command line utility that one can use to share files in an encyrpted, extremely secret manner. ```chew``` splits a file into several pieces and encrypts it. It can also assemble the file back together.

##How to Use

To split a file invoke ```chew``` with the filename followed by the number of chunks you want to file split into. Each chunk will have a ```.bit``` extension, and will have a randomly generated file name.
```bash
$ chew file.avi 20
```

To assemble a file, ```cd``` into a directory with ```bit``` files, and invoke the following command.
```bash
$ chew
```

##What it Can Do
Currently, ```chew``` can only split files. There is no encryption feature yet, and the splitting in itself is a bit buggy.
