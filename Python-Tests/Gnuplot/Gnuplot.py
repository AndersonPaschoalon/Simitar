
class Gnuplot:
    def __init__(self):
        self.__plot_dir='.'
        self.__font='Helvetica,10'
        self.__xlabel='xlabel'
        self.__ylabel='ylabel'
        self.__title='title'
        self.__sizeratio='0'
        self.__linestyle1='12'
        self.__linestyle2='1'
        self.__linestyle3='21'
        self.__linestyle4='41'
        self.__legend1='legend1'
        self.__legend2='legend2'
        self.__legend3='legend3'
        self.__legend4='legend4'
        self.__type='lines'

    def plot_config(self, plot_dir='.', font='Helvetica,10', xlabel='xlabel', ylabel='ylabel', title='title', sizeratio='0',
                    linestyle1='12', linestyle2='1', linestyle3='21', linestyle4='41', legend1='legend1',
                    legend2='legend2', legend3='legend3', legend4='legend4', type='lines'):
        self.__plot_dir=plot_dir
        self.__font=font
        self.__xlabel=xlabel
        self.__ylabel=ylabel
        self.__title=title
        self.__sizeratio=sizeratio
        self.__linestyle1=linestyle1
        self.__linestyle2=linestyle2
        self.__linestyle3=linestyle3
        self.__linestyle4=linestyle4
        self.__legend1=legend1
        self.__legend2=legend2
        self.__legend3=legend3
        self.__legend4=legend4
        self.__type=type

    def plot_2f1error(self, filename="", datafile=""):

    def plot_2function(self, filename="", datafile=""):

    def plot_tickbar_label(self, filename="", datafile=""):

    def plot_2f2data(self, filename="", datafile=""):

    def plot_2functionxyxy(self, filename="", datafile=""):

    def plot_ferror(self, filename="", datafile=""):

    def plot_xtickerror(self, filename="", datafile=""):

    def plot_2f2data_log2(self, filename="", datafile=""):

    def plot_3function(self, filename="", datafile=""):

    def plot_function(self, filename="", datafile=""):

    def plot_xtickerror_hline(self, filename="", datafile=""):

    def plot_2f2data_log(self, filename="", datafile=""):

    def plot_4function(self, filename="", datafile=""):

    def plot_tickbar(self, filename="", datafile=""):



    @staticmethod
    def __map_line_style(line_style):
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

