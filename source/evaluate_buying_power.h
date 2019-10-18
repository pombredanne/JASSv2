/*
	EVALUATE_BUYING_POWER.H
	-----------------------
	Copyright (c) 2019 Andrew Trotman
	Released under the 2-clause BSD license (See:https://en.wikipedia.org/wiki/BSD_licenses)
*/
/*!
	@file
	@brief Compute the buying power (bp) of the results list
	@author Andrew Trotman
	@copyright 2019 Andrew Trotman
*/
#pragma once

#include "evaluate.h"

namespace JASS
	{
	/*
		CLASS EVALUATE_BUYING_POWER
		---------------------------
	*/
	/*!
		@brief Compute the buying power (bp) given a results (where bp=cost_I/sum(cost_i) for I is the
		lowestpriced relevant item and i is all items in the results list up to the cheapest relevant item).
	*/
	class evaluate_buying_power : evaluate
		{
		private:
			evaluate &prices;						///< Each item has a price regardless of the query being processed
			evaluate &assessments;				///< The assessments, which items are relevant to which queries (and at what price)

		public:
			/*
				EVALUATE_BUYING_POWER::EVALUATE_BUYING_POWER()
				----------------------------------------------
			*/
			/*!
				@brief Constructor.
				@details  As all possible prices are valid prices (0 == "free", -1 == "I'll pay for you to take it away), the
				assessments are split into two seperate parts. Ther prices of the items and the relevance of the items.  Each
				of these two are stored in trec_eval format:

			 	1 0 AP880212-0161 1

			 	where the first column is the query id, the second is ignored, the third is the document ID, and the fourth is the
			 	relevance.  The prices use a query id of "PRICE" and the relevance coulmn is the price of the item.  The assessments
			 	are the usual trec_eval format where a relevance of 1 means releance, but a relefvance of 0 is not-relevant.

				@param prices [in] An assessments object which holds the price of each item
				@param assessments [in] A pre-constructed assessments object.
			*/
			evaluate_buying_power(evaluate &prices, evaluate &assessments) :
				prices(prices),
				assessments(assessments)
				{
				}

			/*
				EVALUATE_BUYING_POWER::COMPUTE()
				--------------------------------
			*/
			/*!
				@brief Compute the buying power as  bp=cost_I/sum(cost_i) for I is the
				lowestpriced relevant item and i is all items in the results list up to the cheapest relevant item
				
				@details The Buying Power (bp) of an item is computed as the price of the cheapest relevant item (the optimal
				price) divided by the total spending up-to and including the first relevant item in the results list.  A score
				of 1 means that the lowest priced item is at the top of the results list.  A score of 0 occurs if there are
				no relevant items in the results list.  A score of 1 is also achieved if there are no relevant items for the query.
				This metric is akin to Mean Reciprocal Rank.

				Although prices are assumed to be in dollars and (2 is $2.00, 2.2 = $2.20), the implementation is unit agnostic
				and therefore prices might be in cents (or pence, etc.) or even units other than financial (such as time).

				@pram query_id [in] The ID of the query being evaluated.
				@param results_list [in] The results list to measure.
				@param depth [in] How far down the results list to look.
				@return The buying power of this results list for this query.
			*/
			virtual double compute(const std::string &query_id, const std::vector<std::string> &results_list, size_t depth = 1000);

			/*
				EVALUATE_BUYING_POWER::UNITTEST()
				---------------------------------
			*/
			/*!
				@brief Unit test this class
			*/
			static void unittest(void);

		};
	}
