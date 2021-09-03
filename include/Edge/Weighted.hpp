/***********************************************************/
/***      ______  ____  ______                 _         ***/
/***     / ___\ \/ /\ \/ / ___|_ __ __ _ _ __ | |__	     ***/
/***    | |    \  /  \  / |  _| '__/ _` | '_ \| '_ \	 ***/
/***    | |___ /  \  /  \ |_| | | | (_| | |_) | | | |    ***/
/***     \____/_/\_\/_/\_\____|_|  \__,_| .__/|_| |_|    ***/
/***                                    |_|			     ***/
/***********************************************************/
/***     Header-Only C++ Library for Graph			     ***/
/***	 Representation and Algorithms				     ***/
/***********************************************************/
/***     Author: ZigRazor			     			     ***/
/***	 E-Mail: zigrazor@gmail.com 				     ***/
/***********************************************************/
/***	 Collaboration: ----------- 				     ***/
/***********************************************************/
/***	 License: AGPL v3.0							     ***/
/***********************************************************/

#ifndef __WEIGHTED_H__
#define __WEIGHTED_H__

#pragma once

namespace CXXGRAPH
{
    class Weighted
	{
	private:
		double weight;

	public:
		Weighted();
		Weighted(const double weight);
		virtual ~Weighted() = default;
		double getWeight() const;
		void setWeight(const double weight);
	};

	//inline because the implementation of non-template function in header file
	inline Weighted::Weighted()
	{
		weight = 0.0;
	}

	//inline because the implementation of non-template function in header file
	inline Weighted::Weighted(const double weight)
	{
		this->weight = weight;
	}

	//inline because the implementation of non-template function in header file
	inline double Weighted::getWeight() const
	{
		return weight;
	}

	//inline because the implementation of non-template function in header file
	inline void Weighted::setWeight(const double weight)
	{
		this->weight = weight;
	}

}


#endif // __WEIGHTED_H__