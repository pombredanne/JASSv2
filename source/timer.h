/*
	TIMER.H
	-------
	Copyright (c) 2017 Andrew Trotman
	Released under the 2-clause BSD license (See:https://en.wikipedia.org/wiki/BSD_licenses)
*/
/*!
	@fileT Timer methods in nanoseconds and milliseconds.
	@author Andrew Trotman
	@copyright 2017 Andrew Trotman
*/
#pragma once

#include <chrono>
#include <thread>

#include <stdint.h>

#include "asserts.h"

namespace JASS
	{
	class timer
		{
		private:
			/*
				TYPEDEF TIMER::STOP_WATCH
				-------------------------
			*/
			/*!
				@typedef stop_watch
				@brief An instance of a timer
			*/
			typedef std::chrono::time_point<std::chrono::steady_clock> stop_watch;

			/*
				CLASS TIMER::DURATION
				----------------------
			*/
			/*!
				@brief A duration as returned by a stop_watch.
			*/
			class duration
				{
				private:
					std::chrono::nanoseconds took;			///< The time delta that this duration represents.

				public:
					/*
						TIMER::DURATION::DURATION()
						---------------------------
					*/
					/*!
						@brief Convert a std::chrono::nanoseconds into a JASS::timer::duration object.
					*/
					duration(std::chrono::nanoseconds value)
						{
						took = value;
						}

					/*
						TIMER::DURATION::MILLISECONDS()
						-------------------------------
					*/
					/*!
						@brief Return the time-slice as number of milliseconds.
						@return time in miliseconds.
					*/
					size_t milliseconds(void)
						{
						return std::chrono::duration<double, std::milli>(took).count();
						}

					/*
						TIMER::DURATION::MICROSECONDS()
						-------------------------------
					*/
					/*!
						@brief Return the time-slice as number of microseconds.
						@return time in miliseconds.
					*/
					size_t microseconds(void)
						{
						return std::chrono::duration<double, std::micro>(took).count();
						}

					/*
						TIMER::DURATION::NANOSECONDS()
						------------------------------
					*/
					/*!
						@brief Return the time-slice as number of nanoseconds.
						@return time in nanoseconds.
					*/
					size_t nanoseconds(void)
						{
						return std::chrono::duration<double, std::nano>(took).count();
						}
				};

		public:
			/*
				TIMER::START()
				--------------
			*/
			/*!
				@brief Start a stop watfh
				@return A stop watch object that is later passed to timer::stop()
			*/
			static stop_watch start()
				{
				return std::chrono::steady_clock::now();
				}

			/*
				TIMER::STOP()
				-------------
			*/
			/*!
				@brief Return the time on the stop watch.
				@param watch [in] The stop watch to check.
				@return a duration that can be converted into a human-usable unit such as nanoseconds.
			*/
			static duration stop(stop_watch watch)
				{
				return std::chrono::steady_clock::now() - watch;
				}

			/*
				TIMER::UNITTEST()
				-----------------
			*/
			/*!
				@brief Unit test this class
			*/
			static void unittest(void)
				{
				/*
					Time abot 100 milliseconds
				*/
				auto clock = timer::start();
				std::this_thread::sleep_for (std::chrono::milliseconds(100));
				auto took = timer::stop(clock);

				/*
					Get the actual time in different units
				*/
				auto nano = took.nanoseconds();
				auto micro = took.microseconds();
				auto milli = took.milliseconds();

				/*
					Check that the timer took about the same time in nanoseconds as microseconds
				*/
				auto nano_as_micro = nano / 1000;
				JASS_assert(nano_as_micro >= micro - 1 && nano_as_micro <= micro + 1);

				/*
					Check that the timer took about the same time in nanoseconds as milliseconds
				*/
				auto nano_as_milli = nano / 1000'000;
				JASS_assert(nano_as_milli >= milli - 1 && nano_as_milli <= milli + 1);

				/*
					Yay!
				*/
				puts("timer::PASSED\n");
				}

		};
	}