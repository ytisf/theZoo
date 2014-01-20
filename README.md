About
======
Malware DB is a project created to make the possibility of malware analysis open and available to the public. Since we have found out that almost all versions of malware are very hard to come by in a  way which will allow analysis we have decided to gather all of them for you in an available and safe way. 

Disclaimer
==========
Malware DB's purpose is to allow the study of malware and enable people who are interested in malware analysis or maybe even as a part of their job to have access to live malware, analyse the  ways they operate and maybe even enable advanced and savvy  people to block specific malwares within their own environment.

**Please remember that there are live and dangerous malwares! They come encrypted and locked for a reason!  Do NOT run them unless you are absolutely sure of what you are doing! They are to be used only for educational purposes (and we mean that!) !!!**

We recommend running them in a VM which has no internet connection (or an internal virtual network if you must) and without guest additions or any equivalents. Some of them are worms and will automatically try to spread out. Running them unconstrained meaning the you **will infect yourself or others with vicious and dangerous malwares!!!**


GPL 3
======
Malware DB - the most awesome free malware database on the air 
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
The idea behind Malware DB it to allow it to be modular and let you enter more malwares of your own. Each malware should have a directory of it's own. 

## Root Files:
The main files you see on the root folder are:
- index.csv - 	The main index of the malwares you have access to and can be searched in your local folders.
- malware-db.py - 	The main indexing file. Use it to search for malware in the index.csv file on the same folder. 
- Rebuild_CSV.sh -	Rebuilds index.csv based on the index.log files in all the recursive directories. 

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

	uid,location,type,name,version,author,language,date,platform,architecture

- UID 	-	Determined base on the indexing process. Does not really have any purpose yet. 
- Location 	The location on the drive of the malware you have searched for. This and the UID field are automatically built on run by Rebuild_CSV.sh.
- Type	-	Sorts the different types of malware there are. So far we sort by:	Virus, Trojans, Botnets, Ransomeware, 1Spyware
- Name	-	Just the name of the malware.
- Version	-	Nothing to say here as well.
- Author	-	... I'm not that into documentation...
- Language -	VB/C/ASM/C++/Java or binaries (bin)
- Date	-	See 'Author' section. 
- Platform	-	Platform can be win32,win64,android,ios.
- Architecture	-	Can be x86,x64,arm and so on. 


## Structure of index.log:
index.log is about the only file which we cannot built automatically and you will need to write it down for your self. 
The structure is to be:

	type,name,version,author,language,date,

Don't worry about the UID and Location section which are not there, they will be built by Rebuild_CSV.sh while it collects data on the malwares. 


Bugs and Reports
================
The repository holding all files is currently 
	https://github.com/ytisf/theZoo

Stuff which are in the making:
- [X] Fix EULA for proper disclaimer.
- [X] More precise searching and indexing including platform and more.
- [ ] We have about 400 more malwares to map and add
- [ ] Git update of platform and new malware. 
- [ ] Fix display of search.
- [x] Enable support for platform and architecture in indexing.

If you have any suggestions or malware that you have indexed as in the documentations please send it to us to yuvaln210 [at] your most popular mail server so we can add it for every one's enjoyment. 