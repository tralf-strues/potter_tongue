#pragma once

#include <stdarg.h>
#include "syntax.h"

union NodeData
{
    double      number;
    MathOp      operation;
    const char* id;
};

enum NodeType
{
    DECL_TYPE,
    VDECL_TYPE,
    NAME_TYPE,
    LIST_TYPE,

    BLCK_TYPE,
    STAT_TYPE,

    COND_TYPE,
    IFEL_TYPE,
    LOOP_TYPE,
    ASSG_TYPE,

    CALL_TYPE,
    JUMP_TYPE,

    MATH_TYPE,
    NUMB_TYPE,

    TYPES_COUNT
};

struct Node
{
    NodeType type;
    NodeData data;

    Node*    parent;
    Node*    left;
    Node*    right;
};

#define BINARY_OP(op, root1, root2) newNode(MATH_TYPE, { .operation = op##_OP }, root1,   root2)
#define NAME(name)                  newNode(NAME_TYPE, { .id        = name    }, nullptr, nullptr)

void   destroySubtree    (Node* root);

Node*  newNode           ();
Node*  newNode           (NodeType type, NodeData data, Node* left, Node* right);
void   deleteNode        (Node* node);

void   setLeft           (Node* root, Node* left);
void   setRight          (Node* root, Node* right);

void   copyNode          (Node* dest, const Node* src);
Node*  copyTree          (const Node* root);

bool   isLeft            (const Node* node);

void   setData           (Node* node, NodeType type, NodeData data);
void   setData           (Node* node, double number);
void   setData           (Node* node, MathOp op);
void   setData           (Node* node, const char* id);

int    counterFileUpdate (const char* filename);
void   graphDump         (Node* root, const char* treeFilename, const char* outputFilename);
void   dumpToFile        (FILE* file, Node* root);
Node*  readTreeFromFile  (const char* filename);