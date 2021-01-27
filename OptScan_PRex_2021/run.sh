source venv/bin/activate
# rm /home/newdriver/Storage/Research/Eclipse_Workspace/photonSep2019/PRexOpt/OptScan_Prex/PRex_LHRS_result/LHRS_scan_phi_allrun_rescan/* -r
# rm /home/newdriver/Storage/Research/Eclipse_Workspace/photonSep2019/PRexOpt/OptScan_Prex/PRex_LHRS_result/LHRS_scan_theta_allrun_rescan/* -r
workDir="/home/newdriver/Storage/Research/Eclipse_Workspace/photonSep2019/PRexOpt/OptScan_PRex_2021/result/LHRS/20210126_scan_theta/*"
echo "Will delet all file in folder : ${workDir}"
read -p "Are you sure re-run Opt? " -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
    rm ${workDir} -r
else
    exit -1
fi
python3 optScanGenerator.py
python3 optScan.py
python3 optScanResult.py
