About
======
theZoo is a project created to make the possibility of malware analysis open and available to the public. Since we have found out that almost all versions of malware are very hard to come by in a way which will allow analysis we have decided to gather all of them for you in an available and safe way.
theZoo was born by Yuval tisf Nativ and is now maintained by Shahak Shalev. 

Disclaimer
==========
theZoo's purpose is to allow the study of malware and enable people who are interested in malware analysis or maybe even as a part of their job to have access to live malware, analyse the  ways they operate and maybe even enable advanced and savvy  people to block specific malwares within their own environment.

**Please remember that these are live and dangerous malware! They come encrypted and locked for a reason!  Do NOT run them unless you are absolutely sure of what you are doing! They are to be used only for educational purposes (and we mean that!) !!!**

We recommend running them in a VM which has no internet connection (or an internal virtual network if you must) and without guest additions or any equivalents. Some of them are worms and will automatically try to spread out. Running them unconstrained meaning the you **will infect yourself or others with vicious and dangerous malwares!!!**


GPL 3
======
theZoo - the most awesome free malware database on the air 
Copyright (C) 2014, Yuval Nativ, Lahad Ludar, 5fingers

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
The idea behind theZoo is to allow it to be modular and let you add malware of your own. Each malware should have a directory of it's own. 

## Root Files:
Since version 0.42 theZoo have been going dramatic changes. It now runs in both CLI and ARGVS mode. You can call the program with the same command line arguments as before.
The current default state of theZoo runtime is the CLI which is inspired by MSF. The following files and directories are responsible for the application's behaviour.

### /conf
The conf folder holds files relevant to the particular running of the program but are not part of the application. You can find the EULA file in the conf, the current database version, the CSV index file and more.
### /imports
Contains .py and .pyc import files used by the rest of the application
### /malwares
The actual malwares - be careful!
### /mdbv0.2
Since mdbv0.2 is stable for the command line arguments (where as of 0.42 we are not yet completely sure) and since the size is relativly small we have left out the beta version for those who are interested in it or got used to it. In next version we will confirm arguments as should be.


## Directory Structure:
Each directory is composed of 5 files:
- Malware files in an encrypted ZIP archive. 
- SHA256 sum of the 1st file. 
- MD5 sum of the 1st file.
- Password file for the archive. 
- index.log file for the indexer. 


## Structure of index.csv
The main index.csv is the DB which you will look in to find malwares indexed on your drive. We use the , charachter as the delimiter to our CSVs. 
The structure is al follows:

	uid,location,type,name,version,author,language,date

- UID 	-	Determined based on the indexing process.
- Location 	The location on the drive of the malware you have searched for.
- Type	-	Sorts the different types of malware there are. So far we sort by:	Virus, Trojans, Botnets, Ransomeware, Spyware
- Name	-	Just the name of the malware.
- Version	-	Nothing to say here as well.
- Author	-	... I'm not that into documentation...
- Programming Language - The state of the malware as for source, bin or which type of source. c/cpp/bin...
- Date	-	See 'Author' section.
- Architecture -    The arch the platform was build for. Can be x86, x64, arm7....
- Platform -    Win32, Win64, *nix32, *nix64, iOS, android and so on.

An example line will look as follow:

    4,Source/Original/rBot0.3.3_May2004/rBot0.3.3_May2004,botnet,rBot,0.3.3,unknown,cpp,00/05/2004,x86,win32


Bugs and Reports
================
The repository holding all files is currently 
	https://github.com/ytisf/theZoo

##Change Log for v0.50:
- [x] Better and easier UI. 
- [x] Aligned printing of malwares. 
- [x] Command line arguments are now working. 
- [x] Added 10 more malwares (cool ones) to the DB.

##Change Log for v0.42:
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

##Predicted Change Log for v1.0
- [ ] Fix auto-complete for malware frameworks.
- [ ] Better UI features.
- [ ] Consider changing DB to XML or SQLite3.


If you have any suggestions or malware that you have indexed as in the documentations please send it to us to yuval[]morirt [dot]com  so we can add it for every one's enjoyment.
