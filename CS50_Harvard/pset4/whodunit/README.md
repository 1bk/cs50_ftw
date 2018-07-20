# Questions

## What's `stdint.h`?

Basically a header that defines integer types, limits of specified width integer types, limits of other integer types and macros for integer constant expressions.

`stdint.h` is a header file in the C standard library introduced in the C99 standard library section 7.18 to
allow programmers to write more portable code by providing a set of typedefs that  specify exact-width integer
types, together with the defined minimum and maximum allowable values for each type, using macros.

[Source](https://en.wikibooks.org/wiki/C_Programming/stdint.h)


## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

They essentially are equal to `unsigned char`, `unsigned int`, `int` and `unsigned short`, respectively.

What they do is to allow us to intepret a long string of numbers (long string of binaries) by breaking them up into chunks of more useful numbers.
The numbers are broken up into the chunks as per define by each of these types (i.e. chunks of 8 bits or 32 bits, etc.)

Unsigned literally means it cannot store numbers with a sign (i.e. negative numbers or "-"), but instead can stroe twice as many positive numbers.
For example, in a 16-bit environment, (signed) `int` is 4 bytes in size (or 32 bits), which means it can store numbers in the [-32,768, +32,767] range.
On the other hand, `unsigned int` is also 32 bits in size but can only store numbers in the [0, 65,535] range.
Recall (i) 2^16 = 65,536; (ii) 65,536/2 = 32,768; and (iii) '0' is counted in the range!

Note that in the context of a Bitmap file, this is a good use for the header as we can use it to intepret the first 14 bytes of the bitmap files.

[Source #1](https://www.badprog.com/c-type-what-are-uint8-t-uint16-t-uint32-t-and-uint64-t)
[Source #2](https://www.reddit.com/r/cs50/comments/6r7n10/pset4_whodunit_questions/)

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE    =   8 bits  =  1 byte
DWORD   =  32 bits  =  4 bytes
LONG    =  32 bits  =  4 bytes (singed)
WORD    =  16 bits  =  2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first two bytes is a WORD and denotes the bfType - which should define the file type as:
(1) `BM` in ASCII; or
(2) `0x42 0x4D` in Hexadecimal.

## What's the difference between `bfSize` and `biSize`?

`bfSize` is the size, in bytes, of the bitmap file.
`biSize` is the number of bytes required by the structure. It is basically the size of the `BITMAPINFOHEADER` header file and it is constant at 40 bytes.

[Source #1](https://docs.microsoft.com/en-gb/windows/desktop/api/wingdi/ns-wingdi-tagbitmapfileheader)
[Source #2](https://msdn.microsoft.com/en-gb/02f8ed65-8fed-4dda-9b94-7343a0cfa8c1)
[Source #3](https://stackoverflow.com/questions/25713117/what-is-the-difference-between-bisizeimage-bisize-and-bfsize)


## What does it mean if `biHeight` is negative?

For uncompressed RGB bitmaps, if `biHeight` is **positive**, the bitmap is a _bottom-up DIB_ (Device-Independent Bitmap) with the origin at the _lower left corner_.

If `biHeight` is **negative**, the bitmap is a _top-down DIB_ with the origin at the _upper left corner_.

Note however, for compressed formats, `biHeight` must be positive, regardless of image orientation.

[Source](https://docs.microsoft.com/en-gb/windows/desktop/api/wingdi/ns-wingdi-tagbitmapinfoheader)


## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

It is the `biBitCount` which specifies the number of bits per pixel (bpp).
For uncompressed formats, this value is the _average number_ of bits per pixel.
For compressed formats, this value is the _implied bit depth_ of the uncompressed image, after the image has been decoded.

It essentially specifies the maximum number of colours per pixel.
For example, a normal 24-bit BMP has for each 1 pixel = 3 bytes or 24-bits.
Recall that each byte represents RGB values from [0, 255], since it is 1 byte each.
e.g. RED = 1 byte; GREEN = 1 byte; Blue = 1 byte.

Hence, the more bytes are allocated means there will be more colour depth. Instead of [0,255] colour choices,
there could be more per RGB

[Source #1](https://docs.microsoft.com/en-gb/windows/desktop/api/wingdi/ns-wingdi-tagbitmapinfoheader)


## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

`fopen` will return  `NULL` as it cannot find the file to read (`copy.c:24`) or write (`copy.c:32`).

## Why is the third argument to `fread` always `1` in our code?

**DESCRIPTION**
`size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);`

The function fread() reads nmemb elements of data, each size bytes long, from the stream pointed
to by stream, storing them at the location given by ptr.
[Source #2]("man fread")

Essentially, the third argument represents the number of elements, each one with a size of <size> bytes long.

It basically tells the function how many elements (of <sizze> byte long) we want to read at a time,
and since we are always reading through each _struct_ (with the <size> = sizeof(RGBTRIPLE) in our case) one at
a time, we put the thrid argument as 1.

i.e. sizeof(RGBTRIPLE)*1.
[Source #3](http://www.tutorialspoint.com/c_standard_library/c_function_fread.htm)


## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

`// determine padding for scanlines`
`int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;`
If bi.biWidth = 3; (note biWidth specifies the width of the bitmap in pixels.)
And since sizeof(RGBTRIPLE) = 3 'bytes' ...Why? Becuase in `bmp.h`, RGBTRIPLE is defined as a struct
with `rgbtBlue`, `rgbtGreen`, and `rgbtRed` where each of they are of type `BYTE`.
And recall that `BYTE` is an alias for the C/C++ primitive data of type `uint8_t`, which
is 8 bits or 1 byte in size. _(see 3rd question above)_
So each RGBTRIPLE is (1 byte * 3) = 3 bytes in size!

Incidentally, as we are dealing in bytes, we convert `bi.biWidth` which is in 'pixels' into bytes by:
`bi.biWidth * sizeof(RGBTRIPLE)`.

So,
padding = (4 - (3 * 3) % 4) % 4
        = (4 - (9) % 4) % 4
        = (4 - 1) % 4
        = (3) % 4
        = 3 bytes

Why? The requirement for a bitmap file format is that the length of each scan line has to be a multiple of 4 bytes.
so if the number of pixels are not a multiple of 4, we need to add some paddings.
Note: Paddings are essentially just zeros (0x00).

So initially we have 3 pixels, which in bytes is 3 pixel * 3 bytes per pixel = 9 bytes.
Since 9 bytes is NOT a multiple of 4 bytes, we need to add a padding of 3 bytes to 12 bytes in total, which
is a multiple of 4 bytes!
[Source #4](https://www.youtube.com/watch?v=Igsa7V5ouzg)

## What does `fseek` do?

**As per "man fseek"**
`int fseek(FILE *stream, long offset, int whence);`
The function `fseek` sets the file position indicator for the file stream to the value pointed to by offset.
[Source #1]("man fseek")

It essentially moves the current position of the file pointer to a specific location in a file.

**As per copy.c**
`// skip over padding, if any`
`fseek(inptr, padding, SEEK_CUR);`
For the context of `copy.c` , `fseek` is used to skip over paddings and look for the next pixel or RGBTRIPLE.


## What is `SEEK_CUR`?

`SEEK_CUR` is the current position of the file pointer.

This is an integer constant which, when used as the `whence` argument to the fseek function,
specifies that the offset provided is relative to the current file position.
[Source #1](http://www.tutorialspoint.com/c_standard_library/c_function_fseek.htm)

Essentially, SEEK_CUR is a special value that has been defined for us; if we pass it as the third parameter
to fseek(), that function will know that we want to move the file pointer relative to its current position.

There's nothing special about the value of SEEK_CUR, except that we and fseek have agreed to use it as an
indicator of how we wish the function to behave. There is literally an "if" statement inside fseek that
compares the value of "whence" (the third parameter) to the value of SEEK_CUR, and it changes its behavior
accordingly.
[Source #2](https://www.reddit.com/r/cs50/comments/283i04/pset5_understanding_seek_cur/)
