# mailbox

A library for accessing the Mailbox interface (`/dev/vcio`) on Raspberry Pi.


## Installation

```
$ git clone https://github.com/Terminus-IMRC/mailbox
$ cd mailbox/
$ cmake -B build/
$ cmake --build build/ -t package
$ sudo dpkg -i libmailbox-x.y.z-arch.deb
```


## Running tests

```
$ cd build/
$ ctest -V
```
