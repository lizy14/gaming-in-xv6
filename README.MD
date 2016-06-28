# gaming in xv6

Adding gaming support for the xv6 OS.

As term project of the course _Operating Systems_.


## demo
There is a user-mode game "snake" as demonstration, accepting both keyboard and gamepad input.

### keyboard control

	make qemu
	$ snake

### gamepad control
additional dependencies

	sudo add-apt-repository -q ppa:grumbel/ppa
	sudo apt-get -q update
	sudo apt-get -q install xboxdrv
	sudo apt-get -q install python-virtkey

then

	sudo make xbox-daemon
	make qemu
	$ snake

if does not work, try
	sudo killall python
	sudo killall xboxdrv

Tested only with Microsoft X-Box 360 pad (USB 045e:028e).

## notes

For details, please refer to [our wiki](https://github.com/lizy14/gaming-in-xv6/wiki) and the original `README` file.

By Bin Liu, Yonghe Wang, Zhaoyang Li, Zizhao Zhang, June 2016.
