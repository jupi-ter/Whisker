#include "entity_ast.h"
#include "error.h"
#include <stdlib.h>

EntityDecl* entity_decl_create(Token name, EntityField* fields, int field_count,
    Stmt* init, Stmt* on_create, Stmt* on_update, Stmt* on_destroy, Stmt* on_collision, Token collision_param) {
    EntityDecl* entity = malloc(sizeof(EntityDecl));
    if (!entity) error(error_messages[ERROR_MALLOCFAIL].message);

    entity->name = name;
    entity->fields = fields;
    entity->field_count = field_count;
    entity->init = init;
    entity->on_create = on_create;
    entity->on_update = on_update;
    entity->on_destroy = on_destroy;
    entity->on_collision = on_collision;
    entity->collision_param = collision_param;

    return entity;
}

void entity_decl_free(EntityDecl* entity) {
    if (!entity) return;
    free(entity->name.lexeme);
    for (int i = 0; i < entity->field_count; i++) {
        free(entity->fields[i].name.lexeme);
    }
    free(entity->fields);
    stmt_free(entity->init);
    stmt_free(entity->on_create);
    stmt_free(entity->on_update);
    stmt_free(entity->on_destroy);
    stmt_free(entity->on_collision);
    if (entity->collision_param.lexeme) {
        free(entity->collision_param.lexeme);
    }
    free(entity);
}
