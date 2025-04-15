/**
 * Author: 조민혁
 * Date: 2025/04/11
 * GitHub Link: https://github.com/Mindol7/WhiteHatSchool/tree/main/Programming_Basic/src
 */

#include <stdio.h>
#include <sys/stat.h>
#include "json_c.c"

/* TODO
<기본>: 90점
- 함수 개수 추출하기
- 함수들의 리턴타입 추출하기
- 함수들의 파라미터 타입,변수명 추출하기
- 함수들의 if조건 개수 추출하기

<심화>: 10점(가산점)
- 원본 소스코드 복원해보기 (최소 함수3개 이상)
- ast.json -> ast.c
*/

void count_func_num(json_value node);
void print_func_return_type(json_value node);
void print_func_arg_var(json_value node);
int count_func_if_num(json_value node);

/* Count Function: Counting Function Number */
void count_func_num(json_value node) {
    int func_count = 1; // Default Function is main
    int if_count = 0;
    int ext_len = json_len(node);
    printf("============AST SYNTAX ANALYZE============\n");
    printf("Function (defined): main\n");
    for (int i = 0; i < ext_len; i++) {
        json_value obj = json_get(node, i);
        char *obj_nodetype = json_get_string(obj, "_nodetype");
        if (obj_nodetype && strcmp(obj_nodetype, "FuncDef") == 0) {
            json_value decl = json_get(obj, "decl");
            char *func_name = json_get_string(decl, "name");
            json_value type = json_get(decl, "type");
            char *type_nodetype = json_get_string(type, "_nodetype");
            if (type_nodetype && strcmp(type_nodetype, "FuncDecl") == 0) {
                printf("Function (defined): %s\n", func_name);
                func_count++;
                print_func_return_type(type);
                printf("\n");
            }   
        }
        else if (obj_nodetype && strcmp(obj_nodetype, "Decl") == 0) {
            json_value type = json_get(obj, "type");
            char *type_nodetype = json_get_string(type, "_nodetype");

            if (type_nodetype && strcmp(type_nodetype, "FuncDecl") == 0) {
                char *func_name = json_get_string(obj, "name");
                printf("Function (declared): %s\n", func_name); 
                func_count++;
                print_func_return_type(type);
                printf("\n");
            }
        }
    }
    
    if_count += count_func_if_num(node);
    printf("Total 'If' Count in ast.json: %d\n", if_count);
    printf("Total Function Count in ast.json: %d\n", func_count);
    printf("================================================\n");
}

/* Print Function: Return Type */
void print_func_return_type(json_value node) {
    json_value type_type = json_get(node, "type");

    char *nodetype_ptr = json_get_string(type_type, "_nodetype");
    
    if ((nodetype_ptr && strcmp(nodetype_ptr, "PtrDecl") == 0)) {    
        json_value type_type_type = json_get(type_type, "type");
        json_value type_type_type_type = json_get(type_type_type, "type");
        json_value return_names = json_get(type_type_type_type, "names");
        json_value return_type = json_get(return_names, 0);
        char *return_ = json_get_string(return_type);
        printf("Return Type: %s*\n", return_);
    }
    else {
        json_value type_type_type = json_get(type_type, "type");
        json_value return_names = json_get(type_type_type, "names");
        json_value return_type = json_get(return_names, 0);
        char *return_ = json_get_string(return_type);
        printf("Return Type: %s\n", return_);
    }

    print_func_arg_var(node);
}

/* Print Function: Argument Type and Variable Name */
void print_func_arg_var(json_value node) {
    int count = 1;
    json_value args = json_get(node, "args");

    if(json_is_null(args)) {
        json_value type_type = json_get(node, "type");
        json_value type_type_type = json_get(type_type, "type");
        json_value names_obj = json_get(type_type_type, "names");
        size_t names_len = json_len(names_obj);
        for(int i = 0; i < names_len; i++) {
            json_value names_arr = json_get(names_obj, i);
            char *input_name = json_get_string(names_arr);
            printf("Variable Name: Unknown\n");
            printf("%d's Parameter Type: %s*\n", i+1, input_name);
        }
    }
    else{
        json_value params = json_get(args, "params");
        size_t params_len = json_len(params);
        for(int i = 0; i < params_len; i++) {    
            json_value params_obj = json_get(params, i);
            json_value params_name = json_get(params_obj, "name");
            json_value params_nodetype = json_get(params_obj, "_nodetype");
            char *nodetype_str = json_get_string(params_nodetype);
            char *type_name = json_get_string(params_name);
            
            if(nodetype_str != NULL && strcmp(nodetype_str, "PtrDecl") == 0) {
                if(type_name != NULL) printf("Variable Name: %s\n", type_name);
                else printf("Variable Name: Unknown\n");
                json_value type_type = json_get(params_obj, "type");
                json_value type_type_type = json_get(type_type, "type");
                json_value type_type_type_type = json_get(type_type_type, "type");
                json_value name_obj = json_get(type_type_type_type, "names");
                size_t names_len = json_len(name_obj);
                
                for(int j = 0; j<names_len; j++) {
                    json_value names_arr = json_get(name_obj, j);
                    char *input_name = json_get_string(names_arr);
                    printf("%d's Parameter Type: %s*\n", count++, input_name);
                }
            }
            else {
                if(type_name != NULL) printf("Variable Name: %s\n", type_name);
                else printf("Variable Name: Unknown\n");
                json_value type_type = json_get(params_obj, "type");
                json_value type_nodetype = json_get(type_type, "_nodetype");
                char *nodetype_str = json_get_string(type_nodetype);

                if(nodetype_str != NULL && strcmp(nodetype_str, "PtrDecl") == 0){
                    json_value type_type_type = json_get(type_type, "type");
                    json_value type_type_type_type = json_get(type_type_type, "type");
                    json_value name_obj = json_get(type_type_type_type, "names");
                    size_t names_len = json_len(name_obj);
                    
                    for(int j = 0; j<names_len; j++) {
                        json_value names_arr = json_get(name_obj, j);
                        char *input_name = json_get_string(names_arr);
                        printf("%d's Parameter Type: %s*\n", count++, input_name);
                    }
                }
                else{
                    json_value type_type = json_get(params_obj, "type");
                    json_value type_type_type = json_get(type_type, "type");
                    json_value name_obj = json_get(type_type_type, "names");
                    size_t names_len = json_len(name_obj);
                    
                    for(int j = 0; j<names_len; j++) {
                        json_value names_arr = json_get(name_obj, j);
                        char *input_name = json_get_string(names_arr);
                        printf("%d's Parameter Type: %s\n", count++, input_name);
                    }
                }   
            }
        }
    }
}

/* Counting Function: Counting 'If' Condition Numbers */
int count_func_if_num(json_value node) {
    int if_count = 0;
    
    if(json_get_type(node) == JSON_OBJECT) {
        json_value nodetype = json_get(node, "_nodetype");
        char *nodetype_str = json_get_string(nodetype);

        if(nodetype_str && strcmp(nodetype_str, "If") == 0) if_count++;

        int len = json_len(node);

        for(int i = 0; i<len; i++) {
            json_value child = json_get(node, i);
            if_count += count_func_if_num(child);
        }
    }
    else if(json_get_type(node) == JSON_ARRAY) {
        int len = json_len(node);
        for(int i = 0; i<len; i++) {
            json_value child = json_get(node, i);
            if_count += count_func_if_num(child);
        }
    }

    return if_count;
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Usage: %s <FILE_PATH> \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *path = argv[1];

    FILE *file = fopen(path, "r");
    if(file == NULL) {
        perror("Failed to open File!");
        return -1;
    }
    
    struct stat st;
    stat(path, &st);
    size_t filesize = st.st_size;

    char *buffer = (char *)malloc(filesize + 1);
    if(!buffer) {
        fprintf(stderr, "json_read error: malloc failed\n");
        fclose(file);
        return -1;
    }

    size_t read_size = fread(buffer, 1, filesize, file);
    buffer[read_size] = '\0';
    fclose(file);

    json_value json = json_create(buffer);

    if(json_is_null(json) || json_get_type(json) == JSON_UNDEFINED) {
        fprintf(stderr, "Failed to load JSON\n");
        return 1;
    }

    json_print(json);
    json_value ext = json_get(json, "ext");
    count_func_num(ext);

    return 0;
}