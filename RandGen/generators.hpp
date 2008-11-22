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
 * Static global variables used by the generator and
 * set by the main function (command line arguments)
 */
static ull& amount; //Number of random numbers to generate
static ofstream& fout;
static string& distParam1;
static string& distParam2;
static short distributionSelectionParam;
static short algorithmSelectionParam;

enum RNG_ALGO
{
    MT19937, //Mersenne Twister 19937
    LC_MINSTD, //Linear Congruential
    ECUYER1988, //L'Ecuyer, Additive combine
    HELLEKALEK1995, //Hellekalek 1995, Inverse Congruential
    KREUTZER1986, //Kreutzer 1986, 
};

/**
 * Generates random numbers using the boost algorithms
 */
void GenRandBoost()
{
    ///Cache required parameters
    ulong ulSeed = lexical_cast<ulong>(seedParam);
    int algorithmSelection = algorithmSelectionParam;

    ///Switch distribution
    switch(algorithmSelection)
        {
            case 0: ///MT 19937
                {
                    mt19937 mersenne(ulSeed);
                    ProcessBoostAlgorithm<mt19937>(&mersenne);
                    break;
                }
            case 1: ///Linear congruential
                {
                    minstd_rand minstdrand(ulSeed);
                    ProcessBoostAlgorithm<minstd_rand>(&minstdrand);
                }
            case 2: ///Additive combine
                {
                    ecuyer1988 addComb(ulSeed);
                    ProcessBoostAlgorithm<ecuyer1988>(&addComb);
                    break;
                }
            case 3: ///Inverse congruential
                {
                    hellekalek1995 invCongr(ulSeed);
                    ProcessBoostAlgorithm<hellekalek1995>(&invCongr);
                    break;
                }
            case 4: ///Shuffle output
                {
                    kreutzer1986 shOut(ulSeed);
                    ProcessBoostAlgorithm<kreutzer1986>(&shOut);
                    break;
                }
            case 5: ///Lagged Fibonacci 607
                {
                    lagged_fibonacci607 lf607(ulseed);
                    ProcessBoostAlgorithm<lagged_fibonacci607>(&lf607);
                    break;
                }
            default: break;
        }
}

template<class Algorithm>
void ProcessBoostAlgorithm(Algorithm *algorithm) ///Process type of boost algorithm
{
    ///Cache parameters
    ctr_t amount = lexical_cast<ctr_t>(amountParam);
    int distributionSelection = distributionSelectionParam;
    string filename = filenameParam;

    ///Open fstream
    fstream f(filename.c_str(), fstream::out);
    switch(distributionSelection)
        {
            case 0: ///Uniform small int
                {
                    ///Boost Random stuff
                    uniform_smallint<smallint_t> smallInt(lexical_cast<smallint_t>(llParam), lexical_cast<smallint_t>(ulParam));
                    variate_generator<Algorithm&, uniform_smallint<smallint_t> > generator(*algorithm, smallInt);
                    for(ctr_t i = 0;i < amount;i++)
                        {
                            f << generator() << endl;
                        }
                    break;
                }
            case 1: ///Uniform integer
                {
                    uniform_int<int_t> uniInt(lexical_cast<int_t>(llParam), lexical_cast<int_t>(ulParam));
                    variate_generator<Algorithm&, uniform_int<int_t> > generator(*algorithm, uniInt);
                    for(ctr_t i = 0;i < amount;i++)
                        {
                            f << generator() << endl;
                        }
                    break;
                }
            case 2: ///Uniform real
                {
                    uniform_real<real_t> uniReal(lexical_cast<real_t>(llParam), lexical_cast<real_t>(ulParam));
                    variate_generator<Algorithm&, uniform_real<real_t> > generator(*algorithm, uniReal);
                    for(ctr_t i = 0;i < amount;i++)
                        {
                            f << generator() << endl;
                        }
                    break;
                }
            case 3: ///Triangle
                {
                    triangle_distribution<real_t> triangle(lexical_cast<int_t>(ulParam),
                                                            lexical_cast<int_t>(ulParam),
                                                            lexical_cast<int_t>(distParam1));
                    variate_generator<Algorithm&, triangle_distribution<real_t> > generator(*algorithm, triangle);
                    for(ctr_t i = 0;i < amount;i++)
                        {
                            f << generator() << endl;
                        }
                    break;
                }
            case 4: ///Bernoulli
                {
                    bernoulli_distribution<real_t> bernoulliDist(lexical_cast<real_t>(distParam1)); ///p
                    variate_generator<Algorithm&, bernoulli_distribution<real_t> > generator(*algorithm, bernoulliDist);
                    for(ctr_t i = 0;i < amount;i++)
                        {
                            f << generator() << endl;
                        }
                    break;
                }
            case 5: ///Cauchy
                {
                    cauchy_distribution<real_t> cauchyDist(lexical_cast<real_t>(distParam1),
                                                            lexical_cast<real_t>(distParam2));
                    variate_generator<Algorithm&, cauchy_distribution<real_t> > generator(*algorithm, cauchyDist); ///median, sigma
                    for(ctr_t i = 0;i < amount;i++)
                        {
                            f << generator() << endl;
                        }
                    break;
                }
            case 6: ///Exponential
                {
                    exponential_distribution<real_t> expDist(lexical_cast<real_t>(distParam1)); ///lambda
                    variate_generator<Algorithm&, exponential_distribution<real_t> > generator(*algorithm, expDist);
                    for(ctr_t i = 0;i < amount;i++)
                        {
                            f << generator() << endl;
                        }
                    break;
                }
            case 7: ///Geometric
                {
                    geometric_distribution<int_t,real_t> geometricDist(lexical_cast<real_t>(distParam1)); ///p
                    variate_generator<Algorithm&, geometric_distribution<int_t,real_t> > generator(*algorithm, geometricDist);
                    for(ctr_t i = 0;i < amount;i++)
                        {
                            f << generator() << endl;
                        }
                    break;
                }
            case 8: ///Normal
                {
                    normal_distribution<int_t> smallInt(lexical_cast<int_t>(distParam1), lexical_cast<int_t>(distParam2));///mu, sigma
                    variate_generator<Algorithm&, normal_distribution<int_t> > generator(*algorithm, smallInt);
                    for(ctr_t i = 0;i < amount;i++)
                        {
                            f << generator() << endl;
                        }
                    break;
                }
            case 9: ///Lognormal
                {
                    lognormal_distribution<real_t> lognormalDist(lexical_cast<real_t>(distParam1),
                                                                 lexical_cast<real_t>(distParam2)); ///mean, sigma
                    variate_generator<Algorithm&, lognormal_distribution<real_t> > generator(*algorithm, lognormalDist);
                    for(ctr_t i = 0;i < amount;i++)
                        {
                            f << generator() << endl;
                        }
                    break;
                }
            case 10: ///Uniform on Sphere
                {
                    uniform_on_sphere<real_t> uniOnSphere(lexical_cast<real_t>(distParam1)); ///dim
                    variate_generator<Algorithm&, uniform_on_sphere<real_t> > generator(*algorithm, uniOnSphere);
                    for(ctr_t i = 0;i < amount;i++)
                        {
                            foreach(real_t r, generator())
                            {
                                f << r << endl;
                            }
                        }
                    break;
                }
            default: break;
        }
}

#endif	/* _GENERATORS_HPP */

