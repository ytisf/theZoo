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
from imports.colors import *

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
        notice = '_____________________________________________________________________________\n'
        notice += '|                 ATTENTION!!! ATTENTION!!! ATTENTION!!!                    |\n'
        notice += '|                       ' + globals.vars.appname + ' v' + globals.vars.version + '                            |\n'
        notice += '|___________________________________________________________________________|\n'
        notice += '|This program contains live and dangerous malware files.                    |\n'
        notice += '|This program is intended to be used only for malware analysis and research |\n'
        notice += '|and by agreeing the EULA you agree to use it only for legal purposes and   |\n'
        notice += '|for studying malware.                                                      |\n'
        notice += '|You understand that these file are dangerous and should only be run on VMs |\n'
        notice += '|you can control and know how to handle. Running them on a live system will |\n'
        notice += '|infect your machines with live and dangerous malwares!                     |\n'
        notice += '|___________________________________________________________________________|\n'
        print(red(notice))
        eula_answer = raw_input(
            'Type YES in captial letters to accept this EULA.\n > ')
        if eula_answer == 'YES':
            new = open(globals.vars.eula_file, 'a')
            new.write(eula_answer)
        else:
            print('You need to accept the EULA.\nExiting the program.')
            sys.exit(0)
