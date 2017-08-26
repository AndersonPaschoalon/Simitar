import os
import string

class GnuplotScripts:
    def __init__(self, plot_dir='', data_dir='', font='Helvetica,10', xlabel='xlabel', ylabel='ylabel', title='title',
                 sizeratio='0', linestyle_1='r-', linestyle_2='b-', linestyle_3='g-', linestyle_4='v-',
                 legend1='', legend2='', legend3='', legend4='', type='lines',
                 line_width='2'):
        self.__plot_dir = plot_dir
        self.__data_dir = data_dir
        self.__font = font
        self.__xlabel = xlabel
        self.__ylabel = ylabel
        self.__title = title
        self.__sizeratio = sizeratio
        self.__linestyle_1 = linestyle_1
        self.__linestyle_2 = linestyle_2
        self.__linestyle_3 = linestyle_3
        self.__linestyle_4 = linestyle_4
        self.__linestyle1 = str(self.__map_line_style(self.__linestyle_1))
        self.__linestyle2 = str(self.__map_line_style(self.__linestyle_2))
        self.__linestyle3 = str(self.__map_line_style(self.__linestyle_3))
        self.__linestyle4 = str(self.__map_line_style(self.__linestyle_4))
        self.__legend1 = legend1
        self.__legend2 = legend2
        self.__legend3 = legend3
        self.__legend4 = legend4
        self.__type = type
        self.__lw = line_width

    def plot_config(self, plot_dir='', data_dir='', font='', xlabel='', ylabel='',
                    title='', sizeratio='', linestyle_1='', linestyle_2='', linestyle_3='',
                    linestyle_4='', legend1='', legend2='', legend3='', legend4='',
                    type='', line_width=''):
        if(plot_dir != ''):
            self.__plot_dir = plot_dir
        if (data_dir != ''):
            self.__data_dir = data_dir
        if (font != ''):
            self.__font = font
        if (xlabel != ''):
            self.__xlabel = xlabel
        if (ylabel != ''):
            self.__ylabel = ylabel
        if (title != ''):
            self.__title = title
        if (sizeratio != ''):
            self.__sizeratio = sizeratio
        if (linestyle_1 != ''):
            self.__linestyle_1 = linestyle_1
            self.__linestyle1 = self.__map_line_style(self.__linestyle_1)
        if (linestyle_2 != ''):
            self.__linestyle_2 = linestyle_2
            self.__linestyle2 = self.__map_line_style(self.__linestyle_2)
        if (linestyle_3 != ''):
            self.__linestyle_3 = linestyle_3
            self.__linestyle3 = self.__map_line_style(self.__linestyle_3)
        if (linestyle_4 != ''):
            self.__linestyle_4 = linestyle_4
            self.__linestyle4 = self.__map_line_style(self.__linestyle_4)
        if (legend1 != ''):
            self.__legend1 = legend1
        if (legend2 != ''):
            self.__legend2 = legend2
        if (legend3 != ''):
            self.__legend3 = legend3
        if (legend4 != ''):
            self.__legend4 = legend4
        if (type != ''):
            self.__type = type
        if (line_width != ''):
            self.__lw = line_width

    def plot_2f1error(self, filename="", datafile=""):
        command = self.__plot_command('2f1error', filename, datafile)
        os.system(command)

    def plot_2function(self, filename="", datafile=""):
        command = self.__plot_command('2function', filename, datafile)
        os.system(command)

    def plot_tickbar_label(self, filename="", datafile=""):
        command = self.__plot_command('tickbar-label', filename, datafile)
        os.system(command)

    def plot_2f2data(self, filename="", datafile1="", datafile2=""):
        command = self.__plot_command('2f2data', filename, datafile1=datafile1, datafile2=datafile2)
        os.system(command)

    def plot_2functionxyxy(self, filename="", datafile="", type="lines-lines"):
        self.__type = type
        command = self.__plot_command('2functionxyxy', filename, datafile)
        os.system(command)

    def plot_ferror(self, filename="", datafile=""):
        command = self.__plot_command('ferror', filename, datafile)
        os.system(command)

    def plot_xtickerror(self, filename="", datafile=""):
        command = self.__plot_command('xtickerror', filename, datafile)
        os.system(command)

    def plot_2f2data_log2(self, filename="", datafile1="", datafile2=""):
        command = self.__plot_command('2f2data-log2', filename, datafile1=datafile1, datafile2=datafile2)
        os.system(command)

    def plot_3function(self, filename="", datafile=""):
        command = self.__plot_command('3function', filename, datafile)
        os.system(command)

    def plot_function(self, filename="", datafile=""):
        command = self.__plot_command('function', filename, datafile)
        os.system(command)

    def plot_xtickerror_hline(self, filename="", datafile=""):
        command = self.__plot_command('xtickerror-hline', filename, datafile)
        os.system(command)

    def plot_2f2data_log(self, filename="", datafile1="", datafile2=""):
        command = self.__plot_command('2f2data-log', filename, datafile1=datafile1, datafile2=datafile2)
        os.system(command)

    def plot_4function(self, filename="", datafile=""):
        command = self.__plot_command('4function', filename, datafile)
        os.system(command)

    def plot_tickbar(self, filename="", datafile=""):
        command = self.__plot_command('tickbar', filename, datafile)
        os.system(command)

    def __map_line_style(self, line_style):
        # red
        if line_style == 'r-':
            line_style_code = 1
        elif line_style == 'r+':
            line_style_code = 1
        elif line_style == 'rx':
            line_style_code = 2
        elif line_style == 'r*':
            line_style_code = 3
        elif line_style == 'ro':
            line_style_code = 4
        # blue
        elif line_style == 'b-':
            line_style_code = 11
        elif line_style == 'b+':
            line_style_code = 11
        elif line_style == 'bx':
            line_style_code = 12
        elif line_style == 'b*':
            line_style_code = 13
        elif line_style == 'bo':
            line_style_code = 14
        # green
        elif line_style == 'g-':
            line_style_code = 21
        elif line_style == 'g+':
            line_style_code = 21
        elif line_style == 'gx':
            line_style_code = 22
        elif line_style == 'g*':
            line_style_code = 23
        elif line_style == 'go':
            line_style_code = 24
        # blue
        elif line_style == 'k-':
            line_style_code = 31
        elif line_style == 'k+':
            line_style_code = 31
        elif line_style == 'kx':
            line_style_code = 32
        elif line_style == 'k*':
            line_style_code = 33
        elif line_style == 'ko':
            line_style_code = 34
        # violet
        elif line_style == 'v-':
            line_style_code = 41
        elif line_style == 'v+':
            line_style_code = 41
        elif line_style == 'vx':
            line_style_code = 42
        elif line_style == 'v*':
            line_style_code = 43
        elif line_style == 'vo':
            line_style_code = 44
        # orange
        elif line_style == 'o-':
            line_style_code = 41
        elif line_style == 'o+':
            line_style_code = 41
        elif line_style == 'ox':
            line_style_code = 42
        elif line_style == 'o*':
            line_style_code = 43
        elif line_style == 'oo':
            line_style_code = 44
        # default
        else:
            line_style_code = 1
        return line_style_code

    @staticmethod
    def __var(var_name, var_value):
        return " -e \"" + var_name + "=" + "\'" + var_value + "\'" + "\" "

    def __plot_command(self, plot_type, filename="", datafile="", datafile1="", datafile2=""):
        plot_script = os.path.dirname(os.path.abspath(__file__)) + '/gnuplot/' + plot_type + '.gnu'
        full_filename = self.__plot_dir + '/' + filename
        full_datafile = self.__data_dir + '/' + datafile
        full_datafile1 = ""
        full_datafile2 = ""
        if datafile1 != "":
            full_datafile1 = self.__data_dir + '/' + datafile1
        if datafile2 != "":
            full_datafile2 = self.__data_dir + '/' + datafile2
        command = "gnuplot " + self.__var("filename", full_filename) + self.__var("datafile", full_datafile) + \
                  self.__var('font', self.__font) + self.__var('xlabel', self.__xlabel) + \
                  self.__var('ylabel', self.__ylabel) + self.__var('title', self.__title) + \
                  self.__var('sizeration', self.__sizeratio) + self.__var('linestyle1', self.__linestyle1) + \
                  self.__var('linestyle2', self.__linestyle2) + self.__var('linestyle3',  self.__linestyle3) + \
                  self.__var('linestyle4', self.__linestyle4) + self.__var('legend1', self.__legend1) + \
                  self.__var('legend2', self.__legend2) + self.__var('legend3', self.__legend3) + \
                  self.__var('legend4', self.__legend4) + self.__var('type', self.__type) + \
                  self.__var('lw', self.__lw) + self.__var('datafile1', full_datafile1) + \
                  self.__var('datafile2', full_datafile2)  + " " + plot_script
        return (command)


if __name__ == "__main__":

    gp = GnuplotScripts(plot_dir='plots', data_dir='data')
    gp.plot_function(filename='test1', datafile='data1.csv')
    gp.plot_2function(filename='test2', datafile='data1.csv')
    gp.plot_3function(filename='test3', datafile='data1.csv')
    gp.plot_2f2data(filename='test2data1', datafile1='data1.csv', datafile2='data2.csv')
    gp.plot_2functionxyxy(filename='testxyxy1', datafile='data1.csv')
    gp.plot_4function(filename='test4', datafile='data1.csv')