# sha512
My implementation of SHA512 and HMAC-SHA512

## Building

    make

## Use

* `DATAFILE` is the file to be hashed
* `KEY` is the key for the HMAC as ASCII characters (must not contain whitespace)

```
./SHA512util.out DATAFILE
./HMAC-SHA512util.out KEY DATAFILE
```
