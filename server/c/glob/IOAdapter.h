/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

#ifndef IOADAPTER_H
#define IOADAPTER_H

#include <xmlinc.h>
#include <twine.h>
using namespace SLib;

#include "Threadable.h"
#include "IOConn.h"

namespace Helix {
namespace Glob {


/** This class defines the interface for any IOAdapter that we use.
 * We're fairly simple in our interface and only ask for a few things.
 *
 * @author Steven M. Cherry
 */
class DLLEXPORT IOAdapter : public Threadable
{

	public:

		/// Standard constructor:
		IOAdapter();

		/// Standard copy constructor:
		IOAdapter(const IOAdapter& c);

		/// Standard assignment operator:
		IOAdapter& operator=(const IOAdapter& c);

		/// Standard destructor:
		virtual ~IOAdapter();

		/** When init is called, it should process
		  * the xmlNode that we give it, as this will contain all
		  * of the configuration information that is provided for
		  * the current IOAdapter instantiation.
		  */
		virtual void Init(xmlNodePtr node) = 0;

		/** We implement the Execute method.
		  */
		virtual void Execute(void);

};


// This implementation of a factory/self registration system inspired by code
// from here: http://stackoverflow.com/questions/582331/is-there-a-way-to-instantiate-objects-from-a-string-holding-their-class-name
// thanks to StackOverflow :-)

template<typename T> IOAdapter* createIOT() { return new T(); }
typedef std::map<twine, IOAdapter*(*)() > iomap_type;

class IOAdapterFactory
{
	public:
		static IOAdapter* createInstance(const twine& className) ;

	protected:
		static iomap_type* getMap();

};

template <typename T>
class IOAdapterRegister : IOAdapterFactory
{
	public:
		IOAdapterRegister(const twine& className){
			(*(getMap()))[className] = &createIOT<T>;
		}
};



}} // End Namespace Helix::Glob

#endif // IOADAPTER_H Defined
