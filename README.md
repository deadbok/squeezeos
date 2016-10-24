# Building SqueezeOS Firmware #

Starting with SqueezeOS 7.2 the embedded build system was changed to use Poky (an OpenEmbedded derivative). If you need to build earlier firmware please see the instructions below.

## System Requirements ##

A Debian-based distribution is recommend as the host system for Poky (for example a recent Ubuntu release, 7.04 or newer), but other Linux distributions will most likely work as well. If you don't have a Linux host available, building using a Linux system in [[VMware]] works well.
The latest Ubuntu version that we have used is "10.04 LTS Long Term Support" that could be fetched from http://www.ubuntu.com/desktop/get-ubuntu/download

You will need the following packages installed (for example using apt-get):

 * build-essential
 * python
 * diffstat
 * texinfo
 * texi2html
 * cvs
 * subversion
 * wget
 * gawk
 * help2man
 * gcc-3.4 or gcc-4.4
 * libx11-dev
 * libsdl1.2-dev
 * xmlto
 * curl
 * libcurl4-openssl-dev
 * zip
 * subversion

	sudo apt-get install build-essential python diffstat texinfo\
	texi2html cvs subversion wget gawk help2man gcc-3.4 libx11-dev\
	libsdl1.2-dev xmlto curl libcurl4-openssl-dev zip subversion

should do the trick. If the gcc-3.4 could not be found try using the gcc-4.4. After gcc-4.4 is installed create a soft link from gcc-3.4 to gcc-4.4.

You may also need to fix some configuration problems reported by poky, on Ubuntu 8.04 they include:

 * changing /bin/sh to bash instead of dash
   cd /bin
   rm sh
   ln -s bash sh
 * modifying the mmap minimum address (become root for this; on Ubuntu systems, sudo -i does the trick)
   sudo sh -c 'echo "0" > /proc/sys/vm/mmap_min_addr'

Also, when you run bitbake, it suggests you use [http://psyco.sourceforge.net psyco] to speed things up a bit.  I was able to get it with:
   sudo apt-get install python-psyco

## Downloading Poky And Starting The Build ##

You must use the SqueezeOS Poky version that is available using SVN. You can check it out using (where SQUEEZEOS_VERSION is the version number you are building, for example 7.2):

 svn co http://svn.slimdevices.com/repos/jive/<SQUEEZEOS_VERSION>/trunk/squeezeos/poky

The you need to setup the build environment using:

 cd squeezeos/poky
 source poky-init-build-env

Now the SqueezeOS distribution can be build using:

 bitbake squeezeos-image

'''NOTE: Build fails''' because qemu files have moved. poky/meta/packages/qemu/qemu_0.9.1.bb should refer to the new location: http://git.savannah.gnu.org/cgit/qemu.git/snapshot/qemu-0.9.1.tar.gz (feel free to remove this note when problem is solved)


BEWARE: this will take a '''long''' time the first time you run a build, expect it to take several hours. This will download and build the embedded toolchain, the kernel, system libraries and the SqueezeOS application software.

When the build has finished the kernel, root filesystem and jive.bin images can be found in tmp/deploy/images.

The SVN revision of the poky checkout is used for the build revision, so to build a new revision you must first do an update in poky using:

 svn update

## Other SqueezeOS images ##

A couple of other SqueezeOS images can be build:

;squeezeos-image-boot
:builds the kernel and a minimal image root filesystem, just enough to boot the system. This image can be useful when working on the SqueezeOS platform.
;squeezeos-image-debug
:build the image with debugging enabled for use with oprofile.
;squeezeos-image-debug-tools
:builds additional debugging and profiling tools, for example strace and oprofile. The tools and libraries are packaged in a tgz file for deployment to an SD card.

## Running SqueezeOS in qemu ##

It is possible to run SqueezeOS and the SqueezePlay application in qemu, the arm emulator. To do this edit the build/conf/local.conf file and change target machine, for example:
 # The machine to target
 #MACHINE ?= "jive"
 MACHINE ?= "qemuarm"

Then build the squeezeos-image as before:
 bitbake squeezeos-image

This time it will build the additional kernel and programs needed to run SqueezeOS in qemu. The to start qemu use:
 runqemu qemuarm ext2 tmp/deploy/images/zImage-qemuarm.bin tmp/deploy/images/squeezeos-image-qemuarm.ext2 

At the moment qmeu/kernel don't support the 240,320 frame buffer used by SqueezePlay, so you will need to manually modify the resolution in /usr/share/jive/jive/ui/Framework.lua to use SqueezePlay in qemu. Patches welcome!

## Some additional poky notes ##

### Configuration files ###

'''poky/meta*/packages''' - bitbake recipes for building packages. The recipe tells poky where to download the package from (ftp, http, svn, etc), any dependancies and how to build it.

'''poky/meta*/packages/images''' - these are poky recipes that just define the dependancies to build.

'''poky/meta*/conf/distro''' - these files define the distribution, then specify the package version to use.

'''poky/meta*/conf/machine''' - these files define machine (eg jive) specific properties and packages.

'''poky/build/conf/local.conf''' - local configuration file, specifies machine and distribution.

### Runtime files ###

All downloaded files are in '''poky/sources'''. For svn files it will download to '''poky/sources/svn/...''' and then create a tgz in '''poky/sources'''.

All built files are in '''poky/build/tmp'''. Deleting this will force everything to be remade.

'''poky/build/tmp/cross/bin''' - this is the toolchain. Adding this to your path allows you to compile packages outside of poky.

'''poky/build/tmp/staging''' - this is all the cross compiled headers and libraries that are used for cross compiling other packages.

'''poky/build/tmp/work''' - this is where each package is compiled.

When building a package, it will:

* Extract the source from poky/sources
* Configure and compile the packages
* Image directory contains the installed package (eg result of make install)
* Install directory contains the files to be installed on the target (eg dbg, dev and doc are separate packages).
* temp directory contains log files, these are useful when the build fails

An ipk (like apt or rpm) package is created using the contents of the install directory, and these are put in '''poky/build/tmp/deploy/ipk'''.

When creating an image poky 'installs' ipk packages into '''poky/build/tmp/rootfs'''. And then a '''tar/cramfs/ubi/etc''' image is created and stored in '''poky/build/tmp/deploy/images'''.

### Developing with poky ###

When poky runs it first checks if any recipes have changed. For any packages that use AUTOREV (to pull latest version from svn) it will also check if updates are required. This is slow and inconvenient when developing, so set:

 BB_SRCREV_POLICY = "cache"

in your '''local.conf'''. This will prevent it looking for SVN updates. You can force it to check if required by deleting the files in '''poky/build/tmp/cache'''.

You can make local changes to your package in '''poky/build/tmp/work'''. For example 

 poky/build/tmp/work/arm5te-poky-linux-gnueabi/squeezeplay-7.3+svnr3587-r6/squeezeplay/.

Then recompile using:
 bitbake squeezeplay -c compile -f

note: if you change other areas, you will need to recompile those as well.

For example, if you make changes in squeezeplay-jive, squeezeplay-squeezeos, as well as squeezeplay:
  bitbake squeezeplay squeezeplay-jive squeezeplay-squeezeos -c compile -f

This will force the squeezeplay package to be compiled. And then create an image using:
 bitbake squeezeos-image

This will pull your most recent changes into the built image file (eg jive.bin). You can verify these changes if needed by looking in '''poky/build/tmp/rootfs'''.

Once you are happy with your changes, you can check them in from the '''poky/build/tmp/work''' directory. But first you will need to use svn switch, for example (note it's the http -> http'''s''' that is the only difference in the path):
 svn switch --relocate
 http://svn.slimdevices.com/repos/jive/<squeezeosversion>/trunk/squeezeplay/src/squeezeplay
 https://svn.slimdevices.com/repos/jive/<squeezeosversion>/trunk/squeezeplay/src/squeezeplay

If you have a new package that's not in svn, then:
* Think does it really need to be? poky works best using official packages, and can apply patches if required. We should only use SVN for packages that require lots of changes (eg lua) or packages we write (eg squeezeplay).
* To get up and running you can write a poky recipe that uses a file:// url for it's package source.

## Troubleshooting builds ##
### bitbake fails on git-gui package ###
I've had a bunch of trouble with bitbake failing on git-gui.  I found 2 solutions that seem to work.  Please update this page when anybody figures out how to solve the problem properly
#### Solution 1 ####
     # pushd build/tmp/work/i686-linux/git-native-1.5.4.4-r1/git-1.5.4.4
     # make
     # cd git-gui
     # make
     # popd
     # !?bitbake
#### Solution 2 ####
Get the latest packages/git directory from openembedded.net, and copy it into meta/packages/git.  Then rebuild.
### bitbake fails in squeezeplay ###
There is another known problem where bitbake seems to pick up some local system libraries from a locally instaled libsdl-dev install.

A workaround for now is:
   # mv /usr/bin/sdl-config /usr/bin/sdl-config.bak
   # bitbake squeezeplay-<machine> -c clean
The rerun bitbake
### Newer distributions ###
Builds are likely to fail on newer distributions of Debian and Ubuntu, as well as on 64-bit versions. For best results use the 32-bit version of an older release such as Ubuntu 8.04 LTS.

# Building Earlier Firmware For the Squeezebox Controller Hardware #

## Build environment ##

You need to use Linux as an operating system for the cross compiler. A good solution is to use [[VMware]] on your development PC. Install Ubuntu 6.06 or Ubuntu 6.10. You'll need a 20GB or larger disk, so the standard Ubuntu [[VMware]] appliance is no good.

After a clean install of Ubuntu 6.10 you will need to:

 install vmware tools (not required for the build, but recommended)

 apt-get install build-essential flex bison subversion cramfsprogs

 apt-get install automake1.9 fakeroot libtool libncurses5-dev

 apt-get install gettext ja-trans

 apt-get install libssl-dev (should not be needed)

You should make sure that the following autoconf tools are available. Everyone should use the same versions, otherwise many checkins will just be modifying autoconf changes.

 autoconf2.6 automake1.9.6 libtool1.5.22

## SVN ##

Check out the [[SqueezePlay]] and [[SqueezeOS]] source using (use https if you have a svn account). For the stable branch use:

 svn co http://svn.slimdevices.com/repos/jive/7.3/trunk/squeezeos
 svn co http://svn.slimdevices.com/repos/jive/7.3/trunk/squeezeplay

And the development branch is:

 svn co http://svn.slimdevices.com/repos/jive/7.4/trunk/squeezeos
 svn co http://svn.slimdevices.com/repos/jive/7.4/trunk/squeezeplay

This includes the bootloader, kernel, operating system and [[SqueezePlay]] application. Expect it to take a while to check this all out.

## Building ##

Make a symlink:

 mkdir /usr/local/armln -s <checkout_root>/squeezeboxJive/toolchain/2.95.3 /usr/local/arm/2.95.3

Add this to the end of /.bash_profile:

 export PATH=<checkout_root>/squeezeboxJive/toolchain/gcc-4.2.2-glibc-2.6.1/arm-926ejs-linux-gnueabi/bin:$PATH

Then build:

 cd <checkout_root>/squeezeboxJive/srcfakeroot make# drink lots of coffee

The binary image is stored in squeezeboxJive/image/jive.bin. This is really a zip file. To see the version information use:

 unzip -p jive.bin jive.version

## Installing on hardware ##

Save the jive.bin image on a SD card. Install this on your Jive, and use ‘Settings > Controller Settings > Advanced Settings > Software Update > Continue using SD Card’. It is also possible to do a network based upgrade from [[SqueezeNetwork]] in the Software Update menu.

## Developing on the Squeezebox Controller ##

You can SSH onto the Controller, the password is ‘1234’. With the Controller breakout board you can connect using the serial port (115200 8n1 xon/xoff enabled).

The Controller uses an overlay filesystem you can edit/replace/delete any of the files on the device. To get back to a working system do a factory reset, at the moment you need to ‘touch /.factoryreset’ and reboot.

You can also perform a factory reset by pressing ’+’ while booting.

For plugin development you can use scp to copy files onto the Controller, this is probably the quickest approach.

It is also possible to use nfs to mount the filesystem remotely, I’ve not had much success with this over wireless yet.

If you want to avoid having to put in the SSH password each time you log in (with ssh or scp), you can use SSH [[ControllerPublicKeyAuthentication|public key authentication]].

## Controller BSP (Board Support Package) ##

You can access much of the hardware from lua using the applet in src/private_apps/[[JiveBSP]] (this is under development).

The input devices (matrix, wheel, accelerometer) using the Linux Input Subsystem, and appear in /dev/input. Use evtest to test these from the command line.

Most other hardware can be accessed using the ‘jivectl’ test program. See the ioctl numbers in linux-*/drivers/jive/jive_mgmt.c. For example to change the keypad backlights ‘jivectl 11 4096’. The backlights have a range of 0-4096, the other commands take a value of 0 or 1.

IR is available in /dev/misc/irtx, see userland/jivetest/testir.c. I’ve not looked at this in any detail yet.

wavplay is available for testing audio.

## See also: ##

[[SqueezeOS Internals]]

## Profiling ##

To enable profiling you need to use an SD card. First build the debug build and tools:
 
 bitbake squeezeos-image-debug
 bitbake squeezeos-image-debug-tools

Then decompress squeezeos-image-debug-tools-jive to a temp directory and copy the following files onto the SD card from your development host (modify the paths as appropriate). -L is used to copy symlinks as files in case your SD card filesystem does not support them.

 cp -LR <temp-dir>/usr /media/usbdisk
 cp <temp-dir>/boot/vmlinux-2.6.22-P7 /media/usbdisk/vmlinux

Then copy the newly created debug image (build/tmp/deploy/images/jive_*.bin) to the SD card.

Then put the SD card in the Controller and boot the device. Then perform a software update, updating to the new debug image.

To initialize the profiler do:

 export PATH=/media/mmcblk0p1/usr/bin:$PATH
 export LD_LIBRARY_PATH=/media/mmcblk0p1/usr/lib
 cp /media/mmcblk0p1/usr/bin/objdump /usr/bin 
 opcontrol --setup --vmlinux=/media/mmcblk0p1/vmlinux

Those commands can be automatically run using a jiveboot.sh script on the SD card.

Then to profile do:

 opcontrol --start
 # stuff
 opcontrol --stop
 opreport -l -p /lib/modules/2.6.22-P7

Various profiling options can be used, see the oprofile documentation for more details.

# How to disable the system bell from a VMWare Ubuntu image #
If you're using windows with Linux inside a VMWare image, you're probably being driven crazy by the system bell.  You can mute the PC, mute the Ubuntu image, try to disable sound, whatever, and the system bell still comes through at an incredibly loud and annoying level.  Well, here's the solution that will keep you sane:

Append the following to /etc/modprobe.d/blacklist:

   blacklist pcspkr

Yep, that's all you need to do to regain your sanity.
