#include "tiny_dnn/network.h"

template<class T>
bool tiny_dnn::network<T>::train_one_batch(tiny_dnn::adamax opt, std::vector<tiny_dnn::vec_t> &inputs, std::vector<tiny_dnn::vec_t> &desired_outputs, unsigned int batch_size)
{
    std::vector<tensor_t> input_tensor, output_tensor, t_cost_tensor;
    normalize_tensor(inputs, input_tensor);
    normalize_tensor(desired_outputs, output_tensor);

    std::vector<tensor_t> t_cost = std::vector<tensor_t>();
    check_target_cost_matrix(output_tensor, t_cost);
    set_netphase(net_phase::train);
    net_.setup(false);
    const int n_threads = CNN_TASK_SIZE;
    for (auto n : net_) n->set_parallelize(true);
    opt.reset();
    stop_training_ = false;
    in_batch_.resize(batch_size);
    t_batch_.resize(batch_size);
    {
      for (size_t i = 0; i < inputs.size() && !stop_training_;
           i += batch_size) {
        train_once<tiny_dnn::mse>(
          opt, &input_tensor[i], &output_tensor[i],
          static_cast<int>(std::min((size_t)batch_size, (size_t)inputs.size() - i)),
          n_threads, get_target_cost_sample_pointer(t_cost, i));


        /* if (i % 100 == 0 && layers_.is_exploded()) {
          std::cout << "[Warning]Detected infinite value in weight. stop
        learning." << std::endl;
            return false;
        } */
      }

    }
    set_netphase(net_phase::test);
    return true;
}

template<class T>
bool tiny_dnn::network<T>::train_one_batch(tiny_dnn::adamax opt, std::vector<tiny_dnn::vec_t> &inputs, std::vector<tiny_dnn::vec_t> &desired_outputs, unsigned int batch_size, unsigned int start )
{
    std::vector<tensor_t> input_tensor, output_tensor, t_cost_tensor;
    normalize_tensor(inputs, input_tensor);
    normalize_tensor(desired_outputs, output_tensor);

    std::vector<tensor_t> t_cost = std::vector<tensor_t>();
    check_target_cost_matrix(output_tensor, t_cost);
    set_netphase(net_phase::train);
    net_.setup(false);
    const int n_threads = CNN_TASK_SIZE;
    for (auto n : net_) n->set_parallelize(true);
    opt.reset();
    stop_training_ = false;
    in_batch_.resize(batch_size);
    t_batch_.resize(batch_size);

    train_once<tiny_dnn::mse>(
      opt, &input_tensor[start], &output_tensor[start],
      static_cast<int>(std::min((size_t)batch_size, (size_t)inputs.size() - start)),
      n_threads, get_target_cost_sample_pointer(t_cost, start));


    set_netphase(net_phase::test);
    return true;
}
