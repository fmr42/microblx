/*
 * rml_vel microblx function block (autogenerated, don't edit)
 */

#include "ubx.h"

/* includes types and type metadata */

ubx_type_t types[] = {
	{ NULL },
};

/* block meta information */
char rml_vel_meta[] =
	" { doc='',"
	"   license='',"
	"   real-time=true,"
	"}";

/* declaration of block configuration */
ubx_config_t rml_vel_config[] = {
	{ .name="max_vel", .type_name = "double", .doc="maximum velocity" },
	{ .name="max_acc", .type_name = "double", .doc="maximum acceleration" },
	{ .name="cycle_time", .type_name = "double", .doc="cycle time [s]" },
	{ NULL },
};

/* declaration port block ports */
ubx_port_t rml_vel_ports[] = {
	{ .name="msr_pos", .in_type_name="double", .in_data_len=5, .doc="current measured position"  },
	{ .name="msr_vel", .in_type_name="double", .in_data_len=5, .doc="current measured velocity"  },
	{ .name="des_pos", .in_type_name="double", .in_data_len=5, .doc="desired target position"  },
	{ .name="des_vel", .in_type_name="double", .in_data_len=5, .doc="desired target velocity"  },
	{ .name="cmd_pos", .out_type_name="double", .out_data_len=5, .doc="new position (controller input)"  },
	{ .name="cmd_vel", .out_type_name="double", .out_data_len=5, .doc="new velocity (controller input)"  },
	{ .name="cmd_acc", .out_type_name="double", .out_data_len=5, .doc="new acceleration (controller input)"  },
	{ .name="reached", .out_type_name="int", .out_data_len=1, .doc="the final state has been reached"  },
	{ NULL },
};

/* declare a struct port_cache */
struct rml_vel_port_cache {
	ubx_port_t* msr_pos;
	ubx_port_t* msr_vel;
	ubx_port_t* des_pos;
	ubx_port_t* des_vel;
	ubx_port_t* cmd_pos;
	ubx_port_t* cmd_vel;
	ubx_port_t* cmd_acc;
	ubx_port_t* reached;
};

/* declare a helper function to update the port cache this is necessary
 * because the port ptrs can change if ports are dynamically added or
 * removed. This function should hence be called after all
 * initialization is done, i.e. typically in 'start'
 */
static void update_port_cache(ubx_block_t *b, struct rml_vel_port_cache *pc)
{
	pc->msr_pos = ubx_port_get(b, "msr_pos");
	pc->msr_vel = ubx_port_get(b, "msr_vel");
	pc->des_pos = ubx_port_get(b, "des_pos");
	pc->des_vel = ubx_port_get(b, "des_vel");
	pc->cmd_pos = ubx_port_get(b, "cmd_pos");
	pc->cmd_vel = ubx_port_get(b, "cmd_vel");
	pc->cmd_acc = ubx_port_get(b, "cmd_acc");
	pc->reached = ubx_port_get(b, "reached");
}


/* for each port type, declare convenience functions to read/write from ports */
def_read_arr_fun(read_msr_pos_5, double, 5)
def_read_arr_fun(read_msr_vel_5, double, 5)
def_read_arr_fun(read_des_pos_5, double, 5)
def_read_arr_fun(read_des_vel_5, double, 5)
def_write_arr_fun(write_cmd_pos_5, double, 5)
def_write_arr_fun(write_cmd_vel_5, double, 5)
def_write_arr_fun(write_cmd_acc_5, double, 5)
def_write_fun(write_reached, int)

/* block operation forward declarations */
int rml_vel_init(ubx_block_t *b);
int rml_vel_start(ubx_block_t *b);
void rml_vel_stop(ubx_block_t *b);
void rml_vel_cleanup(ubx_block_t *b);
void rml_vel_step(ubx_block_t *b);


/* put everything together */
ubx_block_t rml_vel_block = {
	.name = "rml_vel",
	.type = BLOCK_TYPE_COMPUTATION,
	.meta_data = rml_vel_meta,
	.configs = rml_vel_config,
	.ports = rml_vel_ports,

	/* ops */
	.init = rml_vel_init,
	.start = rml_vel_start,
	.stop = rml_vel_stop,
	.cleanup = rml_vel_cleanup,
	.step = rml_vel_step,
};


/* rml_vel module init and cleanup functions */
int rml_vel_mod_init(ubx_node_info_t* ni)
{
	DBG(" ");
	int ret = -1;
	ubx_type_t *tptr;

	for(tptr=types; tptr->name!=NULL; tptr++) {
		if(ubx_type_register(ni, tptr) != 0) {
			goto out;
		}
	}

	if(ubx_block_register(ni, &rml_vel_block) != 0)
		goto out;

	ret=0;
out:
	return ret;
}

void rml_vel_mod_cleanup(ubx_node_info_t *ni)
{
	DBG(" ");
	const ubx_type_t *tptr;

	for(tptr=types; tptr->name!=NULL; tptr++)
		ubx_type_unregister(ni, tptr->name);

	ubx_block_unregister(ni, "rml_vel");
}

/* declare module init and cleanup functions, so that the ubx core can
 * find these when the module is loaded/unloaded */
UBX_MODULE_INIT(rml_vel_mod_init)
UBX_MODULE_CLEANUP(rml_vel_mod_cleanup)