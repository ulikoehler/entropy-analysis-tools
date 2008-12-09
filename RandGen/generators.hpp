/* 
 * File:   generators.hpp
 * Author: uli
 *
 * Created on 20. November 2008, 19:30
 */

#ifndef _GENERATORS_HPP
#define	_GENERATORS_HPP

#include "globals.hpp"

using namespace std;
using namespace boost;
using namespace boost::random;

/**
 * Function prototypes
 */
template<class Algorithm> void ProcessBoostAlgorithm(Algorithm* algorithm);
void GenRandBoost();


/**
 * Static global variables used by the generator functions and
 * set by the main function (command line arguments)
 */
static amount_t amount; //Number of random numbers to generate
static ostream* out = &cout;
static string distParam1 = "1";
static string distParam2 = "1";
static string distParam3 = "1";
static string lowerLimit = "0";
static string upperLimit = "1000000";
static ushort distributionNum = 0; //Uniform smallint
static ushort algorithmNum = 0; //MT19937

/**
 * Generates a seeds
 */
template<class T>
T genSeed()
{
    #ifdef __linux__
    static T seed;
    FILE* f = fopen("/dev/urandom", "rb");
    fread(&seed, sizeof(T), 1, f);
    fclose(f);
    return seed;
    #else
    return (T)gettimeofday();
    #endif
}


/**
 * Generates random numbers using the boost algorithms
 */
void GenRandBoost()
{
    ///Generate the seed
    static uint32_t uint32Seed = genSeed<uint32_t>();

    ///Switch distribution
    switch(algorithmNum)
        {
            case 0: ///MT 19937
                {
                    mt19937 mersenne(uint32Seed);
                    ProcessBoostAlgorithm<mt19937>(&mersenne);
                    break;
                }
            case 1: ///Linear congruential
                {
                    minstd_rand minstdrand(uint32Seed);
                    ProcessBoostAlgorithm<minstd_rand>(&minstdrand);
                }
            case 2: ///Additive combine
                {
                    ecuyer1988 addComb(uint32Seed, genSeed<int32_t>());
                    ProcessBoostAlgorithm<ecuyer1988>(&addComb);
                    break;
                }
            case 3: ///Inverse congruential
                {
                    hellekalek1995 invCongr(uint32Seed);
                    ProcessBoostAlgorithm<hellekalek1995>(&invCongr);
                    break;
                }
            case 4: ///Shuffle output
                {
                    kreutzer1986 shOut(uint32Seed);
                    ProcessBoostAlgorithm<kreutzer1986>(&shOut);
                    break;
                }
            case 5: ///Lagged Fibonacci 607
                {
                    lagged_fibonacci607 lf607(uint32Seed);
                    ProcessBoostAlgorithm<lagged_fibonacci607>(&lf607);
                    break;
                }
            default: break;
        }
}

template<class Algorithm>
void ProcessBoostAlgorithm(Algorithm * algorithm) ///Process type of boost algorithm
{
    switch(distributionNum)
        {
            case 0: ///Uniform small int
                {
                    ///Boost Random stuff
                    uniform_smallint<smallint_t> smallInt(lexical_cast<smallint_t>(lowerLimit), lexical_cast<smallint_t>(upperLimit));
                    variate_generator<Algorithm&, uniform_smallint<smallint_t> > generator(*algorithm, smallInt);
                    for(;amount > 0;amount--)
                        {
                            *out << generator() << endl;
                        }
                    break;
                }
            case 1: ///Uniform integer
                {
                    uniform_int<int_t> uniInt(lexical_cast<int_t>(lowerLimit), lexical_cast<int_t>(upperLimit));
                    variate_generator<Algorithm&, uniform_int<int_t> > generator(*algorithm, uniInt);
                    for(;amount > 0;amount--)
                        {
                            *out << generator() << endl;
                        }
                    break;
                }
            case 2: ///Uniform real
                {
                    uniform_real<real_t> uniReal(lexical_cast<real_t>(lowerLimit), lexical_cast<real_t>(upperLimit));
                    variate_generator<Algorithm&, uniform_real<real_t> > generator(*algorithm, uniReal);
                    for(;amount > 0;amount--)
                        {
                            *out << generator() << endl;
                        }
                    break;
                }
            case 3: ///Triangle
                {
                    triangle_distribution<real_t> triangle(lexical_cast<real_t>(distParam1),
                                                            lexical_cast<real_t>(distParam2),
                                                            lexical_cast<real_t>(distParam3));
                    variate_generator<Algorithm&, triangle_distribution<real_t> > generator(*algorithm, triangle);
                    for(;amount > 0;amount--)
                        {
                            *out << generator() << endl;
                        }
                    break;
                }
            case 4: ///Bernoulli
                {
                    /**
                     * Parameter: p
                     */
                    bernoulli_distribution<real_t> bernoulliDist(lexical_cast<real_t>(distParam1));
                    variate_generator<Algorithm&, bernoulli_distribution<real_t> > generator(*algorithm, bernoulliDist);
                    for(;amount > 0;amount--)
                        {
                            *out << generator() << endl;
                        }
                    break;
                }
            case 5: ///Cauchy
                {
                    /**
                     * Parameters: median, sigma
                     */
                    cauchy_distribution<real_t> cauchyDist(lexical_cast<real_t>(distParam1),
                                                            lexical_cast<real_t>(distParam2));
                    variate_generator<Algorithm&, cauchy_distribution<real_t> > generator(*algorithm, cauchyDist);
                    for(;amount > 0;amount--)
                        {
                            *out << generator() << endl;
                        }
                    break;
                }
            case 6: ///Exponential
                {
                    /**
                     * Parameter: lambda
                     */
                    exponential_distribution<real_t> expDist(lexical_cast<real_t>(distParam1));
                    variate_generator<Algorithm&, exponential_distribution<real_t> > generator(*algorithm, expDist);
                    for(;amount > 0;amount--)
                        {
                            *out << generator() << endl;
                        }
                    break;
                }
            case 7: ///Geometric
                {
                    /**
                     * Parameter: p
                     * PDF: p(i) := (1-p) * p^i-1)
                     */
                    geometric_distribution<int_t,real_t> geometricDist(lexical_cast<real_t>(distParam1));
                    variate_generator<Algorithm&, geometric_distribution<int_t,real_t> > generator(*algorithm, geometricDist);
                    for(;amount > 0;amount--)
                        {
                            *out << generator() << endl;
                        }
                    break;
                }
            case 8: ///Normal
                {
                    /**
                     * Parameters: mu, sigma
                     */
                    normal_distribution<real_t> smallInt(lexical_cast<real_t>(distParam1), lexical_cast<real_t>(distParam2));
                    variate_generator<Algorithm&, normal_distribution<real_t> > generator(*algorithm, smallInt);
                    for(;amount > 0;amount--)
                        {
                            *out << generator() << endl;
                        }
                    break;
                }
            case 9: ///Lognormal
                {
                    /**
                     * Parameters: mean, sigma
                     */
                    lognormal_distribution<real_t> lognormalDist(lexical_cast<real_t>(distParam1),
                                                                 lexical_cast<real_t>(distParam2));
                    variate_generator<Algorithm&, lognormal_distribution<real_t> > generator(*algorithm, lognormalDist);
                    for(;amount > 0;amount--)
                        {
                            *out << generator() << endl;
                        }
                    break;
                }
            case 10: ///Uniform on Sphere
                {
                    uniform_on_sphere<real_t> uniOnSphere(lexical_cast<real_t>(distParam1)); ///dim
                    variate_generator<Algorithm&, uniform_on_sphere<real_t> > generator(*algorithm, uniOnSphere);
                    for(;amount > 0;amount--)
                        {
                            BOOST_FOREACH(real_t r, generator())
                            {
                                *out << r << endl;
                            }
                        }
                    break;
                }
            default: break;
        }
}

#endif	/* _GENERATORS_HPP */

