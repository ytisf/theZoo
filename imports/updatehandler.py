#!/usr/bin/env python

    #Malware DB - the most awesome free malware database on the air
    #Copyright (C) 2014, Yuval Nativ, Lahad Ludar, 5Fingers

    #This program is free software: you can redistribute it and/or modify
    #it under the terms of the GNU General Public License as published by
    #the Free Software Foundation, either version 3 of the License, or
    #(at your option) any later version.

    #This program is distributed in the hope that it will be useful,
    #but WITHOUT ANY WARRANTY; without even the implied warranty of
    #MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    #GNU General Public License for more details.

    #You should have received a copy of the GNU General Public License
    #along with this program.  If not, see <http://www.gnu.org/licenses/>.
import sys
import urllib2
from imports import globals


class Updater:

    def get_maldb_ver(self):
        '''
        Get current malwareDB version and see if we need an update
        '''
        try:
            with file(globals.vars.maldb_ver_file) as f:
                return f.read()
        except IOError:
            print("No malware DB version file found.\nPlease try to git clone the repository again.\n")
            return 0

    def update_db(self):
        '''
        Just update the database from GitHub
        :return:
        '''
        try:
            with file(globals.vars.maldb_ver_file) as f:
                f = f.read()
        except IOError:
            print("No malware DB version file found.\nPlease try to git clone the repository again.\n")
            return 0

        curr_maldb_ver = f
        response = urllib2.urlopen(globals.vars.giturl + globals.vars.maldb_ver_file)
        new_maldb_ver = response.read()
        if new_maldb_ver == curr_maldb_ver:
            print globals.bcolors.GREEN + '[+]' + globals.bcolors.WHITE + " No need for an update.\n" + globals.bcolors.GREEN + '[+]' + globals.bcolors.WHITE + " You are at " + new_maldb_ver + " which is the latest version."
            sys.exit(1)

        # Write the new DB version into the file
        f = open(globals.vars.maldb_ver_file, 'w')
        f.write(new_maldb_ver)
        f.close()

        # Get the new CSV and update it
        csvurl = globals.vars.giturl + globals.vars.main_csv_file
        u = urllib2.urlopen(csvurl)
        f = open(globals.vars.main_csv_file, 'wb')
        meta = u.info()
        file_size = int(meta.getheaders("Content-Length")[0])
        print "Downloading: %s Bytes: %s" % (globals.vars.main_csv_file, file_size)
        file_size_dl = 0
        block_sz = 8192
        while True:
            buffer = u.read(block_sz)
            if not buffer:
                break
            file_size_dl += len(buffer)
            f.write(buffer)
            status = r"%10d  [%3.2f%%]" % (file_size_dl, file_size_dl * 100. / file_size)
            status = status + chr(8)*(len(status)+1)
        print status,
        f.close()

    def get_malware(self, id, allmal):
        #get mal location
        loc = allmal[id][globals.vars.column_for_location]
        #concat with location
        ziploc = globals.vars.giturl + '/' + loc + '.zip'
        passloc = globals.vars.giturl + '/' + loc + '.pass'
        #get from git
        u = urllib2.urlopen(ziploc)
        f = open(id+'zip', 'wb')
        meta = u.info()
        file_size = int(meta.getheaders("Content-Length")[0])
        print "Downloading: %s Bytes: %s" % (loc, file_size)
        file_size_dl = 0
        block_sz = 8192
        while True:
            buffer = u.read(block_sz)
            if not buffer:
                break
            file_size_dl += len(buffer)
            f.write(buffer)
            status = r"%10d  [%3.2f%%]" % (file_size_dl, file_size_dl * 100. / file_size)
            status = status + chr(8)*(len(status)+1)
        print status,
        f.close()

        #get pass from git
        u = urllib2.urlopen(passloc)
        f = open(id+'pass', 'wb')
        meta = u.info()
        file_size = int(meta.getheaders("Content-Length")[0])
        print "Downloading: %s Bytes: %s" % (loc, file_size)
        file_size_dl = 0
        block_sz = 8192
        while True:
            buffer = u.read(block_sz)
            if not buffer:
                break
            file_size_dl += len(buffer)
            f.write(buffer)
            status = r"%10d  [%3.2f%%]" % (file_size_dl, file_size_dl * 100. / file_size)
            status = status + chr(8)*(len(status)+1)
        print status,
        f.close()
        #alert ready
