import os

class Cd:
    """Context manager for changing the current working directory"""
    def __init__(self, newPath):
        self.cd(newPath)
        try:
            self.__parent_dir = os.getcwd()
        except:
            print("Error reading local directory")
            exit()


    def cd(self, newPath):
        """Change the working directory"""
        try:
            self.newPath = newPath
            os.chdir(newPath)
        except:
            print("Error accessing directory " + newPath + ".")
            exit()

    def back(self):
        """Returns to the directory where the class was instantiated in the first place"""
        self.cd(self.__parent_dir)

    def pwd(self):
        os.system('pwd')

    def ls(self):
        os.system('ls')

if __name__ == "__main__":

    print('sss')
    Cd = Cd('.')
    Cd.pwd()
    Cd.ls()
    Cd.cd('../..')
    Cd.pwd()
    Cd.ls()
    Cd.back()
    Cd.pwd()
    Cd.ls()
