# coding: utf-8
'''
Created on 2013-9-26

@author: Hali
'''
import os

rootdir = "E:/workspace/Cocos2dDemo/Cocos2dDemo/Resources"  
rootdirReplace = "E:/workspace/Cocos2dDemo/Cocos2dDemo/Resources/"  
staticNum = 0;

def getTab(tabNum):
    tabstr = ""
    i = 0
    while i < tabNum:
        i+=1
        tabstr += "    "
    return tabstr

def printDir(inputDir):
    global staticNum
    print " "
    print getTab(staticNum) + "namespace " + os.path.basename(inputDir) + " {"
    staticNum = staticNum + 1
    ls = os.listdir(inputDir)
    for l in ls:
        temp = os.path.join(inputDir, l)      
        if(os.path.isdir(temp)):
            printDir(temp)
        else:
            varName = l.replace(".", "_")
            print getTab(staticNum) + "extern const char * " + varName + ";"
    staticNum = staticNum - 1 
    print getTab(staticNum) + "}"
    
def printPath(inputDir):
    global staticNum
    print " "
    print getTab(staticNum) + "namespace " + os.path.basename(inputDir) + " {"
    staticNum = staticNum + 1
    ls = os.listdir(inputDir)
    for l in ls:
        temp = os.path.join(inputDir, l)      
        if(os.path.isdir(temp)):
            printPath(temp)
        else:
            varName = l.replace(".", "_")
            varPath = temp.replace(rootdir + "\\", "");
            varPath = varPath.replace("\\", "/")
            print getTab(staticNum) + "const char * " + varName + " = \"" + varPath + "\";";
    staticNum = staticNum - 1 
    print getTab(staticNum) + "}"
    
printDir(rootdir)

print " "
print "-----------------------------------------------------------------"
print " "

printPath(rootdir)