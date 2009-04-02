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

/**
 * Function prototypes
 */
template<class Algorithm> void ProcessBoostAlgorithm (Algorithm* algorithm);
void GenRandBoost ();


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
static Distribution distributionNum; //Uniform smallint
static Generator algorithmNum; //MT19937

/**
 * Generates a seeds
 * Should be used with T = uint32_t or T = uint_64t on non-Linux systems only
 */
template<class T>
T
genSeed ()
{
    #ifdef __linux__
    static T seed;
    FILE* f = fopen ("/dev/urandom", "rb");
    fread (&seed, sizeof (T), 1, f);
    fclose (f);
    return seed;
    #else
    return (T) gettimeofday ();
    #endif
}

/**
 * Generates random numbers using the boost algorithms
 */
void
GenRandBoost ()
{
    ///Generate the seed
    static uint32_t uint32Seed = genSeed<uint32_t > ();

    ///Switch distribution
    switch (algorithmNum)
        {
        case MT19937:
            {
                mt19937 mersenne (uint32Seed);
                ProcessBoostAlgorithm<mt19937 > (&mersenne);
                break;
            }
        case MT11213b:
            {
                mt11213b mersenne (uint32Seed);
                ProcessBoostAlgorithm<mt11213b > (&mersenne);
                break;
            }
        case LinearCongruential:
            {
                minstd_rand minstdrand (uint32Seed);
                ProcessBoostAlgorithm<minstd_rand > (&minstdrand);
            }
        case Ecuyer1988: ///Additive combine
            {
                ecuyer1988 addComb (uint32Seed, genSeed<int32_t > ());
                ProcessBoostAlgorithm<ecuyer1988 > (&addComb);
                break;
            }
        case Hellekalek1995: ///Inverse congruential
            {
                hellekalek1995 invCongr (uint32Seed);
                ProcessBoostAlgorithm<hellekalek1995 > (&invCongr);
                break;
            }
        case Kreutzer1986: ///Shuffle output
            {
                kreutzer1986 shOut (uint32Seed);
                ProcessBoostAlgorithm<kreutzer1986 > (&shOut);
                break;
            }
        case LaggedFibonacci607:
            {
                lagged_fibonacci607 fibonacci (uint32Seed);
                ProcessBoostAlgorithm<lagged_fibonacci607 > (&fibonacci);
                break;
            }
        case LaggedFibonacci1279:
            {
                lagged_fibonacci1279 fibonacci (uint32Seed);
                ProcessBoostAlgorithm<lagged_fibonacci1279 > (&fibonacci);
                break;
            }
            case LaggedFibonacci2281:
            {
                lagged_fibonacci2281 fibonacci (uint32Seed);
                ProcessBoostAlgorithm<lagged_fibonacci2281 > (&fibonacci);
                break;
            }
            case LaggedFibonacci3217:
            {
                lagged_fibonacci3217 fibonacci (uint32Seed);
                ProcessBoostAlgorithm<lagged_fibonacci3217 > (&fibonacci);
                break;
            }
            case LaggedFibonacci4423:
            {
                lagged_fibonacci4423 fibonacci (uint32Seed);
                ProcessBoostAlgorithm<lagged_fibonacci4423 > (&fibonacci);
                break;
            }
            case LaggedFibonacci9689:
            {
                lagged_fibonacci9689 fibonacci (uint32Seed);
                ProcessBoostAlgorithm<lagged_fibonacci9689 > (&fibonacci);
                break;
            }
            case LaggedFibonacci19937:
            {
                lagged_fibonacci19937 fibonacci (uint32Seed);
                ProcessBoostAlgorithm<lagged_fibonacci19937 > (&fibonacci);
                break;
            }
            case LaggedFibonacci23209:
            {
                lagged_fibonacci23209 fibonacci (uint32Seed);
                ProcessBoostAlgorithm<lagged_fibonacci23209 > (&fibonacci);
                break;
            }
            case LaggedFibonacci44497:
            {
                lagged_fibonacci44497 fibonacci (uint32Seed);
                ProcessBoostAlgorithm<lagged_fibonacci44497 > (&fibonacci);
                break;
            }
        default: break;
        }
}

template<class Algorithm>
void
ProcessBoostAlgorithm (Algorithm * algorithm) ///Process type of boost algorithm
{
    switch (distributionNum)
        {
        case UniformSmallInteger: ///Uniform small int
            {
                ///Boost Random stuff
                uniform_smallint<smallint_t> smallInt (lexical_cast<smallint_t > (lowerLimit), lexical_cast<smallint_t > (upperLimit));
                variate_generator<Algorithm&, uniform_smallint<smallint_t> > generator (*algorithm, smallInt);
                for (; amount > 0; amount--)
                    {
                        *out << generator () << endl;
                    }
                break;
            }
        case UniformInteger: ///Uniform integer
            {
                uniform_int<int_t> uniInt (lexical_cast<int_t > (lowerLimit), lexical_cast<int_t > (upperLimit));
                variate_generator<Algorithm&, uniform_int<int_t> > generator (*algorithm, uniInt);
                for (; amount > 0; amount--)
                    {
                        *out << generator () << endl;
                    }
                break;
            }
        case UniformReal: ///Uniform real
            {
                uniform_real<real_t> uniReal (lexical_cast<real_t > (lowerLimit), lexical_cast<real_t > (upperLimit));
                variate_generator<Algorithm&, uniform_real<real_t> > generator (*algorithm, uniReal);
                for (; amount > 0; amount--)
                    {
                        *out << generator () << endl;
                    }
                break;
            }
        case Triangle: ///Triangle
            {
                triangle_distribution<real_t> triangle (lexical_cast<real_t > (distParam1),
                                                        lexical_cast<real_t > (distParam2),
                                                        lexical_cast<real_t > (distParam3));
                variate_generator<Algorithm&, triangle_distribution<real_t> > generator (*algorithm, triangle);
                for (; amount > 0; amount--)
                    {
                        *out << generator () << endl;
                    }
                break;
            }
        case Bernoulli: ///Bernoulli
            {
                /**
                 * Parameter: p
                 */
                bernoulli_distribution<real_t> bernoulliDist (lexical_cast<real_t > (distParam1));
                variate_generator<Algorithm&, bernoulli_distribution<real_t> > generator (*algorithm, bernoulliDist);
                for (; amount > 0; amount--)
                    {
                        *out << generator () << endl;
                    }
                break;
            }
        case Cauchy: ///Cauchy
            {
                /**
                 * Parameters: median, sigma
                 */
                cauchy_distribution<real_t> cauchyDist (lexical_cast<real_t > (distParam1),
                                                        lexical_cast<real_t > (distParam2));
                variate_generator<Algorithm&, cauchy_distribution<real_t> > generator (*algorithm, cauchyDist);
                for (; amount > 0; amount--)
                    {
                        *out << generator () << endl;
                    }
                break;
            }
        case Exponential: ///Exponential
            {
                /**
                 * Parameter: lambda
                 */
                exponential_distribution<real_t> expDist (lexical_cast<real_t > (distParam1));
                variate_generator<Algorithm&, exponential_distribution<real_t> > generator (*algorithm, expDist);
                for (; amount > 0; amount--)
                    {
                        *out << generator () << endl;
                    }
                break;
            }
        case Geometric: ///Geometric
            {
                /**
                 * Parameter: p
                 * PDF: p(i) := (1-p) * p^(i-1)
                 */
                geometric_distribution<int_t, real_t> geometricDist (lexical_cast<real_t > (distParam1));
                variate_generator<Algorithm&, geometric_distribution<int_t, real_t> > generator (*algorithm, geometricDist);
                for (; amount > 0; amount--)
                    {
                        *out << generator () << endl;
                    }
                break;
            }
        case Normal: ///Normal
            {
                /**
                 * Parameters: mu, sigma
                 */
                normal_distribution<real_t> smallInt (lexical_cast<real_t > (distParam1), lexical_cast<real_t > (distParam2));
                variate_generator<Algorithm&, normal_distribution<real_t> > generator (*algorithm, smallInt);
                for (; amount > 0; amount--)
                    {
                        *out << generator () << endl;
                    }
                break;
            }
        case LogNormal: ///Lognormal
            {
                /**
                 * Parameters: mean, sigma
                 */
                lognormal_distribution<real_t> lognormalDist (lexical_cast<real_t > (distParam1),
                                                              lexical_cast<real_t > (distParam2));
                variate_generator<Algorithm&, lognormal_distribution<real_t> > generator (*algorithm, lognormalDist);
                for (; amount > 0; amount--)
                    {
                        *out << generator () << endl;
                    }
                break;
            }
        case UniformOnSphere: ///Uniform on Sphere
            {
                uniform_on_sphere<real_t> uniOnSphere (lexical_cast<real_t > (distParam1)); ///dim
                variate_generator<Algorithm&, uniform_on_sphere<real_t> > generator (*algorithm, uniOnSphere);
                for (; amount > 0; amount--)
                    {

                        BOOST_FOREACH (real_t r, generator ())
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
