using System;
using System.Collections;
using System.Collections.Generic;
using System.Xml;

namespace Helix.Glob
{
	public class XmlHelpers
	{
		public XmlHelpers ()
		{
		}

		public static XmlElement FindChild(XmlElement parent, string childNodeName){
			foreach (XmlNode node in parent.ChildNodes) {
				if (node.NodeType == XmlNodeType.Element && node.Name == childNodeName) {
					return (XmlElement)node;
				}
			}
			return null; // couldn't find it.
		}

		public static List<XmlElement> FindChildren(XmlElement parent, string childNodeName){
			List<XmlElement> ret = new List<XmlElement> ();
			foreach (XmlNode node in parent.ChildNodes) {
				if (node.NodeType == XmlNodeType.Element && node.Name == childNodeName) {
					ret.Add( (XmlElement)node );
				}
			}
			return ret; // Return whatever we found.
		}

		public static bool getBoolAttr( XmlElement el, string attrName, bool defaultValue = false ){
			if (el.HasAttribute (attrName) == false) {
				return defaultValue;
			}
			string attrVal = el.GetAttribute (attrName);
			if (attrVal == "1" ||
			    attrVal == "true" || attrVal == "True" || attrVal == "TRUE" ||
			    attrVal == "yes" || attrVal == "Yes" || attrVal == "YES" ||
				attrVal == "on" || attrVal == "On" || attrVal == "ON"
			) {
				return true;
			} else {
				return false;
			}
		}
	
		public static int getIntAttr( XmlElement el, string attrName, int defaultValue = 0, int min = System.Int32.MinValue, int max = System.Int32.MaxValue ){
			if (el.HasAttribute (attrName) == false) {
				return defaultValue;
			}
			try {
				int ret = Int32.Parse (el.GetAttribute (attrName));
				if(ret > max){
					ret = max;
				}
				if(ret < min){
					ret = min;
				}
				return ret;
			} catch (Exception e){
				return defaultValue;
			}
		}

		public static void setCDATASection(XmlElement message, String msg)
		{
			XmlCDataSection cdata = message.OwnerDocument.CreateCDataSection (msg);
			message.AppendChild (cdata);
		}

	}
}

