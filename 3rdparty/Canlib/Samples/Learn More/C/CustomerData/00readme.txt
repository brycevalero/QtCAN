User data in Kvaser Devices
===========================

Setting user data works with Kvaser Leaf (of all types), Kvaser USBcan
Professional, Kvaser Memorator Professional and Kvaser Memorator
Light (including v2 of all types).


Reading user data
=================

Use

  kvReadDeviceCustomerData(int hnd,
                           int userNumber,
                           int itemNumber,
                           void *data,
                           size_t bufsiz)

to read user data.

userNumber is assigned by Kvaser.

itemnumber is presently not implemented. Must be set to zero.

data and bufsiz points to a buffer of bufsiz bytes (max 8 bytes) where the result
will be placed.

Note: anyone can read the user data. The writing is protected by
a password but reading is not.


Writing user data
=================

To write user data, you use a command-line program. Depending on your device,
it is filo_setparam_userdata.exe for older devices or
hydra_setparam_userdata.exe for newer devices. Please contact
support@kvaser.com for more information.


Maximum number of bytes to write
================================
Presently you cannot write more than 8 bytes of data.


Maximum number of write cycles
==============================

The user data is stored in a flash memory and the number of write cycles is limited.
The ideal application is to write the data once, or a few times. A license key
that your software validates would be a typical way of using this feature.



User number and password for test and development
=================================================

Use user number = 100 and password = upHXy1 (uniform papa hotel xray yankee one)

If you decide to use this user number and password for "production
use", please remember that the password is known to everyone.



Obtaining your own password
===========================

Please contact sales@kvaser.com for more information about how to obtain your
own user number and password.
