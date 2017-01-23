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

from imports import globals


class banners:

    def print_license(self):
        print("")
        print(globals.vars.fulllicense)
        print("")

    def versionbanner(self):
        print("")
        print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
        print("\t\t    " + globals.vars.appname + ' v' + globals.vars.version)
        print("Built by:\t\t" + globals.vars.authors)
        print("Maintained by:\t\t" + ', '.join(globals.vars.maintainers))
        print("Is licensed under:\t" + globals.vars.licensev)
        print("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~")
        print(globals.vars.fulllicense)
        print(globals.vars.usage)

    def print_available_payloads(self, array):
        answer = str(array[globals.vars.column_for_uid]) + "\t" + str(array[globals.vars.column_for_name]) + "\t" + str(array[globals.vars.column_for_version]) + "\t\t"
        answer += str(array[globals.vars.column_for_location]) + "\t\t" + str(array[globals.vars.colomn_for_time])
        print(answer)
