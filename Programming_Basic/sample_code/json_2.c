#include <stdio.h>
#include "json_c.c"


int main(void)
{   
    const char *str = "{\"id\": \"0001\",\"type\": \"donut\",\"name\": \"Cake\",\"ppu\": 0.55,\"batters\": {\"batter\": [{\"id\": \"1001\", \"type\": \"Regular\"},{\"id\": \"1002\", \"type\": \"Chocolate\"},{\"id\": \"1003\", \"type\": \"Blueberry\"},{\"id\": \"1004\", \"type\": \"Devil's Food\"}]}, \"topping\": [{\"id\": \"5001\", \"type\": \"None\"},{\"id\": \"5002\", \"type\": \"Glazed\"},{\"id\": \"5005\", \"type\": \"Sugar\"},{\"id\": \"5007\", \"type\": \"Powdered Sugar\"},{\"id\": \"5006\", \"type\": \"Chocolate with Sprinkles\"},{\"id\": \"5003\", \"type\": \"Chocolate\"},{\"id\": \"5004\", \"type\": \"Maple\"}]}";
	//Creation and assignment of a json_value
	//Dynamic allocation used
	json_value json = json_create(str);

	/* Batters 4개 출력해보기 */

	// json_print(json);

	// json_get_string();
	json_value obj = json_get(json, "batters");
	int obj_size = json_len(obj);
	json_value obj2 = json_get(obj, "batter");
	int obj2_size = json_len(obj2);
	// printf("%d\n", obj_size);

	for(int i = 0; i<obj2_size; i++) {
		json_value ob = json_get(obj2, i);
		json_value ob2 = json_get(obj2, i);
		char *id = json_get_string(ob, "id"); // batter를 가져옴.
		char *type = json_get_string(ob2, "type");
		printf("%s\n", id);
		printf("%s\n", type);
		
	}


	return 0;
}

