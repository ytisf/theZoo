import sqlite3 as lite
from imports import globals
import sys


class DBHandler:

    def __init__(self):
        self._connect()

    def _connect(self):
        try:
            self.con = lite.connect(globals.vars.db_path)
            self.cur = self.con.cursor()
        except lite.Error as e:
            print(f"An error occurred: {e.args[0]}")
            sys.exit()

    def get_full_details(self):
        return self.cur.execute("SELECT * FROM Malwares").fetchall()

    def get_partial_details(self):
        query = "SELECT ID, TYPE, LANGUAGE, ARCHITECTURE, PLATFORM, NAME FROM Malwares"
        return self.cur.execute(query).fetchall()

    def get_mal_list(self):
        query = "SELECT ID, NAME, TYPE FROM Malwares"
        return self.cur.execute(query).fetchall()

    def get_mal_names(self):
        query = "SELECT NAME FROM Malwares"
        return [val[0] for val in self.cur.execute(query).fetchall()]

    def get_mal_tags(self):
        query = "SELECT DISTINCT TAGS FROM Malwares WHERE TAGS IS NOT NULL"
        return [val[0] for val in self.cur.execute(query).fetchall()]

    def get_mal_info(self, mid):
        query = (
            "SELECT TYPE, NAME, VERSION, AUTHOR, LANGUAGE, DATE, ARCHITECTURE, PLATFORM, TAGS "
            f"FROM Malwares WHERE ID = {mid}"
        )
        return self.cur.execute(query).fetchall()

    def query(self, query, param=''):
        if globals.vars.DEBUG_LEVEL == 2:
            print(locals())
        try:
            if param != '':
                params = param if isinstance(param, list) else [param]
                return self.cur.execute(query, params).fetchall()
            return self.cur.execute(query).fetchall()
        except lite.Error as e:
            print(f"An error occurred: {e.args[0]}")
            sys.exit()

    def close_connection(self):
        try:
            self.cur.close()
            self.con.close()
        except lite.Error as e:
            print(f"An error occurred: {e.args[0]}")
            sys.exit()

    def renew_connection(self):
        self._connect()
