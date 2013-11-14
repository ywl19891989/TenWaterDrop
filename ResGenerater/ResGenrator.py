# coding: utf-8
'''
Created on 2013-9-26

@author: Hali
'''
import os
import sys
import argparse

class ResGenerater:

    staticNum = 0;
    projectName = "ResGenerater"
    rootdir = os.path.abspath(".")
    outputDir = os.path.abspath("./output/")
    templateDir = os.path.abspath(".") + os.sep
    
    print "templateDir: " + templateDir
    
    headName = "ResourceName.h"
    cppName = "ResourceName.cpp"
    
    templateHead = templateDir + headName
    templateCpp = templateDir + cppName

    outCpp = ""
    outHead = ""

    headText = ""
    cppText = ""
    
    def getVarName(self, fileName):
        extName = os.path.splitext(fileName)[1][1:]
        name = os.path.splitext(fileName)[0]
#         print "name: " + name + ", extName: " + extName
        if extName == "png":
            return self.replaceUnAccetChar(name)
        else :
            return self.replaceUnAccetChar(fileName)
    
    def canAcceptName(self, name):
        return name != ".DS_Store" and str(name)[0] != "."
    
    def replaceUnAccetChar(self, text):
        tempText = text.replace(".", "_")
        tempText = tempText.replace("-", "_")
        tempText = tempText.replace("@", "_")
        return tempText
    
    def printoutputDir(self, outtext):
#         print outtext
        self.outHead = self.outHead + outtext + "\n"
        
    def printoutputPath(self, outtext):
#         print outtext
        self.outCpp = self.outCpp + outtext + "\n"
    
    def addTab(self):
        self.staticNum = self.staticNum + 1

    def subTab(self):
        self.staticNum = self.staticNum - 1
    
    def reset(self, inputDir, inputProjectName, outputDir, templateDir):
        self.staticNum = 0;
        self.rootdir = os.path.abspath(inputDir)
        self.projectName = inputProjectName
        self.outputDir = os.path.abspath(outputDir) + os.sep;
        self.templateDir = os.path.abspath(templateDir) + os.sep;
        self.templateHead = self.templateDir + self.headName
        self.templateCpp = self.templateDir + self.cppName
        inputFile = open(self.templateHead, "r")
        self.headText = inputFile.read()
        inputFile.close();
        # print headText
        inputFile = open(self.templateCpp, "r")
        self.cppText = inputFile.read()
        inputFile.close();
        # print cppText
    
    def getTab(self, tabNum):
        tabstr = ""
        i = 0
        while i < tabNum:
            i+=1
            tabstr += "    "
        return tabstr
    
    def getSelfTab(self):
        return self.getTab(self.staticNum)
    
    def printDir(self, inputDir):
        dirName = os.path.basename(inputDir)
        if str(dirName)[0] == "." :
            return
        self.printoutputDir(" ")
        self.printoutputDir(self.getSelfTab() + "namespace " + dirName + " {")
        self.addTab()
        ls = os.listdir(inputDir)
        for l in ls:
            temp = os.path.join(inputDir, l)      
            if(os.path.isdir(temp)):
                self.printDir(temp)
            elif self.canAcceptName(str(l)):
                varName = self.getVarName(l)
                self.printoutputDir(self.getSelfTab() + "extern const char * " + varName + ";")
        self.subTab()
        self.printoutputDir(self.getSelfTab() + "}")
        
    def printPath(self, inputDir):
        dirName = os.path.basename(inputDir)
        if str(dirName)[0] == "." :
            return
        self.printoutputPath(" ")
        self.printoutputPath(self.getSelfTab() + "namespace " + dirName + " {")
        self.addTab()
        ls = os.listdir(inputDir)
        for l in ls:
            temp = os.path.join(inputDir, l)      
            if(os.path.isdir(temp)):
                self.printPath(temp)
            elif self.canAcceptName(str(l)):
                varName = self.getVarName(l)
                varPath = temp.replace(self.rootdir + os.sep, "");
                varPath = varPath.replace("\\", "/")
                self.printoutputPath(self.getSelfTab() + "const char * " + varName + " = \"" + varPath + "\";")
        self.subTab()
        self.printoutputPath(self.getSelfTab() + "}")
        
    def runScan(self):
        print "rootDir: " + self.rootdir
        print "projectName: " + self.projectName
        print "-----------------------------------------------------------------"
        print " printDir:"
        print "-----------------------------------------------------------------"
        self.printDir(self.rootdir)
        print "-----------------------------------------------------------------"
        print " printPath:"
        print "-----------------------------------------------------------------"
        self.printPath(self.rootdir)
#         print "-----------------------------------------------------------------"
#         print " outHead:"
#         print "-----------------------------------------------------------------"
#         print self.outHead
#         print "-----------------------------------------------------------------"
#         print " outCpp"
#         print "-----------------------------------------------------------------"
#         print self.outCpp
        # output header file
        tempText = self.headText % (self.projectName, self.projectName, self.projectName, self.outHead, self.projectName)
        outFile = open(self.outputDir + self.headName, "w")
        outFile.write(tempText);
        outFile.flush()
        outFile.close();
        # output cpp file
        tempText = self.cppText % (self.projectName, self.outCpp)
        outFile = open(self.outputDir + self.cppName, "w")
        outFile.write(tempText);
        outFile.flush()
        outFile.close();
        
if __name__ == "__main__":
    t = ResGenerater()
    parser = argparse.ArgumentParser(description="This is a description of %(prog)s", epilog="This is a epilog of %(prog)s", prefix_chars="-+", fromfile_prefix_chars="@", formatter_class=argparse.ArgumentDefaultsHelpFormatter)  
    parser.add_argument("-i", "--input", help="the input dir need generate Res", dest = "inputDir", default = ".")  
    parser.add_argument("-o", "--output", help="the output dir to save output file", dest = "outputDir", default = "./output/")  
    parser.add_argument("-p", "--project", help="input the project name", dest = "projectName", default = "ResGenerater")  
    parser.add_argument("-t", "--template", help="input the template file dir", dest = "templateDir", default = ".")  
    args = parser.parse_args(sys.argv[1:])
    t.reset(args.inputDir, args.projectName, args.outputDir, args.templateDir)
    t.runScan()
