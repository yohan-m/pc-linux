pc-linux
===============================================================================================

git repo for the pc linux source code

Graphical User Interface which displays the position of the drone
- Buttons Connect/Disconnect to open or close the communication with the drone
- A 2D display widget (x,y) and a read-only cursor (z) show the drone's position in real time (test in local for now)

Requirements : Qt and Qwt installed, Qt creator 

src : - Source code of the project 
      - Open pc-linux.pro with Qt creator to open the project

doc : - Documentation of the project in html
      - Open html/index.html to get the documentation 

doc.sh : - Launch this script to generate the documentation

================================================================================================
Installation of the Qwt library :

- Download the last version of qwt (6.1.1) : http://sourceforge.net/projects/qwt/files/qwt/
- Extract the folder qwt-6.1.1

On linux : 

- cd qwt-6.1.1
- Find the path where is installed qt (for example : /usr/lib/x86_64-linux-gnu) : qmake -v 
- Run qmake on the file qwt.pro with the correct path : /usr/lib/x86_64-linux-gnu/bin/qmake qwt.pro
- If you get error: Unknown module(s) in QT: svg -> sudo apt-get install libqt5svg5*
- If you get error : Unknow module(s) in QT: designer -> open qwtconfig.pri and comment the line QWT_CONFIG += QwtDesigner  
- make
- sudo make install

By default, lib and include are installed in : /usr/local/qwt-6.1.1

On windows :

- Search Qt "version" console for Desktop and open it
- cd qwt-6.1.1
- qmake qwt.pro
- mingw32-make
- mingw32-make install
- Compile using release mode (error with debug mode)

By default, lib and include are installed in : C:\qwt-6.1.1
