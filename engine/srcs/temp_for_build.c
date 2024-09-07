#include "../includes/temp_for_build.h"
#include "../../library/drackengine_lib/utility/colors.h"

void test_log(void)
{
    printf("\n%sLogger test\n\n", T_MAGENTA);
    DE_FATAL("Hello World! %f", 1.0f);
	DE_ERROR("Hello World! %f", 1.0f);
	DE_WARNING("Hello World! %f", 1.0f);
	DE_INFO("Hello World! %f", 1.0f);
	DE_DEBUG("Hello World! %f", 1.0f);
	DE_TRACE("Hello World! %f lol %s", 1.0f, "test\n");
}
