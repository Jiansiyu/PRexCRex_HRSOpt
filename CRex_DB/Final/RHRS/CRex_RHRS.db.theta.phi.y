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
D 0 0 0  -3.447207e-03  7.725990e-02  6.485666e-04  5.635940e-02  3.774778e-02 -9.561398e-01  0.000000e+00  3
D 1 0 0   5.453113e-02  4.471653e-01 -1.304988e-01 -3.867371e-01  0.000000e+00  0.000000e+00  0.000000e+00  4
D 2 0 0  -1.579654e+00  8.136548e+00 -2.306598e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  3
D 0 0 2   1.966814e+00 -1.793942e+00 -1.936484e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  3
D 0 2 0   4.608375e-01 -4.433838e+00 -1.758678e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  3
D 0 1 1   1.591565e+00 -5.258629e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
D 1 0 2   3.383647e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
D 1 1 1   3.474980e+02  2.668840e+02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
D 2 0 2  -6.273270e+03  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
D 2 1 1   5.941469e+02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
D 3 0 0  -8.280174e+01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
D 1 2 0   3.354449e+02  2.938388e+02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
D 4 0 0   3.069547e+03  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
D 2 2 0   3.338976e+03  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
D 0 1 3   7.241062e+02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
T 0 0 0   2.557255e-03  1.763617e-02  1.250361e-02 -1.366731e-02 -8.579040e-02  0.000000e+00  0.000000e+00  5
T 0 0 1   2.043271e-01 -4.803750e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
T 0 0 2  -1.106559e+01  1.179254e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
T 0 1 0   9.281606e-02 -5.746120e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
T 0 1 1  -1.893785e+01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
T 0 2 0  -6.788597e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
T 1 0 0  -2.016623e+00  3.445329e-01 -1.169225e-01  1.376611e+00  4.596826e-01  0.000000e+00  0.000000e+00  5
T 1 0 1  -2.997607e+00  1.799937e+01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
T 1 1 0   2.979994e+01  7.450403e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
T 1 1 1   5.230902e+02 -3.679830e+02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
T 2 0 0  -3.658573e+00  5.537375e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
P 0 0 0   1.985466e-04 -1.813966e-03  1.217443e-03 -6.744760e-03  0.000000e+00  0.000000e+00  0.000000e+00  4
P 0 0 1   3.260615e-01 -6.080356e-02  6.322304e-02 -2.177119e-01  0.000000e+00  0.000000e+00  0.000000e+00  4
P 0 0 2   5.044174e+00  1.562150e+00 -6.579352e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  3
P 0 1 0  -5.326127e-01 -4.743152e-02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
P 0 1 1   3.521639e+00  2.617914e+00  3.079655e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  3
P 0 2 0  -2.111528e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
P 1 0 0  -5.077009e-02 -2.094173e-02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
P 1 0 1   7.720937e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
P 1 1 1  -1.038787e+02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
P 2 0 0   4.154068e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
Y 0 0 0   7.076572e-04  1.573352e-05 -4.503106e-06  3.119461e-05  0.000000e+00  0.000000e+00  0.000000e+00  4
Y 0 0 1  -2.706198e-05  1.072574e-04 -9.892428e-06  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  3
Y 0 0 2  -3.573473e-03  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
Y 0 1 0  -7.959301e-05  2.910901e-04  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
Y 0 1 1   5.025844e-04 -8.558158e-03  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
Y 0 2 0  -2.140650e-03  2.555427e-02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  2
Y 1 1 0  -1.924092e-03  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
Y 1 1 1   4.349934e-02  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
Y 2 0 0  -2.253768e-03  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
Y 2 0 1  -1.164716e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
Y 2 1 0  -1.515663e-01  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
Y 1 0 1   5.305098e-03  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  0.000000e+00  1
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