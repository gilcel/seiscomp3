# SeisComP3 for macOS compilation notes

Project homepage: http://www.seiscomp3.org

This software has been developed by the [GEOFON Program](http://geofon.gfz-potsdam.de) at [Helmholtz Centre Potsdam, GFZ German Research Centre for Geosciences](http://www.gfz-potsdam.de) and [gempa GmbH](http://www.gempa.de).

SeisComP3 is distributed under the [SeisComP Public License](COPYING)

## A quick tutorial to compile SeisComP3 on macOS

macOS compilation has been succesful on:
- Mac OS X El Capitan 10.11.x
- macOS Sierra 10.12.x
- macOS High Sierra 10.13.x
- macOS Mojave 10.14.x
- with Apple Xcode 9.x / 10.1 and 10.2.x
- gfortran 6.3 and later

After compilation SeisComP3-macOS will be installed in your Home Directory: ${HOME}/seiscomp3

## Pre-Requirements

- Apple Xcode 9.x or later (clang command-line installation works or download Xcode from the App Store)
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

With Homebrew installed now, we just need to install seiscomp3 dependencies packages for macOS:
```
brew install cmake
brew install boost

brew install flex
brew install openssl
brew install md5sha1sum
```


### Install qt4 for the GUI with Homebrew

Qt 4.x is no longer officialy supported by Homebrew - by default Qt version 5 is installed.
[See homebrew-qt4 page] (https://github.com/cartr/homebrew-qt4)

`brew install qt@4`

If this doesn't work then try with command:
```
brew tap cartr/qt4
brew tap-pin cartr/qt4
brew install qt@4
```

### Install MySQL 5.7 instead of current MySQL 8
The latest Homebrew version installs MySQL8 by default, which seems to have some
upgrade issues with Seiscomp3 InnoDB.

We just install MySQL 5.7 instead:

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

After downloading the zipped "seiscomp3-jakarta-macos.zip" to your Downloads folder move this zipped file to a new directory, e.g.: "seiscomp3-git".
Also create a build-directory e.g. builds-seiscomp3-macos, like this:

```
mkdir ~/Downloads/seiscomp3-git
mkdir ~/Downloads/seiscomp3-git/builds-seiscomp3-macos
```

For easier setup ename the zipped file seiscomp3-macos-seiscomp3-jakarta-macos.zip to "seiscomp3-jakarta-macos.zip"
Note: The zipped filename contains the Branch-name at the beginning...

```
mv ~/Downloads/seiscomp3-macos-seiscomp3-jakarta-macos.zip ~/Downloads/seiscomp3-jakarta-macos.zip
```



Move the zipped file to the ~/Downloads/seiscomp3-git folder:

```
mv ~/Downloads/seiscomp3-jakarta-macos.zip  ~/Downloads/seiscomp3-git/
cd ~/Downloads/seiscomp3-git/
unzip ~/Downloads/seiscomp3-jakarta-macos.zip
```

Now we are ready to compile seiscomp3-macos with GUI manually from the builds directory, like this:

```
cd builds-seiscomp3-macos
cmake -DCMAKE_INSTALL_PREFIX=${HOME}/seiscomp3 -DSC_GLOBAL_GUI=ON ../seiscomp3-jakarta-macos
make -j 2
make install
```

Note: If you have installed Python versions with Homebrew and want to use this Python installation, rather than the System's default, then use cmake like this (e.g with python 2.7):

```
cmake -DCMAKE_INSTALL_PREFIX=${HOME}/seiscomp3 -DSC_GLOBAL_GUI=ON -DPYTHON_EXECUTABLE:FILEPATH=/usr/local/bin/python -DPYTHON_LIBRARY=/usr/local/Cellar/python/2.7.13/Frameworks/Python.framework/Versions/2.7/lib/libpython2.7.dylib ../seiscomp3-jakarta-macos`
```

If everything compiled fine, the files will be installed in ${HOME}/seiscomp3
 
### Increase max open files for seedlink on System Startup

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
http://www.seiscomp3.org/doc/jakarta/current/apps/global.html

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
