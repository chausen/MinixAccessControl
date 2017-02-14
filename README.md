# Minix Access Control
A set of modifications to the Minix 3.2.1 operating system to support access control for processes and files. Developed as a project for UF's COP4600 Spring 2017 taught by Richard Newman. The project specifications were created by him.


## Building the System
* Extract the contents of the tarball into any directory (/home for example)
* From a shell, set your *cdw* to the root of the extracted directory structure
* Execute `make`
* Execute `make build`
* Reboot Minix 

## Overview
### Functionality
The modifications currently establish a simple form of access control between processes. This is done by managing an attribute that was added to each process called *tag*. *Tag* can be managed using two library procedures that can be called in C programs by including `unistd.h`. They are: 
* `get_tag(int pid)`
* `set_tag(int pid, int newvalue)`

*Tag* is initialized to 0 for all new processes. `get_tag` allows the calling process to retrieve it's own *tag* or any process' *tag* if it's owned by root.

`set_tag` allows the calling process to change it's own *tag*, or that of any other process, but it can only be called by a process owned by root.