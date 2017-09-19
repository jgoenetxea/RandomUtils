from os import listdir, rename, path
from os.path import isfile, join

def getAllFileInFolder(folderPath, fileExtension):
    totalExtension = ''
    if fileExtension.startswith('.'):
        totalExtension = fileExtension
    else:
        totalExtension = '.' + fileExtension

    return [f for f in listdir(folderPath) if isfile(join(folderPath, f)) and f.endswith(totalExtension)]


def renameAllInFile(folder, extension):
    fileList = getAllFileInFolder(folder, extension)

    for i, name in enumerate(fileList):
        newname = folder + "/" + str(i) + extension
        rename(folder + "/" + name, newname)

if __name__ == "__main__":
    folder = "/home/VICOMTECH/jgoenetxea/Repositories/git/SwitchTrackingEngineGitHub/build-kanvas_tracker-Desktop_Qt_5_4_2_GCC_64bit-Release/bin/outimages/"

    if len(folder) == 0:
        folder = path.dirname(path.realpath(__file__))

    extension = ".png"
    renameAllInFile(folder, extension)
