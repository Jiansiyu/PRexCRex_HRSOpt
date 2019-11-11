/*
 * HRSOptUID.h
 *
 *  Created on: Nov 7, 2019
 *      Author: newdriver
 */

#ifndef HRSOPTUID_H_
#define HRSOPTUID_H_

#include <TROOT.h>
#include <TVector3.h>

namespace HRSOpt{
const UInt_t NSieveRow = 7;
const UInt_t NSieveCol = 13;

inline const UInt_t GetMomID(const UInt_t uid)  {
	return uid/(NSieveRow *(NSieveCol+1));
}

inline const UInt_t GetRowID(const UInt_t uid){
	auto res=uid %(NSieveRow *(NSieveCol+1));
	const auto Row= res%NSieveRow;
	return Row;
}

inline const UInt_t GetColID(const UInt_t uid){
	auto res=uid %(NSieveRow *(NSieveCol+1));
	const auto Col= res / NSieveRow;
	return Col;
}

inline const TVector3 GetSievePosTCS(const UInt_t Row, const UInt_t Col){

	return TVector3(0.0,0.0,0.0);
}

}



#endif /* HRSOPTUID_H_ */
