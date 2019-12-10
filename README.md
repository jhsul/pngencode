# pngencode
Encode files in a png

## Requirements
- `make`
- `libpng`

## Installation

```sh
$ git clone https://github.com/jhsul/pngencode && cd ./pngencode
$ make
$ # Optional:
$ ln -s ./pngencode /usr/bin/pngencode
```

## Usage
```
Usage: ./pngencode [OPTIONS] <source file> <dest file>

Options:
  -v  verbose output
  -d  decode a png created with ./pngencode
  -h  display this message
```

## Examples

```sh
$ ./pngencode assets/saintpablo.mp3 assets/saintpablo.png
```

<p align="center"> <img src="./assets/saintpablo.png" alt="saintpablo.png"> </p>