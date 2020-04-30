# SeisComP3 for macOS port

This is the ported version of SeisComP3 for Mac OS X / macOS.

Original project homepage: http://www.seiscomp3.org

The original software has been developed by the [GEOFON Program](http://geofon.gfz-potsdam.de) at [Helmholtz Centre Potsdam, GFZ German Research Centre for Geosciences](http://www.gfz-potsdam.de) and [gempa GmbH](http://www.gempa.de).

SeisComP3 is distributed under the [SeisComP Public License](COPYING)

![img](http://www.ecgs.lu/gilles/wp-content/uploads/seiscomp3-macos_screenshot-1024x576.png)

## A quick tutorial to compile SeisComP3 on macOS

SeisComP3-macOS installs on:

- macOS High Sierra 10.13.x
- macOS Mojave 10.14.x
- macOS Catalina 10.15.x


After compilation SeisComP3-macOS will be installed in your Home Directory: ${HOME}/seiscomp3

## Pre-Requirements

- Apple Xcode 9.x or Xcode 10.x or Xcode 11.x (depends on your macOS version)
- or "clang compiler" command-line, install with:
```
  xcode-select --install
```
- GNU GFortran 6.3 or later
- Homebrew package manager for macOS

### Install Apple's Xcode

You can choose to install the developer tools via command-line only (saves space),
or download Xcode IDE (8GB or more) from Apple's App Store for free.

The command-line works pretty well, so open up `Terminal.app` from Applications > Utilities and type:
 `xcode-select --install`

### Install GFortran

Install GNU Fortran by downloading the latest installer for macOS here:
https://gcc.gnu.org/wiki/GFortranBinaries

or direct download from:
https://github.com/fxcoudert/gfortran-for-macOS/releases

### Install Homebrew
Homebrew is the missing package manager for Mac: [Homebrew Webpage here] (http://brew.sh)

In Terminal.app copy/paste this command:

`/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"`

All the dependencies packages will be installed in /usr/local/Cellar/
	
Check if your system is correctly setup with:
`brew doctor`

Note: If you have Macports package manager installed it's better to not to mix up with Homebrew.
or you could rename Macports default directory /opt/local to /opt/local.OFF

### Install seiscomp3 dependencies

With Homebrew installed, install seiscomp3 dependencies packages for macOS:
```
brew install cmake
brew install flex
brew install md5sha1sum
```

Check installed version of OpenSSL with:
```
brew list openssl
```
It should point to OpenSSL v1.11 and later:
```
/usr/local/Cellar/openssl@1.1/1.1.1d/bin/openssl
/usr/local/Cellar/openssl@1.1/1.1.1d/include/openssl/ (104 files)
/usr/local/Cellar/openssl@1.1/1.1.1d/lib/libcrypto.1.1.dylib
/usr/local/Cellar/openssl@1.1/1.1.1d/lib/libssl.1.1.dylib
....
```

If an older version is installed (like OpenSSL 1.0), then delete this version
```
brew uninstall openssl
```

Then (re)install latest version of OpenSSL with Homebrew:
```
brew install openssl
```


Install Boost v1.60, since seiscomp3 is incompatible with Boost versions > 1.60
```
brew install boost@1.60
```

### Install Qt5 for the GUI

Note: macOS 10.13 and later is required for Qt5.
`brew install qt`


If you need Qt4 for any reason (macOS < 10.13 ):
Qt4 is no longer officialy supported by Homebrew 
[See homebrew-qt4 page] (https://github.com/cartr/homebrew-qt4)
`brew install qt@4`

If this doesn't work then try with command:
```
brew tap cartr/qt4
brew tap-pin cartr/qt4
brew install qt@4
```

### Install MySQL 5.7 (instead of current MySQL 8)
The latest Homebrew version installs MySQL8 by default, which seems to have some
upgrade issues with Seiscomp3 InnoDB (but this has been fixed recently).

Just install MySQL 5.7 instead:

```
brew install mysql@5.7
```

### Configure MySQL at startup

Copy default MYSQL configuration file to /usr/local/etc/
`sudo cp $(brew --prefix mysql)/support-files/my-default.cnf /etc/my.cnf`

For better performance with a MySQL database, adjust the following parameters in /etc/my.cnf

```
innodb_buffer_pool_size = 64M
innodb_flush_log_at_trx_commit = 2
```

To have launchd start mysql now and restart at login:
`brew services start mysql`

Recommended: MySQL Workbench application for macOS.
MySQL Workbench from Oracle is a free GUI to administer MySQL databases.
[Install MySQL Workbench from Oracle's website] (https://dev.mysql.com/downloads/workbench/)

### Build seiscomp3 for macOS

After downloading the zipped "seiscomp3-macos-master.zip" to your Downloads folder move it to a new directory, e.g.: "seiscomp3-git".
Also create the installation directory and build-directory e.g. builds-seiscomp3-macos, like this:

Create the installation directory in your Home folder:
```
mkdir -p ${HOME}/seiscomp3
```

Create the build-directory:

```
mkdir ~/Downloads/seiscomp3-git
mkdir ~/Downloads/seiscomp3-git/builds-seiscomp3-macos
```

Move the zipped file to the ~/Downloads/seiscomp3-git folder:

```
mv ~/Downloads/seiscomp3-macos-master.zip  ~/Downloads/seiscomp3-git/
cd ~/Downloads/seiscomp3-git/
unzip ~/Downloads/seiscomp3-macos-master.zip
```

Now we are ready to compile seiscomp3-macos with GUI manually from the builds directory, like this:

```
cd builds-seiscomp3-macos
cmake -DCMAKE_INSTALL_PREFIX=${HOME}/seiscomp3 -DSC_GLOBAL_GUI=ON ../seiscomp3-macos-master
make -j 2
make install
```

Note: If you have installed Python versions with Homebrew and want to use this Python installation, rather than the System's default, then use cmake like this (e.g with python 2.7):

```
cmake -DCMAKE_INSTALL_PREFIX=${HOME}/seiscomp3 -DSC_GLOBAL_GUI=ON -DPYTHON_EXECUTABLE:FILEPATH=/usr/local/bin/python -DPYTHON_LIBRARY=/usr/local/Cellar/python/2.7.13/Frameworks/Python.framework/Versions/2.7/lib/libpython2.7.dylib ../seiscomp3-macos-master`
```

If everything compiled fine, the files will be installed in ${HOME}/seiscomp3.

Start for the GUI application 'scrttv' from ${HOME}/seiscomp3/bin/scrttv
```
${HOME}/seiscomp3/bin/scrttv
```

 
### Increase max open files for seedlink on macOS System Startup

To avoid getting seedlink errors when starting seiscomp3 with "files open exceed max files ...",
increase the max open files on system's startup.

Create a plist file named: `limit.seiscomp3-maxfiles.plist` with this content:

```
<?xml version="1.0" encoding="UTF-8"?>  
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN"  
       "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">  
<dict>
<key>Label</key>
<string>limit.seiscomp3-maxfiles</string>
<key>ProgramArguments</key>
<array>
     <string>launchctl</string>
     <string>limit</string>
     <string>maxfiles</string>
     <string>524288</string>
     <string>524288</string>
</array>
   <key>RunAtLoad</key>
   <true/>
   <key>ServiceIPC</key>
   <false/>
 </dict>
</plist>  
```

Place this plist file in /Library/LaunchDaemons/

Then set root:wheel permission with command:
`sudo chown root:wheel /Library/LaunchDaemons/limit.seiscomp3-maxfiles.plist`

Launch it with command:
`sudo launchctl load -w /Library/LaunchDaemons/limit.seiscomp3-maxfiles.plist`

### Check current seiscomp3 configuration
https://docs.gempa.de/seiscomp3/current/apps/global.html

### Troubleshooting

If you get the -lcrypto compile error:
`ld error: -lcrypto not found` 

then you need to fix it. Just do a:
`brew doctor`
which warns you that /usr/bin occurs befor /usr/local/bin:

`Warning: /usr/bin occurs before /usr/local/bin`

You need to edit your $PATH in ~/.bashrc like this:
`PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:/usr/X11/bin`
to this line:
`PATH=/usr/local/bin:/usr/local/sbin:/bin:/sbin:/usr/bin:/usr/sbin:/usr/X11/bin`

Then in the Terminal, source your ~/.bashrc file:
`source ~/.bashrc`

