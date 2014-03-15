import csv
import sys
import re

import globals
from imports import manysearches
from imports.updatehandler import Updater


class Controller:
    def __init__(self):
        self.modules = None
        self.currentmodule = ''
        self.commands = [   ("search", "searching for malwares using given parameter with 'set'."),
                            ("list all", "lists all available modules"),
                            ("set", "sets options for the search"),
                            ("get", "downloads the malware"),
                            ("update-db", "updates the databse"),
                            ("back", "removes currently chosen malware"),
                            ("help", "displays this help..."),
                            ("exit", "exits...")]

        self.searchmeth = [ ("arch","which architecture etc; x86, x64, arm7 so on..."),
                            ("plat","platform: win32, win64, mac, android so on..."),
                            ("lang","c, cpp, vbs, bin so on..."),
                            ("vip", "1 or 0")]

        self.modules = self.GetPayloads()

        #print 'im at init'
        self.plat = ''
        self.arch = ''
        self.lang = ''
        self.type = ''
        self.vip = ''

    def GetPayloads(self):
        m = []
        csvReader = csv.reader(open(globals.vars.main_csv_file, 'rb'), delimiter=',')
        for row in csvReader:
            m.append(row)
        return m

    def MainMenu(self):
        if len(self.currentmodule) > 0:
            g = int(self.currentmodule) - 1
            just_print = self.modules[int(g)][int(globals.vars.column_for_name)]
            cmd = raw_input(
                globals.bcolors.GREEN + 'mdb ' + globals.bcolors.RED + str(just_print) + globals.bcolors.GREEN + '#> ' + globals.bcolors.WHITE).strip()
        else:
            cmd = raw_input(globals.bcolors.GREEN + 'mdb ' + globals.bcolors.GREEN + '#> ' + globals.bcolors.WHITE).strip()

        try:
            while cmd == "":
                #print 'no cmd'
                self.MainMenu()

            if cmd == 'help':
                print " Available commands:\n"
                for (cmd, desc) in self.commands:
                    print "\t%s\t%s" % ('{0: <12}'.format(cmd), desc)
                print ''
                self.MainMenu()

            if cmd == 'search':
                ar = self.modules
                manySearch = manysearches.MuchSearch()

                # function to sort by arch
                if len(self.arch) > 0:
                    ar = manySearch.sort(ar, globals.vars.column_for_arch, self.arch)
                # function to sort by plat
                if len(self.plat) > 0:
                    ar = manySearch.sort(ar, globals.vars.column_for_plat, self.plat)
                # function to sort by lang
                if len(self.lang) > 0:
                    ar = manySearch.sort(ar, globals.vars.column_for_pl, self.lang)
                if len(self.type) > 0:
                    ar = manySearch.sort(ar, globals.vars.column_for_type, self.type)
                if len(self.vip) > 0:
                    ar = manySearch.sort(ar, globals.vars.column_for_vip, self.vip)
                printController = manysearches.MuchSearch()
                printController.PrintPayloads(ar)
                self.MainMenu()

            if re.match('^set', cmd):
                try:
                    cmd = re.split('\s+', cmd)
                    print cmd[1] + ' => ' + cmd[2]
                    if cmd[1] == 'arch':
                        self.arch = cmd[2]
                    if cmd[1] == 'plat':
                        self.plat = cmd[2]
                    if cmd[1] == 'lang':
                        self.lang = cmd[2]
                    if cmd[1] == 'type':
                        self.type = cmd[2]
                except:
                    print 'Need to use the set method with two arguments.'
                cmd = ''
                self.MainMenu()

            if cmd == 'show':
                if len(self.currentmodule) == 0:
                    print "No modules have been chosen. Use 'use' command."
                if len(self.currentmodule) > 0:
                    print 'Currently selected Module: ' + self.currentmodule
                print '\tarch => ' + str(self.arch)
                print '\tplat => ' + str(self.plat)
                print '\tlang => ' + str(self.lang)
                print '\ttype => ' + str(self.type)
                print ''
                self.MainMenu()

            if cmd == 'exit':
                sys.exit(1)

            if cmd == 'update-db':
                updateHandler = Updater()
                updateHandler.get_maldb_ver()
                self.MainMenu()

            if cmd == 'get':
                updateHandler = Updater()
                try:
                    updateHandler.get_malware(self.currentmodule, self.modules)
                    self.MainMenu()
                except:
                    print globals.bcolors.RED + '[-]' + globals.bcolors.WHITE + 'Error getting malware.'
                    self.MainMenu()

            if re.match('^use', cmd):
                try:
                    cmd = re.split('\s+', cmd)
                    self.currentmodule = cmd[1]
                    cmd = ''
                except:
                    print 'The use method needs an argument.'
                self.MainMenu()

            if cmd == 'back':
                print 'im at back - WTF?'
                self.arch = ''
                self.plat = ''
                self.lang = ''
                self.type = ''
                self.currentmodule = ''
                self.MainMenu()

            if cmd == 'list all':
                print "\nAvailable Payloads:"
                array = self.modules
                i = 0
                print "ID\tName\tType"
                print '-----------------'
                for element in array:
                    answer = array[i][globals.vars.column_for_uid]
                    answer += '\t%s' % ('{0: <12}'.format(array[i][globals.vars.column_for_name]))
                    answer += '\t%s' % ('{0: <12}'.format(array[i][globals.vars.column_for_type]))
                    print answer
                    i=i+1
                self.MainMenu()

            if cmd == 'quit':
                print ":("
                sys.exit(1)

        except KeyboardInterrupt:
            print ("i'll just go now...")
            sys.exit()
