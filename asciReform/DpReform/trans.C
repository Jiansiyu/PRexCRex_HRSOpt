#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[])
{
	FILE *fp2;
	fp2=fopen("temp.dat","w");
    std::ifstream file(argv[1]);
    std::string line;
    while(std::getline(file, line)){
        int index=0;
        double d[20];

        std::stringstream linestream(line.c_str());
                              //kx     kth     ky     kphi     kurb_e  kbeamx   kbeamy
        linestream >> index >> d[0] >> d[1] >> d[2] >> d[3] >> d[4] >> d[5] >> d[6] >>d[7];
        fprintf(fp2,"%d\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\n",index,d[0],d[1],d[2],d[3],2.175996,d[5]/1000.0,d[6]/1000.0, 0.0);
    }
    fclose(fp2);

    return 0;
}
