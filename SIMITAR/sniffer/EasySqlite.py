from termcolor import colored
import sqlite3
import numpy
import os


"""
easysqlite.py: just a wrapper over SQLite for python, to make it very simple to use.
This was the original wrapper I based on
https://gist.github.com/goldsborough/c973d934f620e16678bf
"""
__author__ = "Anderson Paschoalon"
__license__ = "GPL"
__version__ = "1.0.1"
__email__ = "anderson.paschoalon@gmail.com"


class Database:
    """
    The constructor of the Database class
    The constructor can either be passed the name of the database to open
    or not, it is optional. The database can also be opened manually with
    the open() method or as a context manager.
    :param name: Optionally, the name of the database to open.
    """

    def __init__(self, name=None):
        self._is_open = False
        self.conn = None
        self.cursor = None

        if name:
            self.open(name)
            self._name = name
            self._is_open = True

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_value, traceback):
        self.close()

    def open(self, name):
        """
        Opens a new database connection.
        This function manually opens a new database connection. The database
        can also be opened in the constructor or as a context manager.

        :param name: The name of the database to open.
        :return:
        """

        try:
            self.conn = sqlite3.connect(name)
            self.cursor = self.conn.cursor()
            self._is_open = True
            self._name = name

        except sqlite3.Error:
            print(colored( "Error: can't connect to the database!", 'red'))
            self._is_open = False

    def close(self):
        """
        Function to close a datbase connection.
        The database connection needs to be closed before you exit a program,
        otherwise changes might be lost. You can also manage the database
        connection as a context manager, then the closing is done for you. If
        you opened the database connection with the open() method or with the
        constructor ( \__init\__() ), you must close the connection with this
        method.
        :return: True in success
        """

        if self.conn:
            self.conn.commit()
            self.cursor.close()
            self.conn.close()
            self._is_open = False
            return True
        return False

    def rm(self):
        """
        Remove physically the database, if it is already closed.
        :return: True in success
        """
        if not self._is_open:
            os.system('rm -f ' + self._name)
            return True
        else:
            print(colored("Error: Database " + self._name + " is oppened. You must close before remove physically.", 'red'))
            return False

    def print_info(self, table_name):
        """
        Prints a formated table on the standard output.
        :param table_name: table to be printed
        :return: True
        """
        command = 'sqlite3 ' + self._name + '  ".headers ON" ".mode column" "select * from ' + table_name + ';"'
        # print(command)
        os.system(command)
        return True

    def print_table(self, table_name, where_clause=''):
        print('table_name:'+table_name)
        self.cursor.execute('PRAGMA table_info(' + table_name + ');')
        col_info = self.cursor.fetchall()
        col_names = [''] * len(col_info)
        col_max_len = [0] * len(col_info)
        col_title_len = [0] * len(col_info)
        col_sizes = [0] * len(col_info)
        i = 0
        while i < len(col_names):
            col_names[i] = col_info[i][1]
            i += 1
        for i in range(len(col_title_len)):
            col_title_len[i] = len(str(col_names[i]))
        # retrieve all data
        values = []
        if where_clause=='':
            values = self.get(table_name, '*')
        else:
            values = self.get_where(table_name, '*', where_clause)
        nrows = len(values)
        ncols = len(values[0])
        for i in range(nrows):
            for j in range(ncols):
                if len(str(values[i][j])) > col_max_len[j]:
                    col_max_len[j] = len(str((values[i][j])))
        for i in range(len(col_sizes)):
            col_sizes[i] = max(col_max_len[i], col_title_len[i])
        # print table
        spacing = '   '
        padingchar = ' '
        print_str = ''
        for i in range(len(col_names)):
            print_str += str(col_names[i])
            padding_len = col_sizes[i] - len(col_names[i])
            print_str += padingchar * padding_len + spacing
        print(print_str)
        print_str = ''
        for i in range(len(col_names)):
            print_str += '-' * col_sizes[i] + spacing
        print(print_str)
        for i in range(len(values)):
            print_str = ''
            for j in range(len(values[i])):
                print_str += str(values[i][j])
                padding_len = col_sizes[j] - len(str(values[i][j]))
                print_str += padingchar * padding_len + spacing
            print(print_str)

    def get(self, table, thecolumns, limit=None):
        """
        Function to fetch/query data from a database.
        This is the main function used to query a database for data.

        :param table: The name of the database's table to query from.
        :param thecolumns: The string of columns, comma-separated, to fetch.
        :param limit: limit Optionally, a limit of items to fetch.
        :return: list of elements
        """

        query = "SELECT {0} from {1};".format(thecolumns, table)
        self.cursor.execute(query)
        # fetch data
        rows = self.cursor.fetchall()

        return rows[len(rows) - limit if limit else 0:]

    def get_where(self, table, thecolumns, where_clause, limit=None):
        """
        Function to fetch/query data from a database table with where
        clause to filter results.
        This is the main function used to query a database for data.
        :param table: The name of the database's table to query from.
        :param thecolumns: The string of columns, comma-separated, to fetch.
        :param where_clause: clause argument (filter)
        :param limit: Optionally, a limit of items to fetch.
        :return: list of elements
        """
        query = "SELECT {0} from {1} where {2};".format(thecolumns, table, where_clause)
        self.cursor.execute(query)
        # fetch data
        rows = self.cursor.fetchall()
        return rows[len(rows) - limit if limit else 0:]

    def get_last(self, table, thecolumns):
        """
        Utilty function to get the last row of data from a database.
        :param table: The database's table from which to query.
        :param thecolumns: The columns which to query.
        :return: list of elements
        """
        return self.get(table, thecolumns, limit=1)[0]

    @staticmethod
    def to_csv(data, fname="output.csv"):
        """
        Utility function that converts a dataset into CSV format.
        :param data: The data, retrieved from the get() function.
        :param fname: The file name to store the data in.
        :return:
        """
        with open(fname, 'a') as file:
            file.write(",".join([str(j) for i in data for j in i]))

    def write(self, table, columns, data):
        """
        Function to write data to the database.
        The write() function inserts new data into a table of the database.
        :param table: The name of the database's table to write to.
        :param columns: The columns to insert into, as a comma-separated string.
        :param data: The new data to insert, as a comma-separated string.
        :return: True in success
        """
        list_dim = len(numpy.shape(data))
        if list_dim == 1:
            query = "INSERT INTO {0} ({1}) VALUES ({2});".format(table, columns, data)
            self.cursor.execute(query)
            self.conn.commit()
            return True
        elif list_dim == 2:
            data_size0 = numpy.shape(data)[1]
            qvalues = '?, ' * (data_size0 - 1) + '?'
            query = "INSERT INTO {0} ({1})  VALUES ({2}); ".format(table, columns, qvalues)
            # print(query)
            self.cursor.executemany(query, data)
            self.conn.commit()
            return True
        else:
            print(colored( "Error: Data vector dimension is larger than 2: " + str(len(numpy.shape(data))), 'red'))
            print("Use a list with one or two dimensions.")
            return False

    def delete(self, table, where):
        """
         Function to write delete of the database.
        :param table: The database's table from which to query.
        :param where: where SQL clause of delete query
        :return: True in success
        """
        query = "DELETE FROM {0} WHERE {1};".format(table, where)
        self.cursor.execute(query)
        self.conn.commit()
        return True

    def query(self, sql):
        """
        Function to query any other SQL statement.
        This function is there in case you want to execute any other sql
        statement other than a write or get.
        :param sql: A valid SQL statement in string format.
        :return:
        """
        self.cursor.execute(sql)
        self.conn.commit()

    @staticmethod
    def summary(rows):
        """
        Utility function that summarizes a dataset.
        This function takes a dataset, retrieved via the get() function, and
        returns only the maximum, minimum and average for each column.
        :param rows: The retrieved data.
        :return:
        """

        # split the rows into columns
        cols = [[r[c] for r in rows] for c in range(len(rows[0]))]

        # the time in terms of fractions of hours of how long ago
        # the sample was assumes the sampling period is 10 minutes
        t = lambda col: "{:.1f}".format((len(rows) - col) / 6.0)

        # return a tuple, consisting of tuples of the maximum,
        # the minimum and the average for each column and their
        # respective time (how long ago, in fractions of hours)
        # average has no time, of course
        ret = []

        for c in cols:
            hi = max(c)
            hi_t = t(c.index(hi))

            lo = min(c)
            lo_t = t(c.index(lo))

            avg = sum(c) / len(rows)

            ret.append(((hi, hi_t), (lo, lo_t), avg))

        return ret


if __name__ == '__main__':
    # just some tests for this wrapper
    lista = [('Agenor de Sousa', 23, '12345678901', 'agenor@email.com',
              '(10) 8300-0000', 'Salvador', 'BA', '2014-07-29 11:23:01.199001'),
             ('Bianca Antunes', 21, '12345678902', 'bianca@email.com',
              '(10) 8350-0001', 'Fortaleza', 'CE', '2014-07-28 11:23:02.199002'),
             ('Carla Ribeiro', 30, '12345678903', 'carla@email.com',
              '(10) 8377-0002', 'Campinas', 'SP', '2014-07-28 11:23:03.199003'),
             ('Fabiana de Almeida', 25, '12345678904', 'fabiana@email.com',
              '(10) 8388-0003', 'São Paulo', 'SP', '2014-07-29 11:23:04.199004'),
             ('Agenor', 23, '12345678901', 'agenor@email.com',
              '(10) 8300-0000', 'Salvador', 'BA', '2014-07-29 11:23:01.199001'),
             ('Agenor (errado)', 23, '9999999999', 'agenor@email.com',
              '(10) 8300-0000', 'Salvador', 'BA', '2014-07-29 11:23:01.199001')
             ]
    listasimples = [('Agenor de Sousa', 23, '12345678901', 'agenor@email.com',
                     '(10) 8300-0000', 'Salvador', 'BA', '2014-07-29 11:23:01.199001')]

    columns = 'nome, idade, cpf, email, fone, cidade, uf, criado_em'

    db = Database('test-database-py.db')
    db.query("""
                CREATE TABLE IF NOT EXISTS clientes (
                    id INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
                    nome TEXT NOT NULL,
                    idade INTEGER,
                    cpf	VARCHAR(11) NOT NULL,
                    email TEXT NOT NULL,
                    fone TEXT,
                    cidade TEXT,
                    uf VARCHAR(2) NOT NULL,
                    criado_em DATE NOT NULL
                );
                """)

    db.write('clientes', columns, lista)
    db.write('clientes', columns, lista)
    db.write('clientes', columns, lista)
    data_out = db.get('clientes', columns)
    print(data_out)
    age1 = db.get_where('clientes', 'nome', 'idade=23')
    print('Age: ' + str(age1))
    db.delete('clientes', 'cpf=12345678901 AND idade=23')
    db.print_info('clientes')

    ###############
    table_name = 'clientes'
    where_clause = '*'
    db.print_table(table_name)

    db.close()
    # db.rm()