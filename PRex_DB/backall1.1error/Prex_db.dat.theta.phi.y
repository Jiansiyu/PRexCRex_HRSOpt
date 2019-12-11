# -------------------------------------------------------------
# Optimized by Chao Gu @ Mon Nov 18 03:08:32 2019
# Saved to ../PRex_DB/Prex_db.dat.theta.phi.y
# -------------------------------------------------------------
# Optimized by Chao Gu @ Mon Nov 18 03:07:26 2019
# Saved to ../PRex_DB/Prex_db.dat.theta.phi
# -------------------------------------------------------------
# Optimized by Chao Gu @ Mon Nov 18 03:07:09 2019
# Saved to ../PRex_DB/Prex_db.dat.theta
######################### DO NOT REMOVE THIS HEADER ###############################
# LHRS Optics Database
# Author: Ge Jin <gjin@jlab.org>
#
# This is LHRS optics databse for Ay and e'd experiments 1st pass, 2nd pass and 3rd pass data analysis.
# It covers an angle ranging from 12.5 degrees to 17 degrees
#
# t0 time where extracted from data for dvcs run  [7089,7090,7091,7092]
###################################################################################
#
# Sum of progress.
# * Full (1.2 ~ 3.6) GeV and (12.5 ~ 17) degrees region optics,
# * with radiation correction (http://physics.nist.gov/PhysRefData/Star/Text/ESTAR.html -> Collision Loss Only)
# * with spectrometer pointing offsets
# * With Extended Target Correction
# * No  term larger than 1000
# * With Sieve Offsets
# * Finer phi correction with H2 and carbon elastic peaks
# ===========================================
# Theta and phi part is optimized from a 2nd pass and 14.5 degree run 3483 and is tested on a 1st pass 17 degree run 1461
# y_tg part is optimized from a 1st pass and 17 degrees run 1425 and is tested on other configurations ranging in (1.2 ~ 3.6) GeV and (12.5 ~ 17) degrees region 
# Dp part is optimized by 1st pass carbon elastic runs 1454,1456,1461. 
# Dp is tested on 1st pass H2 elastic runs 1396, 1408,1419, and 2nd pass H2 elastic runs 2610,2611,2614,2615
##################################################
#
############ LEFT VDC #########################
[ R.global ]   
0.3327 1 0.0 270.2 0.0 -1.6e-03        VDC Angle, Plane Spacing, Gamma Coefficents  
matrix elements   
t 0 0 0  -1.001135e+00 -3.313373e-01 -4.290819e-02  4.470852e-03  0.000000e+00  0.000000e+00  0.000000e+00  0
y 0 0 0  -8.060915e-03  1.071977e-03  9.019102e-04 -3.239615e-04  0.000000e+00  0.000000e+00  0.000000e+00  0
p 0 0 0  -2.861912e-03 -2.469069e-03  8.427172e-03  2.274635e-03  0.000000e+00  0.000000e+00  0.000000e+00  0
D 0 0 0  -1.584030e-03  6.868670e-02 -6.185880e-03  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  3
D 0 0 1   3.002850e-02 -4.918560e-02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
D 0 0 2  -5.425230e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
D 0 1 0  -7.149190e-03  7.422440e-03  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
D 0 2 0   4.950370e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
D 1 0 0   6.925440e-02  2.562610e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
D 1 0 1   6.148340e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
D 1 0 2  -1.207080e+02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
D 1 1 0  -1.949890e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
D 1 1 1   3.339840e+02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
D 2 0 0  -1.927460e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
T 0 0 0   2.012757e-03  2.527661e-02  1.551232e-02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  3
T 0 0 1   1.033985e-01 -7.295486e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
T 0 0 2  -7.343935e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
T 0 1 0   2.320530e-02 -6.032020e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
T 0 1 1  -1.426108e+01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
T 0 2 0  -5.135726e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
T 1 0 0  -2.311208e+00  7.778718e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
T 1 0 1  -2.273498e+01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
T 1 1 0   2.839137e+01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
T 1 1 1   1.175182e+03  1.895477e+03  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
T 2 0 0  -3.119422e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
P 0 0 0   6.551475e-04  3.066273e-04 -1.046413e-03  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  3
P 0 0 1   4.509652e-01 -5.067574e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
P 0 0 2   4.560448e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
P 0 1 0  -6.002482e-01 -2.815174e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
P 0 1 1  -1.218102e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
P 0 2 0  -4.081901e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
P 1 0 0  -5.842900e-02 -1.392847e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
P 1 0 1   9.363503e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
P 1 1 1  -3.602337e+02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
P 2 0 0   8.728601e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
Y 0 0 0   6.045784e-04  2.541233e-04  5.590846e-05 -2.679816e-03  0.000000e+00  0.000000e+00  0.000000e+00  4
Y 0 0 1  -1.442337e-05  3.042326e-04 -1.907777e-02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  3
Y 0 0 2   1.171041e-02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
Y 0 1 0  -2.459194e-04  6.515828e-04  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
Y 0 1 1  -7.348352e-04 -8.512418e-02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
Y 0 2 0   9.370476e-03  2.014294e-02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
Y 1 1 0   1.138596e-02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
Y 1 1 1   3.177401e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
Y 2 0 0   6.330386e-03  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
Y 2 0 1  -3.700627e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
Y 2 1 0  -2.760681e-02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
Y 1 0 1  -6.018694e-02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
R 0 0 0 0  25.713
R 1 0 0 0  0.1650
R 2 0 0 0 -0.05
R 0 1 0 0 -11.6554
R 0 2 0 0 -9.4951
R 0 0 1 0  0.0
R 0 0 2 0  0.0
R 0 0 0 1  0.0
R 0 0 0 2  0.0
XF 1 0 0 0 0 -2.181E+00
XF 0 1 0 0 0 -1.980E-01
XF 0 0 0 0 1  1.191E+01
TF 1 0 0 0 0 -1.000E-01
TF 0 1 0 0 0 -4.690E-01
TF 0 0 0 0 1  1.967E+00
PF 0 0 1 0 0  3.630E-01
PF 0 0 0 1 0 -0.902E+00
YF 0 0 1 0 0 -5.950E-01
YF 0 0 0 1 0 -1.274E+00