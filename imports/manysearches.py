from imports import globals
from imports import db_handler
from imports.prettytable import PrettyTable
from imports.colors import *

class MuchSearch(object):

    def __init__(self):
        self.db = db_handler.DBHandler()
        self.names = [x.lower() for x in self.db.get_mal_names()]
        self.tags = [x.lower() for x in self.db.get_mal_tags()]

    #:todo: make this more efficient
    def sort(self, args):
        self.hits = {}
        self.query = None
        self.param = None
        self.prequery = "SELECT ID, TYPE, LANGUAGE, ARCHITECTURE, PLATFORM, NAME FROM MALWARES WHERE "
        self.postquery = " COLLATE NOCASE"
        self.ar = []
        args = [x.lower() for x in args]

        for arg in args:
            for optname, values in globals.vars.opts:
                for value in values:
                    if arg in value:
                        self.hits.update({optname: value})
        # Search by Tag
        for arg in args:
            if arg in self.tags:
                self.hits.update({'tags': arg})
        # Malware name checking has its own iterations to avoid false matches
        if not self.hits:
            for arg in args:
                for name in self.names:
                    if arg in name:
                        self.query = "NAME LIKE ?"
                        self.param = name

        if len(self.hits) > 0:
            self.query = self.build_query(self.hits)
            self.ar = self.db.query(self.prequery + self.query + self.postquery)
            self.print_payloads(self.ar)
        elif self.param is not None:
            self.ar = self.db.query(self.prequery + self.query, [self.param])
            self.print_payloads(self.ar)
        else:
            print(red("[!]") + " Filter did not match any malware :(\n")

        return self.hits

    # Dynamicly build the query
    def build_query(self, dic):
        qlist = []
        for key, val in dic.items():
            if isinstance(val, (list, tuple)):
                tmp = str(key) + ' in (' + ','.join(map(lambda x: '\'' + str(x) + '\'', val)) + ') '
            else:
                tmp = str(key) + '=' + '\'' + str(val) + '\''
            qlist.append(' ' + tmp + ' ')
        return "and".join(qlist)

    def print_payloads(self, m, fields=["#", "Type", "Language", "Architecture", "Platform", "Name"]):
        table = PrettyTable(fields)
        table.align = "l"
        for malware in m:
            table.add_row(malware)
        print(table)
        print(bold(green("[+]")) + " Total records found: %s" % len(m) + "\n")
