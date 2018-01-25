/**
 * section: Parsing
 * synopsis: Parse an XML file to a tree and free it
 * purpose: Demonstrate the use of xmlReadFile() to read an XML file
 *          into a tree and and xmlFreeDoc() to free the resulting tree
 * usage: parse1 test1.xml
 * test: parse1 test1.xml
 * author: Daniel Veillard
 * copy: see Copyright for the status of this software.
 */

#include <stdio.h>
#include <assert.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>
#include <libxml/tree.h>

/**
 * print_element_names:
 * @a_node: the initial xml node to consider.
 *
 * Prints the names of the all the xml elements
 * that are siblings or children of a given xml node.
 */
#define DPRINTF(_str, ...) do { \
	fprintf(stderr, "[%s:%d] "_str, __FILE__, __LINE__, ##__VA_ARGS__); \
	} while(0)

static void
print_element_names(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;

    for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("type: %d, node-name: %s, node-value : %s\n", cur_node->type, cur_node->name, cur_node->children->content);
        }

        print_element_names(cur_node->children);
    }
}

static xmlDocPtr get_xml_doc(const char *filename)
{
    xmlDocPtr doc; /* the resulting document tree */

    doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL) {
        DPRINTF("Failed to parse %s\n", filename);
	exit(1);
    }
    return doc;
}
static void free_xml_doc(xmlDocPtr doc)
{
    xmlFreeDoc(doc);
}

static void usage(const char *name)
{
    DPRINTF("Usage: %s <xml-file> <xpath-expr> <value>\n", name);
}

/**
 * update_xpath_nodes:
 * @nodes:		the nodes set.
 * @value:		the new value for the node(s)
 *
 * Prints the @nodes content to @output.
 */
static void
update_xpath_nodes(xmlNodeSetPtr nodes, const xmlChar* value) {
    int size;
    int i;
    
    assert(value);
    size = (nodes) ? nodes->nodeNr : 0;
    
    /*
     * NOTE: the nodes are processed in reverse order, i.e. reverse document
     *       order because xmlNodeSetContent can actually free up descendant
     *       of the node and such nodes may have been selected too ! Handling
     *       in reverse order ensure that descendant are accessed first, before
     *       they get removed. Mixing XPath and modifications on a tree must be
     *       done carefully !
     */
    for(i = size - 1; i >= 0; i--) {
	assert(nodes->nodeTab[i]);
	
	xmlNodeSetContent(nodes->nodeTab[i], value);
	/*
	 * All the elements returned by an XPath query are pointers to
	 * elements from the tree *except* namespace nodes where the XPath
	 * semantic is different from the implementation in libxml2 tree.
	 * As a result when a returned node set is freed when
	 * xmlXPathFreeObject() is called, that routine must check the
	 * element type. But node from the returned set may have been removed
	 * by xmlNodeSetContent() resulting in access to freed data.
	 * This can be exercised by running
	 *       valgrind xpath2 test3.xml '//discarded' discarded
	 * There is 2 ways around it:
	 *   - make a copy of the pointers to the nodes from the result set 
	 *     then call xmlXPathFreeObject() and then modify the nodes
	 * or
	 *   - remove the reference to the modified nodes from the node set
	 *     as they are processed, if they are not namespace nodes.
	 */
	if (nodes->nodeTab[i]->type != XML_NAMESPACE_DECL)
	    nodes->nodeTab[i] = NULL;
    }
}

/**
 * example4:
 * @filename:		the input XML filename.
 * @xpathExpr:		the xpath expression for evaluation.
 * @value:		the new node content.
 *
 * Parses input XML file, evaluates XPath expression and update the nodes
 * then print the result.
 *
 * Returns 0 on success and a negative value otherwise.
 */
static int 
example4(xmlDocPtr _doc, const char* filename, const xmlChar* xpathExpr, const xmlChar* value) {

    xmlDocPtr doc = _doc;

    xmlXPathContextPtr xpathCtx; 
    xmlXPathObjectPtr xpathObj; 
    
    assert(filename);
    assert(xpathExpr);
    assert(value);

    /* Load XML document */
//     doc = xmlParseFile(filename);
    if (doc == NULL) {
	DPRINTF("Error: unable to parse file \"%s\"\n", filename);
	return(-1);
    }

    /* Create xpath evaluation context */
    xpathCtx = xmlXPathNewContext(doc);
    if(xpathCtx == NULL) {
        DPRINTF("Error: unable to create new XPath context\n");
        xmlFreeDoc(doc); 
        return(-1);
    }
    
    /* Evaluate xpath expression */
    xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
    if(xpathObj == NULL) {
        DPRINTF("Error: unable to evaluate xpath expression \"%s\"\n", xpathExpr);
        xmlXPathFreeContext(xpathCtx); 
        xmlFreeDoc(doc); 
        return(-1);
    }

    /* update selected nodes */
    update_xpath_nodes(xpathObj->nodesetval, value);

    
    /* Cleanup of XPath data */
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx); 

    /* dump the resulting document */
    xmlDocDump(stdout, doc);


    /* free the document */
//     xmlFreeDoc(doc); 
    
    return(0);
}

int main(int argc, char **argv) {

    /* Parse command line and process file */
    if (argc < 2) {
	DPRINTF("Error: wrong number of arguments.\n");
	usage(argv[0]);
	return(-1);
    } 

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    char *filename = argv[1];

    xmlDocPtr doc = NULL; /* the resulting document tree */
    xmlNode *root_element = NULL;

    /* Parse the resource from file or URL
     * need to free the resulting tree
     */
    doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL) {
        DPRINTF("Failed to parse %s\n", filename);
	return -1;
    }
    // TODO 
    // do something with this doc
    /*Get the root element node */
    root_element = xmlDocGetRootElement(doc);

    /* rename the name of a node */
    xmlNodeSetName(root_element, "config2");

    print_element_names(root_element);

    if (example4(doc, argv[1], BAD_CAST argv[2], BAD_CAST argv[3])) {
	return(-1);
    }


    /* 
     * Dumping document to stdio or file
     */
    xmlSaveFormatFileEnc("__new.xml", doc, "UTF-8", 1);

    /*free the document */
    xmlFreeDoc(doc);
    /* Cleanup function for the XML library. */
    xmlCleanupParser();
    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
    return(0);
}
