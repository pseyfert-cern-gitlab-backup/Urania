#ifndef V0HHFITTER_CLIENTTREE_H 
#define V0HHFITTER_CLIENTTREE_H 1

// STL include
#include <map>
// RooFit include
#include "RooAbsArg.h"
// Local include
#include "Fitter.h"

/** @class ClientTree ClientTree.h V0hhFitter/ClientTree.h
 *  
 *
 *  @author Matthew M Reid
 *  @date   2014-01-08
 */

namespace V0hhFit {

    class ClientTree {
        public: 
            /// Standard constructor
            ClientTree( );

            // Constructor with pointer to RooAbsArg
            ClientTree( RooAbsArg* thearg,
                    std::vector<std::string> oldobjects );


            //=============================================================================
            //recursively places clients of the "var" given in m_TreeMap
            //goes all the way up the tree until the RooAbsArg has no more clients.
            //=============================================================================
            void recursiveClientCheck(RooAbsArg* var, 
                    std::vector<std::string> oldobjects,
                    int currentdisp=0);

            //=============================================================================
            //looks in the map and removes servers of the clients that are not amongst the 
            //keys of the map and are therefore not affected by the change in dependency on
            //the new var
            //=============================================================================
            void removeOrphanServers();

            //=============================================================================
            //iterates over the tree of clients defined in the map altering all the 
            //dependencies in turn such that dependency is transferred from var to newvar 
            //and is propagated all the way up the tree
            //returns a vector of strings to use as factory commands in the RooWorkspace
            //=============================================================================
            std::vector<std::string> clientReplace(RooAbsArg* var,
						   RooAbsArg* newvar,
						   Fitter& rsf);
	    
            //=============================================================================
            //The versions of the last 3 functions that use TStrings internally.
            //=============================================================================
            void recursiveClientCheckTS(RooAbsArg* var, int currentdisp=0);
            void removeOrphanServersTS();
            std::vector<std::string> clientReplaceTS(RooAbsArg* var,
                    RooAbsArg* newvar);


            //=============================================================================
            // Get the vector of modified object names.
            //=============================================================================
            std::vector<std::string> getModifiedObjectNames();


            //=============================================================================
            // Split a string by some delimiter.
            //=============================================================================
            void split( std::vector<std::string>& splitstring, std::string stringvalue, std::string c );
            
           
            //=============================================================================
            // remove all right-side trailing characters labelled c
            //=============================================================================
            void trim_right( std::string& stringvalue, std::string c );

            
            //=============================================================================
            // remove all left-side leading characters labelled c
            //=============================================================================
            void trim_left( std::string& stringvalue, std::string c );
            
            virtual ~ClientTree( ); ///< Destructor

        protected:

            //a map containing names of clients in the tree (keys)
            //and pairs of ints and strings
            //the int is the displacement of the client from the 
            //variable which this is a ClientTree of.
            //std::string is a comma separated list of servers of the 
            //client.
            std::map<std::string,std::pair<int,std::string> > m_TreeMap;

            //names of objects that this ClientTree has modified, i.e. old objects to
            //put in trash...
            std::vector<std::string> m_ModObjects;

        private:

    };

}

#endif // V0HHFITTER_CLIENTTREE_H
