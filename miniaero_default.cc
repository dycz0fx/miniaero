#include "miniaero_mapper.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstring>
#include <map>
#include <vector>

#include "mappers/default_mapper.h"

using namespace Legion;
using namespace Legion::Mapping;

///
/// Mapper
///

#define SPMD_SHARD_USE_IO_PROC 1

LegionRuntime::Logger::Category log_mapper("mapper");

class MiniAeroMapper : public DefaultMapper
{
public:
  MiniAeroMapper(MapperRuntime *rt, Machine machine, Processor local,
                 const char *mapper_name);

  virtual void default_policy_select_target_processors(
                                    MapperContext ctx,
                                    const Task &task,
                                    std::vector<Processor> &target_procs);
  virtual LogicalRegion default_policy_select_instance_region(
                                    MapperContext ctx, Memory target_memory,
                                    const RegionRequirement &req,
                                    const LayoutConstraintSet &constraints,
                                    bool force_new_instances,
                                    bool meets_constraints);
 // added!!
  virtual void map_task(const MapperContext      ctx,
                        const Task&              task,
                        const MapTaskInput&      input,
                              MapTaskOutput&     output);
private: // added
  std::map<Processor::Kind, std::string> prockind_to_name;
  std::map<Memory::Kind, std::string> memorykind_to_name;
};

MiniAeroMapper::MiniAeroMapper(MapperRuntime *rt, Machine machine, Processor local,
                               const char *mapper_name)
  : DefaultMapper(rt, machine, local, mapper_name)
{
  // added for printing
  // Names of proc_kinds
  prockind_to_name[Processor::NO_KIND] = "NO KIND";
  prockind_to_name[Processor::UTIL_PROC] = "UTIL PROC";// (Utility core)";
  prockind_to_name[Processor::TOC_PROC] = "GPU PROC";// (GPU/Throughput optimized code)";
  prockind_to_name[Processor::OMP_PROC] = "OMP PROC";// (OpenMP (or similar) thread pool)";
  prockind_to_name[Processor::PROC_SET] = "PROC SET";// (Set of processors for OpenMP/Kokkos)";
  prockind_to_name[Processor::PROC_GROUP] = "Processor group";
  prockind_to_name[Processor::LOC_PROC] = "CPU PROC";// (CPU/Latency optimized core)";
  prockind_to_name[Processor::IO_PROC] = "IO PROC";// (I/O core)";
  prockind_to_name[Processor::PY_PROC] = "PY PROC";// (Python interpreter)";

  // Names of memories
  memorykind_to_name[Memory::GPU_FB_MEM] = "GPU Frame-Buffer";// Memory (for 1 GPU & all its SMs)";
  memorykind_to_name[Memory::DISK_MEM] = "Disk memory";// visible to all processors on a node";
  memorykind_to_name[Memory::HDF_MEM] = "HDF memory";// visible to all processors on a node";
  memorykind_to_name[Memory::FILE_MEM] = "File memory";// visible to all processors on a node";
  memorykind_to_name[Memory::LEVEL3_CACHE] = "CPU L3";// Visible to all processors on the node, better performance to processors on same socket";
  memorykind_to_name[Memory::LEVEL2_CACHE] = "CPU L2";// Visible to all processors on the node, better performance to one processor";
  memorykind_to_name[Memory::LEVEL1_CACHE] = "CPU L1";// Visible to all processors on the node, better performance to one processor";
  memorykind_to_name[Memory::Z_COPY_MEM] = "Zero Copy";// Memory (visible to all CPUs within a node and one or more GPUs)";
  memorykind_to_name[Memory::GLOBAL_MEM] = "Global Memory";// (Guaranteed visible to all processors on all nodes (e.g. GASNet memory, universally slow))";
  memorykind_to_name[Memory::SYSTEM_MEM] = "System Memory";// (Visible to all processors on a node)";
  memorykind_to_name[Memory::REGDMA_MEM] = "RDMA Memory";// (Visible to all processors on a node, can be a target of RDMA)";
  memorykind_to_name[Memory::SOCKET_MEM] = "Socket Memory";// (visible to all processors within a node, better performance to processors on same socket)";

}

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

static void create_mappers(Machine machine, HighLevelRuntime *runtime,
                           const std::set<Processor> &local_procs)
{
  MiniAeroMapper* mapper = new MiniAeroMapper(runtime->get_mapper_runtime(),
                                              machine, *local_procs.begin(),
                                              "miniaero_mapper");
  runtime->replace_default_mapper(mapper, Processor::NO_PROC);

/*
  for (std::set<Processor>::const_iterator it = local_procs.begin();
        it != local_procs.end(); it++)
  {
    MiniAeroMapper* mapper = new MiniAeroMapper(runtime->get_mapper_runtime(),
                                                machine, *it, "miniaero_mapper");
    runtime->replace_default_mapper(mapper, *it);
  }*/
}


// added to print
void MiniAeroMapper::map_task(const MapperContext      ctx,
                              const Task&              task,
                              const MapTaskInput&      input,
                                    MapTaskOutput&     output) {
  DefaultMapper::map_task(ctx, task, input, output);
}

void register_mappers()
{
  HighLevelRuntime::add_registration_callback(create_mappers);
}

