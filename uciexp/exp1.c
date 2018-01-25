#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uci.h>

#define UCI_CONFIG_FILE "wireless"
static struct uci_context * ctx = NULL; //定义一个UCI上下文的静态变量.

/**
 *	载入配置文件,并遍历Section.
 */
bool load_config()
{
	struct uci_package * pkg = NULL;
	struct uci_element *e;
	char *tmp;
	const char *value;

	ctx = uci_alloc_context(); // 申请一个UCI上下文.
	uci_set_confdir(ctx, "/tmp/config");

	if (UCI_OK != uci_load(ctx, UCI_CONFIG_FILE, &pkg)) {
		printf("打开UCI文件失败, 跳到末尾清理UCI上下文\n");
		goto cleanup;
	}

	/*遍历UCI的每一个节*/
	uci_foreach_element(&pkg->sections, e) {
		struct uci_section *s = uci_to_section(e);

		if(!strcmp("wifi-iface",s->type)) {
			printf("this seciton is %s.\n", s->type);
			if (NULL != (value = uci_lookup_option_string(ctx, s, "ssid"))) {
				tmp = strdup(value); //如果您想持有该变量值，一定要拷贝一份。当 pkg销毁后value的内存会被释放。
				printf("%s.%s=%s.\n",s->e.name, "ssid", value);
				free(tmp);
			}
			if (NULL != (value = uci_lookup_option_string(ctx, s, "device"))) {
				tmp = strdup(value);
				printf("%s.%s=%s.\n",s->e.name, "device", value);
				free(tmp);
			}
		}
		// 如果您不确定是 string类型 可以先使用 uci_lookup_option() 函数得到Option 然后再判断.
		// Option 的类型有 UCI_TYPE_STRING 和 UCI_TYPE_LIST 两种.
	}
	uci_unload(ctx, pkg); // 释放 pkg
cleanup:
	uci_free_context(ctx);
	ctx = NULL;
}
int main(int argc, char* argv[])
{
	load_config();
}
