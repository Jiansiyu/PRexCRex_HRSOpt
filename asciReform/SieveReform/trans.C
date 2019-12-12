#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
int main(int argc, char* argv[])
{
	FILE *fp1,*fp2;
	//char newname[100];
	//sprintf(newname,"%s.new",argv[1]);
	fp2=fopen("temp.dat","w");
    std::ifstream file(argv[1]);
    std::string line;
    while(std::getline(file, line)){
        unsigned int index=0;
        double d[20];

        std::stringstream linestream(line.c_str());
                              //kx     kth     ky     kphi     kurb_e  kbeamx   kbeamy
        linestream >> index >> d[0] >> d[1] >> d[2] >> d[3] >> d[4] >> d[5] >> d[6];
        
/*        const unsigned int NSieveCol = 13;
        const unsigned int NSieveRow = 7;
        auto  DpID = (unsigned int)index / (NSieveRow * (NSieveCol+1));//starting 0!
	
	unsigned int res=(unsigned int)index % (NSieveRow * (NSieveCol+1));
	 unsigned int Col = res / (NSieveRow); //starting 0!
	 unsigned int Row = res % (NSieveRow); //starting 0!
	 unsigned int FoilID=0;
        
        index=(Col<<16)|(Row);
        std::cout <<"Col:: "<<Col<<"    Shift::"<<(Col<<16)<<"  Combined : "<<((Col<<16)|(Row))<<"   Row:"<<Row<< "  Combined Index:"<<index<<std::endl;*/
        fprintf(fp2,"%d\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\t%1.8e\n",index,d[0],d[1],d[2],d[3],2.17615,d[5]/1000.0,d[6]/1000.0,0.0);
    }
    fclose(fp2);

    std::cout << '\a' << std::flush;
    
    /*
    // encode and decode test for the new
    
    for (unsigned int MomID = 0 ; MomID < 15 ; MomID++){
          
       for (unsigned int FoilID =0 ; FoilID < 15 ; FoilID ++){
       
            for (unsigned int ColID = 0; ColID<15; ColID++){
            
                for (unsigned int RowID=0; RowID<15; RowID++){
                	auto mom=MomID;
                	auto foil=FoilID;
                	auto Col=ColID;
                	auto Row=RowID;
                	
                	unsigned int encoded=(mom<<48)|(foil<<32)|(Col<<16)|(Row);
                	unsigned int temp=encoded;
                	unsigned int decodedRow=(encoded)&(0xffff);
                	unsigned int decodedCol=(encoded>>16)&(0xffff);
                	unsigned int decodedfoil=(encoded>>16)&(0xffff);
                	unsigned int decodedmom=(encoded>>16)&(0xffff);
                	
                	std::cout<< "original ("<< MomID<<", "<< FoilID<<", "<<ColID<<", "<<RowID<<")   encode to :"  <<encoded;
                	std::cout<< "  ==> decode ("<< mom<<", "<< foil<<", "<<Col<<", "<<Row<<")";
                	
                	if ((MomID==mom) && (FoilID==foil) && (ColID==Col) && (RowID==Row)){
                	std::cout<<"   Pass"<<std::endl;
                	
                	} 

                     
                }
            
            }
       }
    }
    */
    return 0;
}
