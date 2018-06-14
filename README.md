About
======
theZoo is a project created to make the possibility of malware analysis open and available to the public. Since we have found out that almost all versions of malware are very hard to come by in a way which will allow analysis, we have decided to gather all of them for you in an accessible and safe way.
theZoo was born by Yuval tisf Nativ and is now maintained by Shahak Shalev. 

**theZoo is open and welcoming visitors!**
Disclaimer
==========
theZoo's purpose is to allow the study of malware and enable people who are interested in malware analysis (or maybe even as a part of their job) to have access to live malware, analyse the ways they operate, and maybe even enable advanced and savvy  people to block specific malware within their own environment.

**Please remember that these are live and dangerous malware! They come encrypted and locked for a reason!  Do NOT run them unless you are absolutely sure of what you are doing! They are to be used only for educational purposes (and we mean that!) !!!**

We recommend running them in a VM which has no internet connection (or an internal virtual network if you must) and without guest additions or any equivalents. Some of them are worms and will automatically try to spread out. Running them unconstrained means that you **will infect yourself or others with vicious and dangerous malware!!!**


GPL 3
======
theZoo - the most awesome free malware database on the air 
Copyright (C) 2015, Yuval Nativ, Lahad Ludar, 5fingers

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


Documentation and Notes
========================

## Background:
theZoo's objective is to offer a fast and easy way of retrieving malware samples and source code in an organized fashion in hopes of promoting malware research.

## Root Files:
Since version 0.42 theZoo has been undergoing dramatic changes. It now runs in both CLI and ARGVS modes. You can call the program with the same command line arguments as before.
The current default state of theZoo runtime is the CLI. The following files and directories are responsible for the application's behaviour.

### /conf
The conf folder holds files relevant to the particular running of the program but are not part of the application. You can find the EULA file in the conf and more.
### /imports
Contains .py and .pyc import files used by the rest of the application
### /malwares/Binaries
The actual malwares samples - be careful!
### /malware/Source
Malware source code :)


## Directory Structure:
Each directory is composed of 4 files:
- Malware files in an encrypted ZIP archive. 
- SHA256 sum of the 1st file. 
- MD5 sum of the 1st file.
- Password file for the archive. 



## Structure of maldb.db
maldb.db is the DB which theZoo is acting upon to find malware indexed on your drive.
The structure is as follows:

	uid,location,type,name,version,author,language,date,architecture,platform,comments,tags

- UID 	-	Determined based on the indexing process.
- Location -	The location on the drive of the malware you have searched for.
- Type	-	Sorts the different types of malware there are. So far we sort by:	Virus, Trojans, Botnets, Ransomware, Spyware
- Name	-	Just the name of the malware.
- Version	-	Nothing to say here as well.
- Author	-	... I'm not that into documentation...
- Programming Language - The state of the malware in regard to source, bin, or which type of source. c/cpp/bin...
- Date	-	See 'Author' section.
- Architecture -    The arch the platform was build for. Can be x86, x64, arm7....
- Platform -    Win32, Win64, *nix32, *nix64, iOS, android and so on.
- Comments - Any comments there may be about the item.
- Tags - Tags matching the item.

An example line will look as follow:

    104,Source/Original/Dexter,trojan,Dexter,2,unknown,c,00/05/2013,x86,win32,NULL,Source

Bugs and Reports
================
The repository holding all files is currently 
	https://github.com/ytisf/theZoo

## Change Log for v0.60:
- [x] Moved DB to SQLite3.
- [x] Searching overhaul to a freestyle fashion.
- [x] Fixed "get" command.
- [x] More & more malwares.

## Change Log for v0.50:
- [x] Better and easier UI. 
- [x] Aligned printing of malwares. 
- [x] Command line arguments are now working. 
- [x] Added 10 more malwares (cool ones) to the DB.

## Change Log for v0.42:
- [x] Fix EULA for proper disclaimer.
- [x] More precise searching and indexing including platform and more.
- [x] Added 10 new malwares.
- [x] Git update of platform and new malware.
- [x] Fix display of search.
- [x] Enable support for platform and architecture in indexing.
- [x] Separate between database and application.
- [x] UI improvements.

## Change Log for v0.43:
- [X] Verify argv to be working properly. (fixes in v0.5)
- [X] Virus-Total upload and indexing module. - Not possible due to restrictions of VT.
- [X] Automatic reporting system for malwares which are not indexed in the framework.

## Change Log for v0.50:
- [X] Malware analysis pack has been removed to reduce clone size.
- [X] More documentation has been added.
- [X] Removed debugging function which were dead in the code.

## Predicted Change Log for v1.0
- [X] Fix auto-complete for malware frameworks. (thanks to 5fingers)
- [X] Consider changing DB to XML or SQLite3. (Sheksa - done :))
- [ ] Move malwares to another repo.
- [ ] Better UI features.

If you have any suggestions or malware that you have indexed (in the manner laid out in the documentation) please send it to us to - yuval[]morirt [dot]com - so we can add it for everyones enjoyment.
