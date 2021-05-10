Logbook Plugin for OpenCPN
=======================================

This is Logbook-Konni originally developed by Konnibe.  I have forked this from his
git repository and I am continuing development.  Konnibe has been unable to continue
development on this logbook due to ill health.

Del   
SV Chiara Stella   
http://sailchiarastella.blogspot.com/

Since Del wrote this, Peter Tulp has maintained it for a number of years.
Now Rick Gleason is maintaining the frontend and distribution.
Peter is still accepting PR's from Rick and others.

Install via OpenCPN Plugin Manager
======================
Current released version is available via OpenCPN > Options > Plugin Manager (PIM)
(Requires a good internet connection)

Maintenance Repository: https://github.com/rgleason/LogbookKonni_pi
Source Repository: https://github.com/delatbabel/LogbookKonni-1.2

Please push all Pull Requests to both maintenance and source repositories.

Downloading the Plugin
======================
An earlier binary release can be found here:

https://github.com/delatbabel/LogbookKonni-1.2/releases/tag/v1.2011

You should be able to find binaries (RPM and DEB) for Linux as well as some for
Windows and OSX there.  There are also two zip files present, you only need the
Layouts zip file (the languages zip file is already included in the distribution).

If the binaries for your platform are not there, then just stand by, we have several
people contributing binaries and it takes a few days to get them in from everyone.

If you can't find the latest OSX release here then have a look at ptulp's fork
of this repository here, he has the latest OSX version built:

https://github.com/ptulp/LogbookKonni-1.2/releases/

After Installing the Plugin
===========================

###Enable the Plugin

* Start OpenCPN
* Select Options from the toolbar (spanner icon) and go to the Plugins tab.
* Select the Logbook plugin and click Enable to enable the plugin.

###Install Additional Files

There are 2 additional zip files distributed with the logbook, you will need to
install the layouts zip file to make use of all of the features. First you should copy
these files to somewhere convenient, e.g. your home directory, desktop,
etc.  They can be installed from there.  Either that or if you have the
logbook source directory from git they can be installed directly from
there.

* LogbookKonni_Languages.zip (language data files -- included with binary packages)
* LogbookKonni_Layouts.zip (layouts help and other files -- NOT included with packages)

###Layouts

These are necessary to display data e.g. in a browser.

* Start OpenCPN
* Select Options from the toolbar (spanner icon) and go to the Plugins tab.
* Select the Logbook plugin
* Click the Preferences button
* In the dialog click "Install" below the label "Install Layouts"
* In the file dialog select the file 'LogbookKonni_Layouts.zip'

Note that the layouts are customisable by the user and can be distributed to
and shared with other OpenCPN logbook users.  If you have developed a useful
custom layout for your logbook then please feel free to send us details.

###Languages

You don't need to install this zip file, it's already included with the package
but we have provided it with the binaries so you can take a look at what's
there or replace files if you need to.

Using the Plugin
================

There are extensive help files included with the plugin.  To access these click
the *help* icon (small book icon) at the end of the logbook main page.  The help
will open in a browser window.

There is also some on line documentation, here:

http://opencpn.org/ocpn/node/323

Compiling
=========

This plugin now builds out of the OpenCPN source tree.  You do not need to build
the entire of OpenCPN or even clone it from git just to build this plugin.  It
should, however, also successfully build from inside the OpenCPN source tree along
with the rest of OpenCPN if you clone it into the OpenCPN/plugins directory.

If you need instructions as to how to build OpenCPN then see the developers
manual at http://opencpn.org/ocpn/developers_manual

You need to have all of the dependencies required to compile OpenCPN installed in
order to be able to build this plugin.  Those might vary depending on your system.

###Clone this repository from github

You might choose to fork this repository on github so you might
use your own git: URL instead of the one below.

```
git clone https://github.com/delatbabel/LogbookKonni-1.2 LogbookKonni_pi
```

or, from your own fork, a command similar to this (replace delatbabel with
your own git user name):

```
git clone git@github.com:delatbabel/LogbookKonni-1.2.git LogbookKonni_pi
```

###Build on Linux

Note that you will need to have all of the development tools installed that
are required to build OpenCPN.  If you have any doubts then run the cmake ..
command and it will complain about missing dependencies.  At the very least
you will need the g++ compiler and development libraries, cmake, gettext, so
install those first and see how far you get.

```
mkdir LogbookKonni_pi/build
cd LogbookKonni_pi/build
cmake ..
cmake --build .
```

###Build on Mac OS X

Tools: Can be installed either manually or from Homebrew (http://brew.sh)

```
#brew install git #If I remember well, it is already available on the system
brew install cmake
brew install gettext
ln -s /usr/local/Cellar/gettext/0.19.2/bin/msgmerge /usr/local/bin/msgmerge
ln -s /usr/local/Cellar/gettext/0.19.2/bin/msgfmt /usr/local/bin/msgfmt
```

To target older OS X versions than the one you are running, you need the respective SDKs installed. The easiest way to achieve that is using https://github.com/devernay/xcodelegacy

####Building wxWidgets
(do not use wxmac from Homebrew, it is not compatible with OpenCPN)
Get wxWidgets 3.0.x source from http://wxwidgets.org
Configure, build and install
```
cd wxWidgets-3.0.2
./configure --enable-unicode --with-osx-cocoa --with-macosx-sdk=/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.7.sdk/ --with-macosx-version-min=10.7 --enable-aui --disable-debug --enable-opengl
make
sudo make install
```

####Building the plugin
Before running cmake, you must set the deployment target to OS X 10.7 to be compatible with the libraries used by core OpenCPN
```
export MACOSX_DEPLOYMENT_TARGET=10.7

mkdir LogbookKonni_pi/build
cd LogbookKonni_pi/build
cmake ..
cmake --build .
```

Packaging
=========

From inside the build directory, the following command will make packages for your
current platform against the as-built code:

```
make package
```

Note that you will need to have the packaging tools installed for your platform and
any other platforms that you build packages for.  e.g. on Ubuntu you will need the
development tools required to build deb file as well as the rpm package required to
build RPM files.

To check the contents of the Debian/Ubuntu package, use this command:

```
dpkg -c logbookkonni_pi_1.27-1_amd64.deb
```

###Packaging on OS X
Get and install the Packages application from http://s.sudre.free.fr/Software/Packages/about.html
After installing Packages create the Plugin package.
```
make create-pkg
```
This will create the Logbookkonni-Plugin_1.2.pkg file in the build directory.
Executing this file will install the plugin.

Building zip files
==================

I can't find any way to successfully build a zip file with cmake, all of
the online documentation about how to do this appears to be incorrect.

On Linux you can use the makezip.sh script to make the required zip files.
They can be installed using the instructions in the "Install Additional Files"
section below.

These zip files will be distributed with the plugin when we make a release.

The language files are included with the packages, the layouts and the help
files are not and will need to be separately installed.

License
=======
The plugin code is licensed under the terms of the GPL v2 or, at your will, later. 
