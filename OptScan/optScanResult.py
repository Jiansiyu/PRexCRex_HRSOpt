'''
Used for 
'''
import os
import json
from collections import OrderedDict
from progress.bar import Bar
from datetime import date
from random import seed
from random import random, randint
from multiprocessing import Pool     # multithread process the single files
import statistics

class OptScannerResult(object):
    def __init__(self):
        self.OptConfigFname=""
        self.TargetPath=""
        self.CurrentWorkFolder=""
        self.OptTemplatedOptmizedFolders=[]
        self.OptTemplateSubFolders=[]
        self.OptSourceFolder=""
        self.optScannerBashScript=""
        self.LoadConfig()
        self.GetSubFolders()

    def LoadConfig(self, runConfigFname="runConfig.json"):
        with open(runConfigFname) as runCondigFile:
            self.runConfig_data=json.load(runCondigFile,object_pairs_hook=OrderedDict) # keep the initial order of the database
            self.OptConfigFname=self.runConfig_data["optConfigFname"]
            self.TargetPath=self.runConfig_data["TargetPath"]
            self.OptSourceFolder=self.runConfig_data["OptSourceFolder"]
            self.optScannerBashScript=self.runConfig_data["optScannerBashScript"]
    
    def GetSubFolders(self, topFolder=""):
        #self.TargetPath="/home/newdriver/Research/Eclipse_Workspace/photonSep2019/PRexOpt/OptScan/result1/"
        if not topFolder:
            topFolder=self.TargetPath
        self.OptTemplateSubFolders= [f.path for f in os.scandir(topFolder) if f.is_dir()]
        self.OptTemplatedOptmizedFolders=[item for item in self.OptTemplateSubFolders if os.path.isfile("{}/CheckDp_test_result.txt".format(item))]
        print("Total Processed Template {} / {}\n\n\n".format(len(self.OptTemplatedOptmizedFolders),len(self.OptTemplateSubFolders)))
        #for item in self.OptTemplateSubFolders:
        #    print(item)
    
    def ReadCheckDpResultText(self):
        bar=Bar("Looking for result:: ", max=len(self.OptTemplatedOptmizedFolders))
        #for path in self.OptTemplateSubFolders:
        for path in self.OptTemplatedOptmizedFolders:
            bar.next()
            txtFilename="{}/CheckDp_test_result.txt".format(path)
            if os.path.isfile(txtFilename):
                with open(txtFilename) as txtFileIO:
                    result=json.load(txtFileIO)
                    standDevLib=[]
                    for item in result["DpSeperation"]:
                        if item != '999':
                            #print("{}:{}".format(item,result["DpSeperation"][item]))
                            standDevLib.append(float(result["DpSeperation"][item]))
                    if float(result["DpSeperation"]['0']) > 4.4 and float(result["DpSeperation"]['3']) < 4.5:
                        print("\n{}==>Mean:{}, stdv:{}\n".format(standDevLib,statistics.mean(standDevLib),statistics.stdev(standDevLib)))
        bar.finish()
    def ReadSingleCheckDpResultText(self,txtResultPath=""):
        print("Total Processed Template {} / {}\n\n\n".format(len(self.OptTemplatedOptmizedFolders),0))#,float(self.OptTemplatedOptmizedFolders)/self.OptTemplateSubFolders))
        txtFilename="{}/CheckDp_test_result.txt".format(txtResultPath)
        if os.path.isfile(txtFilename):
            with open(txtFilename) as txtFileIO:
                result=json.load(txtFileIO)
                standDevLib=[]
                for item in result["DpSeperation"]:
                    if item != '999':
                        standDevLib.append(float(result["DpSeperation"][item]))
                if float(result["DpSeperation"]['0']) > 4.4 and float(result["DpSeperation"]['3']) < 4.5:
                    print("{}==>Mean:{}, stdv:{}".format(standDevLib,statistics.mean(standDevLib),statistics.stdev(standDevLib)))

    def ReadCheckDpMultiThread(self,maxThread=5):
        threadPool=Pool(maxThread)
        threadPool.map(self.ReadSingleCheckDpResultText, self.OptTemplateSubFolders)


if __name__ == "__main__":
    test=OptScannerResult()
    #test.ReadCheckDpMultiThread()
    test.ReadCheckDpResultText()
