# sha512
My implementation of SHA512 and HMAC-SHA512

## Building

    make

## Use

* `DATAFILE` is the file to be hashed
* `KEYFILE` is the file containing the key for the HMAC

```
./SHA512util.out DATAFILE
./HMAC-SHA512util.out KEYFILE DATAFILE
```
