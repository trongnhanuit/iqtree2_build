//
//  modelhmm.h
//  model
//
//  Created by Thomas Wong on 02/02/23.
//

#ifndef modelhmm_h
#define modelhmm_h

#include <string>
#include "utils/tools.h"
#include "utils/optimization.h"
#include "tree/phylohmm.h"
#include "tree/phylotree.h"

#define MIN_TRAN_PROB 1e-5
#define INITIAL_PROB_SAME_CAT 0.95

using namespace std;

class PhyloHmm;

/**
HMM transition Simple model
*/
class ModelHmm: public Optimization
{
    
public:
    /**
     constructor
     @param ncat : number of categories
     */
    ModelHmm(int numcat);
    
    /**
     destructor
     */
    ~ModelHmm();
    
    /**
     @return the number of dimensions
     */
    virtual int getNDim() { return 1; }
    
    /**
     * @return HMM model name
     */
    virtual string getName() { return "SM"; }

    // initialize parameters
    virtual void initialize_param();
    /**
        set the associated PhyloHmm
        @param phyloHmm the associated PhyloHmm
    */
    void setPhyloHmm(PhyloHmm *phyloHmm);

    /**
     Optimize the model parameters
     @param gradient_epsilon: epsilon for optimization
     @return log-likelihood value
     */
    virtual double optimizeParameters(double gradient_epsilon);
    
    /**
     * @return log values of transition matrix
     */
    double* getTransitLog() { return transitLog; }
    
    /**
     Show parameters
     */
    virtual void showParameters(ostream& out);
    
    virtual int getNParameters();

    // probability of transition between the same category
    double tranSameCat;

protected:
    
    int ncat; // number of categories

    /**
        PhyloHmm associated
    */
    PhyloHmm *phylo_hmm;

    // compute the log values of transition matrix
    virtual void computeLogTransits();
    
    // Parameter: log values of transition matrix
    // dimension: ncat x ncat
    // transitLog[i*ncat+j] : log of transition probability for a site with cat i to the next site with cat j
    double* transitLog;

private:
    
    // for optimization
    double computeFunction(double tran_same_cat);

    /**
     Optimize the transition matrix by EM algorithm
     Prerequisite: phylo_hmm->computeBackLikeArray() and phylo_hmm->computeFwdLikeArray() have been invoked
     @return log-likelihood value
     */
    double optimizeParametersByEM();
};

#endif
