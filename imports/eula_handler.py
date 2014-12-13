#!/usr/bin/env python

    # Malware DB - the most awesome free malware database on the air
    # Copyright (C) 2014, Yuval Nativ, Lahad Ludar, 5Fingers

    # This program is free software: you can redistribute it and/or modify
    # it under the terms of the GNU General Public License as published by
    # the Free Software Foundation, either version 3 of the License, or
    #(at your option) any later version.

    # This program is distributed in the hope that it will be useful,
    # but WITHOUT ANY WARRANTY; without even the implied warranty of
    # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    # GNU General Public License for more details.

    # You should have received a copy of the GNU General Public License
    # along with this program.  If not, see <http://www.gnu.org/licenses/>.

import sys
import os
from imports import globals


class EULA:

    def __init__(self, langs=None, oneRun=True):
        #self.oneRun = oneRun
        self.check_eula_file()
        # self.prompt_eula()

    def check_eula_file(self):
        try:
            with open(globals.vars.eula_file):
                return 1
        except IOError:
            return 0

    def prompt_eula(self):
        globals.init()
        os.system('cls' if os.name == 'nt' else 'clear')
        print globals.bcolors.RED
        print '_____________________________________________________________________________'
        print '|                 ATTENTION!!! ATTENTION!!! ATTENTION!!!                    |'
        print '|                       ' + globals.vars.appname + ' v' + globals.vars.version + '                               |'
        print '|___________________________________________________________________________|'
        print '|This program contains live and dangerous malware files                     |'
        print '|This program is intended to be used only for malware analysis and research |'
        print '|and by agreeing the EULA you agree to only use it for legal purposes and   |'
        print '|studying malware.                                                          |'
        print '|You understand that these file are dangerous and should only be run on VMs |'
        print '|you can control and know how to handle. Running them on a live system will |'
        print '|infect you machines will live and dangerous malwares!.                     |'
        print '|___________________________________________________________________________|'
        print globals.bcolors.WHITE
        eula_answer = raw_input(
            'Type YES in captial letters to accept this EULA.\n > ')
        if eula_answer == 'YES':
            new = open(globals.vars.eula_file, 'a')
            new.write(eula_answer)
        else:
            print 'You need to accept the EULA.\nExiting the program.'
            sys.exit(0)
