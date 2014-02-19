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

class init:
    def init(self):
        # Global Variables
        version = "0.5.0 Citadel"
        appname = "theZoo"
        codename = "Citadel"
        authors = "Yuval Nativ, Lahad Ludar, 5fingers"
        licensev = "GPL v3.0"
        fulllicense = appname + " Copyright (C) 2014 " + authors + "\n"
        fulllicense += "This program comes with ABSOLUTELY NO WARRANTY; for details type '" + sys.argv[0] +" -w'.\n"
        fulllicense += "This is free software, and you are welcome to redistribute it."

        useage = '\nUsage: ' + sys.argv[0] +  ' -s search_query -t trojan -p vb\n\n'
        useage += 'The search engine can search by regular search or using specified arguments:\n\nOPTIONS:\n   -h  --help\t\tShow this message\n   -t  --type\t\tMalware type, can be virus/trojan/botnet/spyware/ransomeware.\n   -p  --language\tProgramming language, can be c/cpp/vb/asm/bin/java.\n   -u  --update\t\tUpdate malware index. Rebuilds main CSV file. \n   -s  --search\t\tSearch query for name or anything. \n   -v  --version\tPrint the version information.\n   -w\t\t\tPrint GNU license.\n'

        column_for_pl = 6
        column_for_type = 2
        column_for_location = 1
        colomn_for_time = 7
        column_for_version = 4
        column_for_name = 3
        column_for_uid = 0
        column_for_arch = 8
        column_for_plat = 9
        conf_folder = 'conf'
        eula_file = conf_folder + '/eula_run.conf'
        maldb_ver_file = conf_folder + '/db.ver'
        main_csv_file = conf_folder + '/index.csv'
        giturl = 'https://raw.github.com/ytisf/theZoo/master/'
        addrs = ['reverce_tcp/', 'crazy_mal/', 'mal/', 'show malwares']

class bcolors:
    PURPLE = '\033[95m'
    BLUE = '\033[94m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    RED = '\033[91m'
    WHITE = '\033[0m'

class vars:
    version = "0.4.2 Arthur"
    appname = "Malware DB"
    authors = "Yuval Nativ, Lahad Ludar, 5fingers"
    licensev = "GPL v3.0"
    fulllicense = appname + " Copyright (C) 2014 " + authors + "\n"
    fulllicense += "This program comes with ABSOLUTELY NO WARRANTY; for details type '" + sys.argv[0] +" -w'.\n"
    fulllicense += "This is free software, and you are welcome to redistribute it."

    useage = '\nUsage: ' + sys.argv[0] +  ' -s search_query -t trojan -p vb\n\n'
    useage += 'The search engine can search by regular search or using specified arguments:\n\nOPTIONS:\n   -h  --help\t\tShow this message\n   -t  --type\t\tMalware type, can be virus/trojan/botnet/spyware/ransomeware.\n   -p  --language\tProgramming language, can be c/cpp/vb/asm/bin/java.\n   -u  --update\t\tUpdate malware index. Rebuilds main CSV file. \n   -s  --search\t\tSearch query for name or anything. \n   -v  --version\tPrint the version information.\n   -w\t\t\tPrint GNU license.\n'

    column_for_pl = 6
    column_for_type = 2
    column_for_location = 1
    colomn_for_time = 7
    column_for_version = 4
    column_for_name = 3
    column_for_uid = 0
    column_for_arch = 8
    column_for_plat = 9

    conf_folder = 'conf'
    eula_file = conf_folder + '/eula_run.conf'
    maldb_ver_file = conf_folder + '/db.ver'
    main_csv_file = conf_folder + '/index.csv'
    giturl = 'https://raw.github.com/ytisf/theZoo/master/'

    with file(maldb_ver_file) as f:
        db_ver = f.read()

    maldb_banner = "    	    __  ___      __                               ____  ____\n"
    maldb_banner += "      	   /  |/  /___ _/ /      ______ _________        / __ \/ __ )\n"
    maldb_banner += "    	  / /|_/ / __ `/ / | /| / / __ `/ ___/ _ \______/ / / / __ |\n"
    maldb_banner += "    	 / /  / / /_/ / /| |/ |/ / /_/ / /  /  __/_____/ /_/ / /_/ /\n"
    maldb_banner += "    	/_/  /_/\__,_/_/ |__/|__/\__,_/_/   \___/     /_____/_____/\n\n"
    maldb_banner += "                                version: " + version + "\n"
    maldb_banner += "                                db_version: " + db_ver + "\n"
    maldb_banner += "                                built by: " + authors + "\n\n"

    addrs = ['reverce_tcp/', 'crazy_mal/', 'mal/', 'show malwares']
    addrs = ['list', 'search', 'get', 'exit']
