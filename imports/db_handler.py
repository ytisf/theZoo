import sqlite3
from contextlib import contextmanager
from typing import List, Tuple, Any, Optional, Union
import logging
from imports import globals

logger = logging.getLogger(__name__)

class DBHandler:
    
    def __init__(self):
        self.db_path = globals.vars.db_path
        self._connection = None
        self._connect()
    
    def _connect(self):
        try:
            self._connection = sqlite3.connect(
                self.db_path,
                check_same_thread=False,
                timeout=30.0
            )
            self._connection.execute("PRAGMA journal_mode=WAL")
            self._connection.execute("PRAGMA foreign_keys=ON")
            self._connection.execute("PRAGMA synchronous=NORMAL")
            self._connection.execute("PRAGMA cache_size=10000")
            self._connection.execute("PRAGMA temp_store=MEMORY")
            
            logger.info("Database connection established successfully")
        except sqlite3.Error as e:
            logger.error(f"Database connection failed: {e}")
            raise
    
    @contextmanager
    def get_cursor(self):
        if not self._connection:
            self._connect()
        
        cursor = self._connection.cursor()
        try:
            yield cursor
            self._connection.commit()
        except sqlite3.Error as e:
            self._connection.rollback()
            logger.error(f"Database operation failed: {e}")
            raise
        finally:
            cursor.close()
    
    def _execute_query(self, query: str, params: Optional[Union[List, Tuple]] = None) -> List[Tuple]:
        with self.get_cursor() as cursor:
            if params:
                cursor.execute(query, params)
            else:
                cursor.execute(query)
            return cursor.fetchall()
    
    def get_full_details(self) -> List[Tuple]:
        return self._execute_query("SELECT * FROM Malwares")
    
    def get_partial_details(self) -> List[Tuple]:
        query = """
            SELECT ID, TYPE, LANGUAGE, ARCHITECTURE, PLATFORM, NAME 
            FROM Malwares
        """
        return self._execute_query(query)
    
    def get_mal_list(self) -> List[Tuple]:
        query = "SELECT ID, NAME, TYPE FROM Malwares"
        return self._execute_query(query)
    
    def get_mal_names(self) -> List[str]:
        query = "SELECT NAME FROM Malwares"
        results = self._execute_query(query)
        return [row[0] for row in results if row[0]]
    
    def get_mal_tags(self) -> List[str]:
        query = "SELECT DISTINCT TAGS FROM Malwares WHERE TAGS IS NOT NULL AND TAGS != ''"
        results = self._execute_query(query)
        return [row[0] for row in results]
    
    def get_mal_info(self, mal_id: int) -> List[Tuple]:
        query = """
            SELECT TYPE, NAME, VERSION, AUTHOR, LANGUAGE, DATE, 
                   ARCHITECTURE, PLATFORM, TAGS 
            FROM Malwares 
            WHERE ID = ?
        """
        return self._execute_query(query, (mal_id,))
    
    def query(self, query: str, params: Optional[Union[List, Tuple, Any]] = None) -> List[Tuple]:
        if globals.vars.DEBUG_LEVEL == 2:
            logger.debug(f"Executing query: {query} with params: {params}")
        
        if params is not None and not isinstance(params, (list, tuple)):
            params = (params,)
        
        return self._execute_query(query, params)
    
    def execute_many(self, query: str, params_list: List[Tuple]) -> None:
        with self.get_cursor() as cursor:
            cursor.executemany(query, params_list)
    
    def get_connection_info(self) -> dict:
        with self.get_cursor() as cursor:
            cursor.execute("PRAGMA database_list")
            db_info = cursor.fetchall()
            
            cursor.execute("SELECT COUNT(*) FROM Malwares")
            record_count = cursor.fetchone()[0]
            
            return {
                'database_path': self.db_path,
                'databases': db_info,
                'malware_count': record_count,
                'connection_active': self._connection is not None
            }
    
    def close_connection(self):
        if self._connection:
            try:
                self._connection.close()
                self._connection = None
                logger.info("Database connection closed successfully")
            except sqlite3.Error as e:
                logger.error(f"Error closing database connection: {e}")
                raise
    
    def renew_connection(self):
        self.close_connection()
        self._connect()
    
    def __enter__(self):
        return self
    
    def __exit__(self, exc_type, exc_val, exc_tb):
        self.close_connection()
    
    def __del__(self):
        if hasattr(self, '_connection') and self._connection:
            self._connection.close()
