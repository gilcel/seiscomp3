/***************************************************************************
 *   Copyright (C) 2013 by gempa GmbH
 *
 *   Author: Jan Becker
 *   Email: jabe@gempa.de $
 *
 ***************************************************************************/


#ifndef __SEISCOMP_FDSNXML_RESPONSESTAGE_H__
#define __SEISCOMP_FDSNXML_RESPONSESTAGE_H__


#include <fdsnxml/metadata.h>
#include <string>
#include <fdsnxml/decimation.h>
#include <fdsnxml/polesandzeros.h>
#include <fdsnxml/polynomial.h>
#include <fdsnxml/fir.h>
#include <fdsnxml/coefficients.h>
#include <fdsnxml/responselist.h>
#include <fdsnxml/gain.h>
#include <seiscomp3/core/baseobject.h>
#include <seiscomp3/core/exceptions.h>


namespace Seiscomp {
namespace FDSNXML {


DEFINE_SMARTPOINTER(ResponseStage);


/**
 * \brief This complex type represents channel response and covers SEED
 * \brief blockettes 53 to 56.
 */
class ResponseStage : public Core::BaseObject {
	DECLARE_CASTS(ResponseStage);
	DECLARE_RTTI;
	DECLARE_METAOBJECT_DERIVED;

	// ------------------------------------------------------------------
	//  Xstruction
	// ------------------------------------------------------------------
	public:
		//! Constructor
		ResponseStage();

		//! Copy constructor
		ResponseStage(const ResponseStage &other);

		//! Destructor
		~ResponseStage();


	// ------------------------------------------------------------------
	//  Operators
	// ------------------------------------------------------------------
	public:
		//! Copies the metadata of other to this
		ResponseStage& operator=(const ResponseStage &other);
		bool operator==(const ResponseStage &other) const;


	// ------------------------------------------------------------------
	//  Setters/Getters
	// ------------------------------------------------------------------
	public:
		//! XML tag: PolesZeros
		void setPolesZeros(const OPT(PolesAndZeros)& polesZeros);
		PolesAndZeros& polesZeros();
		const PolesAndZeros& polesZeros() const;

		//! XML tag: Coefficients
		void setCoefficients(const OPT(Coefficients)& coefficients);
		Coefficients& coefficients();
		const Coefficients& coefficients() const;

		//! XML tag: ResponseList
		void setResponseList(const OPT(ResponseList)& responseList);
		ResponseList& responseList();
		const ResponseList& responseList() const;

		//! XML tag: FIR
		void setFIR(const OPT(FIR)& fIR);
		FIR& fIR();
		const FIR& fIR() const;

		//! XML tag: Polynomial
		void setPolynomial(const OPT(Polynomial)& polynomial);
		Polynomial& polynomial();
		const Polynomial& polynomial() const;

		//! XML tag: Decimation
		void setDecimation(const OPT(Decimation)& decimation);
		Decimation& decimation();
		const Decimation& decimation() const;

		//! StageSensitivity is the gain at the stage of the encapsulating
		//! response element and corresponds to SEED blockette 58. In the SEED
		//! convention, stage 0 gain represents the overall sensitivity of the
		//! channel. In this schema, stage 0 gains are allowed but are considered
		//! deprecated. Overall sensitivity should be specified in the
		//! InstrumentSensitivity element.
		//! XML tag: StageGain
		void setStageGain(const OPT(Gain)& stageGain);
		Gain& stageGain();
		const Gain& stageGain() const;

		//! Stage sequence number. This is used in all the response SEED
		//! blockettes.
		//! XML tag: number
		void setNumber(int number);
		int number() const;

		//! Same meaning as Equipment:resourceId.
		//! XML tag: resourceId
		void setResourceId(const std::string& resourceId);
		const std::string& resourceId() const;


	// ------------------------------------------------------------------
	//  Implementation
	// ------------------------------------------------------------------
	private:
		// Attributes
		OPT(PolesAndZeros) _polesZeros;
		OPT(Coefficients) _coefficients;
		OPT(ResponseList) _responseList;
		OPT(FIR) _fIR;
		OPT(Polynomial) _polynomial;
		OPT(Decimation) _decimation;
		OPT(Gain) _stageGain;
		int _number;
		std::string _resourceId;
};


}
}


#endif
