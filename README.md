# mailbox

A library for accessing the Mailbox interface (`/dev/vcio`) on Raspberry Pi.


## Installation

```
$ git clone https://github.com/Terminus-IMRC/mailbox
$ cd mailbox/
$ cmake .
$ make
$ sudo make install
```

Or you can create `.deb` package:

```
$ make package
$ sudo dpkg -i libmailbox-x.y.z-system.deb
```


## Running tests

```
$ ctest -V
```
