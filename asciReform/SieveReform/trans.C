#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

inline std::string getFileName(const std::string & s){
	char sep = '/';
#ifdef _WIN32
        sep = '\\';
#endif
	size_t i = s.rfind(sep, s.length());
	if(i != std::string::npos){
	    return(s.substr(i+1, s.length()-i));
	}  
        return("");
}

int main(int argc, char* argv[])
{
	FILE *fp2;
	char newname[200];
	sprintf(newname,"%s_reform",getFileName(argv[1]).c_str());
	
	std::string inputFilename(argv[1]);

	fp2=fopen(newname,"w");
    	std::ifstream file(argv[1]);
    	std::string line;
    	
    	while(std::getline(file, line)){
        	unsigned int index=0;
        	double d[20];

        	std::stringstream linestream(line.c_str());

                              //kx  kth      ky     kphi    kurb_e  kbeamx  kbeamy   kbeam_z
        	linestream >> index >> d[0] >> d[1] >> d[2] >> d[3] >> d[4] >> d[5] >> d[6];
        	
			// macth the runs and fill the average bpm on target 
			if(true){
				//std::cout<<"Working on file"<< inputFilename.c_str()<<std::endl;
				if(inputFilename.find("21626")!=std::string::npos){
					//std::cout<<" run 21626 detected"<<std::endl;
					d[5]=0.690403;
					d[6]=1.45309;
				}

				if(inputFilename.find("21632")!=std::string::npos){
					//std::cout<<" run 21632 detected"<<std::endl;
					d[5]=0.707264;
					d[6]=1.4647;
				}

				if(inputFilename.find("21641")!=std::string::npos){
					//std::cout<<" run 21641 detected"<<std::endl;
					d[5]=0.72701;
					d[6]=1.46784;
				}

				if(inputFilename.find("21642")!=std::string::npos){
					//std::cout<<" run 21642 detected"<<std::endl;
					d[5]=0.711;
					d[6]=1.46993;
				}
			}

			//for test, change to position to the central bpm 
			d[5]=0.0;
			d[6]=0.0;

        									//kx     kth      ky     kphi    kurb_e  kbeamx  kbeamy   kbeam_z
        	fprintf(fp2,"%d\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\n",index,d[0],d[1],d[2],d[3],2.17615,d[5]/1000.0,d[6]/1000.0,0.0);
			//fprintf(fp2,"%d\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\n",index,d[0],d[1],d[2],d[3],0.0,0.0,0.0,0.0);

    	}

    	fclose(fp2);

    	std::cout << '\a' << std::flush;
    	std::cout<<"reformed file saved as :"<<newname<<std::endl;
    	
    	return 0;
}
