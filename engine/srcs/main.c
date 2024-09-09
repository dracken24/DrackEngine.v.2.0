/*******************************************************************************/
/*\|/-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-\|/*/
/* |            ------------------------------------------------             | */
/* |            *--*  PROJET: DrackLauncher PAR: Dracken24  *--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  DATE:	  	    06-09-2024  	     	*--*             | */
/* |            ------------------------------------------------             | */
/* |            *--*  FILE: 	 	 Main.c       		    *--*             | */
/* |            ------------------------------------------------             | */
/*/|\-~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~---~-/|\*/
/*******************************************************************************/

# include "../includes/engine.h"
# include "../../library/drackengine_lib/drackengine_lib.h"
# include "../../library/drackengine_lib/utility/colors.h"
# include "../includes/temp_for_build.h"
# include "memory/dmemory.h"

int main(void)
{
    Engine   engine;

    initialize_memory();
    dr_init(&engine);
    DE_TRACE(get_memory_usage_str());

    // test_log();

    while (!WindowShouldClose() && !engine.exitCt)
	{
        dr_update(&engine);
	}

    dr_exit(&engine);
    shutdown_memory();
    DE_TRACE(get_memory_usage_str());

    return (0);
}
