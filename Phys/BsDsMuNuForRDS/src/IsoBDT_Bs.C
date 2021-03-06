// Class: ReadBDT
// Automatically generated by MethodBase::MakeClass
//

/* configuration options =====================================================

#GEN -*-*-*-*-*-*-*-*-*-*-*- general info -*-*-*-*-*-*-*-*-*-*-*-

Method         : BDT::BDT
TMVA Release   : 4.1.4         [262404]
ROOT Release   : 5.34/05       [336389]
Creator        : laura
Date           : Thu Sep 19 15:43:56 2013
Host           : Linux ubuntu 3.2.0-23-generic #36-Ubuntu SMP Tue Apr 10 20:39:51 UTC 2012 x86_64 x86_64 x86_64 GNU/Linux
Dir            : /home/laura/root/tmva_original/test
Training events: 101865
Analysis type  : [Classification]


#OPT -*-*-*-*-*-*-*-*-*-*-*-*- options -*-*-*-*-*-*-*-*-*-*-*-*-

# Set by User:
V: "False" [Verbose output (short form of "VerbosityLevel" below - overrides the latter one)]
H: "False" [Print method-specific help message]
NTrees: "50" [Number of trees in the forest]
BoostType: "AdaBoost" [Boosting type for the trees in the forest]
AdaBoostBeta: "5.000000e-01" [Parameter for AdaBoost algorithm]
SeparationType: "giniindex" [Separation criterion for node splitting]
nEventsMin: "200" [Minimum number of events required in a leaf node (default: Classification: max(40, N_train/(Nvar^2)/10), Regression: 10)]
nCuts: "20" [Number of steps during node cut optimisation]
PruneMethod: "nopruning" [Method used for pruning (removal) of statistically insignificant branches]
MaxDepth: "3" [Max depth of the decision tree allowed]
# Default:
VerbosityLevel: "Default" [Verbosity level]
VarTransform: "None" [List of variable transformations performed before training, e.g., "D_Background,P_Signal,G,N_AllClasses" for: "Decorrelation, PCA-transformation, Gaussianisation, Normalisation, each for the given class of events ('AllClasses' denotes all events of all classes, if no class indication is given, 'All' is assumed)"]
CreateMVAPdfs: "False" [Create PDFs for classifier outputs (signal and background)]
IgnoreNegWeightsInTraining: "False" [Events with negative weights are ignored in the training (but are included for testing and performance evaluation)]
RenormByClass: "False" [Individually re-normalize each event class to the original size after boosting]
AdaBoostR2Loss: "quadratic" [Type of Loss function in AdaBoostR2t (Linear,Quadratic or Exponential)]
UseBaggedGrad: "False" [Use only a random subsample of all events for growing the trees in each iteration. (Only valid for GradBoost)]
GradBaggingFraction: "6.000000e-01" [Defines the fraction of events to be used in each iteration when UseBaggedGrad=kTRUE. (Only valid for GradBoost)]
Shrinkage: "1.000000e+00" [Learning rate for GradBoost algorithm]
UseRandomisedTrees: "False" [Choose at each node splitting a random set of variables]
UseNvars: "3" [Number of variables used if randomised tree option is chosen]
UsePoissonNvars: "True" [Interpret "UseNvars" not as fixed number but as mean of a Possion distribution in each split]
UseNTrainEvents: "101865" [Number of randomly picked training events used in randomised (and bagged) trees]
UseWeightedTrees: "True" [Use weighted trees or simple average in classification from the forest]
UseYesNoLeaf: "True" [Use Sig or Bkg categories, or the purity=S/(S+B) as classification of the leaf node]
NodePurityLimit: "5.000000e-01" [In boosting/pruning, nodes with purity > NodePurityLimit are signal; background otherwise.]
UseFisherCuts: "False" [Use multivariate splits using the Fisher criterion]
MinLinCorrForFisher: "8.000000e-01" [The minimum linear correlation between two variables demanded for use in Fisher criterion in node splitting]
UseExclusiveVars: "False" [Variables already used in fisher criterion are not anymore analysed individually for node splitting]
PruneStrength: "0.000000e+00" [Pruning strength]
PruneBeforeBoost: "False" [Flag to prune the tree before applying boosting algorithm]
PruningValFraction: "5.000000e-01" [Fraction of events to use for optimizing automatic pruning.]
NNodesMax: "100000" [Max number of nodes in tree]
DoBoostMonitor: "False" [Create control plot with ROC integral vs tree number]
NegWeightTreatment: "inverseboostnegweights" [How to treat events with negative weights in the BDT training (particular the boosting) : Ignore;  Boost With inverse boostweight; Pair events with negative and positive weights in traning sample and *annihilate* them (experimental!); Randomly pair events with negative and positive weights in leaf node and do not boost them (experimental!) ]
##


#VAR -*-*-*-*-*-*-*-*-*-*-*-* variables *-*-*-*-*-*-*-*-*-*-*-*-

NVar 6
track_minIPchi2          track_minIPchi2          track_minIPchi2          track_minIPchi2                                                 'F'    [8.7323722255e-05,499.771636963]
track_pvdis_mu                    track_pvdis_mu                    track_pvdis_mu                    PVdis                         mm                                'F'    [-192.893432617,199.680450439]
tracksvdis_mu                    tracksvdis_mu                    tracksvdis_mu                    SVdis                         mm                                'F'    [-199.778869629,192.869934082]
track_doca_mu                     track_doca_mu                     track_doca_mu                     doca                          mm                                'F'    [2.37707041606e-07,18.9456481934]
track_angle_mu                    track_angle_mu                    track_angle_mu                    angle                         rad                               'F'    [0.000116512797831,0.650962591171]
track_fc_mu                       track_fc_mu                       track_fc_mu                       fc                                                              'F'    [0.00243311771192,0.995779037476]
NSpec 0


============================================================================ */

#include <vector>
#include <cmath>
#include <string>
#include <iostream>

#define NN_bS new BDTNode_Bs
   
#ifndef BDTNode_Bs__def
#define BDTNode_Bs__def
   
class BDTNode_Bs {
   
public:
   
   // constructor of an essentially "empty" node floating in space
   BDTNode_Bs ( BDTNode_Bs* left,BDTNode_Bs* right,
                          int selector, double cutValue, bool cutType, 
                          int nodeType, double purity, double response ) :
   fLeft         ( left         ),
   fRight        ( right        ),
   fSelector     ( selector     ),
   fCutValue     ( cutValue     ),
   fCutType      ( cutType      ),
   fNodeType     ( nodeType     ),
   fPurity       ( purity       ),
   fResponse     ( response     ){
   }

   virtual ~BDTNode_Bs();

   // test event if it decends the tree at this node to the right
   virtual bool GoesRight( const std::vector<double>& inputValues ) const;
   BDTNode_Bs* GetRight( void )  {return fRight; };

   // test event if it decends the tree at this node to the left 
   virtual bool GoesLeft ( const std::vector<double>& inputValues ) const;
   BDTNode_Bs* GetLeft( void ) { return fLeft; };   

   // return  S/(S+B) (purity) at this node (from  training)

   double GetPurity( void ) const { return fPurity; } 
   // return the node type
   int    GetNodeType( void ) const { return fNodeType; }
   double GetResponse(void) const {return fResponse;}

private:

   BDTNode_Bs*   fLeft;     // pointer to the left daughter node
   BDTNode_Bs*   fRight;    // pointer to the right daughter node
   int                     fSelector; // index of variable used in node selection (decision tree)   
   double                  fCutValue; // cut value appplied on this node to discriminate bkg against sig
   bool                    fCutType;  // true: if event variable > cutValue ==> signal , false otherwise
   int                     fNodeType; // Type of node: -1 == Bkg-leaf, 1 == Signal-leaf, 0 = internal 
   double                  fPurity;   // Purity of node from training
   double                  fResponse; // Regression response value of node
}; 
   
//_______________________________________________________________________
   BDTNode_Bs::~BDTNode_Bs()
{
   if (fLeft  != NULL) delete fLeft;
   if (fRight != NULL) delete fRight;
} 
   
//_______________________________________________________________________
bool BDTNode_Bs::GoesRight( const std::vector<double>& inputValues ) const
{
   // test event if it decends the tree at this node to the right
   bool result;
     result = (inputValues[fSelector] > fCutValue );
   if (fCutType == true) return result; //the cuts are selecting Signal ;
   else return !result;
}
   
//_______________________________________________________________________
bool BDTNode_Bs::GoesLeft( const std::vector<double>& inputValues ) const
{
   // test event if it decends the tree at this node to the left
   if (!this->GoesRight(inputValues)) return true;
   else return false;
}
   
#endif
   
#ifndef IClassifierReader__def
#define IClassifierReader__def

class IClassifierReader {

 public:

   // constructor
   IClassifierReader() : fStatusIsClean( true ) {}
   virtual ~IClassifierReader() {}

   // return classifier response
   virtual double GetMvaValue( const std::vector<double>& inputValues ) const = 0;

   // returns classifier status
   bool IsStatusClean() const { return fStatusIsClean; }

 protected:

   bool fStatusIsClean;
};

#endif

class ReadBDT_bS : public IClassifierReader {

 public:

   // constructor
   ReadBDT_bS( std::vector<std::string>& theInputVars ) 
      : IClassifierReader(),
        fClassName( "ReadBDT_bS" ),
        fNvars( 6 ),
        fIsNormalised( false )
   {      
      // the training input variables
      const char* inputVars[] = { "track_minIPchi2", "track_pvdis_mu", "tracksvdis_mu", "track_doca_mu", "track_angle_mu", "track_fc_mu" };

      // sanity checks
      if (theInputVars.size() <= 0) {
         std::cout << "Problem in class \"" << fClassName << "\": empty input vector" << std::endl;
         fStatusIsClean = false;
      }

      if (theInputVars.size() != fNvars) {
         std::cout << "Problem in class \"" << fClassName << "\": mismatch in number of input values: "
                   << theInputVars.size() << " != " << fNvars << std::endl;
         fStatusIsClean = false;
      }

      // validate input variables
      for (size_t ivar = 0; ivar < theInputVars.size(); ivar++) {
         if (theInputVars[ivar] != inputVars[ivar]) {
            std::cout << "Problem in class \"" << fClassName << "\": mismatch in input variable names" << std::endl
                      << " for variable [" << ivar << "]: " << theInputVars[ivar].c_str() << " != " << inputVars[ivar] << std::endl;
            fStatusIsClean = false;
         }
      }

      // initialize min and max vectors (for normalisation)
      fVmin[0] = 8.73237222549506e-05;
      fVmax[0] = 499.771636962891;
      fVmin[1] = -192.893432617188;
      fVmax[1] = 199.680450439453;
      fVmin[2] = -199.778869628906;
      fVmax[2] = 192.869934082031;
      fVmin[3] = 2.37707041605972e-07;
      fVmax[3] = 18.9456481933594;
      fVmin[4] = 0.000116512797831092;
      fVmax[4] = 0.650962591171265;
      fVmin[5] = 0.00243311771191657;
      fVmax[5] = 0.995779037475586;

      // initialize input variable types
      fType[0] = 'F';
      fType[1] = 'F';
      fType[2] = 'F';
      fType[3] = 'F';
      fType[4] = 'F';
      fType[5] = 'F';

      // initialize constants
      Initialize();

   }

   // destructor
   virtual ~ReadBDT_bS() {
      Clear(); // method-specific
   }

   // the classifier response
   // "inputValues" is a vector of input values in the same order as the 
   // variables given to the constructor
   double GetMvaValue( const std::vector<double>& inputValues ) const;

 private:

   // method-specific destructor
   void Clear();

   // common member variables
   const char* fClassName;

   const size_t fNvars;
   size_t GetNvar()           const { return fNvars; }
   char   GetType( int ivar ) const { return fType[ivar]; }

   // normalisation of input variables
   const bool fIsNormalised;
   bool IsNormalised() const { return fIsNormalised; }
   double fVmin[6];
   double fVmax[6];
   double NormVariable( double x, double xmin, double xmax ) const {
      // normalise to output range: [-1, 1]
      return 2*(x - xmin)/(xmax - xmin) - 1.0;
   }

   // type of input variable: 'F' or 'I'
   char   fType[6];

   // initialize internal variables
   void Initialize();
   double GetMvaValue__( const std::vector<double>& inputValues ) const;

   // private members (method specific)
   std::vector<BDTNode_Bs*> fForest;       // i.e. root nodes of decision trees
   std::vector<double>                fBoostWeights; // the weights applied in the individual boosts
};

double ReadBDT_bS::GetMvaValue__( const std::vector<double>& inputValues ) const
{
   double myMVA = 0;
   double norm  = 0;
   for (unsigned int itree=0; itree<fForest.size(); itree++){
      BDTNode_Bs *current = fForest[itree];
      while (current->GetNodeType() == 0) { //intermediate node
         if (current->GoesRight(inputValues)) current=(BDTNode_Bs*)current->GetRight();
         else current=(BDTNode_Bs*)current->GetLeft();
      }
      myMVA += fBoostWeights[itree] *  current->GetNodeType();
      norm  += fBoostWeights[itree];
   }
   return myMVA /= norm;
}

void ReadBDT_bS::Initialize()
{
  // itree = 0
  fBoostWeights.push_back(1.673313487954);
  fForest.push_back( 
NN_bS(
0, 
0, 
-1, 23.7987, 0, -1, 0.0340058,-99)    );
  // itree = 1
  fBoostWeights.push_back(0.894559);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.609986,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.419756,-99) , 
3, 0.169471, 1, 0, 0.520081,-99) , 
NN_bS(
0, 
0, 
-1, 0.124168, 0, -1, 0.185092,-99) , 
3, 0.889746, 1, 0, 0.452445,-99) , 
NN_bS(
0, 
0, 
-1, 6.79935, 0, -1, 0.101949,-99) , 
0, 23.7987, 0, 0, 0.157983,-99)    );
  // itree = 2
  fBoostWeights.push_back(0.566215);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.638944,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.390001,-99) , 
3, 0.169471, 0, 0, 0.509339,-99) , 
NN_bS(
0, 
0, 
-1, 0.124168, 0, -1, 0.357171,-99) , 
3, 0.889746, 1, 0, 0.483723,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.521868,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.237745,-99) , 
3, 0.677731, 1, 0, 0.460171,-99) , 
NN_bS(
0, 
0, 
-1, 0.478821, 1, -1, 0.163471,-99) , 
0, 6.79935, 0, 0, 0.217346,-99) , 
0, 23.7987, 0, 0, 0.270988,-99)    );
  // itree = 3
  fBoostWeights.push_back(0.392311);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.564096,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.297997,-99) , 
2, 32.7678, 1, 0, 0.552507,-99) , 
NN_bS(
0, 
0, 
-1, 0.979256, 1, -1, 0.425845,-99) , 
5, 0.665977, 1, 0, 0.512544,-99) , 
NN_bS(
0, 
0, 
-1, 0.475455, 1, -1, 0.281167,-99) , 
0, 23.7987, 0, 0, 0.331628,-99)    );
  // itree = 4
  fBoostWeights.push_back(0.290666);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.559527,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.39431,-99) , 
3, 0.270448, 1, 0, 0.518808,-99) , 
NN_bS(
0, 
0, 
-1, 47.5978, 0, -1, 0.292379,-99) , 
3, 0.709952, 1, 0, 0.485484,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.521377,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.372513,-99) , 
1, 5.20441, 1, 0, 0.488723,-99) , 
NN_bS(
0, 
0, 
-1, 3.39362, 0, -1, 0.295517,-99) , 
0, 23.7586, 0, 0, 0.330744,-99) , 
5, 0.475455, 1, 0, 0.393082,-99)    );
  // itree = 5
  fBoostWeights.push_back(0.206439);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.53508,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.374442,-99) , 
3, 0.527797, 1, 0, 0.502647,-99) , 
NN_bS(
0, 
0, 
-1, 16.6579, 1, -1, 0.405842,-99) , 
4, 0.0621019, 1, 0, 0.431303,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.58858,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.327448,-99) , 
0, 118.053, 0, 0, 0.359184,-99) , 
NN_bS(
0, 
0, 
-1, 47.5153, 0, -1, 0.215147,-99) , 
4, 0.0485386, 1, 0, 0.257887,-99) , 
1, -5.95349, 0, 0, 0.412022,-99)    );
  // itree = 6
  fBoostWeights.push_back(0.14849);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.513331,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.333634,-99) , 
2, 14.9522, 1, 0, 0.492776,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.533569,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.394226,-99) , 
0, 47.2211, 0, 0, 0.413246,-99) , 
2, -3.77602, 0, 0, 0.460462,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.547121,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.363447,-99) , 
5, 0.976583, 1, 0, 0.394591,-99) , 
NN_bS(
0, 
0, 
-1, 47.5153, 0, -1, 0.252044,-99) , 
4, 0.0485386, 1, 0, 0.295132,-99) , 
1, -5.95349, 0, 0, 0.442647,-99)    );
  // itree = 7
  fBoostWeights.push_back(0.121397);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, -21.0653, 0, -1, 0.461335,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.516798,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.336635,-99) , 
0, 47.5975, 0, 0, 0.378218,-99) , 
2, 11.3506, 1, 0, 0.454051,-99) , 
NN_bS(
0, 
0, 
-1, 0.0485386, 1, -1, 0.322883,-99) , 
1, -5.95349, 0, 0, 0.440206,-99)    );
  // itree = 8
  fBoostWeights.push_back(0.0621968);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, -21.0653, 0, -1, 0.491608,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.508162,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.364039,-99) , 
4, 0.0252165, 1, 0, 0.392855,-99) , 
2, 11.3506, 1, 0, 0.483041,-99) , 
NN_bS(
0, 
0, 
-1, 0.0485386, 1, -1, 0.349973,-99) , 
1, -5.95349, 0, 0, 0.469195,-99)    );
  // itree = 9
  fBoostWeights.push_back(0.0717439);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.512718,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.405696,-99) , 
2, -21.0653, 0, 0, 0.507156,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.509037,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.374815,-99) , 
0, 71.3962, 0, 0, 0.401507,-99) , 
2, 11.3506, 1, 0, 0.498044,-99) , 
NN_bS(
0, 
0, 
-1, 0.0485386, 1, -1, 0.364251,-99) , 
1, -5.95349, 0, 0, 0.484226,-99)    );
  // itree = 10
  fBoostWeights.push_back(0.0621482);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.503693,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.451262,-99) , 
4, 0.156731, 1, 0, 0.49108,-99) , 
NN_bS(
0, 
0, 
-1, 0.0754166, 1, -1, 0.411658,-99) , 
2, 11.3506, 1, 0, 0.484269,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, -108, 0, -1, 0.480682,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.505176,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.304062,-99) , 
0, 47.5153, 0, 0, 0.335389,-99) , 
4, 0.0485386, 1, 0, 0.381021,-99) , 
1, -5.95349, 0, 0, 0.473682,-99)    );
  // itree = 11
  fBoostWeights.push_back(0.0891638);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.525763,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.46632,-99) , 
3, 0.0847231, 1, 0, 0.482071,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.558752,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.342455,-99) , 
0, 23.7798, 0, 0, 0.402201,-99) , 
3, 1.77949, 1, 0, 0.478205,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.513977,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.233183,-99) , 
2, -108, 0, 0, 0.49621,-99) , 
NN_bS(
0, 
0, 
-1, 47.5153, 0, -1, 0.344476,-99) , 
4, 0.0485386, 1, 0, 0.392432,-99) , 
1, -5.95349, 0, 0, 0.469458,-99)    );
  // itree = 12
  fBoostWeights.push_back(0.0460727);
  fForest.push_back( 
NN_bS(
NN_bS(
0, 
0, 
-1, 1.77949, 1, -1, 0.488614,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.702216,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.414331,-99) , 
5, 0.974804, 1, 0, 0.528139,-99) , 
NN_bS(
0, 
0, 
-1, 2.26175, 0, -1, 0.374893,-99) , 
0, 47.5153, 0, 0, 0.400491,-99) , 
1, -5.95349, 0, 0, 0.479686,-99)    );
  // itree = 13
  fBoostWeights.push_back(0.0484144);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.507864,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.442937,-99) , 
2, -18.9026, 0, 0, 0.504039,-99) , 
NN_bS(
0, 
0, 
-1, 0.253178, 1, -1, 0.422338,-99) , 
3, 1.77949, 1, 0, 0.500131,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.692493,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.425554,-99) , 
5, 0.974804, 1, 0, 0.530736,-99) , 
NN_bS(
0, 
0, 
-1, 2.26175, 0, -1, 0.38575,-99) , 
0, 47.5153, 0, 0, 0.409963,-99) , 
1, -5.95349, 0, 0, 0.491038,-99)    );
  // itree = 14
  fBoostWeights.push_back(0.038617);
  fForest.push_back( 
NN_bS(
NN_bS(
0, 
0, 
-1, 6.22822, 1, -1, 0.490538,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.570846,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.447099,-99) , 
1, -14.8578, 0, 0, 0.499031,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.568353,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.364204,-99) , 
2, -89.1917, 1, 0, 0.382621,-99) , 
4, 0.0485386, 1, 0, 0.420025,-99) , 
1, -5.95349, 0, 0, 0.483459,-99)    );
  // itree = 15
  fBoostWeights.push_back(0.0459561);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.50853,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.470172,-99) , 
3, 0.590569, 1, 0, 0.500714,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.135673,-99) , 
3, 6.22822, 1, 0, 0.500192,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.593448,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.431759,-99) , 
5, 0.975983, 1, 0, 0.46577,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.580215,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.311456,-99) , 
0, 47.4143, 0, 0, 0.356816,-99) , 
4, 0.0963181, 1, 0, 0.425584,-99) , 
1, -5.95349, 0, 0, 0.492727,-99)    );
  // itree = 16
  fBoostWeights.push_back(0.0342789);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.713368,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.493145,-99) , 
3, 5.31512, 0, 0, 0.493905,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.141153,-99) , 
3, 6.22822, 1, 0, 0.493408,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.538011,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.413401,-99) , 
1, -14.8569, 0, 0, 0.472331,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.568983,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.321396,-99) , 
0, 47.4143, 0, 0, 0.363357,-99) , 
4, 0.0963181, 1, 0, 0.43225,-99) , 
1, -5.95349, 0, 0, 0.487313,-99)    );
  // itree = 17
  fBoostWeights.push_back(0.0243596);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 5.31512, 0, 1, 0.502415,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.14536,-99) , 
3, 6.22822, 1, 0, 0.501918,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.610448,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.428672,-99) , 
2, -71.7372, 0, 0, 0.571535,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.529475,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.391452,-99) , 
0, 47.5153, 0, 0, 0.414467,-99) , 
4, 0.0246488, 1, 0, 0.434404,-99) , 
1, -5.95349, 0, 0, 0.495209,-99)    );
  // itree = 18
  fBoostWeights.push_back(0.0273069);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.70123,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.495624,-99) , 
3, 5.31512, 0, 0, 0.496325,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.148413,-99) , 
3, 6.22822, 1, 0, 0.495845,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.524797,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.282982,-99) , 
2, -108, 0, 0, 0.510594,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.577972,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.384506,-99) , 
2, -89.1917, 1, 0, 0.402308,-99) , 
4, 0.0485386, 1, 0, 0.437359,-99) , 
1, -5.95349, 0, 0, 0.490045,-99)    );
  // itree = 19
  fBoostWeights.push_back(0.0239287);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 5.31512, 0, 1, 0.503105,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.151897,-99) , 
3, 6.22822, 1, 0, 0.502626,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.598094,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.432784,-99) , 
2, -71.7372, 0, 0, 0.562653,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.526614,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.399848,-99) , 
0, 47.5153, 0, 0, 0.421066,-99) , 
4, 0.0246488, 1, 0, 0.439031,-99) , 
1, -5.95349, 0, 0, 0.496332,-99)    );
  // itree = 20
  fBoostWeights.push_back(0.0256033);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.690386,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.496469,-99) , 
3, 5.31512, 0, 0, 0.497123,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.155005,-99) , 
3, 6.22822, 1, 0, 0.49666,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.589044,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.447448,-99) , 
5, 0.975983, 1, 0, 0.477322,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.534928,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.338322,-99) , 
0, 23.7075, 0, 0, 0.380551,-99) , 
4, 0.0963181, 1, 0, 0.441949,-99) , 
1, -5.95349, 0, 0, 0.491255,-99)    );
  // itree = 21
  fBoostWeights.push_back(0.0234394);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 5.31512, 0, 1, 0.503481,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.158389,-99) , 
3, 6.22822, 1, 0, 0.503017,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.539583,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.42794,-99) , 
1, -14.8569, 0, 0, 0.480992,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.528554,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.344077,-99) , 
0, 23.7075, 0, 0, 0.383802,-99) , 
4, 0.0963181, 1, 0, 0.445509,-99) , 
1, -5.95349, 0, 0, 0.497347,-99)    );
  // itree = 22
  fBoostWeights.push_back(0.0525515);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 45.151, 0, 1, 0.505743,-99) , 
NN_bS(
0, 
0, 
-1, 0.0890089, 1, -1, 0.451749,-99) , 
2, 14.0188, 1, 0, 0.50121,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0.977035, 1, 1, 0.602201,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.529054,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.402422,-99) , 
0, 4.52439, 0, 0, 0.451459,-99) , 
0, 95.0303, 0, 0, 0.466753,-99) , 
5, 0.901175, 1, 0, 0.492216,-99)    );
  // itree = 23
  fBoostWeights.push_back(0.0470565);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0.369114, 0, 1, 0.648792,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.56803,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.367423,-99) , 
4, 0.0418539, 1, 0, 0.473032,-99) , 
2, 39.0923, 1, 0, 0.559262,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, -19.3129, 0, -1, 0.485781,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.559032,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.370316,-99) , 
0, 23.7523, 0, 0, 0.420397,-99) , 
3, 1.80435, 1, 0, 0.481853,-99) , 
1, 50.1285, 0, 0, 0.484465,-99)    );
  // itree = 24
  fBoostWeights.push_back(0.0470947);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.516746,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.489748,-99) , 
2, -1.76437, 0, 0, 0.50119,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.656379,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.327737,-99) , 
1, -80.7307, 1, 0, 0.398785,-99) , 
1, -24.6475, 0, 0, 0.499068,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0.184253, 0, 1, 0.56743,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.553173,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.285632,-99) , 
0, 3.39069, 0, 0, 0.394542,-99) , 
0, 23.7798, 0, 0, 0.441363,-99) , 
3, 1.80435, 1, 0, 0.495257,-99)    );
  // itree = 25
  fBoostWeights.push_back(0.0419208);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.50876,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.417807,-99) , 
1, -22.0573, 0, 0, 0.506316,-99) , 
NN_bS(
0, 
0, 
-1, 0.0890089, 1, -1, 0.455578,-99) , 
2, 5.89431, 1, 0, 0.500965,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0.184253, 0, 1, 0.555836,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.541505,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.295337,-99) , 
0, 3.39069, 0, 0, 0.396001,-99) , 
0, 23.7798, 0, 0, 0.439408,-99) , 
3, 1.80435, 1, 0, 0.496919,-99)    );
  // itree = 26
  fBoostWeights.push_back(0.067689);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.52946,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.437539,-99) , 
0, 23.7988, 1, 0, 0.507003,-99) , 
NN_bS(
0, 
0, 
-1, -24.9282, 0, -1, 0.480057,-99) , 
4, 0.0930945, 1, 0, 0.493196,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.723887,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.491759,-99) , 
4, 0.184253, 0, 0, 0.545464,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.531081,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.304136,-99) , 
0, 3.39069, 0, 0, 0.397316,-99) , 
0, 23.7798, 0, 0, 0.437651,-99) , 
3, 1.80435, 1, 0, 0.489559,-99)    );
  // itree = 27
  fBoostWeights.push_back(0.0234035);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.571027,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.498001,-99) , 
1, 60.8139, 0, 0, 0.499402,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.651668,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.346876,-99) , 
1, -80.7307, 1, 0, 0.413324,-99) , 
1, -24.6475, 0, 0, 0.497641,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0.184253, 0, 1, 0.554768,-99) , 
NN_bS(
0, 
0, 
-1, 1.13035, 0, -1, 0.399469,-99) , 
0, 23.7798, 0, 0, 0.441898,-99) , 
3, 1.80435, 1, 0, 0.49401,-99)    );
  // itree = 28
  fBoostWeights.push_back(0.0323876);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.507232,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.46006,-99) , 
2, 14.4552, 1, 0, 0.505028,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.646337,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.352197,-99) , 
1, -80.7307, 1, 0, 0.416324,-99) , 
1, -24.6475, 0, 0, 0.50322,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0.184253, 0, 1, 0.54898,-99) , 
NN_bS(
0, 
0, 
-1, 1.13035, 0, -1, 0.405096,-99) , 
0, 23.7798, 0, 0, 0.444437,-99) , 
3, 1.80435, 1, 0, 0.499398,-99)    );
  // itree = 29
  fBoostWeights.push_back(0.122594);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 1.73827, 1, 1, 0.656434,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.59451,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.447836,-99) , 
3, 0.296373, 0, 0, 0.495194,-99) , 
3, 0.889746, 0, 0, 0.528288,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.582111,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.478637,-99) , 
0, 21.7912, 1, 0, 0.54565,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.500201,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.396995,-99) , 
0, 1.51014, 0, 0, 0.444747,-99) , 
0, 4.53086, 0, 0, 0.488039,-99) , 
0, 95.1947, 0, 0, 0.492997,-99)    );
  // itree = 30
  fBoostWeights.push_back(0.0913653);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0.889749, 0, 1, 0.553848,-99) , 
NN_bS(
0, 
0, 
-1, 0.0408939, 0, -1, 0.445205,-99) , 
5, 0.290111, 0, 0, 0.526302,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 10.9005, 0, 1, 0.52349,-99) , 
NN_bS(
0, 
0, 
-1, 0.902201, 1, -1, 0.429883,-99) , 
0, 2.26644, 0, 0, 0.483033,-99) , 
0, 47.5974, 0, 0, 0.490961,-99)    );
  // itree = 31
  fBoostWeights.push_back(0.0808764);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.578714,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.449812,-99) , 
3, 0.171833, 0, 0, 0.516246,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.518544,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.462721,-99) , 
0, 4.53278, 0, 0, 0.484378,-99) , 
0, 47.5974, 0, 0, 0.490137,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.715791,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.423988,-99) , 
3, 5.29985, 0, 0, 0.445261,-99) , 
NN_bS(
0, 
0, 
-1, 0.112366, 1, -1, 0.184091,-99) , 
3, 5.88561, 1, 0, 0.431108,-99) , 
3, 1.80435, 1, 0, 0.486314,-99)    );
  // itree = 32
  fBoostWeights.push_back(0.0450281);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.586564,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.491541,-99) , 
3, 0.601371, 0, 0, 0.516565,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.505352,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.4599,-99) , 
3, 0.300606, 1, 0, 0.485872,-99) , 
0, 47.5974, 0, 0, 0.491467,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.242977,-99) , 
3, 6.31522, 1, 0, 0.490777,-99)    );
  // itree = 33
  fBoostWeights.push_back(0.0414589);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0.173489, 0, 1, 0.56445,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.554699,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.481675,-99) , 
3, 0.889746, 0, 0, 0.493945,-99) , 
4, 0.119069, 0, 0, 0.521244,-99) , 
NN_bS(
0, 
0, 
-1, 7.21739, 1, -1, 0.483576,-99) , 
0, 47.5974, 0, 0, 0.490456,-99)    );
  // itree = 34
  fBoostWeights.push_back(0.0251119);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0.397756, 0, 1, 0.56315,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.504894,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.471264,-99) , 
2, 0.696735, 1, 0, 0.497466,-99) , 
1, 50.1285, 0, 0, 0.499636,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.252909,-99) , 
3, 6.31522, 1, 0, 0.498963,-99)    );
  // itree = 35
  fBoostWeights.push_back(0.0170349);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.662822,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.496189,-99) , 
5, 0.397756, 0, 0, 0.556962,-99) , 
NN_bS(
0, 
0, 
-1, -19.3129, 0, -1, 0.49396,-99) , 
1, 50.1285, 0, 0, 0.496039,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.257683,-99) , 
3, 6.31522, 1, 0, 0.495392,-99)    );
  // itree = 36
  fBoostWeights.push_back(0.0192506);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.55852,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.497312,-99) , 
3, 0.300685, 0, 0, 0.523728,-99) , 
NN_bS(
0, 
0, 
-1, 40.7944, 1, -1, 0.494956,-99) , 
0, 47.5974, 0, 0, 0.500195,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.260955,-99) , 
3, 6.31522, 1, 0, 0.499549,-99)    );
  // itree = 37
  fBoostWeights.push_back(0.0291498);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.549896,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.478314,-99) , 
0, 23.7855, 1, 0, 0.524443,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.611346,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.495833,-99) , 
1, 48.0324, 0, 0, 0.498616,-99) , 
5, 0.333548, 1, 0, 0.504252,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.264684,-99) , 
3, 6.31522, 1, 0, 0.503608,-99)    );
  // itree = 38
  fBoostWeights.push_back(0.0251075);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0.0952813, 0, 1, 0.531234,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.506085,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.384453,-99) , 
0, 40.7944, 1, 0, 0.504315,-99) , 
0, 47.5974, 0, 0, 0.509219,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.270396,-99) , 
3, 6.31522, 1, 0, 0.50858,-99)    );
  // itree = 39
  fBoostWeights.push_back(0.0291279);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.551123,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.497694,-99) , 
4, 0.0952813, 0, 0, 0.524977,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.505988,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.471559,-99) , 
3, 0.601211, 1, 0, 0.498221,-99) , 
0, 47.5974, 0, 0, 0.503092,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.275378,-99) , 
3, 6.31522, 1, 0, 0.502487,-99)    );
  // itree = 40
  fBoostWeights.push_back(0.0364252);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.64104,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.494909,-99) , 
3, 1.7372, 1, 0, 0.574995,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.536965,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.493253,-99) , 
3, 0.169356, 0, 0, 0.513271,-99) , 
3, 0.889746, 0, 0, 0.52428,-99) , 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.523888,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.48727,-99) , 
0, 11.3318, 0, 0, 0.494137,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0,-99) , 
3, 7.21739, 1, 0, 0.493625,-99) , 
0, 47.5974, 0, 0, 0.499219,-99)    );
  // itree = 41
  fBoostWeights.push_back(0.0209585);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.691937,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.44578,-99) , 
3, 1.20014, 0, 0, 0.628272,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.506532,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.445596,-99) , 
1, -13.9604, 0, 0, 0.503601,-99) , 
1, -80.7295, 1, 0, 0.504537,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.284767,-99) , 
3, 6.31522, 1, 0, 0.503963,-99)    );
  // itree = 42
  fBoostWeights.push_back(0.00560683);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.687451,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.450964,-99) , 
3, 1.20014, 0, 0, 0.626156,-99) , 
NN_bS(
0, 
0, 
-1, -67.3706, 0, -1, 0.498865,-99) , 
1, -80.7295, 1, 0, 0.499818,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.289054,-99) , 
3, 6.31522, 1, 0, 0.49927,-99)    );
  // itree = 43
  fBoostWeights.push_back(0.00590882);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.686245,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.452353,-99) , 
3, 1.20014, 0, 0, 0.625587,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.500786,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.208374,-99) , 
1, -67.3706, 0, 0, 0.500267,-99) , 
1, -80.7295, 1, 0, 0.501204,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.290208,-99) , 
3, 6.31522, 1, 0, 0.500656,-99)    );
  // itree = 44
  fBoostWeights.push_back(0.00568817);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.684972,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.453817,-99) , 
3, 1.20014, 0, 0, 0.624987,-99) , 
NN_bS(
0, 
0, 
-1, -67.3706, 0, -1, 0.498795,-99) , 
1, -80.7295, 1, 0, 0.499738,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.291427,-99) , 
3, 6.31522, 1, 0, 0.499197,-99)    );
  // itree = 45
  fBoostWeights.push_back(0.00573152);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.683743,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.455227,-99) , 
3, 1.20014, 0, 0, 0.624409,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.50073,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.210294,-99) , 
1, -67.3706, 0, 0, 0.500217,-99) , 
1, -80.7295, 1, 0, 0.501144,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.292603,-99) , 
3, 6.31522, 1, 0, 0.500604,-99)    );
  // itree = 46
  fBoostWeights.push_back(0.00564243);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.682502,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.456649,-99) , 
3, 1.20014, 0, 0, 0.623825,-99) , 
NN_bS(
0, 
0, 
-1, -67.3706, 0, -1, 0.498789,-99) , 
1, -80.7295, 1, 0, 0.499722,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.29379,-99) , 
3, 6.31522, 1, 0, 0.499189,-99)    );
  // itree = 47
  fBoostWeights.push_back(0.00562067);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.681278,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.458049,-99) , 
3, 1.20014, 0, 0, 0.623249,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.500708,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.212189,-99) , 
1, -67.3706, 0, 0, 0.5002,-99) , 
1, -80.7295, 1, 0, 0.501117,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.294962,-99) , 
3, 6.31522, 1, 0, 0.500584,-99)    );
  // itree = 48
  fBoostWeights.push_back(0.00556556);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.680057,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.459445,-99) , 
3, 1.20014, 0, 0, 0.622674,-99) , 
NN_bS(
0, 
0, 
-1, -67.3706, 0, -1, 0.4988,-99) , 
1, -80.7295, 1, 0, 0.499722,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.296133,-99) , 
3, 6.31522, 1, 0, 0.499196,-99)    );
  // itree = 49
  fBoostWeights.push_back(0.00522519);
  fForest.push_back( 
NN_bS(
NN_bS(
NN_bS(
0, 
0, 
-1, -104.773, 0, 1, 0.622104,-99) , 
NN_bS(
NN_bS(
0, 
0, 
-1, 0, 1, 1, 0.500694,-99) , 
NN_bS(
0, 
0, 
-1, 0, 1, -1, 0.214065,-99) , 
1, -67.3706, 0, 0, 0.500191,-99) , 
1, -80.7295, 1, 0, 0.501098,-99) , 
NN_bS(
0, 
0, 
-1, 0.113526, 1, -1, 0.297294,-99) , 
3, 6.31522, 1, 0, 0.500572,-99)    );
   return;
}
 
// Clean up
inline void ReadBDT_bS::Clear() 
{
   for (unsigned int itree=0; itree<fForest.size(); itree++) { 
      delete fForest[itree]; 
   }
}
   inline double ReadBDT_bS::GetMvaValue( const std::vector<double>& inputValues ) const
   {
      // classifier response value
      double retval = 0;

      // classifier response, sanity check first
      if (!IsStatusClean()) {
         std::cout << "Problem in class \"" << fClassName << "\": cannot return classifier response"
                   << " because status is dirty" << std::endl;
         retval = 0;
      }
      else {
         if (IsNormalised()) {
            // normalise variables
            std::vector<double> iV;
            int ivar = 0;
            for (std::vector<double>::const_iterator varIt = inputValues.begin();
                 varIt != inputValues.end(); varIt++, ivar++) {
               iV.push_back(NormVariable( *varIt, fVmin[ivar], fVmax[ivar] ));
            }
            retval = GetMvaValue__( iV );
         }
         else {
            retval = GetMvaValue__( inputValues );
         }
      }

      return retval;
   }
