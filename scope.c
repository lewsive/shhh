#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "scope.h"
#include "utilities.h"

//allocates a new scope symbol table and returns a pointer to it.
scope_t* scope_create(){
    scope_t* new_s = malloc(sizeof(scope_t));
    if(new_s == NULL){
        bail_with_error("No space for new scope_t!");
    }
    new_s->size = 0;
    new_s->loc_count = 0;
    for(int i = 0; i < MAX_SCOPE_SIZE; i++){
        new_s->entries[i] = NULL;
    }
}

//returns number of variable and constant declarations that are in this scope
extern unsigned int scope_loc_count(scope_t* s){
    return s->loc_count;
}

// Return the current scope's size (number of declared ids).
unsigned int scope_size(scope_t *s){
    return s->size;
}

// Is the current scope full?
bool scope_full(scope_t *s){
    return scope_size(s) >= MAX_SCOPE_SIZE;
}

//adds a association to the scope
static void scope_add(scope_t *s, scope_assoc_t *assoc){
    assoc->attrs->offset_count = (s->loc_count)++;
    s->entries[(s->size)++] = assoc;
}

//crates a new association and adds it the scope
void scope_insert(scope_t* s, const char* name, id_attrs* attrs) {
    scope_assoc_t *new_assoc = malloc(sizeof(scope_assoc_t));
    if (new_assoc == NULL) {
	bail_with_error("No space for association!");
    }
    new_assoc->id = name;
    new_assoc->attrs = attrs;
    scope_add(s, new_assoc);
}

//checks to see if the name has already been declared in the current scope
bool scope_declared(scope_t *s, const char *name)
{
    return scope_lookup(s, name) != NULL;
}

//returns a pointer to the attributes if the name exists in the scope otherwise returns null
id_attrs *scope_lookup(scope_t *s, const char *name){
    for(int i = 0; i < s->size; i++){
        if(strcmp(name,s->entries[i]->id) == 0){
            return s->entries[i]->attrs;
        }
    }
    return NULL;
}