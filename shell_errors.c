
#include "pipex.h"

void	pipex_cleanup(void *env)
{
	t_env *e;

	e = (t_env *)env;
	if (e)
	{
		arena_free(e->data);
		free(e->node);
	}
	handle_exit(e->exit_data);
}
