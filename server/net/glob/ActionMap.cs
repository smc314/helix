/* ***************************************************************************

   Copyright (c): 2013 Hericus Software, Inc.

   License: The MIT License (MIT)

   Authors: Steven M. Cherry

*************************************************************************** */

using System;
using System.Diagnostics;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Xml;

namespace Helix.Glob
{
	public class ActionMap
	{
		/// Our static instance
		protected static ActionMap m_actionmap;

		public ActionMap ()
		{
			using (EnEx ee = new EnEx ("ActionMap::ActionMap()")) {
				m_html = new List<ActionHtml> ();
				LoadActions ();
			}
		}

		public static ActionMap getInstance()
		{
			using (EnEx ee = new EnEx ("ActionMap::getInstance()")) {
				if (m_actionmap == null) {
					m_actionmap = new ActionMap ();
				}
				return m_actionmap;
			}
		}

		public void addLogicAction(string name, string handler)
		{
			using (EnEx ee = new EnEx ("ActionMap::addLogicAction(string name, string handler)")) {
				if (m_logics.ContainsKey (name)) {
					m_logics.Remove (name); // replace it.
				}
				m_logics [name] = handler;
			}
		}

		public void addHtmlAction(string name, string handler)
		{
			using (EnEx ee = new EnEx ("ActionMap::addHtmlAction(string name, string handler)")) {
				ActionHtml ah = new ActionHtml (name);
				m_html.Add (ah);
			}
		}

		public void addAction(XmlElement action)
		{
			using (EnEx ee = new EnEx ("ActionMap::addAction(XmlElement action)")) {
				if (action.Name != "Action") {
					throw new Exception (String.Format ("Unknown node handed to ActionMap.addAction: {0}", action.Name));
				}
				string type = action.GetAttribute ("type");
				if (String.IsNullOrEmpty (type)) {
					throw new Exception ("Action does not have a type.");
				}
				if (type == "logic") {
					string name = action.GetAttribute ("name");
					string handler = action.GetAttribute ("handler");
					addLogicAction (name, handler);
				} else if (type == "html") {
					ActionHtml ah = new ActionHtml (action);
					m_html.Add (ah);
				} else {
					throw new Exception (String.Format ("Unknown Action type: {0}", type));
				}
			}
		}

		public void clearMap()
		{
			using (EnEx ee = new EnEx ("ActionMap::clearMap()")) {
				m_logics.Clear ();
				m_html.Clear ();
			}
		}

		public ActionClass findAction(string name)
		{
			using (EnEx ee = new EnEx ("ActionMap::findAction()")) {
				if (m_logics.ContainsKey (name)) {
					string handler = m_logics [name];
					Type type = Type.GetType (handler, true);
					ActionClass ret = (ActionClass)Activator.CreateInstance (type);
					return ret;
				} else {
					int max = 0;
					int max_index = -1;
					// Find the best match for this target url
					for (int i = 0; i < m_html.Count; i++) {
						int match_quality = m_html [i].matchesURL (name);
						if (match_quality > max) {
							max = match_quality;
							max_index = i;
						}
					}
					if (max_index != -1) {
						return m_html [max_index];
					} else {
						return null;
					}
				}
			}
		}

		public List<KeyValuePair<string,string> > listHandlers()
		{
			using (EnEx ee = new EnEx ("ActionMap::listHandlers()")) {
				List<KeyValuePair<string,string> > ret = new List<KeyValuePair<string, string>> ();
				foreach (KeyValuePair<string, string> action in m_logics) {
					KeyValuePair<string, string> kvp = new KeyValuePair<string, string> ( action.Key, action.Value );
					ret.Add (kvp);
				}

				return ret;
			}
		}

		/// <summary>
		/// Uses reflection to ensure we know about all of the actions present
		/// in the system.
		/// </summary>
		public void LoadActions()
		{
			using (EnEx ee = new EnEx ("ActionMap::LoadActions()")) {
				m_logics = new Dictionary<string, string> ();
				List<Type> actions = FindAllDerivedTypes<ActionLogic> ();
				foreach (Type t in actions) {
					Log.Info ("Adding logic handler [{0}] = [{1}]", t.Name, t.FullName);
					m_logics [t.Name] = t.FullName;
				}
			}
		}

		protected static List<Type> FindAllDerivedTypes<T>()
		{
			using (EnEx ee = new EnEx ("ActionMap::addLogicAction(string name, string handler)")) {
				Assembly assembly = Assembly.GetAssembly (typeof(T));
				var derivedType = typeof(T);
				return assembly.GetTypes ().Where (t => t != derivedType && derivedType.IsAssignableFrom (t)).ToList ();
			}
		}

		protected Dictionary<string, string> m_logics;
		protected List<ActionHtml> m_html;

	}
}

