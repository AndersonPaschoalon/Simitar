import os
import time


class Terminal(object):
    @staticmethod
    def print_color(color, data):
        color_def = {
            # Reset
            "reset": "\033[0m",  # Text Reset
            # Regular Colors
            "black": "\033[0;30m",  # Black
            "red": "\033[0;31m",  # Red
            "green": "\033[0;32m",  # Green
            "yellow": "\033[0;33m",  # Yellow
            "blue": "\033[0;34m",  # Blue
            "purple": "\033[0;35m",  # Purple
            "cyan": "\033[0;36m",  # Cyan
            "white": "\033[0;37m"  # White
        }
        color_code = color_def.get("reset") if color_def.get(color) == "" else color_def.get(color)
        print(color_code + data + color_def.get("reset"))

    @staticmethod
    def requires_sudo():
        if os.geteuid() != 0:
            exit("You need to have root privileges to run this script.\n" +
                 "Please try again, this time using 'sudo'. Exiting.")

    @staticmethod
    def wait(sec):
        Terminal.print_color(color="blue", data="sleeping for "+str(sec) + "s ...")
        time.sleep(sec)

    @staticmethod
    def command(cmd, color=''):
        if color == '':
            print(cmd)
        else:
            Terminal.print_color(color, cmd)
        os.system(cmd)

    _tab = "    "
    _H1 = "###############################################################################"
    _h1 = "# "
    _H2 = "*******************************************************************************"
    _h2 = "* "
    _H3 = "-------------------------------------------------------------------------------"
    _h3 = "- "
    _h4 = "####"
    _h5 = "****"
    _h6 = "----"

    @staticmethod
    def _print_h(title="", type="h1", color="purple"):
        if type == "h1":
            H = Terminal._H1
            h = Terminal._h1
            seq = 1
        elif type == "h2":
            H = Terminal._H2
            h = Terminal._h2
            seq = 2
        elif type == "h3":
            H = Terminal._H3
            h = Terminal._h3
            seq = 3
        elif type == "h4":
            h = Terminal._h4
            seq = 4
        elif type == "h5":
            seq = 5
            h = Terminal._h5
        elif type == "h6":
            seq = 6
            h = Terminal._h6
        else:
            seq = 1
            h = Terminal._h1
            H = Terminal._H1
        if seq <= 3:
            Terminal.print_color(data="", color=color)
            Terminal.print_color(data=H, color=color)
            Terminal.print_color(data=h+title, color=color)
            Terminal.print_color(data=H, color=color)
        else:
            header = h +  "  " + title + "  " + h
            Terminal.print_color(data="", color=color)
            Terminal.print_color(data=header, color=color)
            Terminal.print_color(data="", color=color)

    @staticmethod
    def print_h1(title="", color="purple"):
        Terminal._print_h(title, "h1", color)

    @staticmethod
    def print_h2(title="", color="purple"):
        Terminal._print_h(title, "h2", color)

    @staticmethod
    def print_h3(title="", color="purple"):
        Terminal._print_h(title, "h3", color)

    @staticmethod
    def print_h4(title="", color="purple"):
        Terminal._print_h(title, "h4", color)

    @staticmethod
    def print_h5(title="", color="purple"):
        Terminal._print_h(title, "h5", color)

    @staticmethod
    def print_h6(title="", color="purple"):
        Terminal._print_h(title, "h6", color)

    @staticmethod
    def wait(sec):
        Terminal.print_color(color="blue", data="sleeping for "+str(sec) + "s ...")
        time.sleep(sec)

    @staticmethod
    def user_confirmation(msg=""):
        while True:
            user_input = str(raw_input(msg + '[y/n]')).lower().strip().replace(" ", "")
            #user_input = str(input(msg + '[y/n]')).lower().strip().replace(" ", "")
            if user_input == "y" or user_input == "yes":
                break
            elif user_input == "n" or user_input == "no" or user_input == "not":
                exit(0)
            else:
                print("Invalid option:"+user_input)

    @staticmethod
    def print_table(col_info, matrix_values):
        values = matrix_values
        col_names = [''] * len(col_info)
        col_max_len = [0] * len(col_info)
        col_title_len = [0] * len(col_info)
        col_sizes = [0] * len(col_info)
        i = 0
        while i < len(col_names):
            col_names[i] = col_info[i]
            i += 1
        for i in range(len(col_title_len)):
            col_title_len[i] = len(str(col_names[i]))
        # retrieve all data
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

    @staticmethod
    def print_items(list_items, bullet="*"):
        for i in range(0, len(list_items)):
            print(Terminal._tab + bullet + " " + list_items[i])

    @staticmethod
    def print_enum(list_items):
        for i in range(0, len(list_items)):
            print(Terminal._tab + str(i) + ". " + list_items[i])





"""
class Terminal(object):
    @staticmethod
    def print_color(color, data):
        color_def = {
            # Reset
            "reset": "\033[0m",  # Text Reset
            # Regular Colors
            "black": "\033[0;30m",  # Black
            "red": "\033[0;31m",  # Red
            "green": "\033[0;32m",  # Green
            "yellow": "\033[0;33m",  # Yellow
            "blue": "\033[0;34m",  # Blue
            "purple": "\033[0;35m",  # Purple
            "cyan": "\033[0;36m",  # Cyan
            "white": "\033[0;37m"  # White
        }
        color_code = color_def.get("reset") if color_def.get(color) == "" else color_def.get(color)
        print(color_code + data + color_def.get("reset"))

    @staticmethod
    def print_h1(title, color=''):
        if color == '':
            print('  ')
            print('  ###############################################################################')
            print('  # ' + title)
            print('  ###############################################################################')
        else:
            print('')
            Terminal.print_color(color, '  ###############################################################################')
            Terminal.print_color(color, '  # ' + title)
            Terminal.print_color(color, '  ###############################################################################')

    @staticmethod
    def requires_sudo():
        if os.geteuid() != 0:
            exit("You need to have root privileges to run this script.\n" +
                 "Please try again, this time using 'sudo'. Exiting.")

    @staticmethod
    def command(cmd, color=''):
        if color == '':
            print(cmd)
        else:
            Terminal.print_color(color, cmd)
        os.system(cmd)

    @staticmethod
    def wait(sec):
        Terminal.print_color(color="blue", data="sleeping for "+str(sec) + "s ...")
        time.sleep(sec)

    @staticmethod
    def user_confirmation(msg=""):
        while True:
            user_input = str(raw_input(msg + '[y/n]')).lower().strip().replace(" ", "")
            if user_input == "y" or user_input == "yes":
                break
            elif user_input == "n" or user_input == "no" or user_input == "not":
                exit(0)
            else:
                print("Invalid option:"+user_input)

"""
