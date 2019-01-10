
#include "xml_parse.h"

#include <string.h>
#include <stdlib.h>

void XNP_AddChild(XMLNodeParser * parent, XMLNodeParser * child) {

    if (parent->children == NULL) {
        DEBUG_PRINT("Adding first child to parent\n");
        parent->children = child;
        return;
    }

    XMLNodeParser * current = parent->children;

    while (current->next != NULL) {
        current = current->next;
    }

    DEBUG_PRINT("Adding non-first child to parent\n");
    
    current->next = child;

}

void * XNP_ParseChildren(xmlNode * parent, XMLNodeParser * parser, void * parent_state) {

    // try to parse every child
    for (xmlNode * current = parent->children; current != NULL; current = current->next) {

        if(current->type != XML_ELEMENT_NODE) {
            DEBUG_PRINT("Found node that isn't an element (%s), continuing\n", current->name);
            continue;
        }
        
        XMLNodeParser * parser_child = parser->children;

        // this is never used except for error checking
        void * ret_state = INVALID_NODE_PARSER;

        // try to parse the node until
        while (parser_child && ret_state == INVALID_NODE_PARSER) {
            ret_state = XNP_TryParseNode(current, parser_child, parent_state);
            parser_child = parser_child->next;
        }

        // if the node isn't parsed, and this parser can recurse on itself, try parse
        if(ret_state == INVALID_NODE_PARSER && (parser->flags & SELF_RECURSE)) {
            DEBUG_PRINT("No match found in children, trying to recurse on self\n");
            ret_state = XNP_TryParseNode(current, parser, parent_state);
        }
        
        // if no node parser found, and the caller requested ERROR_ON_UNKNOWN, return error
        if ((ret_state == INVALID_NODE_PARSER) && (parser->flags & ERROR_ON_UNKNOWN)) {
            DEBUG_PRINT("Found unknown node '%s'\n", current->name);
            return FOUND_UNKNOWN_NODE;
        }

        if(parser->flags & RETURN_FIRST_CHILD_STATE) {
            DEBUG_PRINT("Returning first child state\n");
            return ret_state;
        }
        
    }
    
    DEBUG_PRINT("Stopping children parsing\n");
    return PARSER_OK;
}

struct ChildState * XNP_ParseChildren_SaveState(
        xmlNode * parent, XMLNodeParser * parser, void * parent_state) {

    struct ChildState * head = (struct ChildState*)malloc(sizeof(struct ChildState));
    struct ChildState * curr_state = head;
    
    // try to parse every child
    for (xmlNode * current = parent->children; current != NULL; current = current->next) {

        if(current->type != XML_ELEMENT_NODE) {
            DEBUG_PRINT("Found node that isn't an element (%s), continuing\n", current->name);
            continue;
        }
        
        XMLNodeParser * parser_child = parser->children;

        // this is never used except for error checking
        void * ret_state = INVALID_NODE_PARSER;

        // try to parse the node until
        while (parser_child && ret_state == INVALID_NODE_PARSER) {
            ret_state = XNP_TryParseNode(current, parser_child, parent_state);
            parser_child = parser_child->next;
        }

        // if the node isn't parsed, and this parser can recurse on itself, try parse
        if(ret_state == INVALID_NODE_PARSER && (parser->flags & SELF_RECURSE)) {
            DEBUG_PRINT("No match found in children, trying to recurse on self\n");
            ret_state = XNP_TryParseNode(current, parser, parent_state);
        }
        
        // if no node parser found, and the caller requested ERROR_ON_UNKNOWN, return error
        if ((ret_state == INVALID_NODE_PARSER) && (parser->flags & ERROR_ON_UNKNOWN)) {
            DEBUG_PRINT("Found unknown node '%s'\n", current->name);
            return FOUND_UNKNOWN_NODE;
        }

        // if there's no next node, don't malloc
        struct ChildState * next = current->next ?
            (struct ChildState*)malloc(sizeof(struct ChildState)) : NULL;
        
        curr_state->state = ret_state;
        curr_state->next = next;
        curr_state = next;
        
        DEBUG_PRINT("Added child state to list\n");
    }
    
    DEBUG_PRINT("Stopping children parsing\n");
    return head;
}

void * XNP_TryParseNode(xmlNode * node, XMLNodeParser * parser, void * state) {

    DEBUG_PRINT("Trying to parse node '%s' with parser '%s'\n", node->name, parser->node_name);
    
    // if the names don't match, this parser is invalid
    if (strcmp(node->name, parser->node_name) != 0) {
        return INVALID_NODE_PARSER;
    }

    if (parser->parser)
        state = parser->parser(node, state);

    if(parser->flags & AGGREGATE_CHILD_STATE) {
        DEBUG_PRINT("Parsing children with state aggregate\n");
        state = XNP_ParseChildren_SaveState(node, parser, state);
    } else {
        DEBUG_PRINT("Parsing children with no state aggregation\n");
        void * st = XNP_ParseChildren(node, parser, state);
        
        if(parser->flags & RETURN_FIRST_CHILD_STATE) {
            state = st;
        }
    }
    
    return state;

}

void childStateFree(void * ptr) {
    struct ChildState *state = (struct ChildState*)ptr, *last = NULL;
    
    while(state) {
        last = state;
        state = state->next;
        free(last);
    }
}
