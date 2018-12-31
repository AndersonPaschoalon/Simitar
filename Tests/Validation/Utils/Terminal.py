import  os


class Terminal(object):
    @staticmethod
    def print_color(color, data, end='\n'):
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
        print(color_code + data + color_def.get("reset"), end=end)

    @staticmethod
    def print_header(title, color=''):
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
    def command(cmd, color=''):
        if color == '':
            print(cmd)
        else:
            Terminal.print_color(color, cmd)
        os.system(cmd)
