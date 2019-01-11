/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#ifndef XML_PARSE_H
#define XML_PARSE_H

#include <libxml/tree.h>
#include <libxml/parser.h>

#define PARSER_OK (void*)0
#define INVALID_NODE_PARSER (void*)-1
#define FOUND_UNKNOWN_NODE (void*)-2

#define NO_FLAGS 0
#define ERROR_ON_UNKNOWN 0b1
#define RETURN_FIRST_CHILD_STATE 0b10

// Has priority over RETURN_FIRST_CHILD_STATE
#define AGGREGATE_CHILD_STATE 0b100

// When set, the parser will be able to recurse almost-infinitely (due to finite stack size)
#define SELF_RECURSE 0b1000

#ifdef DEBUG
#include <stdio.h>
#define DEBUG_PRINT(a...) printf(a)
#endif
#ifndef DEBUG
#define DEBUG_PRINT(a...)
#endif

typedef void* (*NodeAcceptor) (xmlNode * node, void * state);

typedef struct _xmlnodeparser {
    const char * node_name;
    NodeAcceptor parser;

    int flags;

    struct _xmlnodeparser *children, *next;
} XMLNodeParser;

struct ChildState {
    void * state;
    struct ChildState * next;
};

void XNP_AddChild(XMLNodeParser * parent, XMLNodeParser * child);
void * XNP_ParseChildren(xmlNode * parent, XMLNodeParser * parser, void * parent_state);
struct ChildState * XNP_ParseChildren_SaveState(
        xmlNode * parent, XMLNodeParser * parser, void * parent_state);
void * XNP_TryParseNode(xmlNode * node, XMLNodeParser * parser, void * state);


#endif /* XML_PARSE_H */

