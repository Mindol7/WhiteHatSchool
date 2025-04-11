#include <stdio.h>
#include "json_c.c"

int main() {
    const char *str = "{\"data\":[{\"color\": \"red\", \"value\": \"#f00\"}, {\"color\": \"green\", \"value\": \"#0f0\"}, {\"color\": \"blue\", \"value\": \"#00f\"}, {\"color\": \"cyan\", \"value\": \"#0ff\"}, {\"color\": \"magenta\", \"value\": \"#f0f\"}, {\"color\": \"yellow\", \"value\": \"#ff0\"}, {\"color\": \"black\", \"value\": \"#000\"}]}";

    json_value json = json_create(str);

    json_value obj = json_get(json, "data");
}
/*
* 요구사항 2:
 - json 몇개? - 파싱할 오브젝트 갯수와 일치하는가? (함수화)

 * 요구사항 3:
  - 전체 출력 또는 특정 번호 오브젝트 출력 (함수화)

  * 요구사항 4:
   - object 한개 추가해서 총 8개 json을 파일에 저장 (함수화)
*/