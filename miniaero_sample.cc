#include "miniaero_mapper.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>

#include "sample_mapper.h"

using namespace Legion;
using namespace Legion::Mapping;

///
/// Mapper
///

#define SPMD_SHARD_USE_IO_PROC 1

LegionRuntime::Logger::Category log_mapper("mapper");

class MiniAeroMapper : public SampleMapper
{
public:
  MiniAeroMapper(MapperRuntime *rt, Machine machine, Processor local,
                 const char *mapper_name);

/*  virtual void default_policy_select_target_processors(
                                    MapperContext ctx,
                                    const Task &task,
                                    std::vector<Processor> &target_procs);
  virtual LogicalRegion default_policy_select_instance_region(
                                    MapperContext ctx, Memory target_memory,
                                    const RegionRequirement &req,
                                    const LayoutConstraintSet &constraints,
                                    bool force_new_instances,
                                    bool meets_constraints);
*/
};

MiniAeroMapper::MiniAeroMapper(MapperRuntime *rt, Machine machine, Processor local,
                               const char *mapper_name)
  : SampleMapper(rt, machine, local, mapper_name)
{
  //add_task_to_care(...)
//  add_task_to_care("create_face_connectivity");

//  add_task_to_care("create_cell_connectivity_raw");
//  add_task_to_care("cell_total_volume");

  add_task_to_care("update_rk_stage_alpha_and_initialize_solution_fields");

  add_task_to_care("face_gradient");

  add_task_to_care("face_gradient_border");

  //add_task_to_care("print_gradients"); // rem?
  add_task_to_care("compute_min_max");

  add_task_to_care("compute_min_max_border");

  add_task_to_care("compute_limiter");

  add_task_to_care("compute_face_flux");

  add_task_to_care("compute_face_flux_border");

  //add_task_to_care("print_bc_flux"); // rem?
  add_task_to_care("compute_residuals_and_update_rk_stage_beta");

  //add_task_to_care("output_solution"); // rem?
  //add_task_to_care("init_blocks"); // rem?
  //add_task_to_care("initialize"); // rem>

//  add_task_to_care("calculate_area_vector");
//  add_task_to_care("max_index)";
//  add_task_to_care("calculate_tangent_vector");
//  add_task_to_care("Vec3Cross");
//  add_task_to_care("Vec3Average");
  // ALL THE OTHER TERRA FUNCTIONS??

  name_application("miniaero_sample");
}

/*
void MiniAeroMapper::default_policy_select_target_processors(
                                    MapperContext ctx,
                                    const Task &task,
                                    std::vector<Processor> &target_procs)
{
  target_procs.push_back(task.target_proc);
}

LogicalRegion MiniAeroMapper::default_policy_select_instance_region(
                                MapperContext ctx, Memory target_memory,
                                const RegionRequirement &req,
                                const LayoutConstraintSet &layout_constraints,
                                bool force_new_instances,
                                bool meets_constraints)
{
  return req.region;
}
*/

static void create_mappers(Machine machine, HighLevelRuntime *runtime,
                           const std::set<Processor> &local_procs)
{
  MiniAeroMapper* mapper = new MiniAeroMapper(runtime->get_mapper_runtime(),
                                              machine, *local_procs.begin(),
                                              "miniaero_mapper");
  runtime->replace_default_mapper(mapper, Processor::NO_PROC);
/*  for (std::set<Processor>::const_iterator it = local_procs.begin();
        it != local_procs.end(); it++)
  {
    MiniAeroMapper* mapper = new MiniAeroMapper(runtime->get_mapper_runtime(),
                                                machine, *it, "miniaero_mapper");
    runtime->replace_default_mapper(mapper, *it);
  }*/
}

void register_mappers()
{
  HighLevelRuntime::set_registration_callback(create_mappers);
}

