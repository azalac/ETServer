/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "data.h"
#include "xml_parse.h"

#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void * parse_bone(xmlNode * node, void * state);

void * parse_rotation_axis(xmlNode * node, void * state);

void ResolveIDs(BonePrototype * root, int * bone_count);

/**
 * Parses a double from a string.
 * @param str The string
 * @param ptr The double pointer
 * @return 1 on error, 0 if successful
 */
int parse_double(const char * str, double * ptr) {
    char * end;

    double val = strtod(str, &end);

    if (*end != 0) {
        return 1;
    }

    *ptr = val;
    return 0;
}

int stricmp(const char * one, const char * two) {
    while (*one && *two) {
        int diff = tolower(*one) - tolower(*two);
        if (diff != 0) {
            return diff;
        }
        one++;
        two++;
    }
    return 0;
}

int init_bone_structure(const char * definition_file, BonePrototype ** proto) {

    // =========== PARSER SETUP =============

    XMLNodeParser bone_parser = {0};

    bone_parser.node_name = "bone";
    bone_parser.flags = ERROR_ON_UNKNOWN | SELF_RECURSE;
    bone_parser.parser = parse_bone;

    XMLNodeParser rotation_parser = {0};
    rotation_parser.node_name = "rotation";
    rotation_parser.flags = ERROR_ON_UNKNOWN;

    XMLNodeParser x_axis = {0};
    x_axis.node_name = "X";
    x_axis.flags = ERROR_ON_UNKNOWN;
    x_axis.parser = parse_rotation_axis;

    XMLNodeParser y_axis = {0};
    y_axis.node_name = "Y";
    y_axis.flags = ERROR_ON_UNKNOWN;
    y_axis.parser = parse_rotation_axis;

    XMLNodeParser z_axis = {0};
    z_axis.node_name = "Z";
    z_axis.flags = ERROR_ON_UNKNOWN;
    z_axis.parser = parse_rotation_axis;

    XNP_AddChild(&rotation_parser, &x_axis);
    XNP_AddChild(&rotation_parser, &y_axis);
    XNP_AddChild(&rotation_parser, &z_axis);

    // ============ SETUP FINISHED =============

    LIBXML_TEST_VERSION;

    xmlDoc * doc = NULL;
    if ((doc = xmlReadFile(definition_file, NULL, 0)) == NULL) {
        printf("Error parsing file\n");
        return INIT_XML_ERROR;
    }

    *proto = XNP_TryParseNode(xmlDocGetRootElement(doc), &bone_parser, NULL);

    int n_bones;

    ResolveIDs(*proto, &n_bones);

    xmlFreeDoc(doc);
    xmlCleanupGlobals();

    return n_bones * sizeof (TrackerBone);
}

void * parse_bone(xmlNode * node, void * state) {
    BonePrototype * parent_bone = (BonePrototype*) state;

    BonePrototype * current = (BonePrototype*) malloc(sizeof (BonePrototype));

    memset(current, 0, sizeof(BonePrototype));
    
    if (parent_bone) {
        // insert current into parent_bone
        if (parent_bone->children == NULL) {
            parent_bone->children = current;
        } else {
            BonePrototype * child = parent_bone->children;
            while (child->next) {
                child = child->next;
            }
            child->next = current;
        }
    }

    current->parent = parent_bone;

    xmlAttr * cprop = node->properties;

    while (cprop) {

        xmlChar * value = xmlNodeListGetString(cprop->doc, cprop->children, 1);

        if (strcmp(cprop->name, "name") == 0) {

            int length = xmlStrlen(value) + 1;
            char * name = (char*) malloc(length);
            memcpy(name, value, length);

            current->name = name;
        }

        if (strcmp(cprop->name, "length") == 0 && parse_double(value, &current->length)) {
            DEBUG_PRINT("Error parsing bone length for bone %s", current->name);
        }

        xmlFree(value);

        cprop = cprop->next;
    }

    DEBUG_PRINT("Parsed Bone: {name:%s, length:%f}\n", current->name, current->length);
    
    return current;
}

void * parse_rotation_axis(xmlNode * node, void * state) {

    BonePrototype * parent_bone = (BonePrototype*) state;

    int axis = 0;

    switch (node->name[0]) {
        case 'X':
            axis = 0;
            break;
        case 'Y':
            axis = 1;
            break;
        case 'Z':
            axis = 2;
            break;
    }

    RotLimit * rotation = &parent_bone->rotation[axis];

    xmlAttr * cprop = node->properties;

    while (cprop != NULL) {

        xmlChar * value = xmlNodeListGetString(cprop->doc, cprop->children, 1);

        if (strcmp(cprop->name, "min") == 0 && parse_double(value, &rotation->min)) {
            DEBUG_PRINT("Error parsing minimum value for %s", node->name);
        }

        if (strcmp(cprop->name, "max") == 0 && parse_double(value, &rotation->max)) {
            DEBUG_PRINT("Error parsing maximum value for %s", node->name);
        }

        if (strcmp(cprop->name, "allowed") == 0) {
            rotation->allowed = strcmp("1", value) || stricmp("yes", value) || stricmp("true", value);
        }

        if (strcmp(cprop->name, "direction") == 0) {
            rotation->around_outer = stricmp("outer", value);
#ifdef DEBUG
            if (!stricmp(value, "inner")) {
                DEBUG_PRINT("Error parsing direction");
            }
#endif
        }

        xmlFree(value);

        cprop = cprop->next;
    }

    return NULL;
}

void ResolveIDs(BonePrototype * root, int * bone_count) {

    BonePrototype * current = root;

    int i = 0;

    if (!bone_count) {
        bone_count = &i;
    }

    *bone_count = 0;

    while (current) {

        current->id = (*bone_count)++;

        if (current->children) {
            current = current->children;
        } else {
            while (current) {
                if(!current->next) {
                    break;
                }
                current = current->parent;
            }
            if (current)
                current = current->next;
        }
    }
}

int fill_bone_buffer(BonePrototype * root, void * buffer, int buffer_size) {

    BonePrototype * current = root;

    memset(buffer, 0, buffer_size);
    
    int buffer_index = 0;

    while (current) {

        if(buffer_index + sizeof(TrackerBone) > buffer_size) {
            return INIT_OUT_OF_SPACE;
        }
        
        TrackerBone * bone = buffer + buffer_index;

        buffer_index += sizeof(TrackerBone);
        
        bone->id = current->id;
        
        if (current->children) {
            current = current->children;
        } else {
            while (current) {
                if(!current->next) {
                    break;
                }
                current = current->parent;
            }
            if (current)
                current = current->next;
        }
    }
    
    return 0;
}
