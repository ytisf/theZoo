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
from optparse import OptionParser
from imports.update_handler import Updater
from imports import manysearches
from imports import muchmuchstrings
from imports.eula_handler import EULA
from imports.globals import vars
from imports.terminal_handler import Controller
from imports import db_handler

__version__ = "0.6.0 Moat"
__codename__ = "Moat"
__appname__ = "theZoo"
__authors__ = ["Yuval Nativ", "Shahak Shalev", "Lahad Ludar", "5Fingers"]
__licensev__ = "GPL v3.0"
__maintainer = "Yuval Nativ & Shahak Shalev"
__status__ = "Beta"


def main():

    # Much much imports :)
    updateHandler = Updater
    eulaHandler = EULA()
    bannerHandler = muchmuchstrings.banners()
    db = db_handler.DBHandler()
    terminalHandler = Controller()

    def filter_array(array, colum, value):
        ret_array = [row for row in array if value in row[colum]]
        return ret_array

    def getArgvs():
        parser = OptionParser()
        parser = OptionParser()
        parser.add_option("-f", "--filter", dest="mal_filter", default=[],
                          help="Filter the malwares.", action="append")
        parser.add_option("-u", "--update", dest="update_bol", default=0,
                          help="Updates the DB of theZoo.", action="store_true")
        parser.add_option("-v", "--version", dest="ver_bol", default=0,
                          help="Shows version and licensing information.", action="store_true")
        parser.add_option("-w", "--license", dest="license_bol", default=0,
                          help="Prints the GPLv3 license information.", action="store_true")
        (options, args) = parser.parse_args()
        return options

    # Here actually starts Main()
    arguments = getArgvs()

    # Checking for EULA Agreement
    a = eulaHandler.check_eula_file()
    if a == 0:
        eulaHandler.prompt_eula()

    # Get arguments

    # Check if update flag is on
    if arguments.update_bol == 1:
        a = Updater()
        with open('conf/db.ver', 'r') as f:
            a.update_db(f.readline())
        sys.exit(1)

    # Check if version flag is on
    if arguments.ver_bol == 1:
        print(vars.maldb_banner)
        sys.exit(1)

    # Check if license flag is on
    if arguments.license_bol == 1:
        bannerHandler.print_license()
        sys.exit(1)

    if len(arguments.mal_filter) > 0:
        manySearch = manysearches.MuchSearch()
        print(vars.maldb_banner)
        manySearch.sort(arguments.mal_filter)
        sys.exit(1)

    # Initiate normal run. No arguments given.
    os.system('cls' if os.name == 'nt' else 'clear')
    print(vars.maldb_banner)
    while 1:
        terminalHandler.MainMenu()
    sys.exit(1)


if __name__ == "__main__":
    main()
