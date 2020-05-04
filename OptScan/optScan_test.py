"""

"""
import os
import json
import time
import sys
from collections import OrderedDict
from progress.bar import Bar
from datetime import date
from random import seed
from random import random, randint
from multiprocessing import Pool     # multithread process the single files


class optScanner(object):
    def __init__(self):
        self.OptConfigFname=""
        self.TargetPath=""
        self.CurrentWorkFolder=""
        self.OptTemplateSubFolders=[]
        self.OptSourceFolder=""
        self.optScannerBashScript=""
        self.LoadConfig()
        self.GetSubFolders()

    def LoadConfig(self, runConfigFname="runConfig_test.json"):
        with open(runConfigFname) as runCondigFile:
            self.runConfig_data=json.load(runCondigFile,object_pairs_hook=OrderedDict) # keep the initial order of the database
            self.OptConfigFname=self.runConfig_data["optConfigFname"]
            self.TargetPath=self.runConfig_data["TargetPath"]
            self.OptSourceFolder=self.runConfig_data["OptSourceFolder"]
            self.optScannerBashScript=self.runConfig_data["optScannerBashScript"]
    
    def GetSubFolders(self,topFolder=""):
        if not topFolder:
            topFolder=self.TargetPath
        self.OptTemplateSubFolders=[x[0] for x in os.walk(topFolder)]
    
    def OptimizeSubFolder(self,folderName=""):
        if os.path.exists(folderName):
            optBashCommand="{} {} {}".format(self.optScannerBashScript,self.OptSourceFolder,folderName)
            os.system(optBashCommand)
            # check whether the result have already exist
            #resultFnameCheck="{}/MomemtumDifferenceCanv.jpg".format(folderName)
            #if not os.path.isfile(resultFnameCheck):
            # print(optBashCommand)
        
    def MultiThreadOptimization(self, maxThread=10):
        threadPool=Pool(maxThread)
        threadPool.map(self.OptimizeSubFolder,self.OptTemplateSubFolders)


if __name__ == "__main__":
    test=optScanner()
    test.MultiThreadOptimization()