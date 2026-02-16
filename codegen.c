#include "codegen.h"
#include "error.h"
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define INITIAL_CAPACITY 4096

CodeGen codegen_create(void) {
    CodeGen gen = {0};
    gen.capacity = INITIAL_CAPACITY;
    gen.length = 0;
    gen.indent_level = 0;
    gen.output = malloc(gen.capacity);
    if (!gen.output) error(error_messages[ERROR_MALLOCFAIL].message);
    gen.output[0] = '\0';
    return gen;
}

void codegen_free(CodeGen* gen) {
    free(gen->output);
    gen->output = NULL;
    gen->capacity = 0;
    gen->length = 0;
}

char* codegen_get_output(CodeGen* gen) {
    return gen->output;
}

// Helper to append string
static void append(CodeGen* gen, const char* str) {
    int len = strlen(str);
    
    while (gen->length + len + 1 >= gen->capacity) {
        gen->capacity *= 2;
        char* new_output = realloc(gen->output, gen->capacity);
        if (!new_output) error(error_messages[ERROR_REALLOCFAIL].message);
        gen->output = new_output;
    }
    
    strcpy(gen->output + gen->length, str);
    gen->length += len;
}

// Helper to append formatted string
static void appendf(CodeGen* gen, const char* fmt, ...) {
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    append(gen, buffer);
}

// Helper for indentation
static void append_indent(CodeGen* gen) {
    for (int i = 0; i < gen->indent_level; i++) {
        append(gen, "    ");
    }
}

// Convert FieldType to C type string
static const char* field_type_to_c(FieldType type) {
    switch (type) {
        case TYPE_FLOAT: return "float";
        case TYPE_INT: return "int";
        case TYPE_BOOL: return "bool";
        case TYPE_UINT32: return "uint32_t";
    }
    return "int";
}

// Generate entity struct
static void generate_entity_struct(CodeGen* gen, EntityDecl* entity) {
    appendf(gen, "typedef struct %s {\n", entity->name.lexeme);
    gen->indent_level++;
    
    append_indent(gen);
    append(gen, "uint32_t entity_id;\n");
    
    for (int i = 0; i < entity->field_count; i++) {
        append_indent(gen);
        appendf(gen, "%s %s;\n", 
                field_type_to_c(entity->fields[i].type),
                entity->fields[i].name.lexeme);
    }
    
    gen->indent_level--;
    appendf(gen, "} %s;\n\n", entity->name.lexeme);
}

// Generate entity array
static void generate_entity_array(CodeGen* gen, EntityDecl* entity) {
    appendf(gen, "typedef struct %sArray {\n", entity->name.lexeme);
    gen->indent_level++;
    
    append_indent(gen);
    appendf(gen, "%s* data;\n", entity->name.lexeme);
    append_indent(gen);
    append(gen, "int count;\n");
    append_indent(gen);
    append(gen, "int capacity;\n");
    
    gen->indent_level--;
    appendf(gen, "} %sArray;\n\n", entity->name.lexeme);
}

// Generate GameState
static void generate_game_state(CodeGen* gen, Program* program) {
    append(gen, "typedef struct GameState {\n");
    gen->indent_level++;
    
    // Engine components
    append_indent(gen);
    append(gen, "// Engine components\n");
    append_indent(gen);
    append(gen, "EntityRegistry registry;\n");
    append_indent(gen);
    append(gen, "TransformArray transforms;\n");
    append_indent(gen);
    append(gen, "RenderableArray renderables;\n");
    append_indent(gen);
    append(gen, "CircleArray circles;\n");
    append_indent(gen);
    append(gen, "RectangleArray rectangles;\n");
    append_indent(gen);
    append(gen, "TimerArray timers;\n");
    append(gen, "\n");
    
    // Entity arrays
    append_indent(gen);
    append(gen, "// Game entity arrays\n");
    for (int i = 0; i < program->entity_count; i++) {
        append_indent(gen);
        appendf(gen, "%sArray %ss;\n", 
                program->entities[i]->name.lexeme,
                program->entities[i]->name.lexeme);  // lowercase would be better
    }
    
    gen->indent_level--;
    append(gen, "} GameState;\n\n");
}

void codegen_generate_program(CodeGen* gen, Program* program) {
    // Header includes
    append(gen, "#include <stdint.h>\n");
    append(gen, "#include <stdbool.h>\n");
    append(gen, "#include <stdlib.h>\n");
    append(gen, "#include \"entity.h\"\n");
    append(gen, "#include \"transform.h\"\n");
    append(gen, "#include \"renderable.h\"\n");
    append(gen, "#include \"collision.h\"\n");
    append(gen, "#include \"timer.h\"\n\n");
    
    // Generate entity structs
    for (int i = 0; i < program->entity_count; i++) {
        generate_entity_struct(gen, program->entities[i]);
        generate_entity_array(gen, program->entities[i]);
    }
    
    // Generate GameState
    generate_game_state(gen, program);
    
    append(gen, "// Entity lifecycle functions will go here\n");
}
