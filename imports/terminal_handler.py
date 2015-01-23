import sys
import re
import rlcompleter
try:
    import readline
except ImportError:
    from imports import winreadline as readline

import globals
from imports import manysearches
from imports.update_handler import Updater
from imports import db_handler


class Controller:

    def __init__(self):
        self.modules = None
        self.currentmodule = None
        self.db = db_handler.DBHandler()
        self.commands = [("search", "Search for malwares according to a filter,\n\t\t\te.g 'search cpp worm'."),
                         ("list all", "Lists all available modules"),
                         ("use", "Selects a malware by ID"),
                         ("get", "Downloads selected malware"),
                         ("report-mal", "Report a malware you found"),
                         ("update-db", "Updates the databse"),
                         ("help", "Displays this help..."),
                         ("exit", "Exits...")]

        self.commandsWithoutDescription = {'search': '', 'list all': '', 'use': '',
                                           'get': '', 'report-mal': '', 'update-db': '', 'help': '', 'exit': ''}

        self.searchmeth = [("arch", "which architecture etc; x86, x64, arm7 so on..."),
                           ("plat",
                            "platform: win32, win64, mac, android so on..."),
                           ("lang", "c, cpp, vbs, bin so on..."),
                           ("vip", "1 or 0")]

        self.modules = self.GetPayloads()
        completer = globals.Completer(self.commandsWithoutDescription)

        readline.parse_and_bind("tab: complete")
        readline.set_completer(completer.complete)

    def GetPayloads(self):
        return self.db.get_full_details()

    def MainMenu(self):
        # This will give you the nice prompt you like so much
        while (True):  # Dont hate, affiliate
            try:
                if self.currentmodule is not None:
                    g = self.currentmodule - 1
                    just_print = self.modules[g][int(globals.vars.column_for_name)]
                    cmd = raw_input(
                        globals.bcolors.GREEN + 'mdb ' + globals.bcolors.RED + str(
                            just_print) + globals.bcolors.GREEN + '#> ' + globals.bcolors.WHITE).strip()
                else:
                    cmd = raw_input(
                        globals.bcolors.GREEN + 'mdb ' + globals.bcolors.GREEN + '#> ' + globals.bcolors.WHITE).strip()
            except KeyboardInterrupt:
                print globals.bcolors.BLUE + "\n\n[*]" + globals.bcolors.WHITE \
                    + " Hope you enjoyed your visit at" + globals.bcolors.RED + " theZoo!" + globals.bcolors.WHITE
                exit()

            self.actOnCommand(cmd)

    def actOnCommand(self, cmd):
        try:
            while cmd == "":
                # print 'no cmd'
                return

            if cmd == 'help':
                print " Available commands:\n"
                for (cmd, desc) in self.commands:
                    print "\t%s\t%s" % ('{0: <12}'.format(cmd), desc)
                print ''
                return

            # Checks if normal or freestyle search
            if re.match('^search', cmd):
                manySearch = manysearches.MuchSearch()
                try:
                    args = cmd.rsplit(' ')[1:]
                    manySearch.sort(args)
                except:
                    print globals.bcolors.RED + '[!]' + globals.bcolors.WHITE + 'Uh oh, Invalid query.'
                return

            if cmd == 'exit':
                sys.exit(1)

            if cmd == 'update-db':
                update_handler = Updater()
                db_ver = update_handler.get_maldb_ver()
                update_handler.update_db(db_ver)
                return

            if cmd == 'report-mal':
                rprt_name = raw_input("Name of malware: ")
                rprt_type = raw_input("Type of malware: ")
                rprt_version = raw_input("Version: ")
                rprt_lang = raw_input("Language: ")
                rprt_src = raw_input("Source / Binary (s/b): ")
                rprt_arch = raw_input("Win32, ARM etc. ? ")
                rprt_reporter = raw_input(
                    "Your name for a thank you note on theZoo.\n"
                    "Please notice that this will be public!\n\nName: ")
                rprt_comments = raw_input("Comments? ")

                report = ("//%s//\n" % rprt_name)
                report += ("///type/%s///\n" % rprt_type)
                report += ("///ver/%s///\n" % rprt_version)
                report += ("///lang/%s///\n" % rprt_lang)
                report += ("///src/%s///\n" % rprt_src)
                report += ("///arch/%s///\n" % rprt_arch)
                report += ("//reporter/%s//\n" % rprt_reporter)
                report += ("//comments/%s//\n" % rprt_comments)

                # Just to avoid bots spamming us...
                email = "info"
                email += "\x40"
                email += "morirt\x2ecom"
                print "-------------- Begin of theZoo Report --------------"
                print report
                print "-------------- Ending of theZoo Report --------------"
                print "To avoid compromising your privacy we have chose this method of reporting."
                print "If you have not stated your name we will not write a thanks in our README."
                print "Your email will remain private in scenario and will not be published."
                print ""
                print "Please create an archive file with the structure described in the README file"
                print "And attach it to the email. "
                print("Please send this report to %s" % email)

                return

            if cmd == 'get':
                update_handler = Updater()
                try:
                    update_handler.get_malware(self.currentmodule)
                except:
                    print globals.bcolors.RED + '[-] ' + globals.bcolors.WHITE + 'Error getting malware.'
                return
            # If used the 'use' command
            if re.match('^use', cmd):
                try:
                    cmd = re.split('\s+', cmd)
                    self.currentmodule = int(cmd[1])
                    cmd = ''
                except TypeError:
                    print 'Please enter malware ID'
                except:
                    print 'The use method needs an argument.'
                return

            if cmd == 'list all':
                print "\nAvailable Payloads:"
                array = self.modules
                i = 0
                print "ID\tName\tType"
                print '-----------------'
                for element in array:
                    answer = str(array[i][globals.vars.column_for_uid])
                    answer += '\t%s' % (
                        '{0: <12}'.format(array[i][globals.vars.column_for_name]))
                    answer += '\t%s' % (
                        '{0: <12}'.format(array[i][globals.vars.column_for_type]))
                    print answer
                    i = i + 1
                return

            if cmd == 'quit':
                print ":("
                sys.exit(1)

        except KeyboardInterrupt:
            print ("\n\nI'll just go now...")
            sys.exit()
