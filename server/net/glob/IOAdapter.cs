/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;
using System.Xml;

namespace Helix.Glob
{
	public abstract class IOAdapter : Threadable
	{
		public IOAdapter ()
		{
		}

		public abstract void Init (XmlElement node);

		public override void Execute ()
		{
			throw new NotImplementedException ();
		}
	}
}

