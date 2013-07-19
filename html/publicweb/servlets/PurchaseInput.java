

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.io.StringReader;
import java.io.StringWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Enumeration;
import java.util.Properties;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Result;
import javax.xml.transform.Source;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerConfigurationException;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.xml.sax.InputSource;

/**
 * This is a simple example of an HTTP Servlet.  It responds to the GET
 * and HEAD methods of the HTTP protocol.
 */
public class PurchaseInput extends HttpServlet
{ 
	private static final long serialVersionUID = 1L;
	protected PrintWriter m_out;
	
     protected void doPost(HttpServletRequest req, HttpServletResponse resp)
    	throws ServletException, IOException 
    {
    	
        resp.setContentType("text/html");
        m_out = resp.getWriter();

        try {
            loadPreamble();

            //listFiles("./");
            
            Document doc = newDocument("CustPurchaseRequest"); 
			Element root = doc.getDocumentElement();
			root.setAttribute("user", "licreq");
			root.setAttribute("pass", "l1cr3q");
			root.setAttribute("dbname", "Zed");
	        Enumeration e = req.getParameterNames();
	        while(e.hasMoreElements()){
	        	String name = (String)e.nextElement();
	        	String value = (String)req.getParameter(name);
	        	root.setAttribute(name, value);
	        }

			Document serverResp = sendToZedServer("zed.hericus.com", 443, doc, "CustPurchaseRequest", true);
			m_out.println("<b>");
			try {
				returnHasErrors(serverResp, true);
			} catch (Exception ex){
			}
			m_out.println("</b>");
        } catch (Throwable t){
        	m_out.println("Error occurred: " + t.getLocalizedMessage() );
        	t.printStackTrace(m_out);
        }

        try {
        	loadFooter();
        } catch (Throwable t){
        	
        }
        m_out.close();
        
    }
    
    public void listFiles(String where) throws Exception {
    	File here = new File(where);
    	String[] names = here.list();
    	for(int i = 0; i < names.length; i++){
    		m_out.println(names[i] + "<br/>");
    	}
    }
    
    /** This will load the top portion of the HTML page that displays the status
     *  to the user.
     */
    public void loadPreamble() throws Exception {
		File file = new File("/usr/apps/apache-tomcat-5.5.26/hericus.com/ROOT/preamble.html");
		if(!file.exists()){
			return;
		}
		BufferedReader br = new BufferedReader( new FileReader(file) );
		String line = null;
		do {
			line = br.readLine();
			if(line == null){
				break;
			}
			m_out.println(line);
		}while (line != null);
		br.close();
    }
    
    /** This will add the tail end of the HTML page after the status messages have
     *  been added.
     */
    public void loadFooter() throws Exception {
		File file = new File("/usr/apps/apache-tomcat-5.5.26/hericus.com/ROOT/footer.html");
		if(!file.exists()){
			return;
		}
		BufferedReader br = new BufferedReader( new FileReader(file) );
		String line = null;
		do {
			line = br.readLine();
			if(line == null){
				break;
			}
			m_out.println(line);
		}while (line != null);
		br.close();
    }
    
	/** This centralizes the lookup of the URL to use to contact the server.  Right now
	 * we just use ICE_HOST and ICE_PORT to build the URL.  In the future something more
	 * complicated/elaborate may be put in as a replacement.
	 */
	public URL getServerURL(String host, int port, String action, boolean secure){
		URL url;
		try {
			if(secure){
				url = new URL( "https://" + host + ":" + port + "/" + action);
			} else {
				url = new URL( "http://" + host + ":" + port + "/" + action);
			}
		} catch (MalformedURLException mue){
			url = null;
		}
		return url;
	}
	
	/** This is the actual workhorse method here.  It's responsible for posting an XML document
	 * to the server and receiving the response.  Since the server sometimes just responds with
	 * "OK", the return document may be null.  
	 */
	public Document sendToZedServer(String host, int port, Document doc, String action, boolean secure){
		URL url = getServerURL(host, port, action, secure);
		try {
			
			HttpURLConnection cnx = (HttpURLConnection) url.openConnection();
			cnx.setRequestMethod("POST");//$NON-NLS-1$
			cnx.setRequestProperty("Content-Type", "text/xml");//$NON-NLS-1$ //$NON-NLS-2$
			cnx.setDoInput(true);
			cnx.setDoOutput(true);
			cnx.connect();
	
			OutputStream out = cnx.getOutputStream();
			if (out == null){
				m_out.println("No output connection to server: " + url);
				return null;
			}
			
			String doc_as_string = xmlToString(doc);
			out.write(doc_as_string.getBytes("UTF-8"));

			out.flush();
			out.close();

			//Before reading xml answer from server Check response code
			if (cnx.getResponseCode() != 200){
				m_out.println("Error received from server: "+ cnx.getResponseCode() + " " + url.toString());
				
				// see if there is a content length
				if(cnx.getContentLength() <= 0){
					return null; // no content length.  Just return null
				}
			}
			
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			InputStream is = cnx.getInputStream();
			byte[] buffer = new byte[2048];
			int count = 0;
			while( (count = is.read(buffer)) > 0){
				baos.write(buffer, 0, count);
			}
			cnx.disconnect();
			
			Document result = stringToXmlDocument( new String(baos.toByteArray() ));
			return result;
			
		} catch (Exception e){
			m_out.println("Error sending doc to: " + url + "\n" + e);
			e.printStackTrace(m_out);
			return null;
		}
	}
	
	public String xmlToString(Document doc) {
		if (doc == null) {
			return ""; //$NON-NLS-1$
		}
		// Serialize the XML document into a String
		StringWriter writer = new StringWriter();

		try {
			Result result = new StreamResult(writer);
			Source source = new DOMSource(doc);

			Transformer transformer = TransformerFactory.newInstance()
					.newTransformer();
			transformer.setOutputProperty(OutputKeys.METHOD, "xml"); //$NON-NLS-1$            
			transformer.setOutputProperty(OutputKeys.ENCODING, "UTF-8"); //$NON-NLS-1$
			transformer.transform(source, result);
		} catch (TransformerConfigurationException e) {
		} catch (TransformerException e) {
		}

		return writer.toString();

	}

	public Document stringToXmlDocument(String xml) {
		if (xml == null || xml.length() == 0) {
			return null;
		}
		try {
			StringReader sr = new StringReader(xml);
			InputSource is = new InputSource(sr);
			DocumentBuilder db = DocumentBuilderFactory.newInstance()
					.newDocumentBuilder();
			Document ret = db.parse(is);
			return ret;
		} catch (Exception e) {
			return null;
		}
	}
	
	public Document newDocument(String rootName) {
		try {
			DocumentBuilder db = DocumentBuilderFactory.newInstance().newDocumentBuilder();
			Document doc = db.newDocument();
			doc.appendChild( doc.createElement(rootName) );
			return doc;
		} catch (Exception e){
			return null;
		}
	}
	
	/**
	 * Returns the given attribute from the given node as an boolean if possible.
	 * If the node attribute doesn't exist, or it's not TRUE/FALSE/true/false, this returns
	 * false.
	 */
	public boolean getBoolAttr(Element node, String attrName){
		String tmp = node.getAttribute(attrName);
		if( (tmp.compareToIgnoreCase("TRUE") == 0) ||
			(tmp.compareToIgnoreCase("YES") == 0) ||
			(tmp.compareTo("1") == 0)
		){
			return true;
		} else {
			return false;
		}
	}
	
	/**
	 * Finds the first child of the given Node that has the Node name that is
	 * requested. Does not use XPathAPI. This is equivalent to
	 * XPathAPI.selectSingleNode() but is intended to be much faster.
	 */
	public Node findChild(Node node, String nodeName) {
		if(node == null || nodeName == null){
			return null; // can't find it.
		}
		for (Node child = node.getFirstChild(); child != null; child = child
				.getNextSibling())
		{
			if (child.getNodeName().compareTo(nodeName) == 0) {
				return child;
			}
		}
		return null; // Didn't find it.
	}

	
	/** This function will walk a zed response XML document and look for
	 * errors in it.  If errors are found, and the doAlert parameter is set
	 * to true, then we will alert to the user that errors were found.
	 * <p>
	 * Returns true if errors were found, and false if no errors were found.
	 * 
	 */
	public boolean returnHasErrors(Document response, boolean throwExceptions) throws Exception {
		if(response == null){
			if(throwExceptions){
				throw new Exception("Response from server is null!");
			} else {
				return true;
			}
		}
		
		// Check the response for errors:
		Element root = response.getDocumentElement();
		boolean error_response = getBoolAttr(root, "haserror");
		if(error_response){
			if(throwExceptions){
				Node errors = findChild(root, "Errors");
				StringBuffer err_msg = new StringBuffer();
				for (Node child = errors.getFirstChild(); child != null; child = child.getNextSibling()) {
					if (child.getNodeName().compareTo("Error") == 0) {
						err_msg.append( ((Element)child).getAttribute("msg")).append("\n\n");
					}
				}
				throw new Exception("Error occurred during processing:\n\n" + err_msg.toString());
			} else {
				return true;
			}
		}
		return false;
	}
	
	
}
 
