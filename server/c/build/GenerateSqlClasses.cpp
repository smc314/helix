/* ***************************************************************************

	Copyright: 2013 Hericus Software, LLC

	License: The MIT License (MIT)

	Authors: Steven M. Cherry

*************************************************************************** */

#include <AnException.h>
#include <Log.h>
#include <xmlinc.h>
#include <XmlHelpers.h>
#include <twine.h>
#include <File.h>
using namespace SLib;

#include <map>
using namespace std;

xmlDocPtr m_namedQueryDoc;
xmlDocPtr m_doc;
xmlNodePtr m_root;
map<twine, map<twine, twine> > m_data_objects;
map<twine, map<twine, twine> > m_do_children;
twine m_output;
twine m_output_header;
twine m_output_test;
twine m_output_test_header;
xmlDocPtr m_output_test_xml = NULL;
twine m_currentClass;
twine m_currentPackage;
twine m_currentFile;
map<twine, twine> m_api_outputs;
twine m_api_cpp_header;
twine m_api_cpp_body;

void findAllSqlXmlFiles(twine start, int pass);
void findAllCPPFiles(twine start);
void checkCPPFile(twine fileName);
void buildJSApi(twine api, twine input);
void buildCPPApi(twine api, twine input);
void createAPIFiles();
void initCPPApis();
void processFile(twine file_name, int pass);
void beginOutputFile( vector<xmlNodePtr>& statements );
void finalizeOutputFile();
void buildDataObjects( vector<xmlNodePtr>& statements, vector<xmlNodePtr>& children ) ;
void dumpDataObjects() ;
void beginCPPDataObject(twine& objName);
void beginCPPDataObjectTest( twine& objName, vector<xmlNodePtr>& statements );
void createDataObjectTestXml( twine& objName, vector<xmlNodePtr>& statements );

void dumpJavaDataObject(twine& objName);
void dumpJSDataObject(twine& objName);
map<twine, twine>& addDataObject( twine& name );
void addDataObjectMember(twine obj_name, twine name, twine datatype);
twine& getDataObjectMemberType(twine& obj_name, twine& name);
void generateExecuteNamedQuery() ;
twine logExplain( const twine& stmt ) ;

map<twine, twine> buildObjectParms( twine& objName );
map<twine, twine> buildStatementParms( xmlNodePtr stmt );

void generateReturn(xmlNodePtr stmt);
void generateReturnXML(xmlNodePtr stmt);
void generateReturnDO(xmlNodePtr stmt);

void generateUpdate(xmlNodePtr stmt);
void generateUpdateXML(xmlNodePtr stmt);
void generateUpdateDO(xmlNodePtr stmt);
void generateUpdateDOSqlDB(xmlNodePtr stmt);
void generateUpdateDOTest(xmlNodePtr stmt);

void generateInsert(xmlNodePtr stmt);
void generateInsertXML(xmlNodePtr stmt);
void generateInsertDO(xmlNodePtr stmt);
void generateInsertDOSqlDB(xmlNodePtr stmt);
void generateInsertDOTest(xmlNodePtr stmt);

void generateDelete(xmlNodePtr stmt);
void generateDeleteXML(xmlNodePtr stmt);
void generateDeleteDO(xmlNodePtr stmt);
void generateDeleteDOSqlDB(xmlNodePtr stmt);
void generateDeleteDOTest(xmlNodePtr stmt);

void generateSelectToDO(xmlNodePtr stmt) ;
void generateSelectToDOSqlDB(xmlNodePtr stmt) ;
void generateSelectToDOTest(xmlNodePtr stmt);

twine flattenSql(xmlNodePtr stmt);
twine convertArg(xmlNodePtr e);
twine convertArg(twine type);
twine convertType(xmlNodePtr e);
twine convertType(twine type);
twine NULLForType(xmlNodePtr e);
twine xmlSetForType(twine name, twine type, twine elemname);
twine xmlGetForType(twine name, twine type, twine elemname);
twine jsPropDefinition( twine name, twine type );
twine jsGetForType(twine name, twine type, twine elemname);
twine jsSetForType(twine name, twine type, twine elemname);
twine odbcBindOutputForType(size_t pos, twine name, twine type);
twine odbcBindOutputForType2(size_t pos, twine name, twine type);
twine odbcBindInputForType(size_t pos, twine name, twine type);
twine odbcBindInputForType2(size_t pos, twine name, twine type);
twine odbcBindInputForType3(size_t pos, twine name, twine type);
twine odbcBindInputForType4(size_t pos, twine name, twine type);
twine odbcBindInputForType5(size_t pos, twine name, twine type);
twine replaceInputForType(twine name, twine type);
twine replaceInputForType2(twine name, twine type);
twine paramForType(twine name, twine type);
twine loadTmpl(const twine& tmplName, map<twine, twine>* vars);
twine replaceVars( const twine& tmplName, size_t lineIdx, twine line, map<twine, twine>* vars );

int main (void)
{
	m_namedQueryDoc = xmlNewDoc((const xmlChar*)"1.0");
	m_namedQueryDoc->children = xmlNewDocNode(m_namedQueryDoc, NULL, (const xmlChar*)"NamedQueries", NULL);

	try {
		printf("=========================================================\n");
		printf("Pass 1: Reading all files to build data objects in memory\n");
		printf("=========================================================\n");
		findAllSqlXmlFiles("..", 1);
		dumpDataObjects();

		printf("\n");
		printf("=========================================================\n");
		printf("Pass 2: Reading all files and generating code.           \n");
		printf("=========================================================\n");
		findAllSqlXmlFiles("..", 2);

		printf("\n");
		printf("=========================================================\n");
		printf("Pass 3: Scanning cpp files for Javascript/C++ API Autogen\n");
		printf("=========================================================\n");
		initCPPApis();
		findAllCPPFiles("..");
		createAPIFiles();

		//generateExecuteNamedQuery();
		//dumpDataObjects();
	} catch (AnException& e){
		printf("Error caught during generation:\n%s\n", e.Msg() );
	} catch (...) {
		printf("Unknown error caught!\n");
	}
}


void findAllSqlXmlFiles(twine start, int pass)
{
	// Check all of the normal files.
	vector<twine> files = File::listFiles(start);
	for(size_t i = 0; i < files.size(); i++){
		File child = File(start + "/" + files[i]);
		if(child.name().endsWith(twine(".sql.xml"))){
			printf("Found sql.xml file (%s)\n", child.name()() );
			//fflush(stdout);
			m_currentFile = child.name();
			processFile(child.name(), pass);
		}
	}

	// Then recurse through all of the subdirectories:
	vector<twine> folders = File::listFolders(start);
	for(size_t i = 0; i < folders.size(); i++){
		if(folders[i] != "." && folders[i] != ".."){
			findAllSqlXmlFiles(start + "/" + folders[i], pass);
		}
	}

}

void findAllCPPFiles(twine start)
{
	// Check all of the normal files.
	vector<twine> files = File::listFiles(start);
	for(size_t i = 0; i < files.size(); i++){
		File child = File(start + "/" + files[i]);
		if(child.name().endsWith(twine(".cpp"))){
			m_currentFile = child.name();
			checkCPPFile(child.name());
		}
	}

	// Then recurse through all of the subdirectories:
	vector<twine> folders = File::listFolders(start);
	for(size_t i = 0; i < folders.size(); i++){
		if(folders[i] != "." && folders[i] != ".."){
			findAllCPPFiles(start + "/" + folders[i]);
		}
	}

}


void processFile(twine file_name, int pass)
{
	m_doc = xmlParseFile(file_name());
	if(m_doc == NULL){
		return;
	}
	m_root = xmlDocGetRootElement(m_doc);
	if(strncmp( (const char*)(m_root->name), "SQLXml", 6) != 0){
		printf("Invalid sql.xml file (%s)\n", file_name());
		return;
	}
	m_currentClass.getAttribute(m_root, "generateClass");
	m_currentPackage.getAttribute(m_root, "package");
	
	vector<xmlNodePtr> statements = XmlHelpers::FindChildren(m_root, "SqlStatement");
	vector<xmlNodePtr> children = XmlHelpers::FindChildren(m_root, "ChildVector");
	if(pass == 1){
		buildDataObjects( statements, children );
		return; // only build data objects on the first pass.
	}

	beginOutputFile( statements );
	for(size_t i = 0; i < statements.size(); i++){
		xmlNodePtr statement = statements[i];
		twine type, name, target;
		name.getAttribute(statement, "methodName"); 
		type.getAttribute(statement, "methodType"); 
		target.getAttribute(statement, "target"); 
		printf("Creating method (%s)::(%s) of type (%s)\n", m_currentClass(), name(), type());
		
		if(type != "MULTIINSERT"){
			xmlNodePtr qdRoot = xmlDocGetRootElement(m_namedQueryDoc);
			xmlNodePtr a_method = xmlNewChild(qdRoot, NULL, (const xmlChar*)"Method", NULL);
			xmlSetProp(a_method, (const xmlChar*)"name", xmlGetProp(statement, (const xmlChar*)"methodName") );
			xmlSetProp(a_method, (const xmlChar*)"class", xmlGetProp(m_root, (const xmlChar*)"generateClass") );

		}

		if(type == "RETURN"){
			generateReturn(statement);
			generateReturnXML(statement);
			generateReturnDO(statement);
		} else if(type == "UPDATE"){
			if(target == "sqldb"){
				generateUpdateDOSqlDB(statement);
			} else {
				generateUpdateDO(statement);
			}
			generateUpdateDOTest(statement);
		} else if(type == "INSERT"){
			if(target == "sqldb"){				
				generateInsertDOSqlDB(statement);
			} else {
				generateInsertDO(statement);
			}
			generateInsertDOTest(statement);
		} else if(type == "DELETE"){
			if(target == "sqldb"){
				generateDeleteDOSqlDB(statement);
			} else {
				generateDeleteDO(statement);
			}
			generateDeleteDOTest(statement);
		} else if(type == "SELECTTOXML"){
			if(target == "sqldb"){
				generateSelectToDOSqlDB(statement);
			} else {
				generateSelectToDO(statement);
			}
			generateSelectToDOTest( statement );
		} else {
			printf("Unknown method type (%s)\n", type());
		}
	}
		
	finalizeOutputFile();
}

void checkCPPFile(twine fileName)
{
	if(fileName.endsWith(twine("GenerateSqlClasses.cpp")) ||
		fileName.endsWith(twine("GenerateSqlTests.cpp"))
	){
		return; // this is us, or something ignorable.  skip it.
	}
	printf("Checking cpp file: %s\n", fileName() );

	File cppFile(fileName);
	twine contents = cppFile.readContentsAsTwine();

	size_t idx = contents.find("// LOGICCODEGEN API=");
	while(idx != TWINE_NOT_FOUND){

		// pull out the API name and the Input object name:
		idx += 20;
		size_t idx2 = contents.find(" ", idx);
		twine api = contents.substr(idx, idx2-idx);

		idx = idx2 + 7;
		idx2 = contents.find("\n", idx);
		size_t idx3 = contents.find("\r", idx);
		twine input;
		if(idx3 != TWINE_NOT_FOUND){
			input = contents.substr(idx, idx3-idx);
		} else {
			input = contents.substr(idx, idx2-idx);
		}

		printf("Found API (%s), Input (%s)\n", api(), input() );
		buildJSApi(api, input);
		buildCPPApi(api, input);
		idx = contents.find("// LOGICCODEGEN API=", idx2);
	}
}

void buildJSApi(twine api, twine input)
{
	vector<twine> splits = api.split("/");
	twine shortApi = splits[ splits.size() - 1 ];
	//twine shortApi = splits[3];
	twine package = "PACKAGE"; //splits[2];

	twine out;
	out.append(
		"\t\t/** This function will call the " + api + "\n"
		"\t\t  * server API.\n"
		"\t\t  */\n"
		"\t\t" + shortApi + " : function ( "
	);
	
	size_t howMany = input.get_int();
	if(input == "NULL"){
		// No inputs.
		out.append("\n");
	} else if(input == "ID"){
		out.append("idVal,\n");
	} else if(howMany > 0){
		for(size_t i = 0; i < howMany; i++){
			twine tmp; tmp.format("inputObj%d, ", i);
			out.append(tmp);
		}
		out.append("\n");
	} else {
		out.append("inputObj,\n");
	}

	out.append(
		"\t\t\tcompletionFunction, theThis\n"
		"\t\t){\n"
		"\t\t\t// First build the request XML Document\n"
		"\t\t\tvar requestDoc = qx.xml.Document.create(NULL, \"" + shortApi + "\");\n"
	);

	if(input == "NULL"){
		// No inputs
	} else if(input == "ID"){
		out.append(
			"\t\t\tvar requestRoot = requestDoc.documentElement;\n"
			"\t\t\trequestRoot.setAttribute(\"id\", idVal);\n"
		);
	} else if(howMany > 0){
		out.append( "\t\t\tvar requestRoot = requestDoc.documentElement;\n" );
		for(size_t i = 0; i < howMany; i++){
			twine tmp; tmp.format("inputObj%d", i);
			out.append( 
				"\t\t\tif( " + tmp + " !== undefined && " + tmp + " !== NULL){\n" 
				"\t\t\t\t" + tmp + ".createXMLElement( requestRoot );\n"
				"\t\t\t}\n"
			);
		}
	} else {
		out.append(
			"\t\t\tvar requestRoot = requestDoc.documentElement;\n"
			"\t\t\tinputObj.createXMLElement( requestRoot );\n"
		);
	}

	out.append(
		"\n"
		"\t\t\t// Now send the request to the server.\n"
		"\t\t\t" + package + ".Api.SendRequest(requestDoc, \"" + api + "\",\n"
		"\t\t\t\tcompletionFunction, theThis);\n"
		"\t\t},\n"
		"\n"
	);

	if(m_api_outputs.count(package) > 0){
		twine& t = m_api_outputs[package];
		t.append( out );
	} else {
		m_api_outputs[package] = out;
	}

}

void buildCPPApi(twine api, twine input)
{
	vector<twine> splits = api.split("/");
	twine shortApi = splits[ splits.size() - 1 ];
	twine package = "PACKAGE"; //splits[2];
	size_t howMany = input.get_int();
	if(howMany != 0){
		printf("CPP Api does not support the howMany interface: %s\n", api() );
		return;
	}

	m_api_cpp_header.append(
		"\t\t/** This method will call the " + api + "\n"
		"\t\t  * server API.\n"
		"\t\t  */\n"
		"\t\txmlDocPtr " + shortApi + "( "
	);
	m_api_cpp_body.append( "xmlDocPtr HelixApi::" + shortApi + "( ");
	
	if(input == "NULL"){
		// No inputs.
		m_api_cpp_header.append(");\n\n");
		m_api_cpp_body.append( ")\n"
			"{\n"
			"\tEnEx ee(FL, \"HelixApi::" + shortApi + "( )\");\n\n"
		);
	} else if(input == "ID"){
		m_api_cpp_header.append("int idVal );\n\n");
		m_api_cpp_body.append( "int idVal )\n"
			"{\n"
			"\tEnEx ee(FL, \"HelixApi::" + shortApi + "( int idVal )\");\n\n"
		);
	} else {
		m_api_cpp_header.append("const " + input + "& dataObj );\n\n");
		m_api_cpp_body.append( "const " + input + "& dataObj )\n"
			"{\n"
			"\tEnEx ee(FL, \"HelixApi::" + shortApi + "( const " + input + "& dataObj )\");\n\n"
		);
	}

	m_api_cpp_body.append(
		"\t// First build the request XML Document\n"
		"\tsptr<xmlDoc, xmlFreeDoc> request = xmlNewDoc((const xmlChar*)\"1.0\");\n"
		"\trequest->children = xmlNewDocNode(request, NULL, (const xmlChar*)\"" + shortApi + "\", NULL);\n"
		"\txmlNodePtr root = xmlDocGetRootElement(request);\n"
		"\n"
	);

	if(input == "NULL"){
		// No inputs
	} else if(input == "ID"){
		m_api_cpp_body.append(
			"\tXmlHelpers::setIntAttr(root, \"id\", idVal);\n"
		);
	} else {
		m_api_cpp_body.append(
			"\tdataObj.createXmlNode( root );\n"
		);
	}

	m_api_cpp_body.append(
		"\n"
		"\t// Now send the request to the server.\n"
		"\treturn SendRequest( request, \"" + api + "\");\n"
		"}\n"
		"\n"
	);

}

void initCPPApis()
{
	m_api_cpp_header.append( loadTmpl( "CppApiHeader01.tmpl", NULL ) );

	map<twine, map<twine, twine> >::iterator it;
	for(it = m_data_objects.begin(); it != m_data_objects.end(); it++){
		twine objName = it->first;
		m_api_cpp_header.append("#include <" + objName + ".h>\n" );
	}

	m_api_cpp_header.append( loadTmpl( "CppApiHeader02.tmpl", NULL ) );

	m_api_cpp_body.append( loadTmpl("CppApiBody01.tmpl", NULL ));
}

void createAPIFiles()
{
	map<twine, twine>::iterator it2;
	for(it2 = m_api_outputs.begin(); it2 != m_api_outputs.end(); it2++){
		const twine& package = it2->first;

		try {
			twine header;
			try {
				File apiBase("../qd/common/Api.base");
				header = apiBase.readContentsAsTwine();
			} catch (AnException& e){
				printf("Error reading Api.base for package %s:\n%s", package(), e.Msg() );
				continue;
			}

			header += m_api_outputs[package];
			header.append(
				"\t\t// Dummy function to end the file\n"
				"\t\tDontUseDummyFunction : function ()\n"
				"\t\t{\n"
				"\n"
				"\t\t}\n"
				"\n"
				"\t}\n"
				"});\n"
			);

			twine outputFile = "../qd/common/Api.js";
			File::writeToFile(outputFile, header );

		} catch (AnException& e){
			printf("Error creating Api.js file for package (%s):\n%s", package(), e.Msg() );
		}
	}

	m_api_cpp_header.append( loadTmpl( "CppApiHeader99.tmpl", NULL ) );

	File::writeToFile( "../client/HelixApi.h", m_api_cpp_header );
	File::writeToFile( "../client/HelixApi_Part2.cpp", m_api_cpp_body );
	
}

void beginOutputFile(vector<xmlNodePtr>& statements)
{
	printf("Creating file: (%s) in package (%s)\n", m_currentClass(), m_currentPackage() );
	
	//xmlNodePtr qdRoot = xmlDocGetRootElement(m_namedQueryDoc);
	//xmlNodePtr an_import = xmlNewChild(qdRoot, NULL, (const xmlChar*)"Import", NULL);
	//xmlSetProp(an_import, (const xmlChar*)"name", m_currentPackage + "." + m_currentClass );

	m_output.erase();
	m_output_test.erase();
	m_output_header.erase();
	m_output_test_header.erase();

	beginCPPDataObject(m_currentClass) ;
	beginCPPDataObjectTest( m_currentClass, statements );
	createDataObjectTestXml( m_currentClass, statements );
	
}

void finalizeOutputFile() 
{
	
	twine ifdefName = m_currentClass + "_H";
	twine ifdefTestName = m_currentClass + "_TEST_H";
	ifdefName.ucase();
	ifdefTestName.ucase();

	map<twine, twine> vars;
	vars[ "m_currentClass" ] = m_currentClass;
	vars[ "ifdefName" ] = ifdefName;
	vars[ "ifdefTestName" ] = ifdefTestName;

	m_output_header.append( loadTmpl( "CppObjHeader99.tmpl", &vars ) );
	m_output_test_header.append( loadTmpl( "CppObjTestHeader99.tmpl", &vars ) );

	try {
		twine filename = "../src/" + m_currentPackage;
		twine headername = filename + "/" + m_currentClass + ".h";
		twine headertestname = filename + "/" + m_currentClass + "_test.h";
		twine bodyname = filename + "/" + m_currentClass + ".cpp";
		twine bodytestname = filename + "/" + m_currentClass + "_test.cpp";
		twine dotestinput = filename + "/test/" + m_currentClass + "0001.xml";

		// Check to see if our current file is newer than the .h header.
		// If not, then skip the write as it is not necessary.
		try {
			File source(m_currentFile);
			File target(headername);
			if(source.lastModified() < target.lastModified()){
				// Source is older than the target.  Skip the write.
				//printf("Skipping write for (%s) and (%s)\n", headername(), bodyname());
				//fflush(stdout);
				return;
			}
		} catch (AnException&){
			// Usually because the target does not yet exist.  Ignore this.
		}
		//printf("Writing to (%s)\n", headername());
		//fflush(stdout);
		File::writeToFile(headername, m_output_header);
		File::writeToFile(headertestname, m_output_test_header);
		
		//printf("Writing to (%s)\n", bodyname());
		//fflush(stdout);
		File::writeToFile(bodyname, m_output);
		File::writeToFile(bodytestname, m_output_test);

		// Output the skeleton data object test input file:
		File::EnsurePath( dotestinput );
		//if(!File::Exists( dotestinput ) ){
			xmlSaveFile(dotestinput(), m_output_test_xml);
		//}

		//printf("Finished output for (%s) and (%s)\n", headername(), bodyname());
		//fflush(stdout);
	} catch (AnException& e) {
		printf("Error finalizing file: \n%s\n", e.Msg());
	}
	
}


void buildDataObjects( vector<xmlNodePtr>& statements, vector<xmlNodePtr>& children ) 
{
	for(size_t i = 0; i < statements.size(); i++){
		xmlNodePtr statement = statements[i];
		vector<xmlNodePtr> inputs = XmlHelpers::FindChildren(statement, "Input");
		vector<xmlNodePtr> outputs = XmlHelpers::FindChildren(statement, "Output");
		
		for(size_t j = 0; j < inputs.size(); j++){
			xmlNodePtr var = inputs[j];

			addDataObjectMember( m_currentClass, twine(var, "name"), twine(var, "type") );
		}
		
		for(size_t j = 0; j < outputs.size(); j++){
			xmlNodePtr var = outputs[j];
			twine t2;
			t2.getAttribute(var, "name");
			twine type;
			if(xmlHasProp(var, (const xmlChar*)"type")){
				type.getAttribute(var, "type");
			} else {
				type = "twine";
			}
			if(type == "twine"){
				if(XmlHelpers::getBoolAttr(var, "usecdata")){
					addDataObjectMember( m_currentClass, t2, "cdata");
				} else {
					addDataObjectMember( m_currentClass, t2, "twine");
				}
			} else {
				addDataObjectMember( m_currentClass, t2, type);
			}
		}
	}

	for(size_t i = 0; i < children.size(); i++){
		twine childName( children[i], "name" );
		twine childType( children[i], "type" );

		m_do_children[ m_currentClass ][childName] = childType;
	}
}


void dumpDataObjects() 
{
//map<twine, map<twine, twine> > m_data_objects;

	//printf("m_data_objects.size(): %d\n", m_data_objects.size() );
	map<twine, map<twine, twine> >::iterator it;
	for(it = m_data_objects.begin(); it != m_data_objects.end(); it++){
		twine objName = it->first;

		//dumpJavaDataObject(objName);
		//printf("Dumping JSData Object (%s)\n", objName() );
		dumpJSDataObject(objName);

		map<twine, twine >& objAttrs = m_data_objects[objName];
		map<twine, twine>::iterator it2;
		for(it2 = objAttrs.begin(); it2 != objAttrs.end(); it2++){
			//const twine& attrName = it2->first;
			//printf("objName(%s) attr(%s) = %s\n", objName(), attrName(), objAttrs[attrName]() );
		}

	}

}


void beginCPPDataObject(twine& objName)
{
	map<twine, twine> vars = buildObjectParms( objName );

	m_output_header.append( loadTmpl( "CppObjHeader.start.tmpl", &vars ) );
	m_output.append( loadTmpl("CppObjBody.start.tmpl", &vars ) );

}

void beginCPPDataObjectTest(twine& objName, vector<xmlNodePtr>& statements)
{
	map<twine, twine> vars = buildObjectParms( objName );
	map<twine, twine >& objAttrs = m_data_objects[objName];
	map<twine, twine>::iterator it;
	
	// Override the ifdef name
	twine shortName = objAttrs["short.object.name"];
	twine ifdefName = shortName + "_TEST_H";
	ifdefName.ucase();
	vars[ "ifdefName" ] = ifdefName;

	m_output_test.erase();
	m_output_test_header.erase();

	twine methodNameCheck;
	for(size_t i = 0; i < statements.size(); i++){
		twine methodName( statements[i], "methodName" );
		twine target(statements[i], "target"); 
		if( i == 0 ){
			methodNameCheck.append( 
				"\t\tif( testMethod == \"" + methodName + "\" ){\n"
				"\t\t\t" + methodName + "( ioc, tests[i] );\n"
			);
		} else {
			methodNameCheck.append( 
				"\t\t} else if( testMethod == \"" + methodName + "\" ){\n"
				"\t\t\t" + methodName + "( ioc, tests[i] );\n"
			);
		}
	}
	vars[ "MethodNameCheck" ] = methodNameCheck;

	twine compareMembers;
	for(it = objAttrs.begin(); it != objAttrs.end(); it++){
		const twine& attrName = it->first;
		if(attrName == "do.package.name" || 
			attrName == "js.package.name" ||
			attrName == "short.object.name"
		){
			continue; // skip these.
		}
		twine& attrType = objAttrs[attrName];
		
		if(attrType == "cdata"){
			compareMembers.append("\tif(first->" + attrName + " != second->" + attrName + ") return false;\n");
		} else if(attrType == "base64"){
			compareMembers.append("\tif(first->" + attrName + " != second->" + attrName + ") return false;\n");
		} else if(attrType == "bin"){
			compareMembers.append("\tif(first->" + attrName + " != second->" + attrName + ") return false;\n");
		} else if(attrType == "int"){
			compareMembers.append("\tif(first->" + attrName + " != second->" + attrName + ") return false;\n");
		} else {
			compareMembers.append("\tif(first->" + attrName + " != second->" + attrName + ") return false;\n");
		}
	}
	vars[ "CompareMembers" ] = compareMembers;

	m_output_test_header.append( loadTmpl( "CppObjTestHeader.start.tmpl", &vars ) );
	m_output_test.append( loadTmpl( "CppObjTestBody.start.tmpl", &vars ) );
}

void createDataObjectTestXml( twine& objName, vector<xmlNodePtr>& statements )
{

	if(m_output_test_xml != NULL){
		xmlFreeDoc( m_output_test_xml );
		m_output_test_xml = NULL;
	}

	m_output_test_xml = xmlNewDoc((const xmlChar*)"1.0");
	m_output_test_xml->children = xmlNewDocNode(m_namedQueryDoc, NULL, (const xmlChar*)"DataObjectTest", NULL);
	xmlNodePtr root = xmlDocGetRootElement( m_output_test_xml );
	xmlSetProp( root, (const xmlChar*)"do", objName );
	xmlSetProp( root, (const xmlChar*)"tester", objName + "Test" );

	for(size_t i = 0; i < statements.size(); i++ ){
		twine methodName( statements[i], "methodName" );
		xmlNodePtr test = xmlNewChild( root, NULL, (const xmlChar*)"Test", NULL);
		twine testName; testName.format("test%.4d", i);
		xmlSetProp( test, (const xmlChar*)"name", testName);
		xmlSetProp( test, (const xmlChar*)"method", methodName );
		xmlSetProp( test, (const xmlChar*)"group", (const xmlChar*)"AutoGenerated");

		xmlNodePtr input = xmlNewChild( test, NULL, (const xmlChar*)"Input", NULL);
		xmlNewChild( test, NULL, (const xmlChar*)"Output", NULL);
		xmlNodePtr results = xmlNewChild( test, NULL, (const xmlChar*)"Results", NULL);

		xmlSetProp(results, (const xmlChar*)"success", (const xmlChar*)"false");
		xmlSetProp(results, (const xmlChar*)"savedResults", (const xmlChar*)"0" );
		xmlSetProp(results, (const xmlChar*)"liveResults", (const xmlChar*)"0" );

		// Create an empty input element
		xmlNodePtr inputDO = xmlNewChild( input, NULL, objName, NULL );
		map<twine, twine >& objAttrs = m_data_objects[objName];
		map<twine, twine>::iterator it;
		for(it = objAttrs.begin(); it != objAttrs.end(); it++){
			const twine& attrName = it->first;
			if(attrName == "do.package.name" || 
				attrName == "js.package.name" ||
				attrName == "short.object.name"
			){
				continue; // skip these.
			}
			xmlSetProp( inputDO, attrName, (const xmlChar*)"" );
		}
	}
}

void dumpJavaDataObject(twine& objName)
{
	map<twine, twine >& objAttrs = m_data_objects[objName];
	twine out;
	twine shortName = objAttrs["short.object.name"];

	out.append(
		"/**\n"
		"  * Copyright (c) 2007, 2008, 2009 Hericus Software, LLC\n"
		"  * All rights reserved.\n"
		"  */\n"
		"package " + objAttrs["do.package.name"] + ";\n"
		"\n"
		"import java.sql.Timestamp;\n"
		"import java.util.Vector;\n"
		"\n"
		"import org.w3c.dom.xmlNodePtr;\n"
		"import org.w3c.dom.Node;\n"
		"\n"
		"import com.zed.glob.Xml;\n"
		"import com.zed.logic.sqldo.SqlDataObject;\n"
		"\n"
		"/** Generated SQL Data Object.\n"
		"  *\n"
		"  */\n"
		"public class " + shortName + " extends SqlDataObject {\n"
		"\n"
		"\t/** The name of our object, same as our class name.\n"
		"\t  */\n"
		"\tpublic static final twine OBJECT_NAME = \"" + shortName + "\";\n"
		"\n"
		);

	
	map<twine, twine>::iterator it;
	for(it = objAttrs.begin(); it != objAttrs.end(); it++){
		const twine& attrName = it->first;
		if(attrName == "do.package.name" || 
			attrName == "js.package.name" ||
			attrName == "short.object.name"
		){
			continue; // skip these.
		}
		twine& attrType = objAttrs[attrName];
		
		if(attrType == "cdata"){
			out.append("\tpublic twine " + attrName + ";\n");
		} else if(attrType == "base64"){
			out.append("\tpublic twine " + attrName + ";\n");
		} else if(attrType == "bin"){
			out.append("\tpublic MemBuf " + attrName + ";\n");
		} else {
			out.append("\tpublic " + attrType + " " + attrName + ";\n");
		}
		
	}
	
	out.append(
		"\n"
		"\tpublic " + shortName + "() {\n"
		"\t}\n"
		"\n"
		"\t@Override\n"
		"\tpublic xmlNodePtr createXmlNode(xmlNodePtr parent) throws Exception {\n"
		"\t\txmlNodePtr child = parent.getOwnerDocument().createxmlNodePtr(OBJECT_NAME);\n"
		"\t\tparent.appendChild(child);\n"
		"\n");
	
	for(it = objAttrs.begin(); it != objAttrs.end(); it++){
		const twine& attrName = it->first;
		if(attrName == "do.package.name" || 
			attrName == "js.package.name" ||
			attrName == "short.object.name"
		){
			continue; // skip these.
		}
		twine& attrType = objAttrs[attrName];
		out.append("\t\t" + xmlSetForType(attrName, attrType, "child"));
	}
	
	out.append("\t\treturn child;\n\t}\n\n");
	
	out.append(
		"\t@Override\n"
		"\tpublic void readXmlNode(xmlNodePtr elem) throws Exception {\n"
		"\t\tif(elem.getNodeName().compareTo(OBJECT_NAME) != 0){\n"
		"\t\t\tthrow new Exception(\"Invalid xmlNodePtr (\" + elem.getNodeName() + \") given to \" + OBJECT_NAME + \" to read.\");\n"
		"\t\t}\n"
		"\t\tm_read_from_element = elem; // remember where we read this from\n"
		"\n");
		
	for(it = objAttrs.begin(); it != objAttrs.end(); it++){
		const twine& attrName = it->first;
		if(attrName == "do.package.name" || 
			attrName == "js.package.name" ||
			attrName == "short.object.name"
		){
			continue; // skip these.
		}
		twine& attrType = objAttrs[attrName];
		out.append("\t\t" + xmlGetForType(attrName, attrType, "elem"));
	}
	
	out.append("\t}\n\n");
	
	out.append(
		"\t@Override\n"
		"\tpublic " + shortName + " createFromXmlNode(xmlNodePtr elem) throws Exception {\n"
		"\t\t" + shortName + " ret = new " + shortName + "();\n"
		"\t\tret.readXmlNode(elem);\n"
		"\t\treturn ret;\n"
		"\t}\n"
		"\n"
		"\t/** This will read all child nodes that match our object name, and return\n"
		"\t *  them as a vector of data objects.\n"
		"\t *  \n"
		"\t * @param parent\n"
		"\t * @return\n"
		"\t * @throws Exception\n"
		"\t */ \n"
		"\tpublic Vector<" + shortName + "> readXmlChildren(xmlNodePtr parent) throws Exception {\n"
		"\t\tjava.util.vector<xmlNodePtr> list = XmlHelpers::FindChildren(parent, OBJECT_NAME);\n"
		"\t\tVector<" + shortName + "> v = new Vector<" + shortName + ">();\n"
		"\t\tfor(size_t i = 0; i < list.size(); i++){\n"
		"\t\t\tv.add( createFromXmlNode((xmlNodePtr)list[i]) );\n"
		"\t\t}\n"
		"\t\treturn v;\n"
		"\t}\n"
		"\n"
		"}");
	
	/* FIXME
	try {
		twine filename = "../src/" + objName;
		filename = filename.replaceAll("\\.","/");
		filename = filename + ".java";
		System.out.println("Creating: " + filename);
		FileOutputStream os = new FileOutputStream(new File(filename));
		os.write(out.totwine().getBytes("UTF-8"));
		os.flush();
		os.close();
	} catch (Exception e) {
		e.printStackTrace();
	}
	*/
}

void dumpJSDataObject(twine& objName)
{
	map<twine, twine >& objAttrs = m_data_objects[objName];
	map<twine, twine >& objChildren = m_do_children[objName];
	twine out;
	twine& shortName = objAttrs["short.object.name"];
	twine package = "PACKAGE"; //objAttrs["js.package.name"].split("/")[1];
	//twine filename = "../qd/" + package + "/source/class/" + package + "/sqldo/" + shortName + ".js";
	twine filename = "../qd/common/sqldo/" + shortName + ".js";

	map<twine, twine> vars;
	vars[ "shortName" ] = shortName;
	vars[ "package" ] = package;
	vars[ "filename" ] = filename;

	out.append( loadTmpl( "JsObj01.tmpl", &vars ) );
	
	map<twine, twine>::iterator it;
	bool first = true;
	for(it = objAttrs.begin(); it != objAttrs.end(); it++){
		const twine& attrName = it->first;

		if(attrName == "do.package.name" || 
			attrName == "js.package.name" ||
			attrName == "short.object.name"
		){
			continue; // skip these.
		}
		twine& attrType = objAttrs[attrName];
		if(first){
			first = false;
		} else {
			out.append(",\n");
		}
		out.append("\t\t " + jsPropDefinition(attrName, attrType));
	}
	out.append( loadTmpl( "JsObj02.tmpl", &vars ) );
	for(it = objChildren.begin(); it != objChildren.end(); it++){
		const twine& childName = it->first;
		const twine& childType = it->second;
		out.append(
			"\t\t/** This is an array of child data objects of type " + childType + ".\n"
			"\t\t  */\n"
			"\t\t" + childName + " : [],\n"
			"\n"
		);
	}

	out.append( loadTmpl( "JsObj03.tmpl", &vars ) );
	
	for(it = objAttrs.begin(); it != objAttrs.end(); it++){
		const twine& attrName = it->first;
		if(attrName == "do.package.name" || 
			attrName == "js.package.name" ||
			attrName == "short.object.name"
		){
			continue; // skip these.
		}
		twine& attrType = objAttrs[attrName];
		out.append("\t\t\t" + jsGetForType(attrName, attrType, "elem"));
	}
	
	out.append("\n");
	for(it = objChildren.begin(); it != objChildren.end(); it++){
		const twine& childName = it->first;
		const twine& childType = it->second;
		out.append(
			"\t\t\tthis." + childName + " = PACKAGE.sqldo." + childType + ".readElementChildren( \n"
			"\t\t\t\tPACKAGE.Statics.xmlFindChild( elem, \"" + childName + "\") );\n"
		);
	}

	out.append( loadTmpl("JsObj04.tmpl", &vars ) );
		
	for(it = objAttrs.begin(); it != objAttrs.end(); it++){
		const twine& attrName = it->first;
		if(attrName == "do.package.name" || 
			attrName == "js.package.name" ||
			attrName == "short.object.name"
		){
			continue; // skip these.
		}
		twine& attrType = objAttrs[attrName];
		out.append("\t\t\t" + jsSetForType(attrName, attrType, "subElem") );
	}
	
	out.append("\n");
	for(it = objChildren.begin(); it != objChildren.end(); it++){
		const twine& childName = it->first;
		const twine& childType = it->second;
		out.append(
			"\t\t\tvar subSubElem = doc.createElement(\"" + childName + "\");\n"
			"\t\t\tsubElem.appendChild(subSubElem);\n"
			"\t\t\tPACKAGE.sqldo." + childType + ".writeArray( this." + childName + ", subSubElem );\n"
			"\n"
		);
	}

	out.append( loadTmpl("JsObj05.tmpl", &vars) );
	
	for(it = objAttrs.begin(); it != objAttrs.end(); it++){
		const twine& attrName = it->first;
		if(attrName == "do.package.name" || 
			attrName == "js.package.name" ||
			attrName == "short.object.name"
		){
			continue; // skip these.
		}
		twine ucase = attrName;
		ucase.ucase(0); // uppercase the first letter.

		out.append("\t\t\tnewObj.set" + ucase + "( this.get" + ucase + "() );\n");
	}
	out.append( loadTmpl("JsObj06.tmpl", &vars ) );
	
	try {
		printf("Creating: %s\n", filename());
		File::writeToFile(filename, out);
		
	} catch (AnException& e) {
		printf("Error creating file (%s):\n%s", filename(), e.Msg() );
	}

}


map<twine, twine>& addDataObject( twine& name )
{
	if(name.length() == 0){
		throw AnException(0, FL, "Empty name passed to addDataObject");
	}
	if(m_data_objects.count(name) > 0){
		return m_data_objects[name];
	} else {
		twine dopackage, jspackage;
		dopackage = m_currentPackage;
		jspackage = m_currentPackage;
		map<twine,twine> ret;
		ret[ "short.object.name"] = name;
		ret[ "do.package.name"]  = dopackage;
		ret[ "js.package.name"] = jspackage;
		m_data_objects[name] = ret;
		map<twine,twine> children;
		m_do_children[name] = children;
		return m_data_objects[name];
	}
}

void addDataObjectMember(twine obj_name, twine name, twine datatype)
{
	if(obj_name.length() == 0) return; // bail out early.
	map<twine, twine>& map = addDataObject(obj_name);
	if(map.count(name) > 0 && datatype == "twine"){
		// don't overwrite with just a "twine" datatype.
		return;
	} else {
		if(datatype == "autogen"){
			map[name] = "int";
		} else {
			map[name] = datatype;
		}
	}
}

twine& getDataObjectMemberType(twine& obj_name, twine& name)
{
	if(m_data_objects.count(obj_name) > 0 &&
		m_data_objects[obj_name].count(name) > 0
	){
		return m_data_objects[obj_name][name];
	} else {
		return *( new twine("twine"));
	}
}


void generateExecuteNamedQuery() 
{
	m_output.erase();
	m_output.append(
		"/**\n"
		"  * Copyright (c) 2007, 2008, 2009 Hericus Software, LLC\n"
		"  * All rights reserved.\n"
		"  */\n"
		"package com.zed.logic.utils;\n"
		"\n"
		"import org.w3c.dom.Document;\n"
		"import org.w3c.dom.xmlNodePtr;\n"
		"\n"
		"import com.zed.glob.ActionLogicImplementation;\n"
		"import com.zed.glob.IOConn;\n"
		"import com.zed.glob.log.Log;\n"
	);
	
	vector<xmlNodePtr> imports = XmlHelpers::FindChildren(xmlDocGetRootElement(m_namedQueryDoc), "Import");
	for(size_t i = 0; i < imports.size(); i++){
		xmlNodePtr imp = imports[i];
		twine tmp;
		tmp.getAttribute(imp, "name");
		m_output.append("import " +	tmp + ";\n" );
	}
	
	m_output.append(
		"\n"
		"/**\n"
		"  * Runs a query that has been pre-created on the server, and uses xml to map it's\n"
		"  * input's and outputs.  DO NOT EDIT THIS CLASS BY HAND!\n"
		"  *\n"
		"  * @author Steven M. Cherry\n"
		"  */\n"
		"public class ExecuteNamedQuery implements ActionLogicImplementation {\n"
		"\n"
		"\t/** This will execute the query and return the results to the user. */\n"
		"\tpublic void ExecuteRequest(IOConn ioc) throws Exception {\n"
		"\t\tLog.Trace(\"Enter\");\n"
		"\n"
		"\t\tDocument msg = ioc.GetMsg();\n"
		"\t\txmlNodePtr inputNode = msg.getDocumentxmlNodePtr();\n"
		"\t\tDocument resp = ioc.initializeResponseDocument(\"ExecuteNamedQuery\");\n"
		"\t\txmlNodePtr outputNode = resp.getDocumentxmlNodePtr();\n"
		"\n"
		"\t\ttwine queryName = inputNode.getAttribute(\"queryname\");\n"
		"\t\tif(queryName == NULL || queryName.length() == 0){\n"
		"\t\t\tthrow new Exception(\"Bad Query Name.\");\n"
		"\t\t}\n"
		"\n"
		"\t\toutputNode.setAttribute(\"queryname\", queryName);\n"
		"\n"
		"\t\t// These are the queries that we know about.  If it's not in our list,\n"
		"\t\t// then we'll throw an exception.\n"
	);
			
	vector<xmlNodePtr> methods = XmlHelpers::FindChildren(xmlDocGetRootElement(m_namedQueryDoc), "Method");
	for(size_t i = 0; i < methods.size(); i++){
		xmlNodePtr met = methods[i];
		twine name, clss;
		name.getAttribute(met, "name");
		clss.getAttribute(met, "class");

		if(i == 0){
			m_output.append(
				"\t\tif(queryName.compareTo(\"" + name + "\") == 0){\n"
				"\t\t\t" + clss + "." + name + "XML(ioc, inputNode, outputNode);\n"
			);
		} else {
			m_output.append(
				"\t\t} else if(queryName.compareTo(\"" + name + "\") == 0){\n"
				"\t\t\t" + clss + "." + name + "XML(ioc, inputNode, outputNode);\n"
			);
		}
	}
	
	m_output.append(
		"\t\t} else {\n"
		"\t\t\tthrow new Exception(\"Unknown Named Query: \" + queryName);\n"
		"\t\t}\n"
		"\t\t\n"
		"\t\t// Send the response back:\n"
		"\t\tioc.SendReturn();\n"
		"\t\tioc.Close();\n"
		"\t\t\n"
		"\t\tLog.Trace(\"Exit\");\n"
		"\t}\n"
		"}\n"
	);
	
	/* FIXME:
	try {
		twine filename = "src/com.zed.logic.utils";
		filename = filename.replaceAll("\\.", "/");
		filename = filename + File.separator + "ExecuteNamedQuery.java";
		
		FileOutputStream os = new FileOutputStream(new File(filename));
		os.write(m_output.totwine().getBytes("UTF-8"));
		os.flush();
		os.close();
	} catch (Exception e) {
		e.printStackTrace();
	}
	*/
	
}


twine logExplain( const twine& stmt ) 
{
	return 
	"\t\tif(Log.Sql()){\n"
	"\t\t\t" + m_currentClass + ".doExplainPlan(ioc, \"" + stmt + "\" );\n"
	"\t\t}\n";
	
}

map<twine, twine> buildObjectParms( twine& objName )
{
	map<twine, twine >& objAttrs = m_data_objects[objName];
	map<twine, twine >& objChildren = m_do_children[objName];
	map<twine, twine>::iterator it;
	
	twine out;
	twine shortName = objAttrs["short.object.name"];
	twine ifdefName = shortName + "_H";
	ifdefName.ucase();
	twine shortPackage = m_currentPackage.split("/")[1];

	map<twine, twine> vars;
	vars[ "shortName" ] = shortName;
	vars[ "ifdefName" ] = ifdefName;
	vars[ "shortPackage" ] = shortPackage;
	vars[ "m_currentFile" ] = m_currentFile;


	twine childObjectIncludes;
	for(it = objChildren.begin(); it != objChildren.end(); it++){
		//const twine& childName = it->first;
		const twine& childType = it->second;
		childObjectIncludes.append("#include \"" + childType + ".h\"\n");
	}
	vars[ "ChildObjectIncludes" ] = childObjectIncludes;

	twine defineDataMembers;
	for(it = objAttrs.begin(); it != objAttrs.end(); it++){
		const twine& attrName = it->first;
		if(attrName == "do.package.name" || 
			attrName == "js.package.name" ||
			attrName == "short.object.name"
		){
			continue; // skip these.
		}
		twine& attrType = objAttrs[attrName];
		
		if(attrType == "cdata"){
			defineDataMembers.append("\t\ttwine " + attrName + ";\n");
		} else if(attrType == "base64"){
			defineDataMembers.append("\t\ttwine " + attrName + ";\n");
		} else if(attrType == "bin"){
			defineDataMembers.append("\t\tMemBuf " + attrName + ";\n");
		} else if(attrType == "int"){
			defineDataMembers.append("\t\tintptr_t " + attrName + ";\n");
		} else {
			defineDataMembers.append("\t\t" + attrType + " " + attrName + ";\n");
		}
	}
	vars[ "DefineDataMembers" ] = defineDataMembers;

	twine childVectorDefines;
	for(it = objChildren.begin(); it != objChildren.end(); it++){
		const twine& childName = it->first;
		const twine& childType = it->second;
		childVectorDefines.append("\t\t" + childType + "_svect " + childName + ";\n");
	}
	vars[ "ChildVectorDefines" ] = childVectorDefines;

	twine memberCopyStatements;
	for(it = objAttrs.begin(); it != objAttrs.end(); it++){
		const twine& attrName = it->first;
		if(attrName == "do.package.name" || 
			attrName == "js.package.name" ||
			attrName == "short.object.name"
		){
			continue; // skip these.
		}
		//twine& attrType = objAttrs[attrName];

		memberCopyStatements.append("\t" + attrName + " = c." + attrName + ";\n");
	}
	for(it = objChildren.begin(); it != objChildren.end(); it++){
		const twine& childName = it->first;
		const twine& childType = it->second;
		memberCopyStatements.append(
			"\t" + childName + " = new vector<" + childType + "*>();\n"
			"\tfor(size_t i = 0; i < c." + childName + "->size(); i++){\n"
			"\t\t" + childName + "->push_back( new " + childType + "( *(c." + childName + "->at( i )) ) );\n"
			"\t}\n"
		);
	}
	vars[ "MemberCopyStatements" ] = memberCopyStatements;

	twine memberInitStatements;
	for(it = objAttrs.begin(); it != objAttrs.end(); it++){
		const twine& attrName = it->first;
		if(attrName == "do.package.name" || 
			attrName == "js.package.name" ||
			attrName == "short.object.name"
		){
			continue; // skip these.
		}
		twine& attrType = objAttrs[attrName];
		if(attrType == "int"){
			memberInitStatements.append("\t" + attrName + " = 0;\n");
		} else if(attrType == "float"){
			memberInitStatements.append("\t" + attrName + " = 0.0f;\n");
		} else if(attrType == "twine" ||
				attrType == "cdata" ||
				attrType == "base64" ||
				attrType == "bin"
		){
			memberInitStatements.append("\t" + attrName + ".erase();\n");
		}
	}
	for(it = objChildren.begin(); it != objChildren.end(); it++){
		const twine& childName = it->first;
		const twine& childType = it->second;
		memberInitStatements.append(
			"\t" + childName + " = new vector<" + childType + "*>();\n"
		);
	}
	vars[ "MemberInitStatements" ] = memberInitStatements;

	twine memberCheckSizeStatements;
	for(it = objAttrs.begin(); it != objAttrs.end(); it++){
		const twine& attrName = it->first;
		if(attrName == "do.package.name" || 
			attrName == "js.package.name" ||
			attrName == "short.object.name"
		){
			continue; // skip these.
		}
		twine& attrType = objAttrs[attrName];
		if(attrType == "twine" ||
			attrType == "cdata" ||
			attrType == "base64"
		){
			memberCheckSizeStatements.append(
				//"\tDEBUG(FL, \"Checking size for member: %s\", \"" + attrName + "\");\n"
				"\t" + attrName + ".check_size();\n"
				"\t" + attrName + ".rtrim();\n"
			);
		}
	}
	vars[ "MemberCheckSizeStatements" ] = memberCheckSizeStatements;

	twine xmlReadMembers;
	for(it = objAttrs.begin(); it != objAttrs.end(); it++){
		const twine& attrName = it->first;
		if(attrName == "do.package.name" || 
			attrName == "js.package.name" ||
			attrName == "short.object.name"
		){
			continue; // skip these.
		}
		twine& attrType = objAttrs[attrName];

		xmlReadMembers.append("\t" + xmlGetForType(attrName, attrType, "node") );
	}
	for(it = objChildren.begin(); it != objChildren.end(); it++){
		const twine& childName = it->first;
		const twine& childType = it->second;
		xmlReadMembers.append(
			"\t" + childName + " = " + childType + "::readXmlChildren( XmlHelpers::FindChild( node, \"" + childName + "\") );\n"
		);
	}
	vars[ "XmlReadMembers" ] = xmlReadMembers;

	twine xmlWriteMembers;
	for(it = objAttrs.begin(); it != objAttrs.end(); it++){
		const twine& attrName = it->first;
		if(attrName == "do.package.name" || 
			attrName == "js.package.name" ||
			attrName == "short.object.name"
		){
			continue; // skip these.
		}
		twine& attrType = objAttrs[attrName];

		xmlWriteMembers.append("\t" + xmlSetForType(attrName, attrType, "child") );
	}
	for(it = objChildren.begin(); it != objChildren.end(); it++){
		const twine& childName = it->first;
		const twine& childType = it->second;
		xmlWriteMembers.append(
			"\txmlNodePtr " + childName + "_node = xmlNewChild(child, NULL, (const xmlChar*)\"" +
				childName + "\", NULL);\n"
			"\t" + childType + "::createXmlChildren( " + childName + "_node, " + childName + " );\n"
			"\n"
		);
	}
	vars[ "XmlWriteMembers" ] = xmlWriteMembers;

	return vars;
}

map<twine, twine> buildStatementParms( xmlNodePtr stmt )
{
	vector<xmlNodePtr> outputs = XmlHelpers::FindChildren(stmt, "Output");
	vector<xmlNodePtr> inputs = XmlHelpers::FindChildren(stmt, "Input");

	twine comment = XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Comment") );
	twine sql = XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Sql") );
	twine methodName( stmt, "methodName" );
	twine target(stmt, "target"); 

	map<twine, twine> vars;
	vars[ "doName" ] = m_currentClass;
	vars[ "comment" ] = comment;
	vars[ "sql" ] = sql;
	vars[ "methodName" ] = methodName;
	vars[ "flatSql" ] = flattenSql(stmt);

	twine typedParms;
	twine untypedParms;
	for(size_t i = 0; i < inputs.size(); i++){
		xmlNodePtr input = inputs[i];
		typedParms.append(paramForType(twine(input, "name"), twine(input, "type")) );
		untypedParms.append( ", " + twine(input, "name") );
	}
	vars[ "TypedParms" ] = typedParms;
	vars[ "UntypedParms" ] = untypedParms;
	
	twine odbcBindInputs;
	twine odbcBindObjInputs;
	twine sqldbBindInputs;
	twine sqldbBindObjInputs;
	twine sqldbBindVObjInputs;
	bool has_autogen = false;
	twine autogen_name = "";
	int autogen_offset = 0;
	for(size_t i = 0; i < inputs.size(); i++){
		twine i_1; i_1 = i+1;
		xmlNodePtr input = inputs[i];
		twine inputName( input, "name" );
		twine inputType( input, "type" );

		odbcBindInputs.append( odbcBindInputForType(i+1, inputName, inputType ) );
		sqldbBindInputs.append( odbcBindInputForType4(i+1, inputName, inputType ));
		odbcBindObjInputs.append( odbcBindInputForType2(i+1, inputName, inputType ) );

		if(inputType == "autogen"){
			has_autogen = true;
			autogen_offset = 1;
			autogen_name = inputName;
		} else {
			sqldbBindObjInputs.append( odbcBindInputForType3(i+1 - autogen_offset, inputName, inputType ));
			sqldbBindVObjInputs.append( odbcBindInputForType5(i+1 - autogen_offset, inputName, inputType ));
		}
	}
	vars[ "OdbcBindInputs" ] = odbcBindInputs;
	vars[ "OdbcBindObjInputs" ] = odbcBindObjInputs;
	vars[ "SqlDBBindInputs" ] = sqldbBindInputs;
	vars[ "SqlDBBindObjInputs" ] = sqldbBindObjInputs;
	vars[ "SqlDBBindVObjInputs" ] = sqldbBindVObjInputs;


	if(has_autogen){
		twine recordAutoGenValue;
		twine recordVAutoGenValue;
		recordAutoGenValue.append(
			"\n"
			"\t\t\t// Update the insert object to pick up the new autogen value:\n"
			"\t\t\tobj." + autogen_name + " = sqlite3_last_insert_rowid( db );\n"
		);
		vars[ "RecordAutoGenValue" ] = recordAutoGenValue;
		recordVAutoGenValue.append(
			"\n"
			"\t\t\t\t// Update the insert object to pick up the new autogen value:\n"
			"\t\t\t\tv->at( v_i )->" + autogen_name + " = sqlite3_last_insert_rowid( db );\n"
		);
		vars[ "RecordVAutoGenValue" ] = recordVAutoGenValue;
	} else {
		vars[ "RecordAutoGenValue" ] = "";
		vars[ "RecordVAutoGenValue" ] = "";
	}

	twine sqlReplaceParms;
	twine sqlReplaceObjParms;
	for(size_t i = 0; i < inputs.size(); i++){
		xmlNodePtr input = inputs[i];
		sqlReplaceParms.append(
			"\t// Replace the " + twine(input, "name") + " parameter marker.\n"
			"\tidx = stmt.find('?', idx);\n"
			"\tif(idx != TWINE_NOT_FOUND){\n" +
			replaceInputForType(twine(input, "name"), twine(input, "type")) +
			"\t}\n"
			"\n"
			);
		sqlReplaceObjParms.append(
			"\t// Replace the " + twine(input, "name") + " parameter marker.\n"
			"\tidx = stmt.find('?', idx);\n"
			"\tif(idx != TWINE_NOT_FOUND){\n" +
			replaceInputForType2(twine(input, "name"), twine(input, "type")) +
			"\t}\n"
			"\n"
			);
	}
	vars[ "SqlReplaceParms" ] = sqlReplaceParms;
	vars[ "SqlReplaceObjParms" ] = sqlReplaceObjParms;

	twine inputDOParms;
	for(size_t i = 0; i < inputs.size(); i++){
		inputDOParms.append( ", inputDO." + twine( inputs[i], "name" ) );
	}
	vars[ "InputDOParms" ] = inputDOParms;

	if(target == "sqldb" ){
		vars[ "TestDBConnection" ] = "\tSqlDB& sqldb = TheMain::getInstance()->GetSqlDB(\"hubconfig\");" ;
		vars[ "PrepareDBTest" ] = "";
		vars[ "ExecuteParms" ] = "sqldb";
	} else {
		vars[ "TestDBConnection" ] = "\tOdbcObj& odbc = *ioc.getDBConnection();" ;
		vars[ "PrepareDBTest" ] = 
			"\t// Prepare the statement\n"
			"\ttwine stmt = " + m_currentClass + "::" + methodName + "_prepSQL( ioc" + inputDOParms + ");\n" ;
		vars[ "ExecuteParms" ] = "odbc, stmt, false";
	}

	return vars;
}

void generateReturn(xmlNodePtr stmt)
{

	twine type(stmt, "type");
	twine methodName(stmt, "methodName");

	m_output.append(
		"\t/** This is a RETURN method.  It is designed to run a single select\n"
		"\t  * statement that queries for a single value.  It will then return\n"
		"\t  * that value from the method.  Good examples for uses of this \n"
		"\t  * method type are \"select count(*) from ...\" statements.\n"
		"\t  * <P>\n"
		"\t  * Developer Comments:\n"
		"\t  * <P>" + XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Comment") ) + "\n"
		"\t  * <P>\n"
		"\t  * Sql Statement:\n"
		"\t  * <pre>" + XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Sql") ) + "\n"
		"\t  * </pre>\n"
		"\t  */\n"
		"\tpublic static " + type + " " + methodName +
		"(IOConn ioc" );
	
	vector<xmlNodePtr> inputs = XmlHelpers::FindChildren(stmt, "Input");
	for(size_t i = 0; i < inputs.size(); i++){
		m_output.append(", " + convertArg(inputs[i]) + " " + twine(inputs[i], "name") );
	}
	m_output.append(") throws Exception {\n");

	m_output.append(
		"\t\tLog.Trace(\"Enter\");\n"
		"\t\tConnection con = ioc.getDBConnection();\n"
		"\t\tif(con == NULL){\n"
		"\t\t\tLog.Error(\"Error acquiring DB connection!\");\n"
		"\t\t\tthrow new Exception(\"Error acquiring DB connection!\");\n"
		"\t\t}\n"
		"\t\tLog.Debug(\"%s\", \"" + flattenSql(stmt) + "\");\n" +
		logExplain( flattenSql(stmt) ) +
		"\t\tPreparedStatement stmt = con.prepareStatement(\"" + flattenSql(stmt) + "\");\n" );
	
	for(size_t i = 0; i < inputs.size(); i++){
		twine i_1; i_1 = i+1;
		xmlNodePtr input = inputs[i];
		twine inputName(input, "name");
		m_output.append(
			"\t\tLog.Debug(\"Setting input (%d) to value: %s\", " + i_1 + ", \"\" + " + inputName + ");\n"
			"\t\tstmt.set" + convertType(input) + "( " + i_1 + ", " + inputName + " );\n" );
	}
	
	m_output.append(
		"\t\tstmt.execute();\n"
		"\t\tResultSet rs = stmt.getResultSet();\n"
		"\t\t" + type + " ret;\n"
		"\t\tif(rs.next()){\n"
		"\t\t\tret = rs.get" + convertType(stmt) + "(1);\n"
		"\t\t} else {\n"
		"\t\t\tret = " + NULLForType(stmt) + "; // no result set.\n"
		"\t\t}\n"
		"\t\trs.close();\n"
		"\t\tstmt.close();\n"
		"\t\tLog.Trace(\"Exit\");\n"
		"\t\treturn ret;\n" );

	
	m_output.append(
		"\t}\n"
		"\n" );
}

void generateReturnXML(xmlNodePtr stmt)
{
	m_output.append(
		"\t/** This is a RETURN method.  It is designed to run a single select\n"
		"\t  * statement that queries for a single value.  It will then return\n"
		"\t  * that value from the method.  Good examples for uses of this \n"
		"\t  * method type are \"select count(*) from ...\" statements.\n"
		"\t  * <P>\n"
		"\t  * Developer Comments:\n"
		"\t  * <P>" + XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Comment") ) + "\n"
		"\t  * <P>\n"
		"\t  * Sql Statement:\n"
		"\t  * <pre>" + XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Sql") ) + "\n"
		"\t  * </pre>\n"
		"\t  */\n"
		"\tpublic static void " + twine(stmt, "methodName") + "XML"
		"(IOConn ioc, xmlNodePtr inputNode, xmlNodePtr outputNode) throws Exception {\n" );
	
	vector<xmlNodePtr> inputs = XmlHelpers::FindChildren(stmt, "Input");

	m_output.append(
		"\t\tLog.Trace(\"Enter\");\n"
		"\t\tConnection con = ioc.getDBConnection();\n"
		"\t\tif(con == NULL){\n"
		"\t\t\tLog.Error(\"Error acquiring DB connection!\");\n"
		"\t\t\tthrow new Exception(\"Error acquiring DB connection!\");\n"
		"\t\t}\n"
		"\t\tLog.Debug(\"%s\", \"" + flattenSql(stmt) + "\");\n" +
		logExplain( flattenSql(stmt) ) +
		"\t\tPreparedStatement stmt = con.prepareStatement(\"" + flattenSql(stmt) + "\");\n" );
	
	for(size_t i = 0; i < inputs.size(); i++){
		twine i_1; i_1 = i+1;
		xmlNodePtr input = inputs[i];
		m_output.append(
			"\t\txmlNodePtr input_" + i_1 + " = (xmlNodePtr)XmlHelpers::FindChildWithAttribute(inputNode, \"Input\", \"name\", \"" + twine(input, "name") + "\");\n"
			"\t\tif(input_" + i_1 + " == NULL || input_" + i_1 + ".getAttribute(\"value\") == NULL){\n"
			"\t\t\tthrow new Exception(\"Missing input element for input parameter: " + twine(input, "name") + "\");\n"
			"\t\t}\n"
			"\t\t// Check to see if the input variables are referencing stored session variables.\n"
			"\t\tif( input_" + i_1 + ".getAttribute(\"value\").startsWith(\"${\") ) {\n"
			"\t\t\t// It's a stored session variable.\n"
			"\t\t\tSessionInfo si = SessionList.getInstance().getSession( ioc.getSessionID() );\n"
			"\t\t\ttwine name = input_" + i_1 + ".getAttribute(\"value\");\n"
			"\t\t\tname = name.substring(2, name.length() - 1);\n"
			"\t\t\ttwine value = si.userProperties.get(name);\n"
			"\t\t\tif(value != NULL && value.length() != 0){\n"
			"\t\t\t\tLog.Debug(\"Setting input (%d) from session variable (%s) with value (%s)\", " + i_1 + ", name, value);\n"
			"\t\t\t\tstmt.settwine( " + i_1 + ", value );\n"
			"\t\t\t} else {\n"
			"\t\t\t\t// If it doesn't exist, default it's value to -1.\n"
			"\t\t\t\tLog.Debug(\"Setting input (%d) from session variable (%s) with bogus value -1\", " + i_1 + ", name, value);\n"
			"\t\t\t\tstmt.settwine( " + i_1 + ", \"-1\");\n"
			"\t\t\t}\n"
			"\t\t} else {\n"
			"\t\t\t// It's a direct value.\n"
			"\t\t\tLog.Debug(\"Setting input (%d) directly from xml input value (%s)\", " + i_1 + ", input_" + i_1 + ".getAttribute(\"value\") );\n"
			"\t\t\tstmt.settwine( " + i_1 + ", input_" + i_1 + ".getAttribute(\"value\") );\n"
			"\t\t}\n"
			"\n");
	}
	
	m_output.append(
		"\t\tstmt.execute();\n"
		"\t\tResultSet rs = stmt.getResultSet();\n"
		"\t\tif(rs.next()){\n"
		"\t\t\toutputNode.setAttribute(\"return\", rs.gettwine(1) );\n"
		"\t\t} else {\n"
		"\t\t\toutputNode.setAttribute(\"return\", \"" + NULLForType(stmt) + "\" ); // no result set.\n"
		"\t\t}\n"
		"\t\trs.close();\n"
		"\t\tstmt.close();\n"
		"\t\tLog.Trace(\"Exit\");\n" );
	
	m_output.append(
		"\t}\n"
		"\n" );
}

void generateReturnDO(xmlNodePtr stmt)
{
	twine doName(stmt, "childNodeName"); 
	if( doName.length() == 0){
		return; // If there's no Data Object given, skip generating this.
	}
	twine doPackage(m_root, "dopackage");
	doName = doPackage + "." + doName;

	m_output.append(
		"\t/** This is a RETURN method.  It is designed to run a single select\n"
		"\t  * statement that queries for a single value.  It will then return\n"
		"\t  * that value from the method.  Good examples for uses of this \n"
		"\t  * method type are \"select count(*) from ...\" statements.\n"
		"\t  * <P>\n"
		"\t  * Developer Comments:\n"
		"\t  * <P>" + XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Comment") ) + "\n"
		"\t  * <P>\n"
		"\t  * Sql Statement:\n"
		"\t  * <pre>" + XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Sql") ) + "\n"
		"\t  * </pre>\n"
		"\t  */\n"
		"\tpublic static void " + twine(stmt, "methodName") + "DO"
		"(IOConn ioc, " + doName + " dataObj) throws Exception {\n" );
	
	vector<xmlNodePtr> inputs = XmlHelpers::FindChildren(stmt, "Input");

	m_output.append(
		"\t\tLog.Trace(\"Enter\");\n"
		"\t\tConnection con = ioc.getDBConnection();\n"
		"\t\tif(con == NULL){\n"
		"\t\t\tLog.Error(\"Error acquiring DB connection!\");\n"
		"\t\t\tthrow new Exception(\"Error acquiring DB connection!\");\n"
		"\t\t}\n"
		"\t\tLog.Debug(\"%s\", \"" + flattenSql(stmt) + "\");\n" +
		logExplain( flattenSql(stmt) ) +
		"\t\tPreparedStatement stmt = con.prepareStatement(\"" + flattenSql(stmt) + "\");\n" );
	
	for(size_t i = 0; i < inputs.size(); i++){
		twine i_1; i_1 = i+1;
		xmlNodePtr input = inputs[i];
		m_output.append(
			"\t\tLog.Debug(\"Setting input (%d) to value: %s\", " + i_1 + ", \"\" + dataObj." + twine(input, "name") + ");\n"
			"\t\tstmt.set" + convertType(input) + "( " + i_1 + ", dataObj." + twine(input, "name") + " );\n" );
	}
	
	m_output.append(
		"\t\tstmt.execute();\n"
		"\t\tResultSet rs = stmt.getResultSet();\n"
		"\t\tif(rs.next()){\n"
		"\t\t\toutputNode.setAttribute(\"return\", rs.gettwine(1) );\n"
		"\t\t} else {\n"
		"\t\t\toutputNode.setAttribute(\"return\", \"" + NULLForType(stmt) + "\" ); // no result set.\n"
		"\t\t}\n"
		"\t\trs.close();\n"
		"\t\tstmt.close();\n"
		"\t\tLog.Trace(\"Exit\");\n" );
	
	m_output.append(
		"\t}\n"
		"\n" );
}

void generateUpdateDO(xmlNodePtr stmt)
{
	map<twine, twine> vars = buildStatementParms( stmt );

	m_output.append( loadTmpl("CppObjBody.update.tmpl", &vars ) );
	m_output_header.append( loadTmpl("CppObjHeader.update.tmpl", &vars ) );
}

void generateUpdateDOSqlDB(xmlNodePtr stmt)
{
	map<twine, twine> vars = buildStatementParms( stmt );

	m_output.append( loadTmpl("CppObjBody.update.sqldb.tmpl", &vars ) );
	m_output_header.append( loadTmpl("CppObjHeader.update.sqldb.tmpl", &vars ) );
}

void generateUpdateDOTest(xmlNodePtr stmt)
{
	map<twine, twine> vars = buildStatementParms( stmt );

	m_output.append( loadTmpl("CppObjTestBody.update.tmpl", &vars ) );
	m_output_header.append( loadTmpl("CppObjTestHeader.update.tmpl", &vars ) );
}

void generateInsertDO(xmlNodePtr stmt)
{
	map<twine, twine> vars = buildStatementParms( stmt );

	m_output.append( loadTmpl("CppObjBody.insert.tmpl", &vars ) );
	m_output_header.append( loadTmpl("CppObjHeader.insert.tmpl", &vars ) );
}

void generateInsertDOSqlDB(xmlNodePtr stmt)
{
	map<twine, twine> vars = buildStatementParms( stmt );

	m_output.append( loadTmpl("CppObjBody.insert.sqldb.tmpl", &vars ) );
	m_output_header.append( loadTmpl("CppObjHeader.insert.sqldb.tmpl", &vars ) );

}

void generateInsertDOTest(xmlNodePtr stmt)
{
	map<twine, twine> vars = buildStatementParms( stmt );

	m_output.append( loadTmpl("CppObjTestBody.insert.tmpl", &vars ) );
	m_output_header.append( loadTmpl("CppObjTestHeader.insert.tmpl", &vars ) );
}

void generateDeleteDO(xmlNodePtr stmt)
{
	map<twine, twine> vars = buildStatementParms( stmt );

	m_output.append( loadTmpl("CppObjBody.delete.tmpl", &vars ) );
	m_output_header.append( loadTmpl("CppObjHeader.delete.tmpl", &vars ) );
}

void generateDeleteDOSqlDB(xmlNodePtr stmt)
{
	map<twine, twine> vars = buildStatementParms( stmt );

	m_output.append( loadTmpl("CppObjBody.delete.sqldb.tmpl", &vars ) );
	m_output_header.append( loadTmpl("CppObjHeader.delete.sqldb.tmpl", &vars ) );
}

void generateDeleteDOTest(xmlNodePtr stmt)
{
	map<twine, twine> vars = buildStatementParms( stmt );

	m_output.append( loadTmpl("CppObjTestBody.delete.tmpl", &vars ) );
	m_output_header.append( loadTmpl("CppObjTestHeader.delete.tmpl", &vars ) );
}

void generateSelectToDO(xmlNodePtr stmt) 
{
	twine doName = m_currentClass;
	map<twine, twine >& objAttrs = m_data_objects[doName];
	
	vector<xmlNodePtr> outputs = XmlHelpers::FindChildren(stmt, "Output");
	vector<xmlNodePtr> inputs = XmlHelpers::FindChildren(stmt, "Input");


	m_output_header.append(
		"\t\t/** This is a SELECTTODO method.  It is designed to run a single select\n"
		"\t\t  * statement and create a vector of data objects that represent the result set.\n"
		"\t\t  * This method returns the resulting vector of data objects.  If something\n"
		"\t\t  * goes wrong, we will throw a SQLException.\n"
		"\t\t  * <P>\n"
		"\t\t  * Developer Comments:\n"
		"\t\t  * <P>" + XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Comment") ) + "\n"
		"\t\t  * <P>\n"
		"\t\t  * Sql Statement:\n"
		"\t\t  * <pre>" + XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Sql") ) + "\n"
		"\t\t  * </pre>\n"
		"\t\t  * <P>\n"
		"\t\t  * DataObject Attributes Used: <br/>\n"
		"\t\t  * <ul>\n");

	for(size_t i = 0; i < outputs.size(); i++){
		xmlNodePtr output = outputs[i];
		m_output_header.append("\t\t  *   <li>" + twine(output, "name") + "</li>\n" ); 
	}


	m_output_header.append(
		"\t\t  * </ul>\n"
		"\t\t  */\n"
		"\t\tstatic vector<" + doName + "* >* " + twine(stmt, "methodName") + 
		"(OdbcObj& odbc");

	m_output.append(
		"/* ************************************************************************************** */\n"
		"/* This is a SELECTTODO method.  It is designed to run a single select                    */\n"
		"/* statement and create a vector of data objects that represent the result set.           */\n"
		"/* This method returns the resulting vector of data objects.  If something                */\n"
		"/* goes wrong, we will throw a SQLException.                                              */\n"
		"/*                                                                                        */\n"
		"/* Developer Comments:                                                                    */\n"
		"/* " + XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Comment") ) + "\n */\n"
		"/*                                                                                        */\n"
		"/* Sql Statement:                                                                         */\n"
		"/* " + XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Sql") ) + "\n */\n"
		"/*                                                                                        */\n"
		"/* DataObject Attributes Used:\n"
	);

			
	for(size_t i = 0; i < outputs.size(); i++){
		xmlNodePtr output = outputs[i];
		m_output.append("   * " + twine(output, "name") + "\n" ); 
	}

	m_output.append(
		" */\n"
		"/* ************************************************************************************** */\n"
		"vector<" + doName + "* >* " + doName + "::" + twine(stmt, "methodName") + 
		"(OdbcObj& odbc");

	for(size_t i = 0; i < inputs.size(); i++){
		xmlNodePtr input = inputs[i];
		m_output_header.append(paramForType(twine(input, "name"), twine(input, "type")) );
		m_output.append(paramForType(twine(input, "name"), twine(input, "type")) );
	}
	m_output_header.append(");\n");
	m_output.append(")\n");

	m_output.append(
		"{\n"
		"\tEnEx ee(FL, \"" + doName + "::" + twine(stmt, "methodName") + "()\");\n"
		"\n"
		"\ttwine stmt = \"" + flattenSql(stmt) + "\";\n"
		"\n"
		"\treturn " + doName + "::" + twine(stmt, "methodName") + "(odbc, stmt, true"
	);
	for(size_t i = 0; i < inputs.size(); i++){
		xmlNodePtr input = inputs[i];
		m_output.append(", " + twine(input, "name") );
	}
	m_output.append(
		");\n"
		"\n"
		"}\n"
		"\n"
		"/* ************************************************************************************** */\n"
		"/* This one matches the above in functionality, but allows you to pass in the sql         */\n"
		"/* statement and a flag to indicate whether the input parameters will be used.            */\n"
		"/* ************************************************************************************** */\n"
		"vector<" + doName + "* >* " + doName + "::" + twine(stmt, "methodName") + 
		"(OdbcObj& odbc, twine& stmt, bool useInputs"

	);

	m_output_header.append(
		"\n"
		"\t\t/** This one matches the above in functionality, but allows you to pass in\n"
		"\t\t  * the sql statement and a flag to indicate whether the input parameters\n"
		"\t\t  * will be used.\n"
		"\t\t  */\n"
		"\t\tstatic vector<" + doName + "* >* " + twine(stmt, "methodName") + "(OdbcObj& odbc, twine& stmt, bool useInputs"
	);
	for(size_t i = 0; i < inputs.size(); i++){
		xmlNodePtr input = inputs[i];
		m_output_header.append(paramForType(twine(input, "name"), twine(input, "type")) );
		m_output.append(paramForType(twine(input, "name"), twine(input, "type")) );
	}
	m_output_header.append(");\n\n");
	m_output.append(")\n");
	

	m_output.append(
		"{\n"
		"\tEnEx ee(FL, \"" + doName + "::" + twine(stmt, "methodName") + "(twine& stmt, bool useInputs)\");\n"
		"\n"
		"\tif(odbc.isConnected() == 0){\n"
		"\t\tthrow AnException(0, FL, \"OdbcObj passed into " + doName + "::" + twine(stmt, "methodName") + " is not connected.\");\n"
		"\t}\n"
		"\n"
		"\t// Use an sptr to ensure that if this method throws or causes an exception to be\n"
		"\t// thrown the vector wil be cleaned up before leaving this method.\n"
		"\tsptr< vector<" + doName + "* >, " + doName + "::deleteVector> ret = new vector<" + doName + "* >();\n"
		"\n"
		"\t// Use a single local object to handle fetching the data:\n"
		"\t" + doName + " local;\n"
		"\tint sizeof_int = sizeof(intptr_t);     // so that we can have an address of this variable\n"
		"\tint sizeof_float = sizeof(float); // so that we can have an address of this variable\n"
		"\n"
		"\tSQLTRACE(FL, \"Using SQL: %s\", stmt() );\n"
		"\todbc.SetStmt(stmt, SQL_TYPE_SELECT);\n"
		"\n"
		"\tif(useInputs){\n"
	);
	
	for(size_t i = 0; i < inputs.size(); i++){
		twine i_1; i_1 = i+1;
		xmlNodePtr input = inputs[i];

		m_output.append( odbcBindInputForType(i+1, twine(input, "name"), twine(input, "type") )
		);
	}
	
	m_output.append(
		"\t}\n"
		"\n"
		"\t{ // Used for scope for the timing object.\n"
		"\t\tEnEx eeExe(\"" + doName + "::" + twine(stmt, "methodName") + "()-ExecStmt\");\n"
		"\n"
		"\t\t// Execute the statement\n"
		"\t\tDEBUG(FL, \"Executing the statement for " + doName + "::" + twine(stmt, "methodName") + "\");\n"
		"\t\todbc.ExecStmt();\n"
		"\t}\n"
		"\n"
		"\t// Now that we've executed the statement, we'll know how many output columns we have.\n"
		"\t// Grab the column count so that we don't bind invalid output positions.\n"
		"\tint colCount = odbc.GetResultsetColumnCount();\n"
		"\n"
		"\t// Bind the outputs to our single local object.  We can then make copies of it to\n"
		"\t// fill our return vector.\n"
		"\tDEBUG(FL, \"Binding outputs\");\n"
	);
	
	for(size_t i = 0; i < outputs.size(); i++){
		xmlNodePtr output = outputs[i];
		twine i_1; i_1 = (i+1);

		twine memberName(output, "name");
		twine memberType;
		if(objAttrs.count(memberName) > 0){
			memberType = objAttrs[memberName];
		} else {
			memberType = "twine";
		}

		m_output.append(
			"\tif( " + i_1 + " <= colCount ){\n"
			"\t\tDEBUG(FL, \"Binding member %s\", \"" + memberName + "\");\n"
			"\t\t" + odbcBindOutputForType(i+1, memberName, memberType) +
			"\t}\n"
		);
	}
	
	m_output.append(
		"\n"
		"\tint count;\n"
		"\t{ // Used for scope for the timing object.\n"
		"\t\tEnEx eeExe(\"" + doName + "::" + twine(stmt, "methodName") + "()-FetchLoop\");\n"
		"\t\tDEBUG(FL, \"Fetching data...\");\n"
		"\n"
		"\t\twhile( (count = odbc.FetchData()) != 0){\n"
		"\t\t\t// After a fetch, we need to check all of our data sizes:\n"
		"\t\t\tlocal.checkSize();\n"
	);

	m_output.append(
		"\n"
		"\t\t\t" + doName + "* obj = new " + doName + "( local ); // make a copy of what's in local\n"
		"\t\t\tret->push_back(obj); // add it to our return vector\n"
		"\n"
		"\t\t\t// Clean out the values in local:\n"
		"\t\t\tlocal.init();\n"
	);

	m_output.append(
		"\n"
		"\t\t}\n"
		"\t}\n"
		"\n"
		"\t// When we return, ensure that we release the sptr, so that we don't accidentally\n"
		"\t// delete the vector and its contents when leaving this method.\n"
		"\treturn ret.release();\n"
		"}\n"
		"\n" 
	);

	// This is for the "prepare" method which will do the parameter replacement in our
	// code, rather than in the driver code.

	m_output_header.append(
		"\n"
		"\t\t/** This method will do a replacement of all of the parameter markers in\n"
		"\t\t  * the sql statement with the standard parameter list that is defined.\n"
		"\t\t  * This is useful for automatically prepping a SQL statement that doesn't\n"
		"\t\t  * work with parameter markers.\n"
		"\t\t  */\n"
		"\t\tstatic twine " + twine(stmt, "methodName") + "_prepSQL(IOConn& ioc"
	);
	m_output.append(
		"/* ************************************************************************************** */\n"
		"/* This method will do a replacement of all of the parameter markers in                   */\n"
		"/* the sql statement with the standard parameter list that is defined.                    */\n"
		"/* This is useful for automatically prepping a SQL statement that doesn't                 */\n"
		"/* work with parameter markers.                                                           */\n"
		"/* ************************************************************************************** */\n"
		"twine " + doName + "::" + twine(stmt, "methodName") + 
		"_prepSQL(IOConn& ioc"

	);

	for(size_t i = 0; i < inputs.size(); i++){
		xmlNodePtr input = inputs[i];
		m_output_header.append(paramForType(twine(input, "name"), twine(input, "type")) );
		m_output.append(paramForType(twine(input, "name"), twine(input, "type")) );
	}
	m_output_header.append(");\n\n");
	m_output.append(
		")\n"
		"{\n"
		"\tEnEx ee(FL, \"" + doName + "::" + twine(stmt, "methodName") + "_prepSQL()\");\n"
		"\n"
		"\tsize_t idx = 0;\n"
		"\ttwine stmt = \"" + flattenSql(stmt) + "\";\n"
		"\n"
	);
	for(size_t i = 0; i < inputs.size(); i++){
		xmlNodePtr input = inputs[i];
		m_output.append(
			"\t// Replace the " + twine(input, "name") + " parameter marker.\n"
			"\tidx = stmt.find('?', idx);\n"
			"\tif(idx != TWINE_NOT_FOUND){\n" +
			replaceInputForType(twine(input, "name"), twine(input, "type")) +
			"\t}\n"
			"\n"
			);
	}
	m_output.append(
		"\t// Also take a look at the statement and replace any session variables\n"
		"\tStatics::ReplaceSessionVars(ioc, stmt);\n"
		"\n"
		"\treturn stmt;\n"
		"\n"
		"}\n"
		"\n"
	);

	m_output_header.append(
		"\t\t/** This method returns the sql statement that is used by the above functions.\n"
		"\t\t  */\n"
		"\t\tstatic twine " + twine(stmt, "methodName") + "_getSQL() {\n"
		"\t\t\treturn \"" + flattenSql(stmt) + "\";\n"
		"\t\t}\n"
		"\n"
	);


}

void generateSelectToDOSqlDB(xmlNodePtr stmt) 
{
	twine doName = m_currentClass;
	map<twine, twine >& objAttrs = m_data_objects[doName];
	
	vector<xmlNodePtr> outputs = XmlHelpers::FindChildren(stmt, "Output");
	vector<xmlNodePtr> inputs = XmlHelpers::FindChildren(stmt, "Input");


	m_output_header.append(
		"\t\t/** This is a SELECTTODO method.  It is designed to run a single select\n"
		"\t\t  * statement and create a vector of data objects that represent the result set.\n"
		"\t\t  * This method returns the resulting vector of data objects.  If something\n"
		"\t\t  * goes wrong, we will throw a SQLException.\n"
		"\t\t  * <P>\n"
		"\t\t  * Developer Comments:\n"
		"\t\t  * <P>" + XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Comment") ) + "\n"
		"\t\t  * <P>\n"
		"\t\t  * Sql Statement:\n"
		"\t\t  * <pre>" + XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Sql") ) + "\n"
		"\t\t  * </pre>\n"
		"\t\t  * <P>\n"
		"\t\t  * DataObject Attributes Used: <br/>\n"
		"\t\t  * <ul>\n");

	for(size_t i = 0; i < outputs.size(); i++){
		xmlNodePtr output = outputs[i];
		m_output_header.append("\t\t  *   <li>" + twine(output, "name") + "</li>\n" ); 
	}


	m_output_header.append(
		"\t\t  * </ul>\n"
		"\t\t  */\n"
		"\t\tstatic vector<" + doName + "* >* " + twine(stmt, "methodName") + 
		"(SqlDB& sqldb");

	m_output.append(
		"/* ************************************************************************************** */\n"
		"/* This is a SELECTTODO method.  It is designed to run a single select                    */\n"
		"/* statement and create a vector of data objects that represent the result set.           */\n"
		"/* This method returns the resulting vector of data objects.  If something                */\n"
		"/* goes wrong, we will throw a SQLException.                                              */\n"
		"/*                                                                                        */\n"
		"/* Developer Comments:                                                                    */\n"
		"/* " + XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Comment") ) + "\n */\n"
		"/*                                                                                        */\n"
		"/* Sql Statement:                                                                         */\n"
		"/* " + XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Sql") ) + "\n */\n"
		"/*                                                                                        */\n"
		"/* DataObject Attributes Used:\n"
	);

			
	for(size_t i = 0; i < outputs.size(); i++){
		xmlNodePtr output = outputs[i];
		m_output.append("   * " + twine(output, "name") + "\n" ); 
	}

	m_output.append(
		" */\n"
		"/* ************************************************************************************** */\n"
		"vector<" + doName + "* >* " + doName + "::" + twine(stmt, "methodName") + 
		"(SqlDB& sqldb");

	for(size_t i = 0; i < inputs.size(); i++){
		xmlNodePtr input = inputs[i];
		m_output_header.append(paramForType(twine(input, "name"), twine(input, "type")) );
		m_output.append(paramForType(twine(input, "name"), twine(input, "type")) );
	}
	m_output_header.append(");\n");
	m_output.append(")\n");

	m_output.append(
		"{\n"
		"\tEnEx ee(FL, \"" + doName + "::" + twine(stmt, "methodName") + "()\");\n"
		"\n"
		"\ttwine stmt = \"" + flattenSql(stmt) + "\";\n"
		"\n"
		"\treturn " + doName + "::" + twine(stmt, "methodName") + "(sqldb, stmt, true"
	);
	for(size_t i = 0; i < inputs.size(); i++){
		xmlNodePtr input = inputs[i];
		m_output.append(", " + twine(input, "name") );
	}
	m_output.append(
		");\n"
		"\n"
		"}\n"
		"\n"
		"/* ************************************************************************************** */\n"
		"/* This one matches the above in functionality, but allows you to pass in the sql         */\n"
		"/* statement and a flag to indicate whether the input parameters will be used.            */\n"
		"/* ************************************************************************************** */\n"
		"vector<" + doName + "* >* " + doName + "::" + twine(stmt, "methodName") + 
		"(SqlDB& sqldb, twine& stmt, bool useInputs"

	);

	m_output_header.append(
		"\n"
		"\t\t/** This one matches the above in functionality, but allows you to pass in\n"
		"\t\t  * the sql statement and a flag to indicate whether the input parameters\n"
		"\t\t  * will be used.\n"
		"\t\t  */\n"
		"\t\tstatic vector<" + doName + "* >* " + twine(stmt, "methodName") + "(SqlDB& sqldb, twine& stmt, bool useInputs"
	);
	for(size_t i = 0; i < inputs.size(); i++){
		xmlNodePtr input = inputs[i];
		m_output_header.append(paramForType(twine(input, "name"), twine(input, "type")) );
		m_output.append(paramForType(twine(input, "name"), twine(input, "type")) );
	}
	m_output_header.append(");\n\n");
	m_output.append(")\n");
	

	m_output.append(
		"{\n"
		"\tEnEx ee(FL, \"" + doName + "::" + twine(stmt, "methodName") + "(twine& stmt, bool useInputs)\");\n"
		"\n"
		"\tsqlite3* db = sqldb.GetDatabase();\n"
		"\tsqlite3_stmt* db_stmt = NULL;\n"
		"\n"
		"\t// Use an sptr to ensure that if this method throws or causes an exception to be\n"
		"\t// thrown the vector wil be cleaned up before leaving this method.\n"
		"\tsptr< vector<" + doName + "* >, " + doName + "::deleteVector> ret = new vector<" + doName + "* >();\n"
		"\n"
		"\ttry {\n"
		"\t\tint count;\n"
		"\n"
		"\t\tSQLTRACE(FL, \"Using SQL: %s\", stmt() );\n"
		"\t\tsqldb.check_err( sqlite3_prepare( db, stmt(), (int)stmt.length(), &db_stmt, NULL) );\n"
		"\n"
		"\t\tif(useInputs){\n"
	);
	
	for(size_t i = 0; i < inputs.size(); i++){
		twine i_1; i_1 = i+1;
		xmlNodePtr input = inputs[i];

		m_output.append( odbcBindInputForType4(i+1, twine(input, "name"), twine(input, "type") )
		);
	}
	
	m_output.append(
		"\t\t}\n"
		"\n"
		"\t\t{ // Used for scope for the timing object.\n"
		"\t\t\tEnEx eeExe(\"" + doName + "::" + twine(stmt, "methodName") + "()-ExecStmt\");\n"
		"\n"
		"\t\t\t// Execute the statement\n"
		"\t\t\tDEBUG(FL, \"Executing the statement for " + doName + "::" + twine(stmt, "methodName") + "\");\n"
		"\t\t\tcount = sqldb.check_err( sqlite3_step( db_stmt ) );\n"
		"\t\t}\n"
		"\n"
		"\t\t// Now that we've executed the statement, we'll know how many output columns we have.\n"
		"\t\t// Grab the column count so that we don't bind invalid output positions.\n"
		"\t\tint colCount = sqlite3_column_count( db_stmt );\n"
		"\n"
		"\t\twhile( count != 0 ){\n"
		"\t\t\t// Create the new object for this row\n"
		"\t\t\t" + doName + "* obj = new " + doName + "( );\n"
		"\n"
		"\t\t\t// Pick up all of the output columns\n"
	);
	
	for(size_t i = 0; i < outputs.size(); i++){
		xmlNodePtr output = outputs[i];
		twine i_1; i_1 = (i);

		twine memberName(output, "name");
		twine memberType;
		if(objAttrs.count(memberName) > 0){
			memberType = objAttrs[memberName];
		} else {
			memberType = "twine";
		}

		m_output.append(
			"\t\t\tif( " + i_1 + " < colCount ){\n"
			"\t\t\t\t" + odbcBindOutputForType2(i, memberName, memberType) +
			"\t\t\t}\n"
		);
	}
	
	m_output.append(
		"\n"
		"\t\t\t// Add the object to our return vector\n"
		"\t\t\tret->push_back( obj );\n"
		"\n"
		"\t\t\t// Advance to the next row of data\n"
		"\t\t\tcount = sqldb.check_err( sqlite3_step( db_stmt ) );\n"
		"\t\t}\n"
	);

	m_output.append(
		"\n"
		"\t} catch (AnException& e) {\n"
		"\t\t// Ensure that no matter the exception we release the database back to the object.\n"
		"\t\tif(db_stmt != NULL){\n"
		"\t\t\tsqlite3_finalize( db_stmt );\n"
		"\t\t}\n"
		"\t\tsqldb.ReleaseDatabase();\n"
		"\t\tthrow e; // re-throw the exception\n"
		"\t}\n"
		"\n"
		"\t// When we return, ensure that we release the sptr, so that we don't accidentally\n"
		"\t// delete the vector and its contents when leaving this method.\n"
		"\tif(db_stmt != NULL){\n"
		"\t\tsqlite3_finalize( db_stmt );\n"
		"\t}\n"
		"\tsqldb.ReleaseDatabase();\n"
		"\treturn ret.release();\n"
		"}\n"
		"\n" 
	);

	// This is for the "prepare" method which will do the parameter replacement in our
	// code, rather than in the driver code.

	m_output_header.append(
		"\n"
		"\t\t/** This method will do a replacement of all of the parameter markers in\n"
		"\t\t  * the sql statement with the standard parameter list that is defined.\n"
		"\t\t  * This is useful for automatically prepping a SQL statement that doesn't\n"
		"\t\t  * work with parameter markers.\n"
		"\t\t  */\n"
		"\t\tstatic twine " + twine(stmt, "methodName") + "_prepSQL(IOConn& ioc"
	);
	m_output.append(
		"/* ************************************************************************************** */\n"
		"/* This method will do a replacement of all of the parameter markers in                   */\n"
		"/* the sql statement with the standard parameter list that is defined.                    */\n"
		"/* This is useful for automatically prepping a SQL statement that doesn't                 */\n"
		"/* work with parameter markers.                                                           */\n"
		"/* ************************************************************************************** */\n"
		"twine " + doName + "::" + twine(stmt, "methodName") + 
		"_prepSQL(IOConn& ioc"

	);

	for(size_t i = 0; i < inputs.size(); i++){
		xmlNodePtr input = inputs[i];
		m_output_header.append(paramForType(twine(input, "name"), twine(input, "type")) );
		m_output.append(paramForType(twine(input, "name"), twine(input, "type")) );
	}
	m_output_header.append(");\n\n");
	m_output.append(
		")\n"
		"{\n"
		"\tEnEx ee(FL, \"" + doName + "::" + twine(stmt, "methodName") + "_prepSQL()\");\n"
		"\n"
		"\tsize_t idx = 0;\n"
		"\ttwine stmt = \"" + flattenSql(stmt) + "\";\n"
		"\n"
	);
	for(size_t i = 0; i < inputs.size(); i++){
		xmlNodePtr input = inputs[i];
		m_output.append(
			"\t// Replace the " + twine(input, "name") + " parameter marker.\n"
			"\tidx = stmt.find('?', idx);\n"
			"\tif(idx != TWINE_NOT_FOUND){\n" +
			replaceInputForType(twine(input, "name"), twine(input, "type")) +
			"\t}\n"
			"\n"
			);
	}
	m_output.append(
		"\t// Also take a look at the statement and replace any session variables\n"
		"\tStatics::ReplaceSessionVars(ioc, stmt);\n"
		"\n"
		"\treturn stmt;\n"
		"\n"
		"}\n"
		"\n"
	);

	m_output_header.append(
		"\t\t/** This method returns the sql statement that is used by the above functions.\n"
		"\t\t  */\n"
		"\t\tstatic twine " + twine(stmt, "methodName") + "_getSQL() {\n"
		"\t\t\treturn \"" + flattenSql(stmt) + "\";\n"
		"\t\t}\n"
		"\n"
	);


}

void generateSelectToDOTest(xmlNodePtr stmt)
{
	twine doName = m_currentClass;
	twine methodName(stmt, "methodName" );
	twine target(stmt, "target");
	//map<twine, twine >& objAttrs = m_data_objects[doName];
	
	vector<xmlNodePtr> outputs = XmlHelpers::FindChildren(stmt, "Output");
	vector<xmlNodePtr> inputs = XmlHelpers::FindChildren(stmt, "Input");

	m_output_test_header.append(
		"\t\t/** This method will use our input XML document to prepare for and test\n"
		"\t\t  * the " + doName + "." + methodName + " method.  We will use our list of output\n"
		"\t\t  * xml documents to verify the output of this method.  If the list of ourput\n"
		"\t\t  * documents is empty, we will simply ensure that no exceptions are thrown using\n"
		"\t\t  * the given XML input document.\n"
		"\t\t  */\n"
		"\t\tvoid " + methodName + "(IOConn& ioc, xmlNodePtr node);\n"
		"\n"
	);

	m_output_test.append(
		"void " + doName + "Test::" + methodName + "(IOConn& ioc, xmlNodePtr node)\n"
		"{\n"
		"\tEnEx ee(FL, \"" + doName + "Test::" + methodName + "(IOConn& ioc, xmlNodePtr node)\");\n"
		"\n"
		"\txmlNodePtr inputNode = XmlHelpers::FindChild( node, \"Input\" );\n"
		"\txmlNodePtr outputNode = XmlHelpers::FindChild( node, \"Output\" );\n"
		"\txmlNodePtr resultsNode = XmlHelpers::FindChild( node, \"Results\" );\n"
		"\tif(inputNode == NULL){\n"
		"\t\tthrow AnException(0, FL, \"No input node found in " + methodName + " test.\");\n"
		"\t}\n"
		"\tif(outputNode == NULL){\n"
		"\t\tthrow AnException(0, FL, \"No output node found in " + methodName + " test.\");\n"
		"\t}\n"
		"\tif(resultsNode == NULL){\n"
		"\t\t// Add it in:\n"
		"\t\tresultsNode = xmlNewChild( node, NULL, (const xmlChar*)\"Results\", NULL);\n"
		"\t}\n"
		"\n"
		"\t// Pick up our input data object\n"
		"\t" + doName + " inputDO( XmlHelpers::FindChild( inputNode, " + doName + "::Name()() ) );\n"
		"\n"
		"\t// Pick up our list of output objects to be used for verification\n"
		"\t" + doName + "_svect outputs = " + doName + "::readXmlChildren( outputNode );\n"
		"\n"
	);

	if(target == "sqldb" ){
		m_output_test.append(
			"\t// Get a connection to our database:\n"
			"\tSqlDB& sqldb = TheMain::getInstance()->GetSqlDB(\"hubconfig\");\n"
			"\n"
			"\t// Execute the statement:\n"
			"\t" + doName + "_svect vect = " + doName + "::" + methodName + "(sqldb"
		);
		for(size_t i = 0; i < inputs.size(); i++){
			m_output_test.append(
				", inputDO." + twine( inputs[i], "name" )
			);
		}
	} else {

		m_output_test.append(
			"\t// Get a connection to our database:\n"
			"\tOdbcObj& odbc = *ioc.getDBConnection();\n"
			"\n"
			"\t// Prepare and execute the statement\n"
			"\ttwine stmt = " + doName + "::" + methodName + "_prepSQL( ioc"
		);

		for(size_t i = 0; i < inputs.size(); i++){
			m_output_test.append(
				", inputDO." + twine( inputs[i], "name" )
			);
		}

		m_output_test.append(
			" );\n"
			"\t" + doName + "_svect vect = " + doName + "::" + methodName + "( odbc, stmt, false"
		);

		for(size_t i = 0; i < inputs.size(); i++){
			m_output_test.append(
				", inputDO." + twine( inputs[i], "name" )
			);
		}
	}

	m_output_test.append(
		" );\n"
		"\n"
		"\tif(m_recordMode){\n"
		"\t\t// If we are recording, then save our results to the output node.\n"
		"\t\t" + doName + "::createXmlChildren( outputNode, vect );\n"
		"\t} else {\n"
		"\t\t// If we are not recording, then compare the live results to any saved results\n"
		"\t\tbool matches = " + doName + "Test::compareLists( outputs, vect );\n"
		"\t\tXmlHelpers::setBoolAttr( resultsNode, \"success\", matches );\n"
		"\t\tXmlHelpers::setIntAttr( resultsNode, \"savedResults\", outputs->size() );\n"
		"\t\tXmlHelpers::setIntAttr( resultsNode, \"liveResults\", vect->size() );\n"
		"\t}\n"
		"\n"	
		"}\n"
		"\n"
	);
	
}

twine flattenSql(xmlNodePtr stmt)
{
	twine sql = XmlHelpers::getTextNodeValue( XmlHelpers::FindChild(stmt, "Sql") );
	sql.replace('\n', ' ');
	sql.replace('\r', ' ');
	sql.rtrim().ltrim();
	//sql = sql.replaceAll("[ \t]+", " ");
	return sql;
}

twine convertArg(xmlNodePtr e)
{
	twine type(e, "type");
	return convertArg(type);
}

twine convertArg(twine type)
{
	if(type == "cdata"){
		return "twine";
	} else if(type == "base64"){
		return "twine";
	} else if(type == "bin"){
		return "MemBuf";
	} else if(type == "int" || type == "autogen"){
		return "intptr_t";
	} else {
		return type;
	}
}

twine convertType(xmlNodePtr e)
{
	twine type(e, "type");
	return convertType(type);
}

twine convertType(twine type)
{
	if(type == "int" || type == "autogen"){
		return "intptr_t";
	} else if(type == "long"){
		return "long";
	} else if(type == "float"){
		return "float";
	} else if(type == "cdata"){
		return "twine";
	} else if(type == "base64"){
		return "twine";
	} else if(type == "bin"){
		return "MemBuf";
	} else {
		return type;
	}
}

twine NULLForType(xmlNodePtr e)
{
	twine type(e, "type");
	if(type == "int" || type == "autogen"){
		return "0";
	} else if(type == "long"){
		return "0";
	} else {
		return "NULL";
	}
}

twine paramForType(twine name, twine type)
{
	if(
		type == "float" ||
		type == "long"
	){
		return ", " + type + " " + name;
	} else if(type == "int" || type == "autogen" ){
		return ", intptr_t " + name;
	} else {
		// default to twine
		return ", " + type + "& " + name;
	}
}
	

twine odbcBindOutputForType(size_t pos, twine name, twine type)
{
	twine pos_string;
	pos_string = pos;
	if(type == "int" || type == "autogen"){
		return "odbc.BindOutput(" + pos_string + ", &(local." + name + "), &sizeof_int, DB_INT);\n";
	} else if(type == "long"){
		return "odbc.BindOutput(" + pos_string + ", &(local." + name + "), &sizeof_int, DB_INT);\n";
	} else if(type == "float"){
		return "odbc.BindOutput(" + pos_string + ", &(local." + name + "), &sizeof_float, DB_FLOAT);\n";
	} else {
		// default to twine
		return "odbc.BindOutput(" + pos_string + ", local." + name + ");\n";
	}
}

twine odbcBindOutputForType2(size_t pos, twine name, twine type)
{
	twine pos_string;
	pos_string = pos;
	if(type == "int" || type == "autogen"){
		return "obj->" + name + " = sqlite3_column_int( db_stmt, " + pos_string + ");\n";
	} else if(type == "long"){
		return "obj->" + name + " = sqlite3_column_int( db_stmt, " + pos_string + ");\n";
	} else if(type == "float"){
		return "obj->" + name + " = sqlite3_column_float( db_stmt, " + pos_string + ");\n";
	} else {
		// default to twine
		return "obj->" + name + ".set( (const char*)sqlite3_column_text( db_stmt, " + pos_string + "), (size_t)sqlite3_column_bytes(db_stmt, " + pos_string + ") );\n";
	}
}

twine odbcBindInputForType(size_t pos, twine name, twine type)
{
	twine pos_string;
	pos_string = pos;
	if(type == "int" || type == "autogen"){
		return 
			"\t\t\tDEBUG(FL, \"Setting input (%d) to value: %d\", " + pos_string + ", " + name + " );\n"
			"\t\t\todbc.BindInput(" + pos_string + ", &" + name + ", &sizeof_int, DB_INT);\n";
	} else if(type == "long"){
		return 
			"\t\t\tDEBUG(FL, \"Setting input (%d) to value: %ld\", " + pos_string + ", " + name + " );\n"
			"\t\t\todbc.BindInput(" + pos_string + ", &" + name + ", &sizeof_int, DB_INT);\n";
	} else if(type == "float"){
		return 
			"\t\t\tDEBUG(FL, \"Setting input (%d) to value: %f\", " + pos_string + ", " + name + " );\n"
			"\t\t\todbc.BindInput(" + pos_string + ", &" + name + ", &sizeof_float, DB_FLOAT);\n";
	} else {
		// default to twine
		return 
			"\t\t\tDEBUG(FL, \"Setting input (%d) to value: %s\", " + pos_string + ", " + name + "() );\n"
			"\t\t\todbc.BindInput(" + pos_string + ", " + name + ");\n";
	}

}

twine odbcBindInputForType4(size_t pos, twine name, twine type)
{
	twine pos_string;
	pos_string = pos;
	if(type == "int" || type == "autogen"){
		return 
			"\t\t\t\tDEBUG(FL, \"Setting input (%d) to value: %d\", " + pos_string + ", " + name + " );\n"
			"\t\t\t\tsqldb.check_err( sqlite3_bind_int( db_stmt, " + pos_string + ", (int)" + name + ") );\n";
	} else if(type == "long"){
		return 
			"\t\t\t\tDEBUG(FL, \"Setting input (%d) to value: %d\", " + pos_string + ", " + name + " );\n"
			"\t\t\t\tsqldb.check_err( sqlite3_bind_int( db_stmt, " + pos_string + ", (int)" + name + ") );\n";
	} else if(type == "float"){
		return 
			"\t\t\t\tDEBUG(FL, \"Setting input (%d) to value: %f\", " + pos_string + ", " + name + " );\n"
			"\t\t\t\tsqldb.check_err( sqlite3_bind_float( db_stmt, " + pos_string + ", (int)" + name + ") );\n";
	} else {
		// default to twine
		return 
			"\t\t\t\tDEBUG(FL, \"Setting input (%d) to value: %s\", " + pos_string + ", " + name + "() );\n"
			"\t\t\t\tsqldb.check_err( sqlite3_bind_text( db_stmt, " + pos_string + ", " + name + "(), (int)" + name + ".length(), SQLITE_STATIC) );\n";
	}

}

twine replaceInputForType(twine name, twine type)
{
	if(type == "int" || type == "autogen"){
		return 
			"\t\ttwine tmp; tmp = " + name + ";\n"
			"\t\tstmt.replace(idx, 1, tmp);\n";
	} else if(type == "long"){
		return 
			"\t\ttwine tmp; tmp = (int)" + name + ";\n"
			"\t\tstmt.replace(idx, 1, tmp);\n";
	} else if(type == "float"){
		return 
			"\t\ttwine tmp; tmp = " + name + ";\n"
			"\t\tstmt.replace(idx, 1, tmp);\n";
	} else if(type == "bin"){
		return 
			"\t\tstmt.replace(idx, 1, " + name + "() );\n";
	} else {
		// default to twine
		return 
			//"\t\tstmt.replace(idx, 1, \"'\" + " + name + " + \"'\");\n";
			"\t\tstmt.replace(idx, 1, " + name + " );\n";
	}

}

twine replaceInputForType2(twine name, twine type)
{
	if(type == "int" || type == "autogen"){
		return 
			"\t\ttwine tmp; tmp = obj." + name + ";\n"
			"\t\tstmt.replace(idx, 1, tmp);\n";
	} else if(type == "long"){
		return 
			"\t\ttwine tmp; tmp = (int)obj." + name + ";\n"
			"\t\tstmt.replace(idx, 1, tmp);\n";
	} else if(type == "float"){
		return 
			"\t\ttwine tmp; tmp = obj." + name + ";\n"
			"\t\tstmt.replace(idx, 1, tmp);\n";
	} else if(type == "bin"){
		return 
			"\t\tstmt.replace(idx, 1, obj." + name + "() );\n";
	} else {
		// default to twine
		return 
			//"\t\tstmt.replace(idx, 1, \"'\" + " + name + " + \"'\");\n";
			"\t\tstmt.replace(idx, 1, obj." + name + " );\n";
	}

}

twine odbcBindInputForType2(size_t pos, twine name, twine type)
{
	twine pos_string;
	pos_string = pos;
	if(type == "int" || type == "autogen"){
		return 
			"\t\t\tDEBUG(FL, \"Setting input (%d) to value: %d\", " + pos_string + ", obj." + name + " );\n"
			"\t\t\todbc.BindInput(" + pos_string + ", &(obj." + name + "), &sizeof_int, DB_INT);\n";
	} else if(type == "long"){
		return 
			"\t\t\tDEBUG(FL, \"Setting input (%d) to value: %ld\", " + pos_string + ", obj." + name + " );\n"
			"\t\t\todbc.BindInput(" + pos_string + ", &(obj." + name + "), &sizeof_int, DB_INT);\n";
	} else if(type == "float"){
		return 
			"\t\t\tDEBUG(FL, \"Setting input (%d) to value: %f\", " + pos_string + ", obj." + name + " );\n"
			"\t\t\todbc.BindInput(" + pos_string + ", &(obj." + name + "), &sizeof_float, DB_FLOAT);\n";
	} else {
		// default to twine
		return 
			"\t\t\tDEBUG(FL, \"Setting input (%d) to value: %s\", " + pos_string + ", obj." + name + "() );\n"
			"\t\t\todbc.BindInput(" + pos_string + ", obj." + name + ");\n";
	}

}

twine odbcBindInputForType3(size_t pos, twine name, twine type)
{
	twine pos_string;
	pos_string = pos;
	if(type == "int" || type == "autogen"){
		return 
			"\t\t\t\tDEBUG(FL, \"Setting input (%d) to value: %d\", "+ pos_string + ", obj." + name + " );\n"
			"\t\t\t\tsqldb.check_err( sqlite3_bind_int( db_stmt, " + pos_string + ", (int)obj." + name + ") );\n";
	} else if(type == "long"){
		return 
			"\t\t\t\tDEBUG(FL, \"Setting input (%d) to value: %ld\", " + pos_string + ", obj." + name + " );\n"
			"\t\t\t\tsqldb.check_err( sqlite3_bind_int( db_stmt, " + pos_string + ", (int)obj." + name + ") );\n";
	} else if(type == "float"){
		return 
			"\t\t\t\tDEBUG(FL, \"Setting input (%d) to value: %f\", " + pos_string + ", obj." + name + " );\n"
			"\t\t\t\tsqldb.check_err( sqlite3_bind_float( db_stmt, " + pos_string + ", (float)obj." + name + ") );\n";
	} else {
		// default to twine
		return 
			"\t\t\t\tDEBUG(FL, \"Setting input (%d) to value: %s\", " + pos_string + ", obj." + name + "() );\n"
			"\t\t\t\tsqldb.check_err( sqlite3_bind_text( db_stmt, " + pos_string + ", obj." + name + "(), (int)obj." + name + ".length(), SQLITE_STATIC) );\n";
	}

}

twine odbcBindInputForType5(size_t pos, twine name, twine type)
{
	twine pos_string;
	pos_string = pos;
	if(type == "int" || type == "autogen"){
		return 
			"\t\t\t\tDEBUG(FL, \"Setting input (%d) to value: %d\", "+ pos_string + ", v->at( v_i )->" + name + " );\n"
			"\t\t\t\tsqldb.check_err( sqlite3_bind_int( db_stmt, " + pos_string + ", (int)v->at( v_i )->" + name + ") );\n";
	} else if(type == "long"){
		return 
			"\t\t\t\tDEBUG(FL, \"Setting input (%d) to value: %ld\", " + pos_string + ", v->at( v_i )->" + name + " );\n"
			"\t\t\t\tsqldb.check_err( sqlite3_bind_int( db_stmt, " + pos_string + ", (int)v->at( v_i )->" + name + ") );\n";
	} else if(type == "float"){
		return 
			"\t\t\t\tDEBUG(FL, \"Setting input (%d) to value: %f\", " + pos_string + ", v->at( v_i )->" + name + " );\n"
			"\t\t\t\tsqldb.check_err( sqlite3_bind_float( db_stmt, " + pos_string + ", (float)v->at( v_i )->" + name + ") );\n";
	} else {
		// default to twine
		return 
			"\t\t\t\tDEBUG(FL, \"Setting input (%d) to value: %s\", " + pos_string + ", v->at( v_i )->" + name + "() );\n"
			"\t\t\t\tsqldb.check_err( sqlite3_bind_text( db_stmt, " + pos_string + ", v->at( v_i )->" + name + "(), (int)v->at( v_i )->" + name + ".length(), SQLITE_STATIC) );\n";
	}

}

twine xmlSetForType(twine name, twine type, twine elemname)
{
	if(type == "int" || type == "autogen"){
		return "XmlHelpers::setIntAttr(" + elemname + ", \"" + name + "\", " + name + ");\n";
	} else if(type == "long"){
		return "XmlHelpers::setIntAttr(" + elemname + ", \"" + name + "\", (int)" + name + ");\n";
	} else if(type == "float"){
		return "XmlHelpers::setFloatAttr(" + elemname + ", \"" + name + "\", " + name + ");\n";
	} else if(type == "Timestamp"){
		return "XmlHelpers::setTimestampAttr(" + elemname + ", \"" + name + "\", " + name + ");\n";
	} else if(type == "base64"){
		return "XmlHelpers::setBase64(xmlNewChild(" + elemname + ", NULL, (const xmlChar*)\"" + name + "\", NULL), " + name + ");\n";
	} else if(type == "bin"){
		return "XmlHelpers::setBase64(xmlNewChild(" + elemname + ", NULL, (const xmlChar*)\"" + name + "\", NULL), " + name + ");\n";
	} else {
		return "xmlSetProp(" + elemname + ", (const xmlChar*)\"" + name + "\", " + name + ");\n";
	}
}

twine xmlGetForType(twine name, twine type, twine elemname)
{
	if(type == "int" || type == "autogen"){
		return name + " = XmlHelpers::getIntAttr(" + elemname + ", \"" + name + "\");\n";
	} else if(type == "long"){
		return name + " = XmlHelpers::getIntAttr(" + elemname + ", \"" + name + "\");\n";
	} else if(type == "float"){
		return name + " = (float)XmlHelpers::getFloatAttr(" + elemname + ", \"" + name + "\");\n";
	} else if(type == "Timestamp"){
		return name + " = XmlHelpers::getTimestampAttr(" + elemname + ", \"" + name + "\");\n";
	} else if(type == "cdata"){
		return "xmlNodePtr " + name + "_child = XmlHelpers::FindChild(" + elemname + ", \"" + name + "\"); if( " + name + "_child != NULL) " + name + " = XmlHelpers::getCDATASection(" + name + "_child);\n";
	} else if(type == "base64"){
		return "xmlNodePtr " + name + "_child = XmlHelpers::FindChild(" + elemname + ", \"" + name + "\"); if( " + name + "_child != NULL) " + name + " = XmlHelpers::getBase64(" + name + "_child);\n";
	} else if(type == "bin"){
		return "xmlNodePtr " + name + "_child = XmlHelpers::FindChild(" + elemname + ", \"" + name + "\"); if( " + name + "_child != NULL) { " + name + " = XmlHelpers::getCDATASection(" + name + "_child); " + name + ".decode64(); }\n";
	} else {
		return name + ".getAttribute(" + elemname + ", \"" + name + "\");\n";
	}
}

twine jsPropDefinition( twine name, twine type )
{
	if(type == "int" || type == "autogen"){
		return name + " : {init : 0, check : \"Integer\" }" ;
	} else if(type == "long"){
		return name + " : {init : 0, check : \"Number\" }" ;
	} else {
		return name + " : {init : \"\", check : \"String\" }";
	}
}

twine jsGetForType(twine name, twine type, twine elemname)
{
	twine ucase = name;
	ucase.ucase(0);
	if(type == "int" || type == "autogen"){
		return "if(" + elemname + ".getAttribute(\"" + name + "\")){ this.set" + ucase + "( Number(" + elemname + ".getAttribute(\"" + name + "\") ) ); }\n";
	} else if(type == "long"){
		return "if(" + elemname + ".getAttribute(\"" + name + "\")){ this.set" + ucase + "( Number(" + elemname + ".getAttribute(\"" + name + "\") ) ); }\n";
	} else if(type == "Timestamp"){
		return "if(" + elemname + ".getAttribute(\"" + name + "\")){ this.set" + ucase + "( " + elemname + ".getAttribute(\"" + name + "\").substr(0,19) ); }\n";
	} else if(type == "base64" || type == "bin"){
		return 
			"this.set" + ucase + "(\n"
			"\t\t\t\tPACKAGE.Statics.xmlGetBase64(\n"
			"\t\t\t\t\tPACKAGE.Statics.xmlFindChild( " + elemname + ", \"" + name + "\" )\n"
			"\t\t\t\t)\n"
			"\t\t\t);\n";
	} else {
		return "if(" + elemname + ".getAttribute(\"" + name + "\")){ this.set" + ucase + "( " + elemname + ".getAttribute(\"" + name + "\") ); }\n";
	}
}

twine jsSetForType(twine name, twine type, twine elemname)
{
	twine ucase = name;
	ucase.ucase(0);
	if(type == "int" || type == "autogen"){
		return elemname + ".setAttribute( \"" + name + "\", String(this.get" + ucase + "() ) );\n";
	} else if(type == "long"){
		return elemname + ".setAttribute( \"" + name + "\", String(this.get" + ucase + "() ) );\n";
	} else if(type == "cdata"){
		return 
			"var sub = doc.createElement(\"" + name + "\");\n"
			"\t\t\tPACKAGE.Statics.xmlSetCDATASection( sub, this.get" + ucase + "() );\n"
			"\t\t\t" + elemname + ".appendChild( sub );\n";
	} else if(type == "base64" || type == "bin"){
		return 
			"var sub = doc.createElement(\"" + name + "\");\n"
			"\t\t\tPACKAGE.Statics.xmlSetBase64( sub, this.get" + ucase + "() );\n"
			"\t\t\t" + elemname + ".appendChild( sub );\n";
	} else {
		return elemname + ".setAttribute( \"" + name + "\", this.get" + ucase + "() );\n";
	}
}

twine loadTmpl(const twine& tmplName, map<twine, twine>* vars)
{
	if(!File::Exists("../build/" + tmplName)){
		twine err; err.format( "!! Template %s not found !!\n", tmplName() );
		printf("%s", err() );
		return err;
	}
	File tmpl( "../build/" + tmplName );
	vector<twine> lines = tmpl.readLines();
	twine ret;
	for(size_t i = 0; i < lines.size(); i++){
		if(vars == NULL){
			ret += lines[i];
		} else {
			ret += replaceVars( tmplName, i, lines[i], vars );
		}
		ret += "\n";
	}
	return ret;
}

twine replaceVars( const twine& tmplName, size_t lineIdx, twine line, map<twine, twine>* vars )
{
	if(vars == NULL){ // just in case
		return line;
	}
	size_t idx1 = 0, idx2 = 0;
	while(idx1 < line.length() ){
		idx1 = line.find("${", idx1);
		if(idx1 == TWINE_NOT_FOUND){
			break; // nothing to do
		}
		idx1 += 2; // just past ${
		idx2 = line.find("}", idx1);
		if(idx2 == TWINE_NOT_FOUND){
			continue; // nothing to do
		}
		twine varName = line.substr(idx1, idx2-idx1);
		idx1 -= 2; // back to where it was - at ${
		if(vars->count( varName ) != 0){
			line.replace(idx1, idx2-idx1+1, (*vars)[ varName ] );
		} else {
			printf("Template %s: Unknown variable %s referenced on line %d\n",
				tmplName(), varName(), (int)lineIdx );
			idx1 += 2; // past ${
		}
	}

	return line;
}
