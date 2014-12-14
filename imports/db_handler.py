import sqlite3 as lite
from imports import globals
import sys


class DBHandler:

    def __init__(self):
        try:
            self.con = lite.connect(globals.vars.db_path)
            self.cur = self.con.cursor()
        except lite.Error as e:
            print "An error occurred:", e.args[0]
            sys.exit()

    def get_full_details(self):
        return self.cur.execute("SELECT * FROM Malwares").fetchall()

    def get_partial_details(self):
        return self.cur.execute("SELECT ID, TYPE, LANGUAGE, ARCHITECTURE, PLATFORM, NAME FROM Malwares").fetchall()

    def get_mal_names(self):
        # Sqlite3 returns a tuple even if a single value is returned
        # We use x[0] for x to unpack the tuples
        return [val[0] for val in self.cur.execute("SELECT NAME FROM Malwares").fetchall()]

    def query(self, query, param=''):
        try:
            if param is not '':
                return self.cur.execute(query, param if type(param) is list else [param]).fetchall()
            else:
                return self.cur.execute(query).fetchall()
        except lite.Error as e:
            print "An error occurred:", e.args[0]
            sys.exit()
