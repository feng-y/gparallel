// solopointer1202@gmail.com
// 220200114
#pragma once
#include <memory>
#include <sstream>
#include "util.h"
namespace galois::gparallel {

typedef int id_t;
class node;
class node_info;
typedef std::shared_ptr<node_info> node_ptr;
typedef std::shared_ptr<const node_info> node_cptr;

// This class holds all the information of a physical node, 
// including node name, node ID, upstream nodes, downstream nodes, 
// input and output metas.
class node_info {
public:
    node_info();
    void initialize(std::string name, 
        batch_function_type batch_fn, query_function_type query_fn, 
        end_function_type end_fn, const io_description & io);
public:
    // setter
    void set_end(end_function_type end_fn);

public:
    // getter
    std::string name() const;
    int item_deps_count() const;
    int query_deps_count() const;
    size_t item_node_out_size() const;
    size_t query_node_out_size() const;
    int node_id() const;
    void describe() const;
    void graphviz(std::stringstream&) const;

//private:
    friend class node;
    friend class node_container;

    bool _has_item_input;
    batch_function_type _batch_fn;
    query_function_type _query_fn;
    end_function_type _end_fn;
    id_t _node_id;
    int _node_user_id;
    int _deps_count;
    std::string _name;

    // All input and output metas
    node_io_vec _input_metas;
    node_io_vec _output_metas;

    // gParallel can infer upstream and downstream nodes 
    // through input and output meta which were staraged here
    std::set<node_ptr> _input_nodes;
    std::set<node_ptr> _output_nodes;
};
}