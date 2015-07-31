/**
 * ngx_pool_t test, to test ngx_palloc, ngx_palloc_block, ngx_palloc_large
 */

#include <stdio.h>
#include "ngx_config.h"
#include "ngx_conf_file.h"
#include "nginx.h"
#include "ngx_core.h"
#include "ngx_string.h"
#include "ngx_palloc.h"

volatile ngx_cycle_t  *ngx_cycle;

void ngx_log_error_core(ngx_uint_t level, ngx_log_t *log, ngx_err_t err,
            const char *fmt, ...)
{
}

void dump_pool(ngx_pool_t* pool)
{
    while (pool)
    {
        printf("pool = 0x%x\n", pool);
        printf("  .d\n");
        printf("    .last = 0x%x\n", pool->d.last);
        printf("    .end = 0x%x\n", pool->d.end);
        printf("    .next = 0x%x\n", pool->d.next);
        printf("    .failed = %d\n", pool->d.failed);
        printf("  .max = %d\n", pool->max);
        printf("  .current = 0x%x\n", pool->current);
        printf("  .chain = 0x%x\n", pool->chain);
        printf("  .large = 0x%x\n", pool->large);
        printf("  .cleanup = 0x%x\n", pool->cleanup);
        printf("  .log = 0x%x\n", pool->log);
        printf("available pool memory = %d\n\n", pool->d.end - pool->d.last);
        pool = pool->d.next;
    }
}

void fun(void *p)
{
		    printf("call fun\n");
		    printf("call fun %d\n",*(int*)p);
}
int main()
{
    ngx_pool_t *pool;
	ngx_pool_cleanup_t *clt;

    printf("--------------------------------\n");
    printf("create a new pool:\n");
    printf("--------------------------------\n");
    pool = ngx_create_pool(1024, NULL);
    dump_pool(pool);

    printf("--------------------------------\n");
    printf("alloc block 1 from the pool:\n");
    printf("--------------------------------\n");
    ngx_palloc(pool, 938);
    dump_pool(pool);

    printf("--------------------------------\n");
    printf("alloc block 2 from the pool:\n");
    printf("--------------------------------\n");
    ngx_palloc(pool, 944);
    dump_pool(pool);

    printf("--------------------------------\n");
    printf("alloc block 3 from the pool :\n");
    printf("--------------------------------\n");
	ngx_palloc(pool, 51200);
	dump_pool(pool);
	clt=ngx_pool_cleanup_add(pool, sizeof(void *));/*添加释放特殊结构体的函数*/
	clt->handler=&fun;
	*(int*)clt->data=1000;

	ngx_destroy_pool(pool);
	return 0;
}
