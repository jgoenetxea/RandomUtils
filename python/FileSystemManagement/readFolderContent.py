from os import listdir
from os.path import isfile, join

def getAllFileInFolder(folderPath, fileExtension):
    totalExtension = ''
    if fileExtension.startswith('.'):
        totalExtension = fileExtension
    else:
        totalExtension = '.' + fileExtension

    return [f for f in listdir(folderPath) if isfile(join(folderPath, f)) and f.endswith(totalExtension)]


def getAllFoldersInFolder(folderPath):
    return [f for f in listdir(folderPath) if not isfile(join(folderPath, f))]


if __name__ == '__main__':
    files = getAllFileInFolder('../LoadMatlabFiles/', 'mat')

    for f in files:
        print("File: " + f)
    print("Finished!")
