from imports import globals
from imports import db_handler
from sys import exit
from imports.prettytable import PrettyTable

class MuchSearch(object):

    def __init__(self):
        self.db = db_handler.DBHandler()
        self.names = [x.lower() for x in self.db.get_mal_names()]

    #:todo: make this more efficient
    def sort(self, args):
        self.hits = {}
        self.query = None
        self.param = None
        self.prequery = "SELECT ID, TYPE, LANGUAGE, ARCHITECTURE, PLATFORM, NAME FROM MALWARES WHERE "
        self.ar = []
        args = [x.lower() for x in args]

        for arg in args:
            for optname, values in globals.vars.opts:
                for value in values:
                    if arg in value:
                        self.hits.update({optname: value})
        # Malware name checking has its own iterations to avoid false matches
        if not self.hits:
            for arg in args:
                for name in self.names:
                    if arg in name:
                        self.query = "NAME LIKE ?"
                        self.param = name

        if len(self.hits) > 0:
            self.query = self.build_query(self.hits)
            self.ar = self.db.query(self.prequery + self.query)
            self.print_payloads(self.ar)
        elif self.param is not None:
            self.ar = self.db.query(self.prequery + self.query, [self.param])
            self.print_payloads(self.ar)
        else:
            print "Error: filter did not match any malware :("
            exit()

        return self.hits

    # Build the dynamic query
    def build_query(self, dic):
        qlist = []
        for key, val in dic.items():
            if isinstance(val, (list, tuple)):
                tmp = str(key) + ' in (' + ','.join(map(lambda x: '\'' + str(x) + '\'', val)) + ') '
            else:
                tmp = str(key) + '=' + '\'' + str(val) + '\''
            qlist.append(' ' + tmp + ' ')
        return "and".join(qlist)

    def print_payloads(self, m, fields=["ID", "Type", "Language", "Architecture", "Platform", "Name"]):

        table = PrettyTable(fields)
        table.align["ID"] = "l"
        table.align["Name"] = "l"
        for malware in m:
            table.add_row(malware)
        print table
        print "\n"

